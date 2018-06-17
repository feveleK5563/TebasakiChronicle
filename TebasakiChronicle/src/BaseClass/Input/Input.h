#pragma once
#include "InputClass.h"

//----------------------------------------------------------------
//Input�N���X
//�T�v:Input�������V���O���g���ɂ��A�ȒP�ɗ��p����
//�����:�����
//----------------------------------------------------------------
using namespace K_Input;
class Input
{
private:
	//-----------------------------------------------------
	//�R���X�g���N�^
	//-----------------------------------------------------
	Input();

	//-----------------------------------------------------
	//�f�X�g���N�^
	//-----------------------------------------------------
	~Input();

public:
	//�C���X�^���X�̎擾
	static Input*	GetInstance();

	//�C���v�b�g�N���X�̎擾
	K_Input::InputClass*	GetInput();
	//�C���v�b�g�N���X�̃Z�b�g
	void	SetInputClass(InputClass* input);
public:
	K_Input::InputClass*	inputClass;
};



//�֐��Q
namespace INPUT
{
	//�C���v�b�g�N���X�̎擾
	void	SetInputClass(InputClass* inputClass);
	//�p�b�h�̒ǉ�
	bool	AddGamePad(const VpadIndex& padID);
	//���݂̃Q�[���p�b�h��Ԃ�
	VirtualGamePad*	GetPad(const VpadIndex& padID);

	//[GamePad],[JoyStick],[Key]�̂��ꂼ��̃{�^���E���E�X�e�B�b�N�̊��蓖��
	void	SetButtonConfig(const VpadIndex& padID, const K_Input::VpadButton& padBtn, const K_Input::JoyButton& joyBtn, const K_Input::Key& keyBtn);
	void	SetAxisConfig(const VpadIndex& padID, const K_Input::VpadAxis& axis1, const K_Input::JoyAxis& axis2, const K_Input::Key& key1, const K_Input::Key& key2);
	void	SetStickConfig(const VpadIndex& padID, const K_Input::VpadStick& stick, const K_Input::VpadAxis& axis0, const K_Input::VpadAxis& axis1);

	//�X�e�B�b�N�̌X���̓x����(0.0f�`1.0f)���擾
	float	GetStickPower(const VpadIndex& padID, const K_Input::VpadStick& padStick);
	//�X�e�B�b�N�̌X��(�E��������0�x)���擾
	float	GetStickRotation(const VpadIndex& padID, const K_Input::VpadStick& padStick);

	//�{�^����Ԕ���p�@[�����ꂽ�Ƃ�],[�����Ă���Ƃ�],[�������Ƃ�]��true��Ԃ�
	bool	IsPressButton(const VpadIndex& padID, const VpadButton& button);
	bool	IsStayButton(const VpadIndex& padID, const VpadButton& button);
	bool	IsReaveButton(const VpadIndex& padID, const VpadButton& button);

	//���͏����X�V
	void	Run(const VpadIndex& padID);

	//�f�t�H���g�ݒ�p
	void	Create(const VpadIndex& padID);
	void	Config(const VpadIndex& padID);
}