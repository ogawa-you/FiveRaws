#include<Siv3D.hpp>


class BoxDraw
{
public:
	//�{�b�N�X�̉��ɏo���O�p�`
	Texture RedPin{ U"image/Red.png" };

	Texture WhiteStoneTex{ U"image/white.png" };//����Ή摜
	Texture BlackStoneTex{ U"image/black.png" };//����Ή摜



	//������\������Ƃ��̃t�H���g
	Font font{ 30 };

	//�{�b�N�X��x,y���W
	Point pos;

	//�{�b�N�X�̏c���A����
	Size size;

	//�{�b�N�X�̒��ɕ\�����镶��
	String text;

	//�n�_
	int startpos;

	//�Ԋu���l
	int space;

	//���ڂ̃{�b�N�X��
	int number;

	//�f�t�H���g�R���X�g���N�^�[
	BoxDraw() {}

	//������`
	void Set(Size _size, String _text,int _startpos,int _space,int _number);
	

	/// <summary>
	/// BOX��`��
	/// </summary>
	void DrawBox()const;


	/// <summary>
	///BOX��`��
	/// </summary>
	void DrawBoxStoneVer()const;
};

