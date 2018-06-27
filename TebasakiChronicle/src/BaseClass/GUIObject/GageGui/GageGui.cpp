#include "GageGui.h"
#include "CameraList.h"
#include "../src/BaseClass/Input/Input.h"
#include "../../../CSTList.h"

//!@brief	�R���X�g���N�^
GageGui::GageGui(GameObject& object)
{
	CST::LoadAndGetTexture("LifeBar", "data/image/ScreenUI/LifeBar.png");
	CST::LoadAndGetTexture("enemyGageBar", "data/image/ScreenUI/enemyGageBar.png");

	frame = new GUIObject("LifeBar", K_Math::Vector3(0, 670, 0), K_Math::Box2D(0, 0, 1095, 270));
	fillAreaBox = new GUIObject("enemyGageBar", K_Math::Vector3(-10, 710, 0), K_Math::Box2D(0, 0, 128, 256));
	frame->GetGameObject().SetAngle(K_Math::Vector3(0, 0, 180));
	fillAreaBox->GetGameObject().SetAngle(K_Math::Vector3(0, 0, 0));
	//��]���̕ύX
	frame->GetGameObject().GetImage().GetNowAnimationCharaChip()->basisRenderPos.x -= frame->GetGameObject().GetImage().GetNowAnimationCharaChip()->chip.w / 2;

	moveCnt = 0;
	rotateCnt = 0;
	maxShowLife = K_Math::Vector3(927, 710, 0);
	minShowLife = K_Math::Vector3(101, 710, 0);	
	showLife = maxShowLife;

	maxMoveCnt = 345;
	maxRotateCnt = 180;
	eventMotion = Ev_Non;
	changeAmount = 50.0f;

	//��
	minLife = object.GetStatus().GetMinLife();
	maxLife = object.GetStatus().GetMaxLife();
	life = object.GetStatus().GetLife();

	eventStartFlag = false;
}
//!@brief	�f�X�g���N�^
GageGui::~GageGui()
{
	CST::DeleteTexture("LifeBar");
	CST::DeleteTexture("enemyGageBar");
}


//!@brief	�X�V
void		GageGui::UpDate(GameObject& object)
{
	frame->UpDate();
	fillAreaBox->UpDate();

	//�C�x���g
	Think();
	Process();

	//�Q�[�W����
	if (eventMotion != Ev_End) { return; }

	//�̗͏����擾
	minLife = object.GetStatus().GetMinLife();
	maxLife = object.GetStatus().GetMaxLife();
	life = object.GetStatus().GetLife();

	//�`��ʒu���킩��
	float nowLife = (float)((float)life / (float)maxLife) * abs(maxShowLife.x - 0) + minShowLife.x;

	//�Q�[�W�ϓ�����
	this->Fluctuation(K_Math::Vector3(nowLife, 710, 0));

	//�ʒu��K�p������
	fillAreaBox->GetGameObject().SetPos(showLife);
	
	//�C�x���g���Z�b�g
	if (eventStartFlag)
	{
		//Reset(object);	//���͂Ȃ�
	}

	//�����C�t�ϓ�
	if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::A))
	{
		if (life > 0)
		{
			life -= 1;
		}
	}
	if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::X))
	{
		if (life < 10)
		{
			life++;
		}
	}
}

//!@brief	�`��
void		GageGui::Render()
{
	frame->Render();
	fillAreaBox->Render();
}

//!@brief	�C�x���g���J�n����
//!@brief	�ĂԂƃC�x���g���J�n����
void		GageGui::EventStart()
{
	if (eventMotion == Ev_End || eventMotion == Ev_Non)
	{
		eventStartFlag = true;
	}
}



//!@brief	��ԕύX����
void	GageGui::Think()
{
	if (eventMotion == Ev_End) { return; }

	EventMotion	nowEventMotion = eventMotion;
	switch (nowEventMotion) {
	case Ev_Non:
		if (eventStartFlag)
		{
			nowEventMotion = Ev_Begin;
		}
		break;
	case Ev_Begin:
		if (rotateCnt < maxRotateCnt)
		{
			nowEventMotion = Ev_Rotate;
		}
		break;
	case Ev_Move:
		if (moveCnt > maxMoveCnt)
		{
			moveCnt = maxMoveCnt;
			nowEventMotion = Ev_End;
			showLife = K_Math::Vector3(maxShowLife.x + minShowLife.x, 710, 0);
			eventStartFlag = false;
		}
		break;
	case Ev_Rotate:
		if (rotateCnt >= maxRotateCnt)
		{
			rotateCnt = maxRotateCnt;
			nowEventMotion = Ev_Move;
		}
		break;
	case Ev_End:
		break;
	}
	UpDateEventMotion(nowEventMotion);
}

//!@brief	��������
void	GageGui::Process()
{
	if (eventMotion == Ev_End)
	{ 
		return; 
	}

	switch (eventMotion){
	case Ev_Non:
		break;
	case Ev_Begin:
		break;
	case Ev_Move:
		moveCnt++;
		fillAreaBox->GetGameObject().GetPos().x += 3.0f;
		break;
	case Ev_Rotate:
		rotateCnt++;
		frame->GetGameObject().GetAngle().z--;
		break;
	case Ev_End:
		break;
	}
}


//!@brief	���[�V�����̍X�V
//!@param[in]	eventMotion	���݂̃C�x���g���[�V����
void	GageGui::UpDateEventMotion(const EventMotion& eventMotion)
{
	if (this->eventMotion == eventMotion) { return; }
	this->eventMotion = eventMotion;
}


//!@brief	�Q�[�W��ϓ������܂�
void	GageGui::Fluctuation(const K_Math::Vector3& targetPos)
{
	K_Math::Vector3 vector = targetPos - showLife;
	showLife.x += vector.x / changeAmount;
	showLife.y += vector.y / changeAmount;
}

//!@brief	���Z�b�g
void	GageGui::Reset(GameObject& object)
{
	frame->GetGameObject().SetPos(K_Math::Vector3(0, 670, 0));
	fillAreaBox->GetGameObject().SetPos(K_Math::Vector3(-10, 710, 0));

	frame->GetGameObject().SetAngle(K_Math::Vector3(0, 0, 180));
	fillAreaBox->GetGameObject().SetAngle(K_Math::Vector3(0, 0, 0));

	moveCnt = 0;
	rotateCnt = 0;
	maxShowLife = K_Math::Vector3(927, 710, 0);
	minShowLife = K_Math::Vector3(101, 710, 0);
	showLife = maxShowLife;

	maxMoveCnt = 345;
	maxRotateCnt = 180;
	eventMotion = Ev_Non;
	changeAmount = 50.0f;

	//��
	minLife = object.GetStatus().GetMinLife();
	maxLife = object.GetStatus().GetMaxLife();
	life = object.GetStatus().GetLife();

	eventStartFlag = false;
}


//�R�s�[���֎~���܂�
//GageGui::GageGui(const GageGui& gageGui)
//	: frame("ScreenUI/lifeBar", K_Math::Vector3(0, 720, 0), K_Math::Box2D(0, 0, 1095, 270))
//	, fillAreaBox("ScreenUI/greenBar", K_Math::Vector3(0, 720, 0), K_Math::Box2D(0, 0, 64, 64))
//{
//
//}
GageGui& GageGui::operator=(const GageGui& gageGui)
{
	return *this;
}