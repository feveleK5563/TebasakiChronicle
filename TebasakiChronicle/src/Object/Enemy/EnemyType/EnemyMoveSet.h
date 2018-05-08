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
	void CreateMotionPattern(	int* moveNum,		//動作番号を入れた配列のアドレス値
								int* skillId,		//動作中に取得可能なスキル番号
								int* durationTime,	//動作の継続時間を入れた配列のアドレス値
								K_Math::Box2D*	src,	//アニメーション画像の最初の位置
								int*			sheet,	//アニメーション枚数
								float*			spd,	//アニメーション速度
								bool*			ir,		//ループするか否か
								int				totalMoveNum,		//動作の総数
								int				transitionNum);		//動作パターンの遷移条件の番号

	//指定パターン番号のアニメーションを返す
	const std::vector<AnimationCharaChip*> GetNowAnimChip(int nowPatternOrder);

	//現在の動作パターンを実行し、現在プレイヤーが取得可能なスキル番号を返す
	int EMove(int& nowMoveOrder, int& nowPatternOrder, int& timeCnt, CollisionManager& colmanager, Status& status, Move& move);

	//動作パターンを指定番号に遷移させる
	void PatternTransition(int& nowMoveOrder, int& nowPatternOrder, int& timeCnt, int patternNum);
};