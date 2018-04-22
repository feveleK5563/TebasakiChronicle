#pragma once
#include "MeshModel.h"
#include "K_Graphics\CameraList.h"
#include "K_Graphics\ShaderList.h"
#include "K_Graphics\TextureList.h"
#include "AnimationCharaChip.h"

class ImageManager
{
private:
	const bool	isDelete;
public:
	K_Graphics::CameraClass*			camera;
	K_Graphics::ShaderClass*			shader;

	K_Graphics::SpriteObject*			spobj;
	std::vector<AnimationCharaChip*>	charaChip;
	int									nowAnimNum;
	float								animCnt;

	//コンストラクタ(キャラチップを作成する)
	ImageManager(	K_Graphics::CameraClass*	cc,
					K_Graphics::ShaderClass*	sc, 
					K_Graphics::Texture*		tex);

	//コンストラクタ(外部のキャラチップを参照する)
	//※キャラチップを新たに設定することはできない
	ImageManager(	K_Graphics::CameraClass*			cc,
					K_Graphics::ShaderClass*			sc,
					K_Graphics::Texture*				tex,
					std::vector<AnimationCharaChip*>	acc);

	//デストラクタ
	~ImageManager();

	//----------------------------------------------
	//キャラチップの作成
	void CreateCharaChip(const K_Math::Box2D& src, int sheet, float spd, bool isroop);

	//----------------------------------------------
	//アニメーションパターンの変更
	void ChangeAnimationPattern(int motionNum);

	//----------------------------------------------
	//アニメーション
	void Animation();

	//----------------------------------------------
	//描画
	void ImageDraw(	const K_Math::Vector3& posc, 
					const K_Math::Vector3& angle,
					const K_Math::Vector3& scale);
};