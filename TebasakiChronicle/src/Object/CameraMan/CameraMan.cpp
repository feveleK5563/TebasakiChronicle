#include "CameraMan.h"

CameraMan::CameraMan(int screenWidth, int screenHeight, float dist, const K_Math::Vector3& target) :
	defaultDist(dist),
	settingDist(dist),
	distance(dist),
	trackingPos(target),
	targetPos(&target)
{
	baseShape = CC::CreateBoxShape(1, 1, 1);
	collisionManager.CreateBaseCollisionData(baseShape, trackingPos, K_Math::Vector3(0, 0, 0), false);
	cameraShape = CC::CreateBoxShape((float)screenWidth / 2 + 25, (float)screenHeight / 2 + 25, 100);
}

CameraMan::~CameraMan()
{
	CC::RemoveCollisionShape(&baseShape);
	CC::RemoveCollisionShape(&cameraShape);
}

void CameraMan::Run()
{
	K_Math::Vector3 toVec = *targetPos - trackingPos;
	trackingPos += toVec * 0.05f;

	float toVecDist = settingDist - distance;
	distance += toVecDist * 0.05f;

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

void CameraMan::ChangeTarget(const K_Math::Vector3& target)
{
	targetPos = &target;
}