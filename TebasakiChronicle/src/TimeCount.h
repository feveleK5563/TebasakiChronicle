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
	void SetEndTime(int setEndTime);

	//時間を測る
	//※経過時間が終了時間を超えていた場合は計測が自動的に停止する
	void Run();

	//現在の経過時間を返す
	int GetNowCntTime() const;

	//経過時間が終了時間まで到達していたらtrueを返す
	bool IsTimeEnd() const;
};