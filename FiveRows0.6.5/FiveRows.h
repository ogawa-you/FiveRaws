#pragma once
#include"Base.h"
#include"StoneStatus.h"

class FiveRows
{
private:
	Texture WhiteTex{ U"image/white.png" };//白碁石画像
	Texture BlackTex{ U"image/black.png" };//黒碁石画像
	Texture BoardTex{ U"image/board.jpg" };//囲碁盤画像
	//Texture BackGroundTex{ U"image/tatami (1).jpg" };//囲碁盤画像
	Texture BackGroundTex{ U"image/t6.jpg" };//囲碁盤画像
	

	Audio DefaultSound{ Audio(U"sound/石音.mp3") };

	Audio PutAudio[6] = {
		Audio(U"sound/「うわああ！」.mp3"),
		Audio(U"sound/「うっ！」.mp3"),
		Audio(U"sound/「ぐああっ！」.mp3"),
		Audio(U"sound/「ぐおっ！」.mp3"),
		Audio(U"sound/「重い…っ！」.mp3"),
		Audio(U"sound/「いてっ！」.mp3"),
	};

	Audio PutAudio2{ U"sound/決定、ボタン押下32.mp3" };
	Audio PutAudio3{ U"sound/決定、ボタン押下38.mp3" };
	Audio PutAudio4{ U"sound/「ぐおっ！」.mp3" };

	Audio FinishAudio{ U"sound/「ええーーっ！？すごい！」.mp3" };
	Audio FinishAudio2{ U"sound/スタジアムの拍手.mp3" };
	Audio FinishAudio3{ U"sound/「えー…」.mp3" };

	/// <summary>
	/// 現在の状態
	/// </summary>
	enum class GameStatus
	{
		WhiteTurn,  //白プレイヤーのターン
		BlackTurn,  //黒プレイヤーのターン
		Result,     //試合終了後
		WhiteWin,   //白が勝った時
		BlackWin    //黒が勝った時
	};

	/// <summary>
	/// デバッグでラインごとに表示切替するとき用
	/// </summary>
	enum class DebugLine
	{
		x,			//xのライン
		y,			//yのライン
		slash,		//右斜めのライン
		backslash,	//左斜めのライン
		max,		//すべて表示
		_3x3		//3x3だけ表示
	};

	//囲碁盤のサイズ
	static const int GoBoardSize = 19;

	/// <summary>
	/// AIの重みを管理する構造体
	/// </summary>
	struct AITable 
	{
		double	xLine,		//ｘ軸
				yLine,		//ｙ軸
				diagonal_1,	//右斜め軸
				diagonal_2;	//左斜め軸
		//初期化
		//デフォルトコンストラクター
		AITable():xLine(0),yLine(0),diagonal_1(0),diagonal_2(0){}

		//すべてを0にする
		void Reset()
		{
			xLine = yLine = diagonal_1 = diagonal_2 = 0;
		}

		//全ラインの中から最大の重みを選択
		double GetMaxData()const
		{
			double maxData = 0;
			maxData = xLine > yLine ? xLine : yLine;
			if (maxData < diagonal_1)maxData = diagonal_1;
			if (maxData < diagonal_2)maxData = diagonal_2;

			return maxData;
		}
		
		bool Is3x3()
		{
			int count = 0;

			if (xLine >= 3)count++;
			if (yLine >= 3)count++;
			if (diagonal_1 >= 3)count++;
			if (diagonal_2 >= 3)count++;

			return count >= 2;
		}
	};

	//
	mutable std::map<GoColor, StoneStatus> stoneStatus;

	//二次元配列のグリッド、碁石の画像設置や空き状況管理用	
	GoColor grid[GoBoardSize][GoBoardSize];

	//二次元配列のグリッド、CPUの重み管理用
	AITable AIgrid[GoBoardSize][GoBoardSize];

	//二次元配列のグリッド、プレイヤーの重み管理用
	AITable Playergrid[GoBoardSize][GoBoardSize];

	//デバッグ切り替え用
	DebugLine selectLine = DebugLine::max;

	//囲碁盤の左上の座標
	Point boardStartPosition;

	//五個並んでるときの始点と終点
	Point firstPos, secondPos;

	//囲碁盤画像の倍率
	double boardSize;
	

	//セルの左上の座標
	Vec2 cellStartPosition;

	//セルの高さと幅
	double cellSize;

	//碁石画像の倍率
	double goPieceSize;

	//試合が終わったかの判定フラグ
	bool isWin = false;

	//プレイヤーが左クリックをしたかの判定フラグ
	bool isClick = false;

	Stopwatch waitTime;

	//デバッグモードならフラグを立てる
#ifdef _DEBUG
	//デバッグモードを切り替えるフラグ
	bool isDebugMode = true;
#else
	//デバッグモードを切り替えるフラグ
	bool isDebugMode = false;
#endif


	//現在の番号  
	GoColor currentMark;

	//現在の状態
	GameStatus currentStatus;

	//テスト用のフォント
	Font font20{ 20 };

