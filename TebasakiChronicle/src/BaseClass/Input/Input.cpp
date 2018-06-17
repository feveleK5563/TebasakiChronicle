#include "Input.h"

//�R���X�g���N�^
Input::Input() : inputClass(nullptr) {}
//�f�X�g���N�^
Input::~Input()
{
}

//----------------------------------------------------
//�C���X�^���X�̎擾
//----------------------------------------------------
Input*	Input::GetInstance()
{
	static Input inputInstance;
	return &inputInstance;
}

Input*	input = Input::GetInstance();



//InputClass�̎擾
K_Input::InputClass*	Input::GetInput()
{
	return inputClass;
}

//InputClass�̃Z�b�g
void	Input::SetInputClass(InputClass* input)
{
	this->inputClass = input;
}


//-----------------------------------------------------------------------
//�֐��Q
//-----------------------------------------------------------------------
namespace INPUT
{
	//InputClass�̐ݒ�
	void	SetInputClass(InputClass* inputClass)
	{
		input->inputClass = inputClass;
		//input->SetInputClass(inputClass);
	}
	
	//�Q�[���p�b�h�̒ǉ�
	bool	AddGamePad(const VpadIndex& padID)
	{
		input->GetInput()->AddGamePad(padID);
		return true;
	}

	//���݂̃Q�[���p�b�h�̎擾
	VirtualGamePad*	GetPad(const VpadIndex& padID)
	{
		return input->GetInput()->GetPad(padID);
	}

	//------------------------------------------------------
	//�ݒ菈��
	//------------------------------------------------------
	//�{�^���̊��蓖�Ă̐ݒ�
	void	SetButtonConfig(const VpadIndex& padID, const K_Input::VpadButton& padBtn, const K_Input::JoyButton& joyBtn, const K_Input::Key& keyBtn)
	{
		GetPad(padID)->SetButtonConfig(padBtn, joyBtn, keyBtn);
	}

	//�X�e�B�b�N�̎��̐ݒ�
	void	SetAxisConfig(const VpadIndex& padID, const K_Input::VpadAxis& axis1, const K_Input::JoyAxis& axis2, const K_Input::Key& key1, const K_Input::Key& key2)
	{
		GetPad(padID)->SetAxisConfig(axis1, axis2, key1, key2);
	}

	//�X�e�B�b�N�̐ݒ�
	void	SetStickConfig(const VpadIndex& padID, const K_Input::VpadStick& stick, const K_Input::VpadAxis& axis0, const K_Input::VpadAxis& axis1)
	{
		GetPad(padID)->SetStickConfig(stick, axis0, axis1);
	}

	//�X�e�B�b�N�̌X���x��Ԃ�
	float	GetStickPower(const VpadIndex& padID, const K_Input::VpadStick& padStick)
	{
		return GetPad(padID)->GetStickPower(padStick);
	}

	//�X�e�B�b�N�̊p�x��Ԃ�
	//�E������0�x�Ƃ�����]�x
	float	GetStickRotation(const VpadIndex& padID, const K_Input::VpadStick& padStick)
	{
		return GetPad(padID)->GetStickRotation(padStick);
	}

	//------------------------------------------------------------------------
	//�{�^�����菈��
	//------------------------------------------------------------------------
	//�����ꂽ�Ƃ�,true
	bool	IsPressButton(const VpadIndex& padID, const VpadButton& button)
	{
		if (GetPad(padID)->IsPressButton(button)) { return true; }
		return false;
	}
	//�����Ă����,true
	bool	IsStayButton(const VpadIndex& padID, const VpadButton& button)
	{
		if (GetPad(padID)->IsStayButton(button)) { return true; }
		return false;
	}
	//�����ꂽ�Ƃ�,true
	bool	IsReaveButton(const VpadIndex& padID, const VpadButton& button)
	{
		if (GetPad(padID)->IsReaveButton(button)) { return true; }
		return false;
	}

	//----------------------------------------------------------------------
	//�f�t�H���g�ݒ�
	//----------------------------------------------------------------------
	//�f�t�H���g�̃{�^���z�u�Ȃǂ�ݒ肷��
	void	Config(const VpadIndex& padID)
	{
		//�L�[�R���t�B�O�����邱�Ƃœ��͂��󂯎��
		//�X�e�B�b�N��[A,B,X,Y,L1,R1]��[Z,X,C,V,A,S]�ƘA��������
		SetButtonConfig(padID, VpadButton::A, JoyButton::Button0, Key::Z);
		SetButtonConfig(padID, VpadButton::B, JoyButton::Button1, Key::X);
		SetButtonConfig(padID, VpadButton::X, JoyButton::Button2, Key::C);
		SetButtonConfig(padID, VpadButton::Y, JoyButton::Button3, Key::V);
		SetButtonConfig(padID, VpadButton::L1, JoyButton::Button4, Key::A);
		SetButtonConfig(padID, VpadButton::R1, JoyButton::Button5, Key::S);

		//���X�e�B�b�N��Arrow�L�[��A��������
		SetAxisConfig(padID, VpadAxis::Axis0, JoyAxis::Axis0, Key::ArrowRight, Key::ArrowLeft);
		SetAxisConfig(padID, VpadAxis::Axis1, JoyAxis::Axis1, Key::ArrowUp, Key::ArrowDown);

		//���z�Q�[���p�b�h�̎������蓖�Ă�
		SetStickConfig(padID, VpadStick::L, VpadAxis::Axis0, VpadAxis::Axis1);
	}

	//���͏����X�V
	void	Run(const VpadIndex& padID)
	{
		GetPad(padID)->Run();
	}

	//�f�t�H���g��Input�𐶐�����
	void	Create(const VpadIndex& padID)
	{
		AddGamePad(padID);
		Config(padID);
	}
}