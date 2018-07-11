#pragma once
#include "../../src/BaseClass/Sound/Sound.h"
#include <sstream>

//--------------------------------------------------------------
//!@class		Asset
//!@brief	アセットをファイルからロードしてリソースを設定する
//!@brief	またそのクラスの機能を呼び出す
//--------------------------------------------------------------
class Asset
{
public:
	//!@brief	コンストラクタ
	//!@param[in]	filePath	ファイルパス名(.txtなど)
	Asset(const std::string& filePath);
	//!@brief	デストラクタ
	~Asset();
public:
	//!@brief	サウンドの取得
	//!@param[in]	soundName	設定したサウンド名
	//!@return	Soundの参照
	Sound&	GetSound(const std::string& soundName);
private:
	//!@brief	ファイルロード
	bool	Load(const std::string& filePath);

private:
	SoundEngine			soundEngine;
	std::vector<Sound*>	source;
};