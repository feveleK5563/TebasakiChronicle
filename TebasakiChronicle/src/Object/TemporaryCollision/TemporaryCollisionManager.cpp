#include "TemporaryCollisionManager.h"

//�R���W�����̌`������Ǘ������Ȃ�
TemporaryCollisionManager::TemporaryCollisionManager() {}

//�R���W�����̌`������Ǘ�������
TemporaryCollisionManager::TemporaryCollisionManager(K_Physics::CollisionShape* shape) {}

//�f�X�g���N�^
TemporaryCollisionManager::~TemporaryCollisionManager()
{
	for (auto it : tempCollision)
	{
		delete it;
	}
}

//-----------------------------------------------------------------------------
//�R���W�����𐶐�����
void TemporaryCollisionManager::CreateTemporaryCollision(
	K_Physics::CollisionShape*	shape,
	const CollisionMask&		mmask,
	const CollisionMask&		gmask,
	const K_Math::Vector3&		setpos,
	const K_Math::Vector3&		movevec,
	const Status::Direction&	dir,
	const int					damage,
	const int					deletetime,
	const bool					ishitground,
	const bool					doground)
{
	tempCollision.emplace_back(new TemporaryCollision(shape, mmask, gmask, setpos, movevec, dir, damage, deletetime, ishitground, doground));
}

//-----------------------------------------------------------------------------
//���������R���W�����Ƀe�N�X�`����ݒ肷��
void TemporaryCollisionManager::SetAnimationCharaChip(
	const std::string&			texName,
	K_Graphics::Texture*		texture,
	const K_Math::Box2D&		src,
	int							sheet,
	float						spd,
	bool						isroop)
{
	tempCollision.back()->SetImageManagerAndCharaChip(texName, texture, src, sheet, spd, isroop);
}

//-----------------------------------------------------------------------------
//�R���W�����̍X�V���s��
//�R���W����������ŗv�����������ꍇ���ł�����
void TemporaryCollisionManager::Update()
{
	auto it = tempCollision.begin();
	for (;it != tempCollision.end();)
	{
		if ((*it)->Update())
		{
			delete (*it);
			it = tempCollision.erase(it);
		}
		else
		{
			++it;
		}
	}
	tempCollision.shrink_to_fit();
}

//-----------------------------------------------------------------------------
//�R���W�����̕`����s��
void TemporaryCollisionManager::Render()
{
	for (auto it : tempCollision)
	{
		it->Render();
	}
}