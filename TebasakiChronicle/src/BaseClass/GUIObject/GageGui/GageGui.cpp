#include "GageGui.h"
#include "CameraList.h"
#include "../src/BaseClass/Input/Input.h"
#include "../../../CSTList.h"

//!@brief	コンストラクタ
GageGui::GageGui(GameObject& object)
{
	CST::LoadAndGetTexture("LifeBar", "data/image/ScreenUI/LifeBar.png");
	CST::LoadAndGetTexture("enemyGageBar", "data/image/ScreenUI/enemyGageBar.png");

	frame = new GUIObject("LifeBar", K_Math::Vector3(0, 670, 0), K_Math::Box2D(0, 0, 1095, 270));
	fillAreaBox = new GUIObject("enemyGageBar", K_Math::Vector3(-10, 710, 0), K_Math::Box2D(0, 0, 128, 256));
	frame->GetGameObject().SetAngle(K_Math::Vector3(0, 0, 180));
	fillAreaBox->GetGameObject().SetAngle(K_Math::Vector3(0, 0, 0));
	//回転軸の変更
	frame->GetGameObject().GetImage().GetNowAnimationCharaChip()->basisRenderPos.x -= frame->GetGameObject().GetImage().GetNowAnimationCharaChip()->chip.w / 2;

	moveCnt = 0;
	rotateCnt = 0;
	maxShowLife = K_Math::Vector3(927, 710, 0);
	minShowLife = K_Math::Vector3(101, 710, 0);	
	showLife = maxShowLife;

	maxMoveCnt = 345;
	maxRotateCnt = 180;
	eventMotion = Ev_Non;
	changeAmount = 50.0f;

	//仮
	minLife = object.GetStatus().GetMinLife();
	maxLife = object.GetStatus().GetMaxLife();
	life = object.GetStatus().GetLife();

	eventStartFlag = false;
}
//!@brief	デストラクタ
GageGui::~GageGui()
{
	CST::DeleteTexture("LifeBar");
	CST::DeleteTexture("enemyGageBar");
}


//!@brief	更新
void		GageGui::UpDate(GameObject& object)
{
	frame->UpDate();
	fillAreaBox->UpDate();

	//イベント
	Think();
	Process();

	//ゲージ処理
	if (eventMotion != Ev_End) { return; }

	//体力情報を取得
	minLife = object.GetStatus().GetMinLife();
	maxLife = object.GetStatus().GetMaxLife();
	life = object.GetStatus().GetLife();

	//描画位置がわかる
	float nowLife = (float)((float)life / (float)maxLife) * abs(maxShowLife.x - 0) + minShowLife.x;

	//ゲージ変動処理
	this->Fluctuation(K_Math::Vector3(nowLife, 710, 0));

	//位置を適用させる
	fillAreaBox->GetGameObject().SetPos(showLife);
	
	//イベントリセット
	if (eventStartFlag)
	{
		//Reset(object);	//今はなし
	}

	//仮ライフ変動
	if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::A))
	{
		if (life > 0)
		{
			life -= 1;
		}
	}
	if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::X))
	{
		if (life < 10)
		{
			life++;
		}
	}
}

//!@brief	描画
void		GageGui::Render()
{
	frame->Render();
	fillAreaBox->Render();
}

//!@brief	イベントを開始する
//!@brief	呼ぶとイベントを開始する
void		GageGui::EventStart()
{
	if (eventMotion == Ev_End || eventMotion == Ev_Non)
	{
		eventStartFlag = true;
	}
}



//!@brief	状態変更部分
void	GageGui::Think()
{
	if (eventMotion == Ev_End) { return; }

	EventMotion	nowEventMotion = eventMotion;
	switch (nowEventMotion) {
	case Ev_Non:
		if (eventStartFlag)
		{
			nowEventMotion = Ev_Begin;
		}
		break;
	case Ev_Begin:
		if (rotateCnt < maxRotateCnt)
		{
			nowEventMotion = Ev_Rotate;
		}
		break;
	case Ev_Move:
		if (moveCnt > maxMoveCnt)
		{
			moveCnt = maxMoveCnt;
			nowEventMotion = Ev_End;
			showLife = K_Math::Vector3(maxShowLife.x + minShowLife.x, 710, 0);
			eventStartFlag = false;
		}
		break;
	case Ev_Rotate:
		if (rotateCnt >= maxRotateCnt)
		{
			rotateCnt = maxRotateCnt;
			nowEventMotion = Ev_Move;
		}
		break;
	case Ev_End:
		break;
	}
	UpDateEventMotion(nowEventMotion);
}

//!@brief	処理部分
void	GageGui::Process()
{
	if (eventMotion == Ev_End)
	{ 
		return; 
	}

	switch (eventMotion){
	case Ev_Non:
		break;
	case Ev_Begin:
		break;
	case Ev_Move:
		moveCnt++;
		fillAreaBox->GetGameObject().GetPos().x += 3.0f;
		break;
	case Ev_Rotate:
		rotateCnt++;
		frame->GetGameObject().GetAngle().z--;
		break;
	case Ev_End:
		break;
	}
}


//!@brief	モーションの更新
//!@param[in]	eventMotion	現在のイベントモーション
void	GageGui::UpDateEventMotion(const EventMotion& eventMotion)
{
	if (this->eventMotion == eventMotion) { return; }
	this->eventMotion = eventMotion;
}


//!@brief	ゲージを変動させます
void	GageGui::Fluctuation(const K_Math::Vector3& targetPos)
{
	K_Math::Vector3 vector = targetPos - showLife;
	showLife.x += vector.x / changeAmount;
	showLife.y += vector.y / changeAmount;
}

//!@brief	リセット
void	GageGui::Reset(GameObject& object)
{
	frame->GetGameObject().SetPos(K_Math::Vector3(0, 670, 0));
	fillAreaBox->GetGameObject().SetPos(K_Math::Vector3(-10, 710, 0));

	frame->GetGameObject().SetAngle(K_Math::Vector3(0, 0, 180));
	fillAreaBox->GetGameObject().SetAngle(K_Math::Vector3(0, 0, 0));

	moveCnt = 0;
	rotateCnt = 0;
	maxShowLife = K_Math::Vector3(927, 710, 0);
	minShowLife = K_Math::Vector3(101, 710, 0);
	showLife = maxShowLife;

	maxMoveCnt = 345;
	maxRotateCnt = 180;
	eventMotion = Ev_Non;
	changeAmount = 50.0f;

	//仮
	minLife = object.GetStatus().GetMinLife();
	maxLife = object.GetStatus().GetMaxLife();
	life = object.GetStatus().GetLife();

	eventStartFlag = false;
}


//コピーを禁止します
//GageGui::GageGui(const GageGui& gageGui)
//	: frame("ScreenUI/lifeBar", K_Math::Vector3(0, 720, 0), K_Math::Box2D(0, 0, 1095, 270))
//	, fillAreaBox("ScreenUI/greenBar", K_Math::Vector3(0, 720, 0), K_Math::Box2D(0, 0, 64, 64))
//{
//
//}
GageGui& GageGui::operator=(const GageGui& gageGui)
{
	return *this;
}