#pragma once
#include "EnemyMove.h"
#include "EnemyMoveTransition.h"
#include "../../../BaseClass/ImageManager/AnimationCharaChip.h"

//敵動作のパターンを作成するよ！
class EnemyMovePattern
{
public:
	struct MoveSetUpData	//敵の動作パターン生成に必要なデータ
	{
		int*			moveIdArr;			//動作番号を入れた配列のアドレス値
		int*			skillIdArr;			//動作中に取得可能なスキル番号
		int*			durationTimeArr;	//動作の継続時間を入れた配列のアドレス値
		K_Math::Box2D*	srcArr;				//アニメーション画像の最初の位置
		int*			sheetArr;			//アニメーション枚数
		float*			spdArr;				//アニメーション速度
		bool*			isRoopArr;			//ループするか否か
		int*			transitionIdArr;	//他動作パターンへの遷移条件の番号
		int				patternNum;			//動作パターンの総数
		int				totalMoveNum;		//動作の総数

		MoveSetUpData(	int* miarr, int* siarr, int* dtarr, K_Math::Box2D* srcarr, int* shtarr,
						float* spdarr, bool* irarr, int* tiarr, int pnum, int tmnum):
			moveIdArr(miarr), skillIdArr(siarr), durationTimeArr(dtarr), srcArr(srcarr), sheetArr(shtarr), 
			spdArr(spdarr), isRoopArr(irarr), transitionIdArr(tiarr), patternNum(pnum), totalMoveNum(tmnum){}
	};

private:
	struct MovePattern		//動作の種類、時間を内包したやつ
	{
		EnemyMove*	em;		//動作をこいつで行う
		int skillId;		//動作中に取得可能なスキル番号
		int moveTimeMax;	//動作終了までの時間

		MovePattern(int sklid, int mtime) :
			em(nullptr),
			skillId(sklid),
			moveTimeMax(mtime) {}
	};
	std::vector<MovePattern*> mp;
	std::vector<AnimationCharaChip*> animChip;
	std::vector<EnemyMoveTransition*> emt;

public:
	//コンストラクタ
	EnemyMovePattern(const MoveSetUpData& msud);

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

	//アニメーションのキャラチップを返す
	const std::vector<AnimationCharaChip*>& GetNowAnimChip();

	//指定番号の遷移条件を実行し、tfを返す
	bool GetTransition(int num, CollisionManager& colmanager, Status& status);
};