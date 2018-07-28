#pragma once
#include "EnemyMovePattern.h"

//EnemyMovePatternをまとめたやつ
class EnemyMoveSet
{
private:
	std::vector<EnemyMovePattern*>		empattern;		//動作パターン


public:
	EnemyMoveSet();
	~EnemyMoveSet();

	//動作パターン集合の生成
	void CreateMotionPattern(EnemyMovePattern::MoveSetUpData& msud);

	//指定パターン番号のアニメーションを返す
	const std::vector<AnimationCharaChip*>& GetNowAnimChip(int nowPatternOrder);

	//現在の動作パターンを実行し、現在プレイヤーが取得可能なスキル番号を返す
	int EMove(int& nowMoveOrder, int& nowPatternOrder, TimeCount& timeCnt, CollisionManager& colmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move);

	//動作パターンを指定番号に遷移させる
	void PatternTransition(int& nowMoveOrder, int& nowPatternOrder, TimeCount& timeCnt, int patternNum);
};