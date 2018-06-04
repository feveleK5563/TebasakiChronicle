#pragma once
#include "../../CSTList.h"
#include "../../BaseClass/Collision/CollisionManager.h"
#include "../../BaseClass/Collision/CollisionCreator.h"

class CameraMan
{
private:
	K_Physics::CollisionShape* baseShape;
	K_Physics::CollisionShape* cameraShape;
	CollisionManager collisionManager;

	float						defaultDist;
	float						settingDist;
	float						distance;

	K_Math::Vector3				trackingPos;
	const K_Math::Vector3*		targetPos;

public:
	CameraMan(int screenWidth, int screenHeight, float dist, const K_Math::Vector3& target);
	~CameraMan();

	void Run();

	void SetDistance(float setDist);

	void ChangeTarget(const K_Math::Vector3& target);
};