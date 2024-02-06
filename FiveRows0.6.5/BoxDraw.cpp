#include "BoxDraw.h"

void BoxDraw::Set(Size _size, String _text, int _startpos, int _space, int _number)
{
	size = _size;

	text = _text;

	startpos = _startpos;

	space = _space;

	number = _number;

	//x���W�̓X�N���[���T�C�Y�̓񕪂̈ꂩ�甠�̉����̓񕪂̈����������
	//y���W�͎n�_���甠�̉����̃T�C�Y�ƊԊu���l�𑫂������̂𔠂̐�����������
	pos = { Scene::Width() / 2 - size.x / 2, startpos + ((size.y + space) * number) };
}

void BoxDraw::DrawBox()const
{
	double x = pos.x;

	double y = pos.y;

	double w = size.x;

	double h = size.y;
	//--------------------------------------------------------------------------------------
	//���C���ƂȂ锠
	RoundRect MainBox{ x     ,	y    ,	w	     ,	h	     ,	10 };
	//���C���̔��̒��ɂ����
	RoundRect InsideBoxFrame{ x + 5 ,	y + 5,	w - 5 * 2,	h - 5 * 2,	 5 };
	//���C���̔��Ɠ����̊Ԃɒ��F
	RoundRect BoxFrameColor{ x + 2 ,	y + 2,	w - 2 * 2,	h - 2 * 2,	10 };


	//�`��
	MainBox.drawShadow(MainBox.mouseOver() ? Vec2(8, 8) : Vec2(4, 4), 16, 2).draw(Palette::White).drawFrame(2, Palette::Black);

	InsideBoxFrame.drawFrame(3, Palette::Black);

	BoxFrameColor.drawFrame(2, Palette::Lightgrey);

	//�J�[�\������������F��ς��ĎO�p��\��
	if (MainBox.mouseOver())
	{
		BoxFrameColor.drawFrame(2, Palette::Red);
		RedPin.scaled(0.3).rotatedAt(25, 25, 90_deg).draw(x - 75, y + 5);
		RedPin.scaled(0.3).rotatedAt(25, 25, 270_deg).draw(x + w + 2, y + 27);
	}

	//-------------------------------------------------------------------------------------------

	font(text).drawAt(x + w / 2, y + h / 2, Palette::Black);//������`��
}

void BoxDraw::DrawBoxStoneVer()const
{
	double x = pos.x;

	double y = pos.y;

	double w = size.x;

	double h = size.y;
	//--------------------------------------------------------------------------------------
	//���C���ƂȂ锠
	RoundRect MainBox{ x     ,	y    ,	w	     ,	h	     ,	10 };
	//���C���̔��̒��ɂ����
	RoundRect InsideBoxFrame{ x + 5 ,	y + 5,	w - 5 * 2,	h - 5 * 2,	 5 };
	//���C���̔��Ɠ����̊Ԃɒ��F
	RoundRect BoxFrameColor{ x + 2 ,	y + 2,	w - 2 * 2,	h - 2 * 2,	10 };


	//�`��
	MainBox.drawShadow(MainBox.mouseOver() ? Vec2(8, 8) : Vec2(4, 4), 16, 2).draw(Palette::White).drawFrame(2, Palette::Black);

	InsideBoxFrame.drawFrame(3, Palette::Black);

	BoxFrameColor.drawFrame(2, Palette::Lightgrey);

	//�J�[�\������������F��ς��ĎO�p��\��
	if (MainBox.mouseOver())
	{
		BoxFrameColor.drawFrame(2, Palette::Red);
		WhiteStoneTex.scaled(0.1).drawAt(x + w + 30,y + h / 2 );
		BlackStoneTex.scaled(0.1).drawAt(x - 30, y + h / 2 );
	}

	//-------------------------------------------------------------------------------------------

	font(text).drawAt(x + w / 2, y + h / 2 ,Palette::Black);//������`��
}

