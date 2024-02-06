#include "FiveRows.h"


FiveRows::FiveRows()
{

}

//人専用
void FiveRows::CellHitBox(GoColor goStoneColor)
{
	//左クリックされたら空セルに現在の色の碁石情報を入れる
	for (auto p : step(Size(GoBoardSize, GoBoardSize)))
	{
		RectF cell(cellStartPosition + p * cellSize, cellSize);//セルを作成

		GoColor mark = grid[p.y][p.x]; //セルのマーク

		// セルが空白で、なおかつクリックされたら
		if ((mark == GoColor::None) && cell.leftClicked())
		{
			grid[p.y][p.x] = KeyLControl.pressed() && isDebugMode ? GoColor::Black : goStoneColor;//セルに現在のマークを書き込む

			isClick = true;//クリックされた

			DefaultSound.playOneShot(GameData::MainVolume * GameData::EffectVolume);//効果音を流す

			break;
		}
	}
}

//五個そろってるか
void FiveRows::CheckLine(GoColor goStoneColor)
{
	Point first, second;

	//もしそのマスに碁石があれば縦、横、斜めをチェックする
	for (int iy = 0; iy < GoBoardSize; iy++)
	{
		for (int ix = 0; ix < GoBoardSize; ix++)
		{
			first = { ix, iy };

			GoColor cell = grid[iy][ix];//セルを参照

		//右をチェックする
			if (cell == goStoneColor)
			{
				int count = 0;
				for (int right = ix; right < ix + 5 && right < GoBoardSize; right++)
				{
					if (grid[iy][right] == goStoneColor)
					{
						count++;
					}

					if (count == 5)
					{
						//勝ち
						isWin = true;

						second = { right,iy };

						goto WIN;
					}
				}
				stoneStatus[goStoneColor].SetCount(count);
			}

			//下をチェックする
			if (cell == goStoneColor)
			{
				int count = 0;
				for (int down = iy; down < iy + 5; down++)
				{
					if (grid[down][ix] == goStoneColor)
					{
						count++;
					}

					if (count == 5)
					{
						//勝ち
						isWin = true;

						second = { ix,down };

						goto WIN;
					}
				}
				stoneStatus[goStoneColor].SetCount(count);

			}

			//右下をチェックする
			if (cell == goStoneColor)
			{
				int count = 0;
				for (int rightdown = ix; rightdown < ix + 5; rightdown++)
				{
					if (grid[iy + count][rightdown] == goStoneColor)
					{
						count++;
					}

					if (count == 5)
					{
						//勝ち
						isWin = true;

						second = { rightdown,iy + 5 - 1 };

						goto WIN;
					}
				}
				stoneStatus[goStoneColor].SetCount(count);
			}

			//左下をチェックする
			if (cell == goStoneColor)
			{
				int count = 0;
				for (int leftdown = ix; leftdown > ix - 5 && leftdown > -1; leftdown--)
				{
					if (grid[iy + count][leftdown] == goStoneColor)
					{
						count++;
					}

					if (count == 5)
					{
						//勝ち
						isWin = true;

						second = { leftdown,iy + 5 - 1 };

						goto WIN;
					}
				}
				stoneStatus[goStoneColor].SetCount(count);
			}
		}
	}

	currentStatus = ((currentStatus == GameStatus::WhiteTurn) ? GameStatus::BlackTurn : GameStatus::WhiteTurn);//勝ちでないなら現在の状態を入れ替える

	return;

	//五個そろった処理
	//勝った処理への遷移、単発の勝利処理(音の再生など)
WIN:
	FiveRows::firstPos = first;
	FiveRows::secondPos = second;
	//白のターンならの白勝ちに
	if (currentStatus == GameStatus::WhiteTurn)
	{
		currentStatus = GameStatus::WhiteWin;
	}
	//黒のターンなら黒の勝ちに
	if (currentStatus == GameStatus::BlackTurn)
	{
		currentStatus = GameStatus::BlackWin;
	}

	//勝利音楽を流す
	FinishAudio2.playOneShot(GameData::MainVolume* GameData::EffectVolume);
}

//セルの座標を返す
Point FiveRows::GetPosition(Point mapPos) const
{
	//最初の左上のセルの座標、真ん中の座標1
	Vec2 firstPosition = cellStartPosition + Vec2{ cellSize / 2, cellSize / 2 };

	//返す値の座標
	Vec2 returnPosition = firstPosition + mapPos * cellSize;


	return returnPosition.asPoint();
}

