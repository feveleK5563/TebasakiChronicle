#include "Asset.h"
#include "../src/Helper.h"

//!@brief	�R���X�g���N�^
//!@param[in]	filePath	�t�@�C���p�X��(.txt�Ȃ�)
Asset::Asset(const std::string& filePath)
{
	Load(filePath);
}
//!@brief	�f�X�g���N�^
Asset::~Asset()
{
	for (auto& it : source)
	{
		soundEngine.DeleteSound((*it).GetName().c_str());
		Memory::SafeDelete(it);
	}
}

//!@brief	�T�E���h�̎擾
//!@param[in]	soundName	�ݒ肵���T�E���h��
//!@return	Sound�̎Q��
Sound&	Asset::GetSound(const std::string& soundName)
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

//!@brief	�t�@�C�����[�h
bool	Asset::Load(const std::string& filePath)
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
		if (str.find_first_of("/") == std::string::npos)
		{
			continue;
		}
		size_t num = str.find(",");
		name = str.substr(0,num);
		path = str.substr(num+1);
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

	return true;
}
