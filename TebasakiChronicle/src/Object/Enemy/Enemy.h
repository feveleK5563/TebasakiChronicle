#pragma once
#include "EnemyType.h"
#include "EnemyController.h"

//以下のincludeはGameObjectで代替する
#include "../../BaseClass/ImageManager/ImageManager.h"

class Enemy
{
public:
	
	EnemyController*	eController;		//動作管理くん
	int					nowMoveOrder;		//現在の動作順番
	int					nowPatternOrder;	//現在の動作パターン番号
	int					beforeMoveOrder;	//前の動作順番
	int					beforePatternOrder;	//前の動作パターン番号

	//以下のメンバ変数はGameObjectやMoveクラスとかが持ってるものだと思う
	int					life;
	K_Math::Vector3		pos;
	K_Math::Vector3		angle;
	K_Math::Vector3		scale;
	K_Math::Vector3		moveVec;
	ImageManager*		imgManager;

	//コンストラクタ
	Enemy(EnemyType* cpyet, const K_Math::Vector3& setPos);
	//デストラクタ
	~Enemy();

	//敵情報を設定
	void SetEnemyType(EnemyType* cpyet, const K_Math::Vector3& setPos);

	//更新
	void Update();

	//描画
	void Render();
};