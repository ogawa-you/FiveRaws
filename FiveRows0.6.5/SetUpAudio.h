#pragma once
#include"Base.h"
#include"ConfigGauge.h"

class SetUpAudio : public App::Scene
{
private:
    Texture BackScreenTex{ U"image/irori.jpg" };

    Font font20{ 20 };

    

    RoundRect backBox{ 200, 150, 824, 476, 10 };//�Q�[�W�̔w�i�̔��̏��

    double widthSpace = 35.1;//�c���̉����̊Ԋu

    double heightSpace = 120;//���ʃQ�[�W�̏c���̊Ԋu

    Rect firstGaugeRect = { 481 ,255 ,371, 26 };//�Q�[�W�̏��
    Rect secondGgaugeRect = { 481 ,375 ,371, 26 };//�Q�[�W�̏��
    Rect thirdGaugeRect = { 481 ,495 ,371, 26 };//�Q�[�W�̏��

    Vec2 lineLeftTopPos = { 481 ,255 };//��{�ڂ̉��ʃQ�[�W�̍���̍��W

    Vec2 lineWidthHeight = { 371, 26 };//���ʃQ�[�W�̕��ƍ���

    Color selectColor = Color(62, 58, 57);//�I�����Ă鎞�̐F

    Color notSelectColor = Color(137, 137, 137);//�I�����ĂȂ����̐F

    double cellSize = 35.1;//�����蔻��̏c���Ɖ���

    RectF select[3];
    bool selectGauge[3];

    ConfigGauge firstGauge;
    ConfigGauge secondGauge;
    ConfigGauge thirdGauge;

public:

    SetUpAudio(const InitData& init)
        : IScene(init)
    {
        Initialize();
    }
    ~SetUpAudio();

    void update() override;

    void draw() const override;

    void Initialize();
};


