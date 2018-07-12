#pragma once
#include "../../src/BaseClass/Sound/Sound.h"
#include "../../src/Effect/Effect.h"
#include <sstream>

class AssetCreator;
class AssetSound;
class AssetEffect;

//--------------------------------------------------------------
//!@class		Asset
//!@brief	アセットをファイルからロードしてリソースを設定する
//!@brief	またそのクラスの機能を呼び出す
//--------------------------------------------------------------
class Asset
{
public:
	//!@brief	コンストラクタ
	//!@param[in]	assetCreator	サウンドアセット
	Asset(AssetSound* assetSound);
	//!@brief	コンストラクタ
	//!@param[in]	assetEffect	エフェクトアセット
	Asset(AssetEffect* assetEffect);
	//!@brief	デストラクタ
	~Asset();
public:
	//!@brief	サウンドの取得
	//!@param[in]	soundName	設定したサウンド名
	//!@return	Soundの参照
	Sound&			GetSound(const std::string& soundName);
	//!@brief	エフェクトの取得
	//!@param[in]	effectID	設定したエフェクトID
	//!@return	effectの参照
	EffectManager&	GetEffect(const int effectID);
public:
	//!@brief	サウンドファイルのロード
	//!@param[in]	filePath	ファイルパス名(.txt)
	bool	LoadSound(const std::string& filePath);
	//!@brief	エフェクトファイルのロード
	//!@param[in]	filePath	ファイルパス名(.txt)
	bool	LoadEffect(const std::string& filePath);

private:
	//!@brief	サウンドアセットの取得
	AssetSound&		GetAssetSound();
	//!@brief	エフェクトアセットの取得
	AssetEffect&	GetAsestEffect();

private:
	AssetSound*		assetSound;
	AssetEffect*	assetEffect;
};


//-----------------------------------------------------
class AssetCreator
{
public:
	//!@brief	デストラクタ
	virtual ~AssetCreator();
public:
	//!@brief	ファイルのロード
	//!@param[in]	filePath	ファイルパス(.txt)
	//!@return	true:成功 false:失敗
	virtual bool	Load(const std::string& filePath) = 0;
};


//-----------------------------------------------------
class AssetSound : public AssetCreator
{
public:
	//!@brief	コンストラクタ
	AssetSound(const std::string& filePath);
	//!@brief	デストラクタ
	~AssetSound();
public:
	//!@brief	ファイルのロード
	//!@param[in]	filePath	ファイルパス(.txt)
	//!@return	true:成功 false:失敗
	bool	Load(const std::string& filePath);
	//!@brief	サウンドの取得
	Sound&	GetSound(const std::string& soundName) const;

private:
	SoundEngine			soundEngine;
	std::vector<Sound*>	source;
};

//------------------------------------------------------
class AssetEffect : public AssetCreator
{
public:
	//!@brief	コンストラクタ
	AssetEffect(const std::string& filePath);
	//!@brief	デストラクタ
	~AssetEffect();
public:
	//!@brief	ファイルのロード
	//!@param[in]	filePath	ファイルパス(.txt)
	//!@return	true:成功 false:失敗
	bool	Load(const std::string& filePath);
	//!@brief	エフェクトの取得
	EffectManager&	GetEffect(const int effectID) const;
private:
	EffectManager*	effect;
};