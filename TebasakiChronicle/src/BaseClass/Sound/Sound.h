#pragma once
#include "K_Audio\SoundSource.h"
#include "SoundClass.h"
#include <string>
#define STREAMING K_Audio::SoundSource::LoadMode::Streaming
#define ALLREAD K_Audio::SoundSource::LoadMode::AllRead

//板倉ライブラリサウンドクラスラッピング

//サウンドクラス
//サウンドソースを扱います。
//再生などの処理はこのクラスが行います
//デストラクタで死にます
 class Sound
{
private:

	K_Audio::SoundSource* soundSource;
	K_Audio::SoundSource::LoadMode mode;
	std::string name;
	std::string path;

public:
	Sound();
	~Sound();

	inline std::string GetName()
	{
		return name;
	}
	inline std::string GetPath()
	{
		return path;
	}
	inline K_Audio::SoundSource::LoadMode GetMode()
	{
		return mode;
	}
	//サウンドをロードする
	//1,名前 2,パス 3,読み込みのタイプ
	//void
	void LoadSound(const char* soundName,const char* path, K_Audio::SoundSource::LoadMode mode = STREAMING);
	
	//サウンドを再生する
	//1,ループフラグ(デフォルトでON) 2,音量(0~1.0f,デフォルトで1.0f)
	//void
	void Play(bool isLoop = true, float gain = 1.0f);

	//多重再生可能なサウンドを再生する。
	//1,音量(0~1.0f,デフォルトで1.0f)
	//void
	void PlaySE(float gain = 1.0f);

	//サウンドの停止、再開する場合は最初から
	//なし
	//void
	void Stop();

	//サウンドの一時停止
	//なし
	//void
	void Pause();

	//サウンドが再生中かどうか
	//なし
	//bool
	bool IsPlay();
	
	//サウンドソースをセットする。
	//1,K_Audio::SoundSource*
	//void
	void SetSource(K_Audio::SoundSource* sound);

};

 //サウンドエンジンクラス
 //サウンドクラスの管理を行います
 //明示的にDeleteSoundメソッドを呼ばなくても解放は行われます。
 //AddSourceでSoundを登録して下さい
class SoundEngine final
{
private:
	K_Audio::SoundSource* GetSource(const char*  sourceName);
	
	//K_Audio::SoundClassのインスタンスを得る
	static K_Audio::SoundClass* GetK_AudioSoundClass();
public:
	SoundEngine(const SoundEngine&) = delete;		//コピー禁止
	SoundEngine();
	~SoundEngine();

	//サウンドソースを登録し、再生可能な状態にする
	//1,サウンドソース
	//void
	void AddSource(Sound& sound);

	//引数で指定したサウンドソースを破棄
	//1,サウンドソース名
	//void
	void DeleteSound(const char*  sourceName);

};