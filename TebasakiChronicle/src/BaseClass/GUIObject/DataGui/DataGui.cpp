#include "DataGui.h"
#include "../src/Helper.h"

//!@brief	�R���X�g���N�^
DataGui::DataGui(GameObject& gameObj)
{
	lifeNeedle = new GUIObject("ScreenUI/Life�j", K_Math::Vector3(31, 155, 0), K_Math::Box2D(0, 0, 67, 120));

	minAngle = 0;		//life��0�̂Ƃ�180�ɂȂ�
	maxAngle = 180;		//life��max�̂Ƃ�-180�̌���

	//���C�t�̍ő�(hp:10)��angle0
	//���C�t�̍ŏ�(hp:0)��angle180
	life = gameObj.GetLife();
	maxLife = gameObj.GetStatus().GetMaxLife();
	timeCnt = 0;
	
	life = 10;
	maxLife = 10;
	raito = minAngle;
	showLife = K_Math::Vector3(0, 0, raito);
	changeAmount = 50.0f;
	offsetAngle = 180.0f;
}

//!@brief	�f�X�g���N�^
DataGui::~DataGui()
{
	Memory::SafeDelete(lifeNeedle);
}

//!@brief	�X�V
void	DataGui::UpDate()
{
	lifeNeedle->GetGameObject().SetAngle(showLife);
	lifeNeedle->UpDate();
}

//!@brief	�`��
void	DataGui::Render()
{
	lifeNeedle->Render();
}


//!@brief	�����̌v�Z
//!@param[in]	gameObj	�Q�[���I�u�W�F�N�g
void	DataGui::Raito(GameObject& gameObj)
{
	life = gameObj.GetLife();
	maxLife = gameObj.GetStatus().GetMaxLife();

	raito = (float)((float)life / (float)maxLife) * abs(minAngle - maxAngle) - offsetAngle;

	//�Q�[�W�ϓ�
	Fluctuation(K_Math::Vector3(0, 0, raito));
}

//���̃��C�t����
void	DataGui::RaitoRaito()
{
	timeCnt++;
	if (timeCnt >= 60)
	{
		if (life > 0)
		{
			life--;
		}
		timeCnt = 0;
	}

	//�����̌v�Z
	raito = (float)((float)life / (float)maxLife) * abs(minAngle - maxAngle) - offsetAngle;
	//�Q�[�W�ϓ�
	this->Fluctuation(K_Math::Vector3(0, 0, raito));
}


//!@brief	�j�̕ϓ�����
void	DataGui::Fluctuation(const K_Math::Vector3& targetPos)
{
	K_Math::Vector3 vector = targetPos - showLife;
	showLife.z += vector.z / changeAmount;
}