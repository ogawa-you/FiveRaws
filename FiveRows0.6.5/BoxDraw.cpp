#include "BoxDraw.h"

void BoxDraw::Set(Size _size, String _text, int _startpos, int _space, int _number)
{
	size = _size;

	text = _text;

	startpos = _startpos;

	space = _space;

	number = _number;

	//x座標はスクリーンサイズの二分の一から箱の横幅の二分の一を引いた数
	//y座標は始点から箱の横幅のサイズと間隔数値を足したものを箱の数だけかける
	pos = { Scene::Width() / 2 - size.x / 2, startpos + ((size.y + space) * number) };
}

void BoxDraw::DrawBox()const
{
	double x = pos.x;

	double y = pos.y;

	double w = size.x;

	double h = size.y;
	//--------------------------------------------------------------------------------------
	//メインとなる箱
	RoundRect MainBox{ x     ,	y    ,	w	     ,	h	     ,	10 };
	//メインの箱の中にある線
	RoundRect InsideBoxFrame{ x + 5 ,	y + 5,	w - 5 * 2,	h - 5 * 2,	 5 };
	//メインの箱と内側の間に着色
	RoundRect BoxFrameColor{ x + 2 ,	y + 2,	w - 2 * 2,	h - 2 * 2,	10 };


	//描画
	MainBox.drawShadow(MainBox.mouseOver() ? Vec2(8, 8) : Vec2(4, 4), 16, 2).draw(Palette::White).drawFrame(2, Palette::Black);

	InsideBoxFrame.drawFrame(3, Palette::Black);

	BoxFrameColor.drawFrame(2, Palette::Lightgrey);

	//カーソルがあったら色を変えて三角を表示
	if (MainBox.mouseOver())
	{
		BoxFrameColor.drawFrame(2, Palette::Red);
		RedPin.scaled(0.3).rotatedAt(25, 25, 90_deg).draw(x - 75, y + 5);
		RedPin.scaled(0.3).rotatedAt(25, 25, 270_deg).draw(x + w + 2, y + 27);
	}

	//-------------------------------------------------------------------------------------------

	font(text).drawAt(x + w / 2, y + h / 2, Palette::Black);//文字を描画
}

void BoxDraw::DrawBoxStoneVer()const
{
	double x = pos.x;

	double y = pos.y;

	double w = size.x;

	double h = size.y;
	//--------------------------------------------------------------------------------------
	//メインとなる箱
	RoundRect MainBox{ x     ,	y    ,	w	     ,	h	     ,	10 };
	//メインの箱の中にある線
	RoundRect InsideBoxFrame{ x + 5 ,	y + 5,	w - 5 * 2,	h - 5 * 2,	 5 };
	//メインの箱と内側の間に着色
	RoundRect BoxFrameColor{ x + 2 ,	y + 2,	w - 2 * 2,	h - 2 * 2,	10 };


	//描画
	MainBox.drawShadow(MainBox.mouseOver() ? Vec2(8, 8) : Vec2(4, 4), 16, 2).draw(Palette::White).drawFrame(2, Palette::Black);

	InsideBoxFrame.drawFrame(3, Palette::Black);

	BoxFrameColor.drawFrame(2, Palette::Lightgrey);

	//カーソルがあったら色を変えて三角を表示
	if (MainBox.mouseOver())
	{
		BoxFrameColor.drawFrame(2, Palette::Red);
		WhiteStoneTex.scaled(0.1).drawAt(x + w + 30,y + h / 2 );
		BlackStoneTex.scaled(0.1).drawAt(x - 30, y + h / 2 );
	}

	//-------------------------------------------------------------------------------------------

	font(text).drawAt(x + w / 2, y + h / 2 ,Palette::Black);//文字を描画
}

