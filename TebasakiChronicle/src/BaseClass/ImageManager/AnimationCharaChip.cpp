#include "AnimationCharaChip.h"

//コンストラクタ
AnimationCharaChip::AnimationCharaChip(	const K_Math::Box2D& src,
										const int sheet,
										const float spd,
										const bool ir):
			chip(src), chipSheetNum(sheet), animSpd(spd), isAnimRoop(ir) {}

//デストラクタ
AnimationCharaChip::~AnimationCharaChip() {}