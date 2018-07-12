#include "Asset.h"
#include "../src/Helper.h"


//!@brief	�R���X�g���N�^
//!@param[in]	assetCreator	��������A�Z�b�g
Asset::Asset(AssetSound* assetSound)
{
	this->assetSound = assetSound;
}
Asset::Asset(AssetEffect* assetEffect)
{
	this->assetEffect = assetEffect;
}

//!@brief	�f�X�g���N�^
Asset::~Asset()
{
	Memory::SafeDelete(assetSound);
	Memory::SafeDelete(assetEffect);
}


//!@brief	�T�E���h�̎擾
//!@param[in]	soundName	�ݒ肵���T�E���h��
//!@return	Sound�̎Q��
Sound&	Asset::GetSound(const std::string& soundName)
{
	return assetSound->GetSound(soundName);
}

//!@brief	�G�t�F�N�g�̎擾
//!@param[in]	effectID	�ݒ肵���G�t�F�N�gID
//!@return	effect�̎Q��
EffectManager&	Asset::GetEffect(const int effectID)
{
	return assetEffect->GetEffect(effectID);
}

//!@brief	�t�@�C�����[�h
//!@param[in]	filePath	�t�@�C���p�X��(.txt)
bool	Asset::LoadSound(const std::string& filePath)
{
	if (assetSound == nullptr)
	{
		assetSound = new AssetSound(filePath);
	}
	return true;
}

//!@brief	�G�t�F�N�g�t�@�C���̃��[�h
//!@param[in]	filePath	�t�@�C���p�X��(.txt)
bool	Asset::LoadEffect(const std::string& filePath)
{
	if (assetEffect == nullptr)
	{
		assetEffect = new AssetEffect(filePath);
	}
	return true;
}


//!@brief	�T�E���h�A�Z�b�g�̎擾
AssetSound&		Asset::GetAssetSound()
{
	return *assetSound;
}
//!@brief	�G�t�F�N�g�A�Z�b�g�̎擾
AssetEffect&	Asset::GetAsestEffect()
{
	return *assetEffect;
}



//------------------------------------------------------
//!@brief	�f�X�g���N�^
AssetCreator::~AssetCreator() {}

//------------------------------------------------------
AssetSound::AssetSound(const std::string& filePath)
{
	Load(filePath);
}

AssetSound::~AssetSound()
{
	for (auto& it : source)
	{
		soundEngine.DeleteSound((*it).GetName().c_str());
		Memory::SafeDelete(it);
	}
}

bool	AssetSound::Load(const std::string& filePath)
{
	std::ifstream	stream(filePath);
	std::string	str;
	std::string name;
	std::string path;

	if (stream.fail())
	{
		return false;
	}
	int cnt = 0;
	//1�s�̓ǂݍ���
	while (std::getline(stream, str))
	{
		//�R�����g�A�E�g(/)�������玟�̍s��
		if (str.at(0) == '/')
		{
			continue;
		}
		size_t num = str.find(",");
		name = str.substr(0, num);
		path = str.substr(num + 1);
		//�T�E���h�̃��[�h
		source.emplace_back(new Sound());
		source[cnt]->LoadSound(name.c_str(), path.c_str(), ALLREAD);
		cnt++;
	}

	//�T�E���h���G���W���ɒǉ�
	for (auto it = source.begin(); it != source.end(); ++it)
	{
		soundEngine.AddSource(**it);
	}
	stream.close();
	return true;
}

//!@brief	�A�Z�b�g�̎擾
Sound&	AssetSound::GetSound(const std::string& soundName) const
{
	int cnt = 0;
	for (auto it : source)
	{
		if ((*it).GetName() == soundName)
		{
			break;
		}
		cnt += 1;
	}
	return *source[cnt];
}


//-----------------------------------------------------------------
//!@brief	�R���X�g���N�^
AssetEffect::AssetEffect(const std::string& filePath)
{
	effect = EffectManager::GetInstance();
	Load(filePath);
}
//!@brief	�f�X�g���N�^
AssetEffect::~AssetEffect()
{
	effect->AllDeleteEffect();
}
//!@brief	�t�@�C���̃��[�h
//!@param[in]	filePath	�t�@�C���p�X(.txt)
//!@return	true:���� false:���s
bool	AssetEffect::Load(const std::string& filePath)
{
	std::ifstream	stream(filePath);
	std::string		line;
	int				effectID = -1;	//�G�t�F�N�gID
	std::string		textureName;	//�e�N�X�`����
	std::string		texturePath;	//�e�N�X�`���p�X
	K_Math::Box2D	chip;			//�`�b�v
	int				sheet;			//�V�[�g��
	float			animSpeed;		//�A�j���[�V�����X�s�[�h
	bool			animLoop;		//�A�j���[�V���������[�v�����邩
	int				endTime;		//�I������

	if (stream.fail())
	{
		return false;
	}
	while (std::getline(stream, line))
	{
		//�R�����g�A�E�g(/)�������玟�̍s��
		if (line.at(0) == '/')
		{
			continue;
		}
		//�g�[�N�����󔒂ɂ���
		std::string::size_type token;
		while ((token = line.find_first_of("(,);")) != std::string::npos)
		{
			line[token] = ' ';
		}
		//�󔒂ɓK�p�����������ǂ݂���
		std::stringstream ss;
		ss << line;
		//�ǂݍ���
		ss >> effectID;
		ss >> textureName;
		ss >> texturePath;
		ss >> chip.x >> chip.y >> chip.w >> chip.h;
		ss >> sheet;
		ss >> animSpeed;
		ss >> animLoop;
		ss >> endTime;

		//�G�t�F�N�g�쐬
		effect->CreateEffectData(static_cast<EffectName>(effectID), textureName, texturePath, new AnimationCharaChip(chip, sheet, animSpeed, animLoop), endTime);
	}
	stream.close();
	return true;
}
//!@brief	�A�Z�b�g�̎擾
EffectManager&	AssetEffect::GetEffect(const int effectID) const
{
	return *effect;
}