//CPUの動きを作る
void FiveRows::CPUDataManagement(GoColor goColor)
{

	AITable(*p)[GoBoardSize] = AIgrid;

	//19*19を回す
	for (int y = 0; y < GoBoardSize; y++)
	{
		for (int x = 0; x < GoBoardSize; x++)
		{
			AIxLineDataTableMake(x, y, goColor,AIgrid);//x座標の重みを作る
			AIyLineDataTableMake(x, y, goColor, AIgrid);//y座標の重みを作る
			AIdiagonalLeftDown(x, y, goColor, AIgrid);//右斜めの重みを作る
			AIdiagonalRightDown(x, y, goColor, AIgrid);//左斜めの重みを作る

			AIgrid[y][x].Is3x3();//3*3ができてるか
			//p[y][x].Is3x3();//3*3ができてるか
		}
	}
}

//CPUの動きを作る
void FiveRows::PlayerDataManagement(GoColor goColor)
{
	AITable(*p)[GoBoardSize] = Playergrid;


	//19*19を回す
	for (int y = 0; y < GoBoardSize; y++)
	{
		for (int x = 0; x < GoBoardSize; x++)
		{
			AIxLineDataTableMake(x, y, goColor,Playergrid);//x座標の重みを作る
			AIyLineDataTableMake(x, y, goColor, Playergrid);//y座標の重みを作る
			AIdiagonalLeftDown(x, y, goColor, Playergrid);//右斜めの重みを作る
			AIdiagonalRightDown(x, y, goColor, Playergrid);//左斜めの重みを作る

			Playergrid[y][x].Is3x3();//3*3ができてるか
		}
	}
}

bool FiveRows::IsWithinRangeX(int x)
{
	return -1 < x && GoBoardSize > x;
}

bool FiveRows::IsWithinRangeY(int y)
{
	return -1 < y && GoBoardSize > y;
}

bool FiveRows::IsWithinRange(int x,int y)
{
	return IsWithinRangeX(x) && IsWithinRangeY(y);
}

void FiveRows::Initialize()
{
	//初期定義,初期化

	boardSize = 0.35;					    //囲碁盤画像の倍率

	cellStartPosition
		= { ((Scene::Width()/2)-(BoardTex.width()* 0.4 /2)) + 4,
		  ((Scene::Height() / 2) - (BoardTex.height() * 0.4 / 2)) + 4};    //セルの左上の座標

	cellSize = (BoardTex.width() * 0.4 / 19)- 0.5;				            //セルの高さと幅

	goPieceSize = 0.08;                         //碁石画像の倍率

	currentStatus = GameStatus::BlackTurn;      //最初が白か黒か

	firstPos = { 0,0 }, secondPos = { 0,0 };    //始点と終点の初期値

	//グリッドに初期値0を入れる
	for (int y = 0; y < GoBoardSize; y++)
	{
		for (int x = 0; x < GoBoardSize; x++)
		{
			grid[y][x] = GoColor::None;
			AIgrid[y][x].Reset();
			Playergrid[y][x].Reset();
		}
	}

	stoneStatus.clear();

	waitTime.restart();

}

void FiveRows::GameManagement(VSPlayerOrCPU currentMode, GoColor cpuColor)
{
	//デバッグ用キー
	if (Key1.down())selectLine = DebugLine::x;
	if (Key2.down())selectLine = DebugLine::y;
	if (Key3.down())selectLine = DebugLine::slash;
	if (Key4.down())selectLine = DebugLine::backslash;
	if (Key5.down())selectLine = DebugLine::max;

	if (currentMode == VSPlayerOrCPU::VSPlayer)PlayerGameManagement();
	
	if (currentMode == VSPlayerOrCPU::VSCPU)CPUGameManagement(cpuColor);
}

