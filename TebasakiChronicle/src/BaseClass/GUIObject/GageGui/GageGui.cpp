#include "GageGui.h"
#include "CameraList.h"
#include "../src/BaseClass/Input/Input.h"

//!@brief	コンストラクタ
GageGui::GageGui()
	: frame("ScreenUI/lifeBar", K_Math::Vector3(0, 670, 0), K_Math::Box2D(0, 0, 1095, 270))
	, fillAreaBox("ScreenUI/enemyBar", K_Math::Vector3(-10, 710, 0), K_Math::Box2D(0, 0, 128, 256))
{
	frame.GetGameObject().SetAngle(K_Math::Vector3(0, 0, 180));
	fillAreaBox.GetGameObject().SetAngle(K_Math::Vector3(0, 0, 0));
	//回転軸の変更
	frame.GetGameObject().GetImage().GetNowAnimationCharaChip()->basisRenderPos.x -= frame.GetGameObject().GetImage().GetNowAnimationCharaChip()->chip.w / 2;

	moveCnt = 0;
	rotateCnt = 0;
	beginCnt = 0;
	maxShowLife = K_Math::Vector3(1028, 710, 0);
	minShowLife = K_Math::Vector3(101, 710, 0);

	maxMoveCnt = 345;	//345
	maxRotateCnt = 180;
	eventMotion = Ev_Non;
	showLife = 1028;
	//仮
	minLife = 0;
	maxLife = 10;
	life = 10;

	timeCnt = 0;

}
//!@brief	デストラクタ
GageGui::~GageGui()
{

}

//!@brief	割合を算出する
void		GageGui::Raito(float maxValue, float nowValue, float raito)
{
	nowGagePos = nowValue / maxValue * raito;
}


//!@brief	位置に割合を適用する
void		GageGui::ProcessPos()
{
	frame.GetGameObject().SetPos(K_Math::Vector3(
		frame.GetGameObject().GetPos().x + nowGagePos,
		frame.GetGameObject().GetPos().y + nowGagePos,
		frame.GetGameObject().GetPos().z + nowGagePos)
	);
}



//!@brief	更新
void		GageGui::UpDate()
{
	frame.UpDate();
	fillAreaBox.UpDate();

	//イベント
	Think();
	Process();

	//ゲージ処理
	if (eventMotion != Ev_End) { return; }

	//life = (float)life / (float)maxLife;
	//描画位置がわかる
	showLife = (float)life / (float)maxLife * (maxShowLife.x - minShowLife.x);	//hpんぼ比率
	float preLife = ((float)life - 1) / (float)maxLife * (maxShowLife.x - minShowLife.x);
	
	fillAreaBox.GetGameObject().SetPos(K_Math::Vector3(showLife, 710, 0));
	//if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::A))
	{
	//	life -= 1;
		//std::cout << "おされた" << std::endl;
	}
}

//!@brief	描画
void		GageGui::Render()
{
	frame.Render();
	fillAreaBox.Render();
}



//!@brief	状態変更部分
void	GageGui::Think()
{
	if (eventMotion == Ev_End) { return; }

	EventMotion	nowEventMotion = eventMotion;
	switch (nowEventMotion) {
	case Ev_Non:
		//ボスが登場したら、Ev_Beginに切り替える
		if (beginCnt >= maxMoveCnt)
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
	if (eventMotion == Ev_End) { return; }

	switch (eventMotion){
	case Ev_Non:
		if (beginCnt < maxMoveCnt)
		{
			beginCnt++;
		}
		break;
	case Ev_Begin:
		break;
	case Ev_Move:
		moveCnt++;
		fillAreaBox.GetGameObject().GetPos().x += 3.0f;
		break;
	case Ev_Rotate:
		rotateCnt++;
		frame.GetGameObject().GetAngle().z--;
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





//コピーを禁止します
GageGui::GageGui(const GageGui& gageGui)
	: frame("ScreenUI/lifeBar", K_Math::Vector3(0, 720, 0), K_Math::Box2D(0, 0, 1095, 270))
	, fillAreaBox("ScreenUI/greenBar", K_Math::Vector3(0, 720, 0), K_Math::Box2D(0, 0, 64, 64))
{

}
GageGui& GageGui::operator=(const GageGui& gageGui)
{
	return *this;
}