#include "Object3D.h"
#include "../src/BaseClass/Collision/CollisionManager.h"

//!@brief コンストラクタ
//!@param[in] filePath モデルのパス
//!@param[in] texName テクスチャのパス
Object3D::Object3D(const std::string& filePath_, const std::string& texFilePath_,
	const K_Math::Vector3& pos_, const K_Math::Vector3& rotation_, const K_Math::Vector3& scale_)
	: modelData(nullptr), model(nullptr), object(nullptr), decisionObj(nullptr),
	texList(new K_Graphics::TextureList()),
	decisionPos(pos_), decisionRotation(rotation_), decisionScale(scale_),
	filePath(filePath_), texFilePath(texFilePath_)
{
	Load(filePath, texFilePath);
	CreateMeshModel();
	CreateMeshObject();
	CreateDecisionObj();
	SetDecisionParam(decisionPos, decisionRotation, decisionScale);
}

//!@brief デストラクタ
Object3D::~Object3D()
{
	if (model != nullptr)
	{
		delete model;
		model = nullptr;
	}
}

//!@brief モデルのロードとテクスチャのロード
//!@param[in] filePath モデルのパス
//!@param[in] texName テクスチャのパス
//!@return 成功ならtrue
bool	Object3D::Load(const std::string& filePath, const std::string& texFilePath)
{
	//テクスチャの読み込み
	if (!texList->LoadTexture("fbxTex", texFilePath))
	{
		return false;
	}
	//モデルの読み込み
	modelData = factory.LoadFBXModel(filePath, texList);
	return true;
}

//!@brief 地形オブジェクトのパラメータ設定
//!@param[in] decisionPos_ 地形の位置
//!@param[in] decisionAngle_ 地形の向き
//!@param[in] decisionSize_ 地形のサイズ
void	Object3D::SetDecisionParam(const K_Math::Vector3& decisionPos_,
	const K_Math::Vector3& decisionRotation_,
	const K_Math::Vector3& decisionScale_)
{
	decisionPos = decisionPos_;
	decisionRotation = decisionRotation_;
	decisionScale = decisionScale_;
	decisionObj->GetRigidBody()->SetCollisionPosition(decisionPos);
	decisionObj->GetRigidBody()->SetCollisionRotation(decisionRotation);
	decisionObj->SetScaling(decisionScale);
}

//!@brief モデルの描画
void	Object3D::Render()
{
	object->Draw(CST::GetPerspectiveCamera(), CST::GetShaderClass(2),
		decisionPos,
		decisionRotation,
		decisionScale);
}

//!@brief モデルデータをもとにMeshModelクラスを作成
void	Object3D::CreateMeshModel()
{
	model = new K_Graphics::MeshModel(modelData);
}
//!@brief MeshModelを扱いやすくするMeshObjectクラスを作成
void	Object3D::CreateMeshObject()
{
	object = new K_Graphics::MeshObject(model);
}

//!@brief 地形オブジェクトの作成
void	Object3D::CreateDecisionObj()
{
	decisionObj = new K_Physics::MapPolygon(filePath.c_str(), CC::GetBulletPhysics(),
		CollisionMask::Non, CollisionMask::Ground);
}

