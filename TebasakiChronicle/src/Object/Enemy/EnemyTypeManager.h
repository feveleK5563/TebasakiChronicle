#pragma once
#include "EnemyType.h"

class EnemyTypeManager
{
public:
	std::vector<EnemyType*> eType;

	//コンストラクタ
	EnemyTypeManager();
	//デストラクタ
	~EnemyTypeManager();

	//ファイルを読み込んで敵のデータを作る
	//引数：読み込むファイルへのパス(string)
	void LoadEnemyData(const std::string& filePath);

	//指定番号の敵データのアドレス値を返す
	//※注 ここで取得したデータをdeleteしてはいけない(戒め)
	EnemyType* GetEnemyTypeData(int enemyNum);
};