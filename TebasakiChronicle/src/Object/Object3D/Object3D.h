#pragma once
#include "MeshModel.h"
#include "../src/CSTList.h"
#include "MapPolygon.h"
#include "../src/BaseClass/Collision/CollisionCreator.h"


//------------------------------------------------------------------------
//概要: 3Dモデルをロードし、形を作り出す
//製作者:　日比野　真聖
//------------------------------------------------------------------------
class Object3D
{
public:
	//!@brief コンストラクタ
	//!@param[in] filePath モデルのパス
	//!@param[in] texFilePath テクスチャのパス
	//!@param[in] pos_	位置
	//!@param[in] rotation_ 向き
	//!@param[in] scale_ 大きさ
	Object3D(const std::string& filePath,
		const K_Math::Vector3& pos_,const K_Math::Vector3& rotation_,const K_Math::Vector3& scale_);
	//!@brief デストラクタ
	~Object3D();

	//!@brief モデルのロードとテクスチャのロード
	//!@param[in] filePath モデルのパス
	//!@param[in] texName テクスチャのパス
	//!@return 成功ならtrue
	bool	Load(const std::string& filePath);

	//!@brief 地形オブジェクトの設定
	//!@param[in] decisionPos_ 地形の位置
	//!@param[in] decisionAngle_ 地形の向き
	//!@param[in] decisionSize_ 地形のサイズ
	void	SetDecisionParam(const K_Math::Vector3& decisionPos_,
		const K_Math::Vector3& decisionRotation_,
		const K_Math::Vector3& decisionScale_);

	//!@brief モデルの描画
	void	Render();

private:
	//!@brief モデルデータをもとにMeshModelクラスを作成
	void	CreateMeshModel();
	//!@brief MeshModelを扱いやすくするMeshObjectクラスを作成
	void	CreateMeshObject();
	//!@brief 地形オブジェクトの作成
	void	CreateDecisionObj();

private:
	K_Graphics::ModelDataFactory	factory;		//ファクトリ
	K_Graphics::ModelDatas*			modelData;		//メッシュモデル
	K_Graphics::MeshModel*			model;			//モデルクラス
	K_Graphics::MeshObject*			object;			//MeshModelを扱いやすくする
	K_Physics::MapPolygon*			decisionObj;	//当たり判定オブジェクト
	K_Graphics::TextureList*		texList;		//テクスチャリスト
private:
	K_Math::Vector3					decisionPos;		//当たり判定オブジェクトの位置
	K_Math::Vector3					decisionRotation;	//当たり判定オブジェクトの回転
	K_Math::Vector3					decisionScale;		//当たり判定オブジェクトのスケール
private:
	std::string						filePath;		//モデルのファイルパス
	std::string						texFilePath;	//テクスチャのファイルパス
	std::string						imageName;		//テクスチャ名
};