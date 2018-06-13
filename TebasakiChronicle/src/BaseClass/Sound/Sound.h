#include "K_Audio\SoundSource.h"
#include "SoundClass.h"
#include <string>
#define STREAMING K_Audio::SoundSource::LoadMode::Streaming
#define ALLREAD K_Audio::SoundSource::LoadMode::AllRead

//�q���C�u�����T�E���h�N���X���b�s���O

//�T�E���h�N���X�̏������B�����΂����̂łŃV���O���g��
//�f�X�g���N�^���f�X�g���C�Ŏ��ɂ܂�

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
	//�T�E���h�����[�h����
	//1,���O 2,�p�X 3,�ǂݍ��݂̃^�C�v
	//void
	void LoadSound(const char* soundName,const char* path, K_Audio::SoundSource::LoadMode mode = STREAMING);
	
	//�T�E���h���Đ�����
	//1,���[�v�t���O(�f�t�H���g��ON) 2,����(0~1.0f,�f�t�H���g��1.0f)
	//void
	void Play(bool isLoop = true, float gain = 1.0f);

	//���d�Đ��\�ȃT�E���h���Đ�����B
	//1,����(0~1.0f,�f�t�H���g��1.0f)
	//void
	void PlaySE(float gain = 1.0f);

	//�T�E���h�̒�~�A�ĊJ����ꍇ�͍ŏ�����
	//�Ȃ�
	//void
	void Stop();

	//�T�E���h�̈ꎞ��~
	//�Ȃ�
	//void
	void Pause();

	//�T�E���h���Đ������ǂ���
	//�Ȃ�
	//bool
	bool IsPlay();
	
	//�T�E���h�\�[�X���Z�b�g����B
	//1,K_Audio::SoundSource*
	//void
	void SetSource(K_Audio::SoundSource* sound);

};


class SoundEngine final
{
private:
	K_Audio::SoundSource* GetSource(const char*  sourceName);
	

public:
	SoundEngine(const SoundEngine&) = delete;		//�R�s�[�֎~
	SoundEngine();
	~SoundEngine();


	//�C���X�^���X�𓾂�
	static K_Audio::SoundClass* Create();

	//�T�E���h�\�[�X��o�^���A�Đ��\�ȏ�Ԃɂ���
	void AddSource(Sound&);

	//�����Ŏw�肵���T�E���h�\�[�X��j��
	//1,�T�E���h�\�[�X��
	//void
	void DeleteSound(const char*  sourceName);

};