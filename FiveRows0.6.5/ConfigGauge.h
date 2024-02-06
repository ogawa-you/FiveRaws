#include<Siv3D.hpp>

#pragma once
class ConfigGauge
{
public:
	ConfigGauge()
	{

	}
	Audio music;

	double effectVolume;

	const int gaugeCount = 10;	//�Q�[�W�̕�����

	int selectVolume;			//���ʂ̑傫��

	Rect gaugeRect;				//���ʃQ�[�W�̍���̍��W�ƕ��ƍ���

	double widthSpace;			//�c���̉����̊Ԋu

	Rect selectHitBox;			//���������蔻��

	Color selectColor = Color(62, 58, 57);		//�I�����Ă鎞�̐F

	Color notSelectColor = Color(137, 137, 137);//�I�����ĂȂ����̐F
	
	Font font20{ 20 };			//�t�H���g

	Font font25{ 25 };			//�t�H���g

	String string;				//�\�����镶��

	bool select = false;		//���ݑI������Ă邩

	mutable bool debug = false; //�f�o�b�O���[�h

	//���W�Z�b�g
	void Set(int x,int y,int w,int h,int volume,String _string);	

	//���W�Z�b�g
	void Set(Rect _gaugeRect, int volume,String _string);

	//���Z�b�g
	void AudioSet(Audio _music,double _effectVolume);

	//�Q�[�W�����A����
	void CreateGauge();

	//�Q�[�W�����A�`��
	void GaugeDraw()const;
};