	/// <summary>
	/// 左クリックされたら空セルに現在の色の碁石情報を入れる
	/// </summary>
	/// <param name="goStoneColor">現在の色</param>
	void CellHitBox(GoColor goStoneColor);
	
	/// <summary>
	/// 5個そろってるかをチェックする
	/// </summary>
	/// <param name="goStoneColor">チェックする色</param>
	void CheckLine(GoColor goStoneColor);
	
	/// <summary>
	/// 配列の座標からグラフィック座標をとる
	/// </summary>
	/// <param name="mapPos">配列のx,y座標</param>
	/// <returns>x,y</returns>
	Point GetPosition(Point mapPos)const;
	
	/// <summary>
	/// AIの重みデータを作成
	/// </summary>
	/// <param name="goColor">石の色</param>
	void CPUDataManagement(GoColor goColor);

	/// <summary>
	/// Playerの重みデータを作成
	/// </summary>
	/// <param name="goColor">石の色</param>
	void PlayerDataManagement(GoColor goColor);
	
	/// <summary>
	/// AIの横並び数のデータを作成する
	/// </summary>
	/// <param name="x">AI配列のx座標</param>
	/// <param name="y">AI配列のy座標</param>
	/// <param name="goColor">石の色</param>
	void AIxLineDataTableMake(int x, int y,GoColor goColor,AITable (*aitable)[GoBoardSize]);

	/// <summary>
	/// AIの縦並び数のデータを作成する
	/// </summary>
	/// <param name="x">AI配列のx座標</param>
	/// <param name="y">AI配列のy座標</param>
	/// <param name="goColor">石の色</param>
	void AIyLineDataTableMake(int x, int y, GoColor goColor, AITable(*aitable)[GoBoardSize]);
	
	/// <summary>
	/// AIの斜め並び数のデータを作成する
	/// </summary>
	/// <param name="x">AI配列のx座標</param>
	/// <param name="y">AI配列のy座標</param>
	/// <param name="Xadd">xが増加する数</param>
	/// <param name="Yadd">yが増加する数</param>
	/// <param name="diagonal">参照する配列</param>
	/// <param name="goColor">石の色</param>
	void AIdiagonalLineDataTableMake(int x, int y , int Xadd, int Yadd, double& diagonal, GoColor goColor);
	
	/// <summary>
	/// AIの右下並びデータを作成する
	/// </summary>
	/// <param name="x">AI配列のx座標</param>
	/// <param name="y">AI配列のy座標</param>
	/// <param name="goColor">石の色</param>
	void AIdiagonalRightDown(int x, int y, GoColor goColor, AITable(*aitable)[GoBoardSize]);

	/// <summary>
	/// AIの左下並びデータを作成する
	/// </summary>
	/// <param name="x">AI配列のx座標</param>
	/// <param name="y">AI配列のy座標</param>
	/// <param name="goColor">石の色</param>
	void AIdiagonalLeftDown(int x, int y, GoColor goColor, AITable(*aitable)[GoBoardSize]);
	
	/// <summary>
	/// 配列でXが盤上か？trueなら盤上
	/// </summary>
	/// <param name="x">配列のx座標</param>
	/// <returns>trueかfalseか、画面内ならtrue</returns>
	bool IsWithinRangeX(int x);

	/// <summary>
	/// 配列でYが盤上か？trueなら盤上
	/// </summary>
	/// <param name="x">配列のy座標</param>
	/// <returns>trueかfalseか、画面内ならtrue</returns>
	bool IsWithinRangeY(int y);

	/// <summary>
	/// 配列でX,Yが盤上か？trueなら盤上
	/// </summary>
	/// <param name="x">配列のx,y座標</param>
	/// <returns>trueかfalseか、画面内ならtrue</returns>
	bool IsWithinRange(int x,int y);

	/// <summary>
	/// CPUAI用の関数
	/// </summary>
	void CPUPlay(GoColor cpuColor);


public:

	FiveRows();

	//試合が終わってGameシーンから抜けるときtrueにする
	//初期化はシーンを切り替えるため必要ない
	bool isFinishGame = false;

	/// <summary>
	/// ゲーム管理、描画以外はすべてここに入ってる
	/// </summary>
	/// <param name="currentMode">1Pか2Pかを判別</param>
	/// <param name="cpuColor">CPUの色、デフォルトは黒</param>
	void GameManagement(VSPlayerOrCPU currentMode, GoColor cpuColor = GoColor::Black);

	/// <summary>
	/// ゲーム管理、描画以外はすべてここに入ってる
	/// </summary>
	void PlayerGameManagement();


	/// <summary>
	/// ゲーム管理、描画以外はすべてここに入ってる
	/// </summary>
	/// <param name="cpuColor">CPUの色</param>
	void CPUGameManagement(GoColor cpuColor);


	/// <summary>
	///囲碁盤画像の描画
	///碁石の描画
	///マウスカーソルが触れると半透明の丸を表示 
	/// </summary>
	void BoardDraw()const;

	/// <summary>
	/// デバッグ描画
	/// </summary>
	void DebugDraw()const;

	/// <summary>
   /// 初期化
   /// </summary>
	void Initialize();
};

