#include "EnemyType.h"

EnemyType::EnemyType(std::string imgName, int ml, int hd) :
	imageName(imgName),
	maxLife(ml),
	hitDamage(hd),
	emSet(new EnemyMoveSet())
{
	//テクスチャを読み込む
	CSTList* cst = CSTList::GetInstance();
	cst->GetTextureList()->LoadTexture(imageName, "data/image/" + imgName + ".tga");
	texture = cst->GetTextureList()->GetTexture(imageName);
}

EnemyType::~EnemyType()
{
	//不要な画像(テクスチャ)を開放する
	CSTList* cst = CSTList::GetInstance();
	cst->GetTextureList()->DeleteTexture(imageName);

	delete emSet;
}
