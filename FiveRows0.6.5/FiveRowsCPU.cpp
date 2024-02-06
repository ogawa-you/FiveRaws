#include "FiveRows.h"

void FiveRows::CPUPlay(GoColor cpuColor)
{
	Array<Point> cpuMaxStorongPosition;//加減配列、x,y座標を記録する
	Array<Point> playerMaxStorongPosition;//加減配列、x,y座標を記録する
	Array<Point> maxStorongPosition;//加減配列、x,y座標を記録する

	double cpuMaxData = 0;
	double playerMaxData = 0;



	//最も重みの高いセルの座標を求める
	//重みの高い空セルに現在の色の碁石情報を入れる
	for (int y = 0; y < GoBoardSize; y++)
	{
		for (int x = 0; x < GoBoardSize; x++)
		{
			//現在の重みより大きい数値があれば重み最大値を更新して配列の中をリセットする	
			if (cpuMaxData < AIgrid[y][x].GetMaxData())
			{
				cpuMaxData = AIgrid[y][x].GetMaxData();//aiに重み最大値を入れる

				cpuMaxStorongPosition.clear();//配列を初期化する
			}

			if (cpuMaxData == AIgrid[y][x].GetMaxData())
			{
				cpuMaxStorongPosition << Point(x, y);//配列に現在の座標を入れる
			}
		}
	}

	for (int y = 0; y < GoBoardSize; y++)
	{
		for (int x = 0; x < GoBoardSize; x++)
		{
			//現在の重みより大きい数値があれば重み最大値を更新して配列の中をリセットする	
			if (playerMaxData < Playergrid[y][x].GetMaxData())
			{
				playerMaxData = Playergrid[y][x].GetMaxData();//aiに重み最大値を入れる

				playerMaxStorongPosition.clear();//配列を初期化する
			}

			if (playerMaxData == Playergrid[y][x].GetMaxData())
			{
				playerMaxStorongPosition << Point(x, y);//配列に現在の座標を入れる
			}
		}
	}

	Point selectPosition;

	if (cpuMaxData >= 5)
	{
		maxStorongPosition = cpuMaxStorongPosition;
		goto PUSH;
	}
	else if (playerMaxData >= 5)
	{
		maxStorongPosition = playerMaxStorongPosition;
		goto PUSH;
	}
	else if (cpuMaxData >= 4.5)
	{
		maxStorongPosition = cpuMaxStorongPosition;
		goto PUSH;
	}
	else if (playerMaxData >= 4.5)
	{
		maxStorongPosition = playerMaxStorongPosition;
		goto PUSH;
	}
	else if (cpuMaxData >= 4)
	{
		maxStorongPosition = cpuMaxStorongPosition;
		goto PUSH;
	}
	else if (playerMaxData >= 4)
	{
		maxStorongPosition = playerMaxStorongPosition;
		goto PUSH;
	}
	else if (cpuMaxData >= 3.5)
	{
		maxStorongPosition = cpuMaxStorongPosition;
		goto PUSH;
	}
	else if (playerMaxData >= 3.5)
	{
		maxStorongPosition = playerMaxStorongPosition;
		goto PUSH;
	}
	else
	{
		maxStorongPosition = cpuMaxStorongPosition;
		goto PUSH;
	}

PUSH:
	if (waitTime.s() <= 0.5)
	{
		return;
	}
	
	selectPosition = maxStorongPosition[Random(maxStorongPosition.size() - 1)];//最も大きい重みのセルから一つランダムに選ぶ

	grid[selectPosition.y][selectPosition.x] = cpuColor;//選んだセルに書き込む

	DefaultSound.play();//効果音を流す

	CheckLine(currentMark);//そろってるかチェック
}


void FiveRows::AIxLineDataTableMake(int x, int y, GoColor goColor, AITable(*aitable)[GoBoardSize])
{
	//空白でないならreturnする
	if (grid[y][x] != GoColor::None)
	{
		aitable[y][x].xLine = 0;

		return;
	}

	//自分のマスの左右が自分の色以外かを見る
	//まず左からチェック
	//左に置けないならtrue
	bool isLeftCheckEnd = x - 1 < 0 || grid[y][x - 1] != goColor;
	//次に右チェック
	//右に置けないならtrue
	bool isRightCheckEnd = x + 1 > GoBoardSize - 1 || grid[y][x + 1] != goColor;

	//左右を見て両方が自分の色じゃなかったら重みを0にする
	if (isLeftCheckEnd && isRightCheckEnd)
	{
		aitable[y][x].xLine = 0;

		return;
	}

	double leftCount = 0;
	double rightCount = 0;

	GoColor limit = GoColor::None;
	int ix = 0;

	//左を調べて異色か盤の端までカウント
	for (ix = x - 1/*自分自身を見ないため最初に-1する*/; IsWithinRangeX(ix) && (limit = grid[y][ix]) == goColor/*自分の色か*/; ix--)
	{
		leftCount++;
	}

	//上でforを抜けるときにixが余分に-1されてる
	if (IsWithinRangeX(ix) && limit == GoColor::None)
	{
		leftCount += 0.25;
	}


	//右を調べて異色か盤の端までカウント
	for (ix = x + 1/*自分自身を見ないため最初に-1する*/; IsWithinRangeX(ix) && (limit = grid[y][ix]) == goColor/*自分の色か*/; ix++)
	{
		rightCount++;
	}

	//上でforを抜けるときにixが余分に+1されてる
	if (IsWithinRangeX(ix) && limit == GoColor::None)
	{
		rightCount += 0.25;
	}

	//求めたカウントと自分自身を足して重みにする
	aitable[y][x].xLine = leftCount + rightCount + 1;
}

