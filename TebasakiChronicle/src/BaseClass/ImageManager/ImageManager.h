#pragma once
#include <math.h>
#include "AnimationCharaChip.h"

class ImageManager
{
private:
	const bool	isDelete;
public:
	CSTList*							cst;
	std::string							textureName;
	K_Graphics::SpriteObject*			spobj;
	std::vector<AnimationCharaChip*>	charaChip;
	int									nowAnimNum;
	float								animCnt;

	//コンストラクタ(キャラチップは後で作成する)
	//キャラチップをImageManager内で作成しない場合は第二引数にfalseを指定
	ImageManager(K_Graphics::Texture* tex, bool isde = true);

	//デストラクタ
	~ImageManager();

	//----------------------------------------------
	//キャラチップの作成
	bool CreateCharaChip(const K_Math::Box2D& src, int sheet, float spd, bool isroop);

	//----------------------------------------------
	//キャラチップを変更
	//※コンストラクタでisdeをfalseにしていないと失敗する
	bool ChangeCharaChip(const std::vector<AnimationCharaChip*>& acc);

	//----------------------------------------------
	//アニメーションパターンの変更
	void ChangeAnimationPattern(int motionNum, bool timeReset = true);

	//----------------------------------------------
	//アニメーション
	void Animation();

	//----------------------------------------------
	//描画
	void ImageDraw(	const K_Math::Vector3& posc, 
					const K_Math::Vector3& angle,
					const K_Math::Vector3& scale);
};