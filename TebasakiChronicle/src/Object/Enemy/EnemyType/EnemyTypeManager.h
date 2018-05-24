#pragma once
#include "EnemyType.h"
#include "../../../Helper.h"

class EnemyTypeManager
{
public:
	struct EnemyData	//敵情報のまとめ
	{
		EnemyType::ParameterData* paramater;
		EnemyType::CollisionData* collision;
		std::vector<EnemyMovePattern::MoveSetUpData*> movesetupdata;

		EnemyData(){}

		~EnemyData()
		{
			Memory::SafeDelete(paramater);
			Memory::SafeDelete(collision);

			for (auto it : movesetupdata)
				Memory::SafeDelete(it);
		}
	};

public:
	std::vector<EnemyType*> eType;

	//コンストラクタ
	EnemyTypeManager();
	//デストラクタ
	~EnemyTypeManager();

	//ファイルを読み込んで敵のデータを作る
	//引数：読み込むファイルへのパス(string)
	void CreateEnemyData(EnemyData* ed);

	//指定番号の敵データのアドレス値を返す
	EnemyType* GetEnemyTypeData(int enemyNum);
};