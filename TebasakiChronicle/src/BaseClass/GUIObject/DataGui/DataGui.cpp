#include "DataGui.h"
#include "../src/Helper.h"

//!@brief	コンストラクタ
DataGui::DataGui(GameObject& gameObj)
{
	lifeNeedle = new GUIObject("ScreenUI/Life針", K_Math::Vector3(31, 155, 0), K_Math::Box2D(0, 0, 67, 120));

	minAngle = 0;		//lifeが0のとき180になる
	maxAngle = 180;		//lifeがmaxのとき-180の向き

	//ライフの最大(hp:10)がangle0
	//ライフの最小(hp:0)がangle180
	life = gameObj.GetLife();
	maxLife = gameObj.GetStatus().GetMaxLife();
	timeCnt = 0;
	
	life = 10;
	maxLife = 10;
	raito = minAngle;
	showLife = K_Math::Vector3(0, 0, raito);
	changeAmount = 50.0f;
	offsetAngle = 180.0f;
}

//!@brief	デストラクタ
DataGui::~DataGui()
{
	Memory::SafeDelete(lifeNeedle);
}

//!@brief	更新
void	DataGui::UpDate()
{
	lifeNeedle->GetGameObject().SetAngle(showLife);
	lifeNeedle->UpDate();
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

	raito = (float)((float)life / (float)maxLife) * abs(minAngle - maxAngle) - offsetAngle;

	//ゲージ変動
	Fluctuation(K_Math::Vector3(0, 0, raito));
}

//仮のライフ処理
void	DataGui::RaitoRaito()
{
	timeCnt++;
	if (timeCnt >= 60)
	{
		if (life > 0)
		{
			life--;
		}
		timeCnt = 0;
	}

	//割合の計算
	raito = (float)((float)life / (float)maxLife) * abs(minAngle - maxAngle) - offsetAngle;
	//ゲージ変動
	this->Fluctuation(K_Math::Vector3(0, 0, raito));
}


//!@brief	針の変動処理
void	DataGui::Fluctuation(const K_Math::Vector3& targetPos)
{
	K_Math::Vector3 vector = targetPos - showLife;
	showLife.z += vector.z / changeAmount;
}