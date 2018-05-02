#pragma once
#include <vector>
#include "SystemClass.h"

//“®ì‚ÌŠî’êƒNƒ‰ƒX
class EnemyMove
{
public:
	EnemyMove(){}
	virtual ~EnemyMove() {}
	virtual void Move(K_Math::Vector3& moveVec) = 0;
};

//-----------------------------------------------
//‰½‚à‚µ‚È‚¢
class EMove_NoMotion : public EnemyMove
{
public:
	void Move(K_Math::Vector3& moveVec);
};

//-----------------------------------------------
//‰E‚ÉˆÚ“®‚·‚é
class EMove_WalkRight : public EnemyMove
{
public:
	void Move(K_Math::Vector3& moveVec);
};

//-----------------------------------------------
//ã‚ÉˆÚ“®‚·‚é
class EMove_Up : public EnemyMove
{
public:
	void Move(K_Math::Vector3& moveVec);
};

//-----------------------------------------------
//‰º‚ÉˆÚ“®‚·‚é
class EMove_Down : public EnemyMove
{
public:
	void Move(K_Math::Vector3& moveVec);
};