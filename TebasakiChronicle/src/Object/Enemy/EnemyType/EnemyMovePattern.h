#pragma once
#include <math.h>
#include "CharacterBehavior.h"
#include "EnemyMoveTransition.h"
#include "../../../BaseClass/ImageManager/AnimationCharaChip.h"
#include "../../../Helper.h"

//敵動作のパターンを保持する
class EnemyMovePattern
{
public:
	struct MoveSetUpData	//敵の動作パターン生成に必要なデータ
	{
		int*				moveIdArr;			//動作番号を入れた配列のアドレス値
		int*				behaviorIdArr;		//動作中に取得可能な振る舞い番号
		int*				durationTimeArr;	//動作の継続時間を入れた配列のアドレス値
		K_Math::Box2D*		srcArr;				//アニメーション画像の最初の位置
		K_Math::Vector2*	basisPosArr;		//描画の基準座標(0, 0で中心)
		int*				sheetArr;			//アニメーション枚数
		float*				spdArr;				//アニメーション速度
		bool*				isRoopArr;			//ループするか否か
		int*				transitionIdArr;	//他動作パターンへの遷移条件の番号
		int					patternNum;			//動作パターンの総数
		int					totalMoveNum;		//動作の総数

		MoveSetUpData(	int* miarr, int* siarr, int* dtarr, K_Math::Box2D* srcarr, K_Math::Vector2* basisposarr, int* shtarr,
						float* spdarr, bool* irarr, int* tiarr, int pnum, int tmnum):
			moveIdArr(miarr), behaviorIdArr(siarr), durationTimeArr(dtarr), srcArr(srcarr), basisPosArr(basisposarr), sheetArr(shtarr),
			spdArr(spdarr), isRoopArr(irarr), transitionIdArr(tiarr), patternNum(pnum), totalMoveNum(tmnum){}

		~MoveSetUpData()
		{
			Memory::SafeDeleteArr(moveIdArr);
			Memory::SafeDeleteArr(behaviorIdArr);
			Memory::SafeDeleteArr(durationTimeArr);
			Memory::SafeDeleteArr(srcArr);
			Memory::SafeDeleteArr(basisPosArr);
			Memory::SafeDeleteArr(sheetArr);
			Memory::SafeDeleteArr(spdArr);
			Memory::SafeDeleteArr(isRoopArr);
			Memory::SafeDeleteArr(transitionIdArr);
		}
	};

private:
	struct MovePattern		//動作の種類、時間を内包したやつ
	{
		CharacterBehavior	em;		//動作をこいつで行う
		int behaviorId;		//動作中に取得可能なスキル番号
		int moveTimeMax;	//動作終了までの時間

		MovePattern(int moveNum, int beId, int mtime) :
			behaviorId(beId),
			moveTimeMax(mtime),
			em(moveNum) {}
	};
	std::vector<MovePattern*> mp;
	std::vector<AnimationCharaChip*> animChip;
	std::vector<EnemyMoveTransition*> emt;

public:
	//コンストラクタ
	EnemyMovePattern(const MoveSetUpData& msud);

	//デストラクタ
	~EnemyMovePattern();

	//動作が終了したか否かを返す
	bool IsEndMovePattern(int& nowMoveOrder, TimeCount& timeCnt, TemporaryCollisionManager& tempmanager, GameObject& gameObject);

	//動作を行い、現在取得可能なスキルの番号を返す
	int EMove(int& nowMoveOrder, TimeCount& timeCnt, TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager);

	//終了時の処理を行う
	void EMoveEnd(int& nowMoveOrder, TimeCount& timeCnt, TemporaryCollisionManager& tempmanager, GameObject& gameObject);

	//動作順をリセットする
	void MoveReset(int& nowMoveOrder);

	//アニメーションのキャラチップを返す
	const std::vector<AnimationCharaChip*>& GetNowAnimChip();

	//指定番号の遷移条件を実行し、クリアしたらtrueを返す
	bool IsTransition(int num, CollisionManager& colmanager, Status& status, const bool endMovePattern);
};