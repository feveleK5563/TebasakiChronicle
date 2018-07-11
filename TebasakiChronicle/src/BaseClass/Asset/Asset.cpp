#include "Asset.h"

//!@brief	コンストラクタ
//!@param[in]	filePath	ファイルパス名(.txtなど)
Asset::Asset(const std::string& filePath)
{
	Load(filePath);
}
//!@brief	デストラクタ
Asset::~Asset()
{
	for (auto it : source)
	{
		soundEngine.DeleteSound(it->GetName().c_str());
		delete it;
		it = nullptr;
	}
}

//!@brief	サウンドの取得
//!@param[in]	soundName	設定したサウンド名
//!@return	Soundの参照
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

//!@brief	ファイルロード
bool	Asset::Load(const std::string& filePath)
{
	std::stringstream	ss(filePath);
	std::string	line;
	
	while (std::getline(ss, line))
	{
		std::string name;
		std::string path;
		//コメントアウト(/)が来たら次の行へ
		if (line.find_first_of("/")) { continue; }
		//カンマが来たら文字を区切る
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
