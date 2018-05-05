#pragma once
#include "EnemyType/EnemyMoveSet.h"

//敵の種類別に設定された動作アドレスを所有し、
//動作処理を呼び出すクラス
class EnemyController
{
private:
	EnemyMoveSet* ems;	//動作(delete禁止)

	int skillId;		//現在の敵から読み取れるスキル番号
	int timeCnt;		//時間計測

public:

	//コンストラクタ
	EnemyController(EnemyMoveSet* cpyems);
	//デストラクタ
	~EnemyController();

	//スキル番号を取得
	int& GetSkillId();

	//動作の実行
	void Move(int& nowMoveOrder, int& nowPatternOrder, K_Math::Vector3& moveVec);

	//EnemyMoveSetからキャラチップを取得
	const std::vector<AnimationCharaChip*> GetNowCharaChip(int nowPatternOrder);
};