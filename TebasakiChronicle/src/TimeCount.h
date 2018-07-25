#pragma once

class TimeCount
{
private:
	int cntTime;	//経過時間
	int endTime;	//終了時間
	bool isTimeEnd;	//終了時間を超過しているか否か
	bool isCount;

public:
	TimeCount();

	//経過時間を0にする
	void ResetCntTime();

	//終了時間を設定する
	void SetEndTime(int setEndTime);

	//時間を測る
	void Run();

	//強制的に現在の時間を設定する
	void SetTime(int time);

	//時間の加算を許すか否かを設定(falseを指定するとRunを呼んでも数値が変化しなくなる)
	void Count(bool isCount);

	//現在の経過時間を返す
	int GetNowCntTime() const;

	//経過時間が終了時間まで到達していたらtrueを返す
	bool IsTimeEnd() const;
};