#pragma once

class TimeCount
{
private:
	int cntTime;	//経過時間
	int endTime;	//終了時間
	bool isTimeEnd;	//終了時間を超過しているか否か

public:
	TimeCount();

	//経過時間を0にする
	void ResetCntTime();

	//終了時間を設定する
	//-1で無効
	void SetEndTime(int setEndTime);

	//時間を測る
	void Run();

	//現在の経過時間を返す
	int GetNowCntTime() const;

	//設定されている終了時間を返す
	int GetEndTime() const;

	//経過時間が終了時間まで到達していたらtrueを返す
	bool IsTimeEnd() const;
};