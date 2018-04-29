#include "ImageManager.h"

//コンストラクタ(キャラチップを作成する)
ImageManager::ImageManager(K_Graphics::Texture* tex, bool isde) :
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
	if (timeReset)
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
//描画
void ImageManager::ImageDraw3D(	const K_Math::Vector3& posc,
								const K_Math::Vector3& angle,
								const K_Math::Vector3& scale)
{
	K_Math::Box2D src = charaChip[nowAnimNum]->chip;
	if (charaChip[nowAnimNum]->chipSheetNum >= 0)
	{
		src.x += src.w * (int(animCnt) % charaChip[nowAnimNum]->chipSheetNum);
	}
	else
	{
		src.x -= src.w * (int(animCnt) % charaChip[nowAnimNum]->chipSheetNum);
	}
	spobj->controlPoint = K_Math::Vector2(src.w / 2.f, src.h / 2.f);

	K_Math::Vector3 pos = posc;
	pos.x() -= (float)src.w / 2.f;
	pos.y() += (float)src.h / 2.f;

	spobj->Draw3D(
		CST::GetPerspectiveCamera(),
		CST::GetShaderClass(),
		src,
		pos,
		angle,
		scale);
}