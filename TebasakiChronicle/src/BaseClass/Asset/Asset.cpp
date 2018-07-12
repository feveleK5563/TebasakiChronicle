#include "Asset.h"
#include "../src/Helper.h"


//!@brief	コンストラクタ
//!@param[in]	assetCreator	生成するアセット
Asset::Asset(AssetSound* assetSound)
{
	this->assetSound = assetSound;
}
Asset::Asset(AssetEffect* assetEffect)
{
	this->assetEffect = assetEffect;
}

//!@brief	デストラクタ
Asset::~Asset()
{
	Memory::SafeDelete(assetSound);
	Memory::SafeDelete(assetEffect);
}


//!@brief	サウンドの取得
//!@param[in]	soundName	設定したサウンド名
//!@return	Soundの参照
Sound&	Asset::GetSound(const std::string& soundName)
{
	return assetSound->GetSound(soundName);
}

//!@brief	エフェクトの取得
//!@param[in]	effectID	設定したエフェクトID
//!@return	effectの参照
EffectManager&	Asset::GetEffect(const int effectID)
{
	return assetEffect->GetEffect(effectID);
}

//!@brief	ファイルロード
//!@param[in]	filePath	ファイルパス名(.txt)
bool	Asset::LoadSound(const std::string& filePath)
{
	if (assetSound == nullptr)
	{
		assetSound = new AssetSound(filePath);
	}
	return true;
}

//!@brief	エフェクトファイルのロード
//!@param[in]	filePath	ファイルパス名(.txt)
bool	Asset::LoadEffect(const std::string& filePath)
{
	if (assetEffect == nullptr)
	{
		assetEffect = new AssetEffect(filePath);
	}
	return true;
}


//!@brief	サウンドアセットの取得
AssetSound&		Asset::GetAssetSound()
{
	return *assetSound;
}
//!@brief	エフェクトアセットの取得
AssetEffect&	Asset::GetAsestEffect()
{
	return *assetEffect;
}



//------------------------------------------------------
//!@brief	デストラクタ
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
	//1行の読み込み
	while (std::getline(stream, str))
	{
		//コメントアウト(/)が来たら次の行へ
		if (str.at(0) == '/')
		{
			continue;
		}
		size_t num = str.find(",");
		name = str.substr(0, num);
		path = str.substr(num + 1);
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
	stream.close();
	return true;
}

//!@brief	アセットの取得
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
//!@brief	コンストラクタ
AssetEffect::AssetEffect(const std::string& filePath)
{
	effect = EffectManager::GetInstance();
	Load(filePath);
}
//!@brief	デストラクタ
AssetEffect::~AssetEffect()
{
	effect->AllDeleteEffect();
}
//!@brief	ファイルのロード
//!@param[in]	filePath	ファイルパス(.txt)
//!@return	true:成功 false:失敗
bool	AssetEffect::Load(const std::string& filePath)
{
	std::ifstream	stream(filePath);
	std::string		line;
	int				effectID = -1;	//エフェクトID
	std::string		textureName;	//テクスチャ名
	std::string		texturePath;	//テクスチャパス
	K_Math::Box2D	chip;			//チップ
	int				sheet;			//シート数
	float			animSpeed;		//アニメーションスピード
	bool			animLoop;		//アニメーションをループさせるか
	int				endTime;		//終了時間

	if (stream.fail())
	{
		return false;
	}
	while (std::getline(stream, line))
	{
		//コメントアウト(/)が来たら次の行へ
		if (line.at(0) == '/')
		{
			continue;
		}
		//トークンを空白にする
		std::string::size_type token;
		while ((token = line.find_first_of("(,);")) != std::string::npos)
		{
			line[token] = ' ';
		}
		//空白に適用した文字列を読みこむ
		std::stringstream ss;
		ss << line;
		//読み込み
		ss >> effectID;
		ss >> textureName;
		ss >> texturePath;
		ss >> chip.x >> chip.y >> chip.w >> chip.h;
		ss >> sheet;
		ss >> animSpeed;
		ss >> animLoop;
		ss >> endTime;

		//エフェクト作成
		effect->CreateEffectData(static_cast<EffectName>(effectID), textureName, texturePath, new AnimationCharaChip(chip, sheet, animSpeed, animLoop), endTime);
	}
	stream.close();
	return true;
}
//!@brief	アセットの取得
EffectManager&	AssetEffect::GetEffect(const int effectID) const
{
	return *effect;
}