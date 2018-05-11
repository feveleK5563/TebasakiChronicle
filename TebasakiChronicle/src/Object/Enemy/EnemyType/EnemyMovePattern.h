#pragma once
#include "EnemyMove.h"
#include "EnemyMoveTransition.h"
#include "../../../BaseClass/ImageManager/AnimationCharaChip.h"

//敵動作のパターンを作成するよ！
class EnemyMovePattern
{
public:

	struct MovePattern		//動作の種類、時間を内包したやつ
	{
		EnemyMove*	em;		//動作をこいつで行う
		int skillId;		//動作中に取得可能なスキル番号
		int moveTimeMax;	//動作終了までの時間

		MovePattern(int sklid, int mtime) :
			em(nullptr),
			skillId(sklid),
			moveTimeMax(mtime){}
	};
	std::vector<MovePattern*> mp;
	std::vector<AnimationCharaChip*> animChip;
	std::vector<EnemyMoveTransition*> emt;

	//コンストラクタ
	EnemyMovePattern(	int* moveIdArr,			//動作番号を入れた配列のアドレス値
						int* skillIdArr,		//動作中に取得可能なスキル番号
						int* durationTimeArr,	//動作の継続時間を入れた配列のアドレス値
						K_Math::Box2D*	src,	//アニメーション画像の最初の位置
						int*			sheet,	//アニメーション枚数
						float*			spd,	//アニメーション速度
						bool*			ir,		//ループするか否か
						int*			transitionIdArr,	//他動作パターンへの遷移条件の番号
						int				patternNum,			//動作パターンの総数
						int				totalMoveNum);		//動作の総数

	//デストラクタ
	~EnemyMovePattern();

	//動作を行い、現在取得可能なスキルの番号を返す
	int EMove(int& nowMoveOrder, int& timeCnt, CollisionManager& colmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move, bool& endMovePattern);

	//動作順をリセットする
	void MoveReset(int& nowMoveOrder);

	//動作を設定する
	void SetMoveAndTime(int moveNum, int skillId, int durationTime);

	//動作パターン遷移条件を設定する
	void SetTransition(int transitionNum);
};