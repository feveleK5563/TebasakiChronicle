#include "ImageManager.h"

//コンストラクタ(キャラチップを作成する)
ImageManager::ImageManager(const std::string& texName, K_Graphics::Texture* tex, bool isde) :
	textureName(texName),
	spobj(new K_Graphics::SpriteObject(tex)),
	animCnt(0.f),
	nowAnimNum(0),
	isDelete(isde) {}

//デストラクタ
ImageManager::~ImageManager()
{
	delete spobj;

	if (isDelete)
	{
		for (auto it : charaChip)
			delete it;
	}
}

//-----------------------------------------------------------------------------
//テクスチャ名の取得
std::string& ImageManager::GetTextureName()
{
	return textureName;
}
//-----------------------------------------------------------------------------
//指定した番号のキャラチップを取得
AnimationCharaChip* ImageManager::GetNowAnimationCharaChip()
{
	return charaChip[nowAnimNum];
}

//-----------------------------------------------------------------------------
//キャラチップを作成
bool ImageManager::CreateCharaChip(const K_Math::Box2D& src, int sheet, float spd, bool isroop)
{
	if (isDelete)
	{
		charaChip.emplace_back(new AnimationCharaChip(src, sheet, spd, isroop));
		return true;
	}
	return false;
}

//-----------------------------------------------------------------------------
//キャラチップを変更
bool ImageManager::ChangeCharaChip(const std::vector<AnimationCharaChip*>& acc)
{
	if (isDelete)
		return false;

	charaChip = acc;
	animCnt = 0.f;
	nowAnimNum = 0;

	return true;
}

//-----------------------------------------------------------------------------
//アニメーションの変更
void ImageManager::ChangeAnimationPattern(int motionNum, bool timeReset)
{
	if (timeReset &&
		nowAnimNum != motionNum)
		animCnt = 0.f;

	nowAnimNum = motionNum;
}

//-----------------------------------------------------------------------------
//アニメーション
void ImageManager::Animation()
{
	animCnt += 1.f / charaChip[nowAnimNum]->animSpd;

	//ループしない場合は最後の動作で停止
	if (charaChip[nowAnimNum]->isAnimRoop == false &&
		(int)animCnt >= fabs(charaChip[nowAnimNum]->chipSheetNum))
	{
		animCnt = fabsf((float)charaChip[nowAnimNum]->chipSheetNum) - 1.f;
	}
}

//-----------------------------------------------------------------------------
//描画(3D)
void ImageManager::ImageDraw3D(	const K_Math::Vector3&	posc,
								const K_Math::Vector3&	anglec,
								const K_Math::Vector3&	scalec,
								int						direction)
{
	//テクスチャの読み込み位置の調整
	K_Math::Box2D src = charaChip[nowAnimNum]->chip;
	if (charaChip[nowAnimNum]->chipSheetNum >= 0)
	{
		src.x += src.w * (int(animCnt) % charaChip[nowAnimNum]->chipSheetNum);
	}
	else
	{
		src.x -= src.w * (int(animCnt) % charaChip[nowAnimNum]->chipSheetNum);
	}
	spobj->controlPoint = K_Math::Vector2(src.w / 2.f, src.h / 2.f);	//回転の基準位置をテクスチャの中心に設定

	//座標をテクスチャの中心に設定
	K_Math::Vector3 pos = posc;
	pos.x() -= (float)src.w / 2.f;
	pos.y() += (float)src.h / 2.f;

	//画像の向きを調整
	K_Math::Vector3 angle = anglec;
	angle.y() += K_Math::DegToRad((float)direction);

	spobj->Draw3D(
		CST::GetPerspectiveCamera(),
		CST::GetShaderClass(),
		src,
		pos,
		angle,
		scalec);
}