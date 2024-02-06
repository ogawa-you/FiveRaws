#pragma once
#include"Base.h"
#include"ConfigGauge.h"

class SetUpAudio : public App::Scene
{
private:
    Texture BackScreenTex{ U"image/irori.jpg" };

    Font font20{ 20 };

    

    RoundRect backBox{ 200, 150, 824, 476, 10 };//ゲージの背景の箱の情報

    double widthSpace = 35.1;//縦線の横幅の間隔

    double heightSpace = 120;//音量ゲージの縦幅の間隔

    Rect firstGaugeRect = { 481 ,255 ,371, 26 };//ゲージの情報
    Rect secondGgaugeRect = { 481 ,375 ,371, 26 };//ゲージの情報
    Rect thirdGaugeRect = { 481 ,495 ,371, 26 };//ゲージの情報

    Vec2 lineLeftTopPos = { 481 ,255 };//一本目の音量ゲージの左上の座標

    Vec2 lineWidthHeight = { 371, 26 };//音量ゲージの幅と高さ

    Color selectColor = Color(62, 58, 57);//選択してる時の色

    Color notSelectColor = Color(137, 137, 137);//選択してない時の色

    double cellSize = 35.1;//当たり判定の縦幅と横幅

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


