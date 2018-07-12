#pragma once
#include "../../src/BaseClass/Sound/Sound.h"
#include "../../src/Effect/Effect.h"
#include <sstream>

class AssetCreator;
class AssetSound;
class AssetEffect;

//--------------------------------------------------------------
//!@class		Asset
//!@brief	�A�Z�b�g���t�@�C�����烍�[�h���ă��\�[�X��ݒ肷��
//!@brief	�܂����̃N���X�̋@�\���Ăяo��
//--------------------------------------------------------------
class Asset
{
public:
	//!@brief	�R���X�g���N�^
	//!@param[in]	assetCreator	�T�E���h�A�Z�b�g
	Asset(AssetSound* assetSound);
	//!@brief	�R���X�g���N�^
	//!@param[in]	assetEffect	�G�t�F�N�g�A�Z�b�g
	Asset(AssetEffect* assetEffect);
	//!@brief	�f�X�g���N�^
	~Asset();
public:
	//!@brief	�T�E���h�̎擾
	//!@param[in]	soundName	�ݒ肵���T�E���h��
	//!@return	Sound�̎Q��
	Sound&			GetSound(const std::string& soundName);
	//!@brief	�G�t�F�N�g�̎擾
	//!@param[in]	effectID	�ݒ肵���G�t�F�N�gID
	//!@return	effect�̎Q��
	EffectManager&	GetEffect(const int effectID);
public:
	//!@brief	�T�E���h�t�@�C���̃��[�h
	//!@param[in]	filePath	�t�@�C���p�X��(.txt)
	bool	LoadSound(const std::string& filePath);
	//!@brief	�G�t�F�N�g�t�@�C���̃��[�h
	//!@param[in]	filePath	�t�@�C���p�X��(.txt)
	bool	LoadEffect(const std::string& filePath);

private:
	//!@brief	�T�E���h�A�Z�b�g�̎擾
	AssetSound&		GetAssetSound();
	//!@brief	�G�t�F�N�g�A�Z�b�g�̎擾
	AssetEffect&	GetAsestEffect();

private:
	AssetSound*		assetSound;
	AssetEffect*	assetEffect;
};


//-----------------------------------------------------
class AssetCreator
{
public:
	//!@brief	�f�X�g���N�^
	virtual ~AssetCreator();
public:
	//!@brief	�t�@�C���̃��[�h
	//!@param[in]	filePath	�t�@�C���p�X(.txt)
	//!@return	true:���� false:���s
	virtual bool	Load(const std::string& filePath) = 0;
};


//-----------------------------------------------------
class AssetSound : public AssetCreator
{
public:
	//!@brief	�R���X�g���N�^
	AssetSound(const std::string& filePath);
	//!@brief	�f�X�g���N�^
	~AssetSound();
public:
	//!@brief	�t�@�C���̃��[�h
	//!@param[in]	filePath	�t�@�C���p�X(.txt)
	//!@return	true:���� false:���s
	bool	Load(const std::string& filePath);
	//!@brief	�T�E���h�̎擾
	Sound&	GetSound(const std::string& soundName) const;

private:
	SoundEngine			soundEngine;
	std::vector<Sound*>	source;
};

//------------------------------------------------------
class AssetEffect : public AssetCreator
{
public:
	//!@brief	�R���X�g���N�^
	AssetEffect(const std::string& filePath);
	//!@brief	�f�X�g���N�^
	~AssetEffect();
public:
	//!@brief	�t�@�C���̃��[�h
	//!@param[in]	filePath	�t�@�C���p�X(.txt)
	//!@return	true:���� false:���s
	bool	Load(const std::string& filePath);
	//!@brief	�G�t�F�N�g�̎擾
	EffectManager&	GetEffect(const int effectID) const;
private:
	EffectManager*	effect;
};