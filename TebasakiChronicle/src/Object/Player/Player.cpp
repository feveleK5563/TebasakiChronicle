#include "Player.h"


//--------------------------------------------------------------
//概要:プレイヤーの実装
//製作者:日比野
//--------------------------------------------------------------

//-----------------------------------------------
//コンストラクタ
//-----------------------------------------------
Player::Player()
{

}

//-----------------------------------------------
//デストラクタ
//-----------------------------------------------
Player::~Player()
{
	delete input;
	delete physics;
	delete collision;
	delete targetTag;
}

//初期化
void	Player::Initliaze()
{
	//オブジェクトの初期化
	//-----まとめて処理をしたい--------
	K_Math::Vector3 vec = { 0,0,0 };
	object.GetStatus()->GetPos() = vec;
	object.GetStatus()->GetAngle() = vec;
	object.GetStatus()->GetScale() = { 1,1,1 };
	object.GetStatus()->GetDirection() = Status::Direction::Left;
	object.GetStatus()->GetAttackPoint() = 1.0f;
	object.GetStatus()->GetLife() = 1.0f;
	object.GetStatus()->GetState() = Status::State::Jump;
	

	//コントローラーの初期化
	controller.SetInput(input);
	//カメラガンの初期化
	cameraGun.Initailize();

	//こりじょんの設定-------------------------------
	//物理を扱うBulletPhysics
	physics = new K_Physics::BulletPhysics();

	//ボックスの形の生成
	shape = physics->CreateBoxShape(10, 10, 1);

	//生成した[形]でコリジョンや剛体を作成
	//K_Physics::RigidBodyData*	rigid = physics->CreateRigidBody(shape, 1.0f, false, 1);
	collision = physics->CreateCollisionObject(shape, false, 1);

	//コリジョンに情報を持たせる
	collision->tag.tagIndex = 2;
	collision->tag.tagName = "Player";
}

//更新
void	Player::UpDate()
{
	//ジャンプボタンを押す
	if (input->GetPad(K_Input::VpadIndex::Pad0)->IsPressButton(K_Input::VpadButton::R1))
	{
		std::cout << "ジャンプボタン" << std::endl;
	}

	//撮影ボタンを押す
	if (input->GetPad(K_Input::VpadIndex::Pad0)->IsStayButton(K_Input::VpadButton::L1))
	{
		cameraGun.active = true;
		K_Math::Vector3 dir;
		if (object.GetDirection() == Status::Direction::Left)
		{
			dir = K_Math::Vector3(-2, 0, 0);
		}
		else
		{
			dir = K_Math::Vector3(2, 0, 0);
		}
		//カメラマーカーを前に飛ばす
		cameraGun.MoveDir(dir);
	}

	//撮影ボタンを離す
	if (input->GetPad(K_Input::VpadIndex::Pad0)->IsReaveButton(K_Input::VpadButton::L1))
	{
		//カメラマーカーをプレイヤーの位置に戻す
		cameraGun.object.SetMoveVec(K_Math::Vector3(0, 0, 0));
		cameraGun.MoveDir(K_Math::Vector3(0, 0, 0));
		cameraGun.active = false;	//非表示
	}

	//左スティックの倒れている深さ
	float stickDepth = input->GetPad(K_Input::VpadIndex::Pad0)->GetStickPower(K_Input::VpadStick::L);
	//右方向を0度とした回転度
	float stickAngle = input->GetPad(K_Input::VpadIndex::Pad0)->GetStickRotation(K_Input::VpadStick::L);

	if (stickDepth != 0)
	{
		if (K_Math::DegToRad(-90) < stickAngle && stickAngle < K_Math::DegToRad(90))
		{
			object.SetDirection(Status::Direction::Right);
		}
		else
		{
			object.SetDirection(Status::Direction::Left);
		}
	}
	//カメラガンの更新
	if (!cameraGun.active)
	{
		//プレイヤーの位置に常についていく
		cameraGun.MoveDir(object.GetMoveVec());
		cameraGun.object.GetPos() += cameraGun.object.GetMoveVec();
		cameraGun.object.GetPos() = object.GetPos();
		//-------------------------------------------
		//コリジョンの位置を設定
		cameraGun.collision->SetCollisionPosition(object.GetPos());
	}
	else
	{
		cameraGun.UpDate();
	}
	std::cout << "カメラコリジョン" << cameraGun.collision->GetCollisionPosition().x() << std::endl;

	
	//コントローラーの更新
	controller.UpDate(object.GetMoveVec());

	//プレイヤーの移動
	//位置の移動
	if (object.GetMoveVec().x() != 0)
	{
		object.GetPos() += object.GetMoveVec();
	}

	physics->MoveCharacter(collision, object.GetMoveVec());
	physics->Run();
}

//描画
void	Player::Render()
{
	cameraGun.Render();
}


//InputClassの取得処理
void	Player::GetInputClass(K_Input::InputClass* input)
{
	this->input = input;
}




