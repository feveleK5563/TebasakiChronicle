#include "ImageManager.h"

//�R���X�g���N�^(�L�����`�b�v���쐬����)
ImageManager::ImageManager(K_Graphics::Texture* tex, bool isde) :
	spobj(new K_Graphics::SpriteObject(tex)),
	animCnt(0.f),
	nowAnimNum(0),
	isDelete(isde) {}

//�f�X�g���N�^
ImageManager::~ImageManager()
{
	delete spobj;

	if (isDelete)
	{
		for (auto it : charaChip)
			delete it;
	}
}

//-----------------------------------------------------------------------------
//�w�肵���ԍ��̃L�����`�b�v���擾
AnimationCharaChip* ImageManager::GetNowAnimationCharaChip()
{
	return charaChip[nowAnimNum];
}

//-----------------------------------------------------------------------------
//�L�����`�b�v���쐬
bool ImageManager::CreateCharaChip(const K_Math::Box2D& src, int sheet, float spd, bool isroop)
{
	if (isDelete)
	{
		charaChip.emplace_back(new AnimationCharaChip(src, sheet, spd, isroop));
		return true;
	}
	return false;
}

//-----------------------------------------------------------------------------
//�L�����`�b�v��ύX
bool ImageManager::ChangeCharaChip(const std::vector<AnimationCharaChip*>& acc)
{
	if (isDelete)
		return false;

	charaChip = acc;
	animCnt = 0.f;
	nowAnimNum = 0;

	return true;
}

//-----------------------------------------------------------------------------
//�A�j���[�V�����̕ύX
void ImageManager::ChangeAnimationPattern(int motionNum, bool timeReset)
{
	if (timeReset &&
		nowAnimNum != motionNum)
		animCnt = 0.f;

	nowAnimNum = motionNum;
}

//-----------------------------------------------------------------------------
//�A�j���[�V����
void ImageManager::Animation()
{
	animCnt += 1.f / charaChip[nowAnimNum]->animSpd;

	//���[�v���Ȃ��ꍇ�͍Ō�̓���Œ�~
	if (charaChip[nowAnimNum]->isAnimRoop == false &&
		(int)animCnt >= fabs(charaChip[nowAnimNum]->chipSheetNum))
	{
		animCnt = fabsf((float)charaChip[nowAnimNum]->chipSheetNum) - 1.f;
	}
}

//-----------------------------------------------------------------------------
//�`��(3D)
void ImageManager::ImageDraw3D(	const K_Math::Vector3&	pos,
								const K_Math::Vector3&	angle,
								const K_Math::Vector3&	scale,
								int						direction)
{
	//�e�N�X�`���̓ǂݍ��݈ʒu�̒���
	K_Math::Box2D src = charaChip[nowAnimNum]->chip;
	if (charaChip[nowAnimNum]->chipSheetNum >= 0)
	{
		src.x += src.w * (int(animCnt) % charaChip[nowAnimNum]->chipSheetNum);
	}
	else
	{
		src.x -= src.w * (int(animCnt) % charaChip[nowAnimNum]->chipSheetNum);
	}
	spobj->controlPoint = K_Math::Vector2(src.w / 2.f, src.h / 2.f);	//�`���ʒu���e�N�X�`���̒��S�ɐݒ�(�f�t�H���g)
	spobj->controlPoint += charaChip[nowAnimNum]->basisRenderPos;		//���S����`���ʒu�����炷

	//�摜�̌����𒲐�
	K_Math::Vector3 anglec = angle;
	anglec.y += K_Math::DegToRad((float)direction);

	CST::GetShaderClass(0)->UseShader();
	spobj->Draw3D(
		CST::GetPerspectiveCamera(),
		CST::GetShaderClass(0),
		src,
		pos,
		anglec,
		scale);
}

//-----------------------------------------------------------------------------
//�`��(2D)
void ImageManager::ImageDraw2D(	const K_Math::Vector3&	pos,
								const K_Math::Vector3&	angle,
								const K_Math::Vector3&	scale,
								int						direction)
{
	//�e�N�X�`���̓ǂݍ��݈ʒu�̒���
	K_Math::Box2D src = charaChip[nowAnimNum]->chip;
	if (charaChip[nowAnimNum]->chipSheetNum >= 0)
	{
		src.x += src.w * (int(animCnt) % charaChip[nowAnimNum]->chipSheetNum);
	}
	else
	{
		src.x -= src.w * (int(animCnt) % charaChip[nowAnimNum]->chipSheetNum);
	}
	spobj->controlPoint = K_Math::Vector2(src.w / 2.f, src.h / 2.f);	//�`���ʒu���e�N�X�`���̒��S�ɐݒ�(�f�t�H���g)
	spobj->controlPoint += charaChip[nowAnimNum]->basisRenderPos;		//���S����`���ʒu�����炷

	K_Math::Box2D draw = src;
	draw.x = (int)pos.x;
	draw.y = (int)pos.y;

	CST::GetShaderClass(0)->UseShader();
	spobj->Draw2D(
		CST::GetOrthoCamera(),
		CST::GetShaderClass(0),
		src,
		draw,
		angle.z);
}