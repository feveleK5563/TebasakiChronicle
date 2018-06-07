#include "DataGui.h"
#include "../src/Helper.h"

//!@brief	コンストラクタ
DataGui::DataGui(GameObject& gameObj)
{
	lifeNeedle = new GUIObject("ScreenUI/Life針", K_Math::Vector3(30, 145, 0), K_Math::Box2D(0, 0, 67, 120));

	minAngle = 180;		//lifeが0のとき180になる
	maxAngle = -180;	//lifeがmaxのとき-180の向き
	angle = maxAngle;
	raito = 0.0f;

	life = gameObj.GetLife();
	life = 9;
	maxLife = gameObj.GetStatus().GetMaxLife();
	timeCnt = 0;
	upDataFlag = true;
}

//!@brief	デストラクタ
DataGui::~DataGui()
{
	Memory::SafeDelete(lifeNeedle);
}

//!@brief	更新
void	DataGui::UpDate()
{
	if (upDataFlag)
	{
		lifeNeedle->GetGameObject().SetAngle(K_Math::Vector3(0, 0, angle + raito));
		lifeNeedle->UpDate();
	}
}

//!@brief	描画
void	DataGui::Render()
{
	lifeNeedle->Render();
}


//!@brief	割合の計算
//!@param[in]	gameObj	ゲームオブジェクト
void	DataGui::Raito(GameObject& gameObj)
{
	life = gameObj.GetLife();
	maxLife = gameObj.GetStatus().GetMaxLife();

	raito = life / maxLife * 180;
	//範囲制御
	if (raito > 180 || raito < 0)
	{
		raito = 0;
		upDataFlag = false;
	}
	
}

//仮のライフ処理
void	DataGui::RaitoRaito()
{
	timeCnt++;
	if (timeCnt >= 60)
	{
		life--;
		timeCnt = 0;
	}
	
	raito = ((float)life / (float)maxLife) * 180.0f;
	//範囲制御
	if (raito > 180 || raito < 0)
	{
		raito = 0;
		upDataFlag = false;
	}
}