void FiveRows::PlayerGameManagement()
{
	switch (currentStatus)
	{



	case FiveRows::GameStatus::WhiteTurn:
	case FiveRows::GameStatus::BlackTurn:
		//タイトルに帰る
		if (SimpleGUI::ButtonAt(U"Back", Vec2(50, 30)))isFinishGame = true;

		currentMark = currentStatus == FiveRows::GameStatus::WhiteTurn ? GoColor::White : GoColor::Black;       //現在の色に応じて色を変える

		CellHitBox(currentMark);//セルを選択した処理

		if (isClick)
		{
			CheckLine(currentMark);      //そろってるかチェック
			isClick = false;             //クリックされてない
		}
		break;

	case FiveRows::GameStatus::WhiteWin:

		font20(U"whitewin").draw();
		//初期化
		if (SimpleGUI::ButtonAt(U"Reset", Vec2(640, 690)))Initialize();
		if (SimpleGUI::ButtonAt(U"ゲーム終了", Vec2(900, 690)))currentStatus = GameStatus::Result;

		break;
	case FiveRows::GameStatus::BlackWin:

		font20(U"blackewin").draw();
		//初期化
		if (SimpleGUI::ButtonAt(U"Reset", Vec2(640, 690)))Initialize();
		if (SimpleGUI::ButtonAt(U"ゲーム終了", Vec2(900, 690)))currentStatus = GameStatus::Result;

		break;

	case FiveRows::GameStatus::Result:
		isFinishGame = true;
		break;
	default:
		break;
	}
}

void FiveRows::CPUGameManagement(GoColor cpuColor)
{

	

	//プレイヤーの色をcpuの色の逆として認識
	GoColor playerColor = GoColor::None;

	if (cpuColor == GoColor::Black)playerColor = GoColor::White;
	if (cpuColor == GoColor::White)playerColor = GoColor::Black;

	switch (currentStatus)
	{
	case FiveRows::GameStatus::WhiteTurn:
	case FiveRows::GameStatus::BlackTurn:

		//タイトルに帰る
		if (SimpleGUI::ButtonAt(U"Back", Vec2(50, 30)))isFinishGame = true;

		currentMark = currentStatus == FiveRows::GameStatus::WhiteTurn ? GoColor::White : GoColor::Black;       //現在の色に応じて色を変える

		CPUDataManagement(cpuColor);
		PlayerDataManagement(playerColor);

		

		if(currentMark == cpuColor)
		{
			CPUPlay(cpuColor);
		}
		else
		{
			CellHitBox(currentMark);//セルを選択した処理
			if (isClick)
			{
				CheckLine(currentMark);      //そろってるかチェック
				isClick = false;             //クリックされてない
				waitTime.restart();
			}
		}


		break;

	case FiveRows::GameStatus::WhiteWin:

		font20(U"whitewin").draw();
		//初期化
		if (SimpleGUI::ButtonAt(U"Reset", Vec2(640, 690)))Initialize();
		if (SimpleGUI::ButtonAt(U"ゲーム終了", Vec2(900, 690)))currentStatus = GameStatus::Result;

		break;
	case FiveRows::GameStatus::BlackWin:

		font20(U"blackewin").draw();
		//初期化
		if (SimpleGUI::ButtonAt(U"Reset", Vec2(640, 690)))Initialize();
		if (SimpleGUI::ButtonAt(U"ゲーム終了", Vec2(900, 690)))currentStatus = GameStatus::Result;

		break;

	case FiveRows::GameStatus::Result:
		isFinishGame = true;
		break;
	default:
		break;
	}
}

//void FiveRows::GameManagement()
//{
//
//	switch (currentStatus)
//	{
//	case FiveRows::GameStatus::WhiteTurn:
//	case FiveRows::GameStatus::BlackTurn:
//
//		currentMark = currentStatus == FiveRows::GameStatus::WhiteTurn ? GoColor::White : GoColor::Black;       //マークを白にする
//
//		CellHitBox(currentMark);//セルを選択した処理
//
//		if (isClick)
//		{
//			CheckLine(currentMark);      //そろってるかチェック
//			isClick = false;                //クリックされてない
//		}
//		break;
//	case FiveRows::GameStatus::Result:
//		isFinishGame = true;
//		break;
//	case FiveRows::GameStatus::WhiteWin:
//
//		font20(U"whitewin").draw();
//		//初期化
//		if (SimpleGUI::ButtonAt(U"Reset", Vec2(640, 690)))Initialize();
//		if (SimpleGUI::ButtonAt(U"ゲーム終了", Vec2(900, 690)))currentStatus = GameStatus::Result;
//
//		break;
//	case FiveRows::GameStatus::BlackWin:
//		//currentStatus = GameStatus::Result;
//		font20(U"blackewin").draw();
//		//初期化
//		if (SimpleGUI::ButtonAt(U"Reset", Vec2(640, 690)))Initialize();
//		if (SimpleGUI::ButtonAt(U"ゲーム終了", Vec2(900, 690)))currentStatus = GameStatus::Result;
//
//		break;
//	default:
//		break;
//	}
//}
