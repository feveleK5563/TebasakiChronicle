#include "CameraMan.h"

CameraMan::CameraMan(int screenWidth, int screenHeight, float dist, const K_Math::Vector3& target) :
	defaultDist(dist),
	settingDist(dist),
	distance(dist),
	trackingPos(target)
{
	baseShape = CC::CreateBoxShape(100, 100, 100);
	collisionManager.CreateBaseCollisionData(baseShape, trackingPos, K_Math::Vector3(0, 0, 0), false);
	cameraShape = CC::CreateBoxShape((float)screenWidth / 2.f, (float)screenHeight / 2.f, 100);
	collisionManager.CreateSubCollisionData(cameraShape, CollisionMask::Non, CollisionMask::CameraManCollision, K_Math::Vector3(0, 0, 0));
}

CameraMan::~CameraMan()
{
	CC::RemoveCollisionShape(&baseShape);
	CC::RemoveCollisionShape(&cameraShape);
}

void CameraMan::Run(const K_Math::Vector3& target)
{
	K_Math::Vector3 toVec = target - trackingPos;
	trackingPos += toVec * 0.1f;

	float toVecDist = settingDist - distance;
	distance += toVecDist * 0.1f;

	CST::GetPerspectiveCamera()->SetTarget(trackingPos.x, trackingPos.y, trackingPos.z);
	CST::GetPerspectiveCamera()->SetPosition(distance, K_Math::Vector3(0, 0, -1));

	//ƒRƒŠƒWƒ‡ƒ“‚ð•t‚¢‚Ä‚±‚³‚¹‚é
	collisionManager.SetBaseCollisionObjectPosition(trackingPos);
	collisionManager.SetSubCollisionPos(0);
}

void CameraMan::SetDistance(float setDist)
{
	settingDist = setDist;
}