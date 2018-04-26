#include "EnemyMove.h"

//-----------------------------------------------
//âΩÇ‡ÇµÇ»Ç¢
void EMove_NoMotion::Move(K_Math::Vector3& moveVec)
{
	//Ç±Ç±Ç…ÅuâΩÇ‡ÇµÇ»Ç¢ÅvèàóùÇèëÇ≠
}

//-----------------------------------------------
//âEÇ…ï‡Ç≠
void EMove_WalkRight::Move(K_Math::Vector3& moveVec)
{
	++moveVec.x();
}

//-----------------------------------------------
//è„Ç…à⁄ìÆÇ∑ÇÈ
void EMove_Up::Move(K_Math::Vector3& moveVec)
{
	--moveVec.y();
}

//-----------------------------------------------
//â∫Ç…à⁄ìÆÇ∑ÇÈ
void EMove_Down::Move(K_Math::Vector3& moveVec)
{
	++moveVec.y();
}