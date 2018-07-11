#pragma once
#include "../../src/BaseClass/Sound/Sound.h"
#include <sstream>

//--------------------------------------------------------------
//!@class		Asset
//!@brief	�A�Z�b�g���t�@�C�����烍�[�h���ă��\�[�X��ݒ肷��
//!@brief	�܂����̃N���X�̋@�\���Ăяo��
//--------------------------------------------------------------
class Asset
{
public:
	//!@brief	�R���X�g���N�^
	//!@param[in]	filePath	�t�@�C���p�X��(.txt�Ȃ�)
	Asset(const std::string& filePath);
	//!@brief	�f�X�g���N�^
	~Asset();
public:
	//!@brief	�T�E���h�̎擾
	//!@param[in]	soundName	�ݒ肵���T�E���h��
	//!@return	Sound�̎Q��
	Sound&	GetSound(const std::string& soundName);
private:
	//!@brief	�t�@�C�����[�h
	bool	Load(const std::string& filePath);

private:
	SoundEngine			soundEngine;
	std::vector<Sound*>	source;
};