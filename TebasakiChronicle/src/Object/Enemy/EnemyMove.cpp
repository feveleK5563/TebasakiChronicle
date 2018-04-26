#include "EnemyMove.h"

//-----------------------------------------------
//何もしない
void EMove_NoMotion::Move(K_Math::Vector3& moveVec)
{
	//ここに「何もしない」処理を書く
}

//-----------------------------------------------
//右に歩く
void EMove_WalkRight::Move(K_Math::Vector3& moveVec)
{
	++moveVec.x();
}

//-----------------------------------------------
//上に移動する
void EMove_Up::Move(K_Math::Vector3& moveVec)
{
	--moveVec.y();
}

//-----------------------------------------------
//下に移動する
void EMove_Down::Move(K_Math::Vector3& moveVec)
{
	++moveVec.y();
}