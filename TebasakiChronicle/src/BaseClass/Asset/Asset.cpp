#include "Asset.h"

//!@brief	�R���X�g���N�^
//!@param[in]	filePath	�t�@�C���p�X��(.txt�Ȃ�)
Asset::Asset(const std::string& filePath)
{
	Load(filePath);
}
//!@brief	�f�X�g���N�^
Asset::~Asset()
{
	for (auto it : source)
	{
		soundEngine.DeleteSound(it->GetName().c_str());
		delete it;
		it = nullptr;
	}
}

//!@brief	�T�E���h�̎擾
//!@param[in]	soundName	�ݒ肵���T�E���h��
//!@return	Sound�̎Q��
Sound&	Asset::GetSound(const std::string& soundName)
{
	for (auto it : source)
	{
		if ((*it).GetName() == soundName)
		{
			return *it;
		}
	}
}

//!@brief	�t�@�C�����[�h
bool	Asset::Load(const std::string& filePath)
{
	std::stringstream	ss(filePath);
	std::string	line;
	
	while (std::getline(ss, line))
	{
		std::string name;
		std::string path;
		//�R�����g�A�E�g(/)�������玟�̍s��
		if (line.find_first_of("/")) { continue; }
		//�J���}�������當������؂�
		if (line.find(",") != std::string::npos)
		{
			ss >> name;
		}
		ss >> path;

		source.push_back(new Sound());
		(*source.data())->LoadSound(name.c_str(), path.c_str(), ALLREAD);
	}
	return true;
}
