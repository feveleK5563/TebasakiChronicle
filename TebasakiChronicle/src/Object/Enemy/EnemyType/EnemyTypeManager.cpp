#include "EnemyTypeManager.h"

//コンストラクタ
EnemyTypeManager::EnemyTypeManager() {}

//デストラクタ
EnemyTypeManager::~EnemyTypeManager()
{
	for (auto it : eType)
		delete it;
}

//-----------------------------------------------------------------------------
//ファイルを読み込んで敵のデータを作る
//引数：読み込むファイルへのパス(string)
void EnemyTypeManager::CreateEnemyData(EnemyData* ed)
{
	if (ed == nullptr)
		return;

	eType.emplace_back(new EnemyType(*(ed->paramater), *(ed->collision)));	//パラメータとコリジョンの配置を設定

	for (auto it : ed->movesetupdata)
	{
		eType.back()->GetEnemyMoveSet()->CreateMotionPattern(*it);	//動作パターンを一つ設定
	}

	delete ed;
}

//-----------------------------------------------------------------------------
//指定番号の敵データのアドレス値を返す
EnemyType* EnemyTypeManager::GetEnemyTypeData(int enemyNum)
{
	if (enemyNum < (int)eType.size())
	{
		return eType[enemyNum];
	}
	return nullptr;
}