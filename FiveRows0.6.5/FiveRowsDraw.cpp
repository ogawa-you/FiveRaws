#include "FiveRows.h"

//描画全般
void FiveRows::BoardDraw()const
{
	//背景色
	Scene::SetBackground(Palette::Lightgreen);

	//BackGroundTex.scaled(0.29).drawAt(Scene::Width() / 2, Scene::Height() / 2);
	BackGroundTex.scaled(0.6).drawAt(Scene::Width() / 2, Scene::Height() / 2);

	//どの色のターンなのかわかるように色づけ
	//if(currentStatus == FiveRows::GameStatus::WhiteTurn)Rect(640, 0, 640, 720).draw(Palette::White);
	//if(currentStatus == FiveRows::GameStatus::BlackTurn)Rect(0,0,640,720).draw(Palette::Black);

	//画像の描画とサイズ補正と位置補正
	BoardTex.scaled(0.4).drawAt(Scene::Width()/2 ,Scene::Height()/2 );

	//碁盤に合わせた19x19のセル
	for (int y = 0; y < GoBoardSize; y++)
	{
		for (int x = 0; x < GoBoardSize; x++)
		{
			RectF cell(cellStartPosition + Point(x, y) * cellSize, cellSize);//セルを作成

			GoColor mark = grid[y][x]; //セルのマーク

			if (mark == GoColor::White)
			{
				WhiteTex.scaled(goPieceSize).drawAt(cell.center());//白マークを描く

				continue; //このセルはこれ以上処理しない
			}


			if (mark == GoColor::Black)
			{
				BlackTex.scaled(goPieceSize).drawAt(cell.center()); //黒マークを描く

				continue; //このセルはこれ以上処理しない
			}

			//セルがマウスオーバーされたら
			if (cell.mouseOver())
			{
				Cursor::RequestStyle(CursorStyle::Hand);//カーソルを手のアイコンに

				Circle(cell.center(), 15).draw(ColorF(1.0, 0.6));;//セルの上に半透明の白を描く(丸)
			}
		}
	}

	//試合終了時線を引く
	Line(GetPosition(firstPos), GetPosition(secondPos))
		.stretched(cellSize * 0.4)
		.draw(LineStyle::RoundCap, 5, Palette::Red);

	
	//表示用、ここがconstなので処理はPlayerGameManagement()に書いてある
	if(currentStatus == GameStatus::BlackWin || currentStatus == GameStatus::WhiteWin)
	{ 
		SimpleGUI::ButtonAt(U"Reset", Vec2(640, 690));
		SimpleGUI::ButtonAt(U"ゲーム終了", Vec2(900, 690));
	}
	else
	{
		SimpleGUI::ButtonAt(U"Back", Vec2(50, 30));
	}

	DebugDraw();//デバッグを描画
}

//デバッグ時の描画
void FiveRows::DebugDraw()const
{
	//デバッグモードがオンなら
	if (isDebugMode == false)return;

	// 19x19 のセル
	for (int y = 0; y < GoBoardSize; y++)
	{
		for (int x = 0; x < GoBoardSize; x++)
		{
			RectF cell(cellStartPosition + Point(x, y) * cellSize, cellSize);//セルを作成

			Color fontColor;//フォントの色

			double AI = 0;//セルのマーク

			//現在の状態に応じて処理切り替え
			switch (selectLine)
			{
			case FiveRows::DebugLine::x:
				AI = AIgrid[y][x].xLine;//横だけ表示
				fontColor = Palette::Purple;
				break;
			case FiveRows::DebugLine::y:
				AI = AIgrid[y][x].yLine;//縦だけ表示
				fontColor = Palette::Blue;
				break;
			case FiveRows::DebugLine::slash:
				AI = AIgrid[y][x].diagonal_1;//右斜めを表示
				fontColor = Palette::Green;
				break;
			case FiveRows::DebugLine::backslash:
				AI = AIgrid[y][x].diagonal_2;//左斜めを表示
				fontColor = Palette::Brown;
				break;
			case FiveRows::DebugLine::max:
				AI = Playergrid[y][x].GetMaxData();//すべて表示
				fontColor = Palette::Red;
				break;
			default:
				break;
			}

			if (AI != 0)font20(AI).drawAt(cell.center(), fontColor);//文字を表示

		}
	}

	//石が何個そろってるかを表示
	font20(U"黒：", stoneStatus[GoColor::Black].count).draw(0, 60, Palette::Black);
	font20(U"白：", stoneStatus[GoColor::White].count).draw(0, 80, Palette::White);
}
