#include "EnemyMove.h"

//-----------------------------------------------
//何もしない
void EMove_NoMotion::EMove(CollisionManager& cmanager, Status& status, Move& move)
{
	//ここに「何もしない」処理を書く
}

//-----------------------------------------------
//向いている方向に移動する
void EMove_Movement::EMove(CollisionManager& cmanager, Status& status, Move& move)
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
//地面についているときのみジャンプ
void EMove_Jump::EMove(CollisionManager& cmanager, Status& status, Move& move)
{
	if (int a = cmanager.GetConflictionObjectsUserData(3).size() > 0)
	{
		move.JumpOperation();
	}
}