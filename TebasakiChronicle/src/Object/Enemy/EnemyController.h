#pragma once
#include "EnemyMoveSet.h"

//敵の種類別に設定された動作アドレスを所有し、
//動作処理を呼び出すクラス
class EnemyController
{
public:
	EnemyMoveSet* ems;		//動作(delete禁止)

	int skillId;			//現在の敵から読み取れるスキル番号
	int timeCnt;			//時間計測

	//コンストラクタ
	EnemyController(EnemyMoveSet* cpyems);
	//デストラクタ
	~EnemyController();

	//動作の実行
	void Move(int& nowMoveOrder, int& nowPatternOrder, K_Math::Vector3& moveVec);

	//EnemyMoveSetからキャラチップを取得
	const std::vector<AnimationCharaChip*> GetNowCharaChip(int nowPatternOrder);
};