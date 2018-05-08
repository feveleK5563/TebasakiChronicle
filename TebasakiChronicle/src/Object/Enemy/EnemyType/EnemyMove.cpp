#include "EnemyMove.h"

//-----------------------------------------------
//何もしない
void EMove_NoMotion::EMove(Status& status, Move& move)
{
	//ここに「何もしない」処理を書く
}

//-----------------------------------------------
//向いている方向に移動する
void EMove_Movement::EMove(Status& status, Move& move)
{
	if (status.GetDirection() == status.Right)
	{
		move.GetMoveVec().x() += move.GetAddVec();
	}
	else
	{
		move.GetMoveVec().x() -= move.GetAddVec();
	}
}

//-----------------------------------------------
//ジャンプ
void EMove_Jump::EMove(Status& status, Move& move)
{
	move.JumpOperation();
}