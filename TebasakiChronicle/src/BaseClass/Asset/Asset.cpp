#include "Asset.h"
#include "../src/Helper.h"

//!@brief	コンストラクタ
//!@param[in]	filePath	ファイルパス名(.txtなど)
Asset::Asset(const std::string& filePath)
{
	Load(filePath);
}
//!@brief	デストラクタ
Asset::~Asset()
{
	for (auto& it : source)
	{
		soundEngine.DeleteSound((*it).GetName().c_str());
		Memory::SafeDelete(it);
	}
}

//!@brief	サウンドの取得
//!@param[in]	soundName	設定したサウンド名
//!@return	Soundの参照
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

//!@brief	ファイルロード
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
	//1行の読み込み
	while (std::getline(stream, str))
	{
		//コメントアウト(/)が来たら次の行へ
		if (str.find_first_of("/") == std::string::npos)
		{
			continue;
		}
		size_t num = str.find(",");
		name = str.substr(0,num);
		path = str.substr(num+1);
		//サウンドのロード
		source.emplace_back(new Sound());
		source[cnt]->LoadSound(name.c_str(), path.c_str(), ALLREAD);
		cnt++;
	}

	//サウンドをエンジンに追加
	for (auto it = source.begin(); it != source.end(); ++it)
	{
		soundEngine.AddSource(**it);
	}

	return true;
}
