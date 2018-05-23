#include "AnimationCharaChip.h"

//コンストラクタ
AnimationCharaChip::AnimationCharaChip(	const K_Math::Box2D&	src,
										int						sheet,
										float					spd,
										bool					ir,
										const K_Math::Vector2& renderPos) :
	chip(src), chipSheetNum(sheet), animSpd(spd), isAnimRoop(ir), basisRenderPos(renderPos) {}

//デストラクタ
AnimationCharaChip::~AnimationCharaChip() {}