#include<Siv3D.hpp>


class BoxDraw
{
public:
	//ボックスの横に出す三角形
	Texture RedPin{ U"image/Red.png" };

	Texture WhiteStoneTex{ U"image/white.png" };//白碁石画像
	Texture BlackStoneTex{ U"image/black.png" };//黒碁石画像



	//文字を表示するときのフォント
	Font font{ 30 };

	//ボックスのx,y座標
	Point pos;

	//ボックスの縦幅、横幅
	Size size;

	//ボックスの中に表示する文字
	String text;

	//始点
	int startpos;

	//間隔数値
	int space;

	//何個目のボックスか
	int number;

	//デフォルトコンストラクター
	BoxDraw() {}

	//初期定義
	void Set(Size _size, String _text,int _startpos,int _space,int _number);
	

	/// <summary>
	/// BOXを描画
	/// </summary>
	void DrawBox()const;


	/// <summary>
	///BOXを描画
	/// </summary>
	void DrawBoxStoneVer()const;
};

