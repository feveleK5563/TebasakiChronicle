#include "Sound.h"

SoundEngine::SoundEngine()
{
	GetK_AudioSoundClass();
}


K_Audio::SoundSource * SoundEngine::GetSource(const char * sourceName)
{
	return GetK_AudioSoundClass()->GetSource(sourceName);
}

SoundEngine::~SoundEngine()
{

}

K_Audio::SoundClass* SoundEngine::GetK_AudioSoundClass()
{
	static std::unique_ptr<K_Audio::SoundClass> soundClass(new K_Audio::SoundClass());
	return soundClass.get();
}

void SoundEngine::AddSource(Sound& source)
{
	GetK_AudioSoundClass()->CreateSource(source.GetName().c_str(), source.GetPath().c_str(), source.GetMode());
	K_Audio::SoundSource* sound = GetK_AudioSoundClass()->GetSource(source.GetName().c_str());
	source.SetSource(sound);
}

void SoundEngine::DeleteSound(const char*  sourceName)
{
	GetK_AudioSoundClass()->DeleteSource(sourceName);
}



Sound::Sound()
{
	soundSource = nullptr;
}

Sound::~Sound()
{
	
}

void Sound::LoadSound(const char* soundName, const char* path, K_Audio::SoundSource::LoadMode mode)
{
	this->name = soundName;
	this->path = path;
	this->mode = mode;
}

void Sound::Play(bool isLoop, float gain)
{
	soundSource->SetVolume(gain);
	soundSource->Play(isLoop);
}

void Sound::PlaySE(float gain)
{
	soundSource->SetVolume(gain);
	soundSource->PlayCopy();
}

void Sound::Stop()
{
	soundSource->Stop();
}

void Sound::Pause()
{
	soundSource->Pause();
}

bool Sound::IsPlay()
{
	return soundSource->IsPlay();
}

void Sound::SetSource(K_Audio::SoundSource* sound)
{
	soundSource = sound;
}