void FiveRows::AIyLineDataTableMake(int x, int y, GoColor goColor, AITable(*aitable)[GoBoardSize])
{
	//空白でないならreturnする
	if (grid[y][x] != GoColor::None)
	{
		aitable[y][x].yLine = 0;

		return;
	}

	//自分のマスの上下が自分の色以外かを見る
	//まず上からチェック
	//上に置けないならtrue
	bool isUpCheckEnd = y - 1 < 0 || grid[y - 1][x] != goColor;
	//次に下チェック
	//下に置けないならtrue
	bool isDownCheckEnd = y + 1 > GoBoardSize - 1 || grid[y + 1][x] != goColor;

	//上下を見て両方自分の色じゃなかったら重みを0にする
	if (isUpCheckEnd && isDownCheckEnd)
	{
		aitable[y][x].yLine = 0;

		return;
	}

	double upCount = 0;
	double downCount = 0;

	GoColor limit = GoColor::None;
	int iy = 0;

	//上を調べて同色のところか盤の端までカウント
	for (iy = y - 1; IsWithinRangeY(iy) && (limit = grid[iy][x]) == goColor; iy--)
	{
		upCount++;
	}

	if (IsWithinRangeY(iy) && limit == GoColor::None)
	{
		upCount += 0.25;
	}

	//下を調べて同色のところか盤の端までカウント
	for (iy = y + 1; IsWithinRangeY(iy) && (limit = grid[iy][x]) == goColor; iy++)
	{
		downCount++;
	}

	if (IsWithinRangeY(iy) && limit == GoColor::None)
	{
		downCount += 0.25;
	}

	//求めたカウントと自分自身を足して重みにする
	aitable[y][x].yLine = upCount + downCount + 1;
}

void FiveRows::AIdiagonalLineDataTableMake(int x, int y, int Xadd, int Yadd, double& diagonal, GoColor goColor)
{

	//空白でないならreturnする
	if (grid[y][x] != GoColor::None)
	{
		diagonal = 0;

		return;
	}

	//自分のマスの斜上から斜下が自分の色以外かを見る
	//まず斜上からチェック
	//斜上に置けないならtrue
	bool isDiagonalUpCheckEnd = (y - Yadd < 0 || x - Xadd < 0)/*左上*/ || (y - Yadd > GoBoardSize - 1 || x - Xadd > GoBoardSize - 1)/*右上*/ || grid[y - Yadd][x - Xadd] != goColor;
	//次に斜下チェック
	//斜下に置けないならtrue
	bool isDiagonalDownCheckEnd = (y + Yadd < 0 || x + Xadd < 0)/*左下*/ || (y + Yadd > GoBoardSize - 1 || x + Xadd > GoBoardSize - 1)/*右下*/ || grid[y + Yadd][x + Xadd] != goColor;

	//上下を見て両方埋まってたら重みを0にする
	if (isDiagonalUpCheckEnd && isDiagonalDownCheckEnd)
	{
		diagonal = 0;

		return;
	}

	double upCount = 0;
	double downCount = 0;

	GoColor limit = GoColor::None;
	int ix = 0;
	int iy = 0;

	//左上,右上を調べて異色か盤の端までカウント
	for (iy = y - Yadd, ix = x - Xadd; IsWithinRange(ix, iy) && (limit = grid[iy][ix]) == goColor; iy += -Yadd, ix += -Xadd)
	{
		upCount++;
	}

	if (IsWithinRange(ix, iy) && limit == GoColor::None)
	{
		upCount += 0.25;
	}

	//左下,右下を調べて異色か盤の端までカウント
	for (iy = y + Yadd, ix = x + Xadd; IsWithinRange(ix, iy) && (limit = grid[iy][ix]) == goColor; iy += Yadd, ix += Xadd)
	{
		downCount++;
	}

	if (IsWithinRange(ix, iy) && limit == GoColor::None)
	{
		downCount += 0.25;
	}

	//求めたカウントと自分自身を足して重みにする
	diagonal = upCount + downCount + 1;
}

void FiveRows::AIdiagonalRightDown(int x, int y, GoColor goColor, AITable(*aitable)[GoBoardSize])
{
	AIdiagonalLineDataTableMake(x, y, 1, 1, aitable[y][x].diagonal_1, goColor);
}

void FiveRows::AIdiagonalLeftDown(int x, int y, GoColor goColor, AITable(*aitable)[GoBoardSize])
{
	AIdiagonalLineDataTableMake(x, y, -1, 1, aitable[y][x].diagonal_2, goColor);
}
