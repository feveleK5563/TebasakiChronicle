#pragma once
#include "../SceneAbstract.h"
#include "../../CSTList.h"
#include "MeshModel.h"
#include "../../BaseClass/Input/Input.h"
#include "../../src/BaseClass/GUIObject/GUIObject.h"
#include <FontRenderer.h>

class Scene_StageSelect : public SceneAbstract
{
private:
	//!@brief	ステージの詳細情報
	struct StageDetail
	{
		//!@brief	コンストラクタ
		StageDetail(const std::string& stageName, const std::string& overview);
		std::string	stageName;	//ステージ名
		std::string	overview;	//ステージ概要
	};
	//!@brief	ステージマップ
	class StageMap
	{
	public:
		//!@brief	コンストラクタ
		StageMap(GUIObject* guiMap, StageDetail* stageDetail);
		//!@brief	デストラクタ
		~StageMap();
		//!@brief	GUIMapの取得
		GUIObject&		GetGuiMap() const;
		//!@brief	ステージ情報の詳細の取得
		StageDetail&	GetStageDetail() const;
	private:
		GUIObject*		guiMap;				//ステージのマップGUI
		StageDetail*	stageDetail;		//ステージの詳細情報
	};
	//!@brief	ステージの詳細を画像にする
	class StageDetailGUI
	{
	public:
		//!@brief	コンストラクタ
		//!@param[in]	stageDetail	現在選択されているステージ情報を受け取る
		StageDetailGUI(const StageDetail& stageDetail);
		//!@brief	デストラクタ
		~StageDetailGUI();
	public:
		//!@brief	ステージ情報の更新
		//!@param[in]	stageDetail	現在選択されているステージ情報を受け取る
		void	UpDate(const StageDetail& stageDetail);
		//!@brief	テキストの描画
		void	DrawText();
	private:
		StageDetail		stageDetail;
		std::vector<K_Graphics::FontRenderer*>	detailFont;
		GUIObject*		backGround;
	};
	//!@brief	状態
	enum class State
	{
		FadeIn,		//フェードイン
		Normal,		//通常
		FadeOut,	//フェードアウト
		NextScene	//次のシーン
	};
private:
	float	maxAngleCnt;
	float	angleCnt;
	float	angle;
	float	rotSpeed;
	bool	rotMove;
	int		selectNowNo;
	K_Math::Vector3			baseRotPos;		//マップが回転する基点
	std::vector<StageMap*>	stageMap;		//ステージマップ
	StageDetailGUI*			detailGui;		//詳細GUI
private:
	//フェード
	GUIObject*				fadeGui;		//フェード用
	float					alpha;			//透明度
	State					state;			//状態
	SceneName				nowScene;		//次のシーン
private:
	//スライドパラメータ
	float	upDownSpeed;	//上下のスライドスピード
	float	rightSpeed;		//右のスライドスピード

public:
	Scene_StageSelect();			//コンストラクタ
	~Scene_StageSelect();			//デストラクタ
	SceneName Update() override;	//更新(次に設定したいシーン名を返す)
	void Draw() override;			//描画

private:
	//!@brief	ステージマップの回転移動
	void	StageMapRotation();
	//!@brief	入力で回転を行う
	void	InputMapRotation();
	//!@brief	ステージの決定処理を行う
	//!@retrurn	次のシーン
	void	DecideStageMap();
	//!@brief	状態の変化に応じた処理
	void	StateCorrespond(SceneName& nextScene);
	//!@brief	ステージマップをスライドさせる
	//!@param[in]	nowStageNo	現在のステージ番号
	void	SlideStageMap(const int nowStageNo);
};