#include "TemporaryCollision.h"

//コンストラクタ
//コリジョンの形状情報をdeleteする
TemporaryCollision::TemporaryCollision(	K_Physics::CollisionShape*	shape,
										CollisionMask&				mmask,
										CollisionMask&				gmask,
										K_Math::Vector3&			setpos,
										K_Math::Vector3&			movevec,
										Status::Direction&			dir,
										int							damage,
										int							deletetime,
										bool						ishitground,
										bool						doground):
	cShape(shape),
	deleteTime(deletetime),
	isHitGround(ishitground)
{
	colmanager.CreateGroundCollisionData(shape, setpos, K_Math::Vector3(0, 0, 0), doground);
	colmanager.CreateSubCollisionData(shape, mmask, gmask, K_Math::Vector3(0, 0, 0));

	gameObject.GetStatus().SetStatusData(
		Status::State::Active,
		setpos,
		K_Math::Vector3(0, 0, 0),
		K_Math::Vector3(1, 1, 1),
		dir,
		damage,
		0);

	colmanager.SetSubCollisionTug(0, &gameObject.GetState());
}

//コンストラクタ
//コリジョンの形状情報をdeleteしない(そもそも所有させない)
TemporaryCollision::TemporaryCollision(	K_Physics::CollisionData*	basedata,
										K_Physics::CollisionData*	subdata,
										K_Math::Vector3&			setpos,
										K_Math::Vector3&			moveVec,
										Status::Direction&			dir,
										int							damage,
										int							deletetime,	
										bool						ishitground):
	cShape(nullptr),
	deleteTime(deletetime),
	isHitGround(ishitground)
{
	colmanager.SetBaseCollisionData(basedata, setpos);
	colmanager.SetSubCollisionData(subdata);

	gameObject.GetStatus().SetStatusData(
		Status::State::Active,
		setpos,
		K_Math::Vector3(0, 0, 0),
		K_Math::Vector3(1, 1, 1),
		dir,
		damage,
		0);

	colmanager.SetSubCollisionTug(0, &gameObject.GetState());
}

//デストラクタ
TemporaryCollision::~TemporaryCollision()
{
	if (cShape != nullptr)
	{
		CC::RemoveCollisionShape(&cShape);
	}
}

//-----------------------------------------------------------------------------
//画像管理者を生成し、同時にキャラチップを設定する
void TemporaryCollision::SetImageManagerAndCharaChip(	std::string&			texName,
														K_Graphics::Texture*	texture,
														K_Math::Box2D&			src,
														int						sheet,
														float					spd,
														bool					isroop)
{
	gameObject.SetImage(texName, texture);
	gameObject.GetImage().CreateCharaChip(src, sheet, spd, isroop);
}

//-----------------------------------------------------------------------------
//更新(消滅する際はtrueが返る)
bool TemporaryCollision::Update()
{
	//消滅
	if (Extinction())
	{
		return true;
	}

	//コリジョンの動作
	colmanager.MoveBaseCollision(	gameObject.GetMove().GetMoveVec(),
									gameObject.GetStatus().GetDirection(),
									true);

	//アニメーションの更新
	if (&gameObject.GetImage() != nullptr)
	{
		gameObject.GetImage().Animation();
	}

	return false;
}

//-----------------------------------------------------------------------------
//消滅フラグを立てる
bool TemporaryCollision::Extinction()
{
	if ((gameObject.GetStatus().GetState() != Status::State::Active) ||		//外部によってStateがActive以外にされていたら消滅
		(timeCnt >= deleteTime) ||											//時間経過で消滅
		(isHitGround == true && colmanager.CheckHitBaseCollisionObject()))	//地形と接触して消える場合の判定
	{
		return true;
	}
	++timeCnt;
	
	return false;
}

//-----------------------------------------------------------------------------
//描画
void TemporaryCollision::Render()
{
	//アニメーションの更新
	if (&gameObject.GetImage() != nullptr)
	{
		gameObject.GetImage().ImageDraw3D(	gameObject.GetStatus().GetPos(),
											gameObject.GetStatus().GetAngle(),
											gameObject.GetStatus().GetScale(),
											gameObject.GetStatus().GetDirection());
	}
}