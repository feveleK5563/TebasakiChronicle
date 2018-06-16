#include "DataGui.h"
#include "../src/Helper.h"

//!@brief	�R���X�g���N�^
DataGui::DataGui(GameObject& gameObj)
{
	lifeNeedle = new GUIObject("ScreenUI/Life�j", K_Math::Vector3(30, 145, 0), K_Math::Box2D(0, 0, 67, 120));

	minAngle = 180;		//life��0�̂Ƃ�180�ɂȂ�
	maxAngle = -180;	//life��max�̂Ƃ�-180�̌���
	angle = maxAngle;
	raito = 0.0f;
	decreaseAmount = 1.0f;

	life = gameObj.GetLife();
	maxLife = gameObj.GetStatus().GetMaxLife();
	timeCnt = 0;
	upDataFlag = true;
}

//!@brief	�f�X�g���N�^
DataGui::~DataGui()
{
	Memory::SafeDelete(lifeNeedle);
}

//!@brief	�X�V
void	DataGui::UpDate()
{
	if (upDataFlag)
	{
		lifeNeedle->GetGameObject().SetAngle(K_Math::Vector3(0, 0, angle + raito));
		lifeNeedle->UpDate();
	}
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

	raito = ((float)life / (float)maxLife) * 180.0f;

	//�͈͐���
	if (raito > 180 || raito < 0)
	{
		raito = 0;
		upDataFlag = false;
	}
}

//���̃��C�t����
void	DataGui::RaitoRaito()
{
	timeCnt++;
	if (timeCnt >= 60)
	{
		life--;
		timeCnt = 0;
	}
	
	float preRaito = raito;
	float nowRaito;
	//�����̌v�Z
	nowRaito = ((float)life / (float)maxLife) * 180.0f;
	
	//��������
	float amount = abs(nowRaito - preRaito);

	//���̃x�N�g�����̑傫���𕪊�����
	//raito = ((float)life / (float)maxLife) * 180.0f;
	if (raito >= amount)
	{
		raito += 0.00001f;
	}
	//�͈͐���
	if (raito > 180 || raito < 0)
	{
		raito = 0;
		upDataFlag = false;
	}

}