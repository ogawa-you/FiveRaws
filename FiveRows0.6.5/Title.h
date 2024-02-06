#pragma once
#include"Base.h"

class Title : public App::Scene
{
private:
    //画像たち
    const Texture TitleName{ U"image/Title3.png" };
    const Texture TitlePng{ U"image/title.png" };
    const Texture RedPin{ U"image/Red.png" };
    const Texture Makimono{ U"image/makimono.png" };
    const Texture kumo{ U"image/kumo4.png" };
    const Texture kumo2{ U"image/kumo5.png" };


    /// <summary>
    /// 状態
    /// </summary>
    enum class TitleStatus
    {
        //五目並べ1p
        FiveRows1P, 
        //五目並べ2p
        FiveRows2P,
        //設定
        SetUp,                
    };

    //メニューの定義----------------------------------------------------------------------------------------------------------------
    //箱の情報定義
    mutable BoxDraw fiveRows1pBox;
    mutable BoxDraw fiveRows2pBox;
    mutable BoxDraw setUpBox;

    //最初のメニューの幅と高さ
    const Size MenuBoxSize = { 220,80 };

    //始点
    const int MenuStartPoint = 300;

    //間隔数値
    const int MenuSpace = 60;
    //------------------------------------------------------------------------------------------------------------------------------

    //現在の状態
    TitleStatus currentStatus;

    double move = 0;
    double move2 = 0;

    bool turn = false;
    bool turn2 = false;

    Font font20{ 20 };

    /// <summary>
    /// 選択できる四角の処理
    /// </summary>
    void ChangeScene(BoxDraw boxdraw, TitleStatus titleStatus);

public:

    Title(const InitData& init)
        : IScene(init)
    {
        Initialize();
    }
    ~Title();

    void update() override;

    void draw() const override;

    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name="init"></param>
    void Initialize();
};