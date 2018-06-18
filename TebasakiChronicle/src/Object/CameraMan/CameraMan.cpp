#include "CameraMan.h"

CameraMan::CameraMan(int screenWidth, int screenHeight, float dist, const K_Math::Vector3& target) :
	defaultDist(dist),
	settingDist(dist),
	distance(dist),
	trackingPos(target) {}

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
}

void CameraMan::SetDistance(float setDist)
{
	settingDist = setDist;
}