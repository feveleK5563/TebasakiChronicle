#include "EnemyLoader.h"

EnemyLoader::EnemyLoader(){}
EnemyLoader::~EnemyLoader(){}

//順番1：パラメータデータの読み込み
void EnemyLoader::LoadEnemyParamaterData(std::ifstream& ifs, EnemyTypeManager::EnemyData* ed)
{
	//テクスチャのパス
	std::string texPath;
	//使用する画像名
	std::string texName;
	//最大体力
	int maxLife;
	//付与ダメージ
	int hitDamage;
	//移動速度
	float moveSpeed;
	//ジャンプ力
	float jumpPower;
	ifs >> texPath >> texName >> maxLife >> hitDamage >> moveSpeed >> jumpPower;

	ed->paramater = new EnemyType::ParameterData(texPath, texName, maxLife, hitDamage, moveSpeed, jumpPower);
}

//順番2：コリジョン形状の生成と配置データの読み込み
void EnemyLoader::LoadEnemyCollisionData(std::ifstream& ifs, EnemyTypeManager::EnemyData* ed)
{
	//ベースコリジョンの形状
	float shapeSize[3];
	ifs >> shapeSize[0] >> shapeSize[1] >> shapeSize[2];
	K_Physics::CollisionShape* bs = CC::CreateBoxShape(shapeSize[0], shapeSize[1], shapeSize[2]);
	//足元、頭上判定用コリジョンの形状
	K_Math::Vector3 cfp = { 0.f, -shapeSize[1], 0.f };
	K_Math::Vector3 chp = { 0.f, shapeSize[1], 0.f };
	K_Physics::CollisionShape* cs = CC::CreateBoxShape(shapeSize[0] - 1.f, 1.f, 1.f);
	//被ダメ、被カメラ用コリジョンの形状
	K_Math::Vector3 rp;
	ifs >> rp.x >> rp.y >> rp.z;
	ifs >> shapeSize[0] >> shapeSize[1] >> shapeSize[2];
	K_Physics::CollisionShape* rs = CC::CreateBoxShape(shapeSize[0], shapeSize[1], shapeSize[2]);
	//視界用コリジョンの形状
	K_Math::Vector3 vp;
	ifs >> vp.x >> vp.y >> vp.z;
	ifs >> shapeSize[0] >> shapeSize[1] >> shapeSize[2];
	K_Physics::CollisionShape* vs = CC::CreateBoxShape(shapeSize[0], shapeSize[1], shapeSize[2]);
	//攻撃動作遷移用コリジョンの形状
	K_Math::Vector3 aap;
	ifs >> aap.x >> aap.y >> aap.z;
	ifs >> shapeSize[0] >> shapeSize[1] >> shapeSize[2];
	K_Physics::CollisionShape* aas = CC::CreateBoxShape(shapeSize[0], shapeSize[1], shapeSize[2]);

	ed->collision = new EnemyType::CollisionData(bs, rs, vs, aas, cs, rp, vp, aap, cfp, chp);
}

//順番3：動作データの読み込み
void EnemyLoader::LoadEnemyMoveData(std::ifstream& ifs, EnemyTypeManager::EnemyData* ed)
{
	int patternNum;		//動作パターンの総数
	ifs >> patternNum;
	for (int i = 0; i < patternNum; ++i)
	{
		//動作の設定
		int totalMoveNum;	//動作の数
		ifs >> totalMoveNum;

		int* moveIdArr = new int[totalMoveNum] {};			//動作番号
		int* skillIdArr = new int[totalMoveNum] {};			//その動作中に受け取れるスキル番号(ID)
		int* durationTimeArr = new int[totalMoveNum] {};	//次の動作に移行するまでの時間
		//動作に合わせたアニメーションの設定
		K_Math::Box2D* srcArr = new K_Math::Box2D[totalMoveNum];			//一枚目のテクスチャ読み込み位置
		K_Math::Vector2* basisPosArr = new K_Math::Vector2[totalMoveNum]{};	//描画基準座標
		int* sheetArr = new int[totalMoveNum];								//1アニメーションのテクスチャ枚数
		float* spdArr = new float[totalMoveNum];							//アニメーション待機時間
		bool* irArr = new bool[totalMoveNum];								//ループするか否か
		
		for (int i = 0; i < totalMoveNum; ++i)
		{
			ifs >>	*(moveIdArr + i) >> *(skillIdArr + i) >> *(durationTimeArr + i) >>
					(srcArr + i)->x >> (srcArr + i)->y >> (srcArr + i)->w >> (srcArr + i)->h >>
					(basisPosArr + i)->x >> (basisPosArr + i)->y >>
					*(sheetArr + i) >> *(spdArr + i) >> *(irArr + i);
		}
		
		//他の動作への遷移条件
		int* transitionIdArr = new int[patternNum];
		for (int i = 0; i < patternNum; ++i)
		{
			ifs >> *(transitionIdArr + i);
		}

		ed->movesetupdata.emplace_back(new EnemyMovePattern::MoveSetUpData(
			moveIdArr,
			skillIdArr,
			durationTimeArr,
			srcArr,
			basisPosArr,
			sheetArr,
			spdArr,
			irArr,
			transitionIdArr,
			patternNum,
			totalMoveNum));
	}
}

//敵情報の読み込み
EnemyTypeManager::EnemyData* EnemyLoader::LoadEnemyData(const std::string& enemyDataPath)
{
	//本来ならここでファイルを読み込む(今は仮)
	//Prototypeに出てくる剣の子

	EnemyTypeManager::EnemyData* ed = new EnemyTypeManager::EnemyData();

	std::ifstream ifs(enemyDataPath);
	if (!ifs)
	{
		return nullptr;
	}

	//パラメータを読み込む
	LoadEnemyParamaterData(ifs, ed);

	//コリジョンの配置データを読み込む
	LoadEnemyCollisionData(ifs, ed);

	//動作データを読み込む
	LoadEnemyMoveData(ifs, ed);
	
	return ed;
}