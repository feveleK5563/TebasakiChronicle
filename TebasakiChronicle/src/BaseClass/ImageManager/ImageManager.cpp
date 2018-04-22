#include "ImageManager.h"

//コンストラクタ(キャラチップを作成する)
ImageManager::ImageManager(	K_Graphics::CameraClass* cc,
							K_Graphics::ShaderClass* sc,
							K_Graphics::Texture* tex) :
	camera(cc),
	shader(sc),
	spobj(new K_Graphics::SpriteObject(tex)),
	animCnt(0.f),
	nowAnimNum(0),
	isDelete(true) {}

//コンストラクタ(外部のキャラチップを参照する)
ImageManager::ImageManager(	K_Graphics::CameraClass* cc,
							K_Graphics::ShaderClass* sc, 
							K_Graphics::Texture* tex,
							std::vector<AnimationCharaChip*> acc) :
	camera(cc),
	shader(sc),
	spobj(new K_Graphics::SpriteObject(tex)),
	animCnt(0.f),
	nowAnimNum(0),
	charaChip(acc),
	isDelete(false) {}

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
void ImageManager::CreateCharaChip(const K_Math::Box2D& src, int sheet, float spd, bool isroop)
{
	if (isDelete)
	{
		charaChip.emplace_back(new AnimationCharaChip(src, sheet, spd, isroop));
	}
}

//-----------------------------------------------------------------------------
//アニメーションパターンの変更
void ImageManager::ChangeAnimationPattern(int motionNum)
{
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
		(int)animCnt >= charaChip[nowAnimNum]->chipSheetNum)
	{
		animCnt = (float)charaChip[nowAnimNum]->chipSheetNum;
	}
}

//-----------------------------------------------------------------------------
//描画
void ImageManager::ImageDraw(	const K_Math::Vector3& posc,
								const K_Math::Vector3& angle,
								const K_Math::Vector3& scale)
{
	K_Math::Box2D src = charaChip[nowAnimNum]->chip;
	src.x += src.w * (int(animCnt) % charaChip[nowAnimNum]->chipSheetNum);
	spobj->controlPoint = K_Math::Vector2(src.w / 2.f, src.h / 2.f);

	K_Math::Vector3 pos = posc;
	pos.x() -= (float)src.w / 2.f;
	pos.y() += (float)src.h / 2.f;

	spobj->Draw3D(
		camera,
		shader,
		src,
		pos,
		angle,
		scale);
}