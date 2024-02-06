#pragma once
#include"Base.h"

class SetUp : public App::Scene
{
private:
    //白碁石画像
    Texture WhiteStoneTex{ U"image/white.png" };

    //黒碁石画像
    Texture BlackStoneTex{ U"image/black.png" };

    //背景画像(灰色)
    const Texture BackScreen{ U"image/SetUpBack.jpg" };
    
    //背景画像(オレンジ)
    const Texture BackScreen2{ U"image/SetUpBack2.jpg" };

    //背景画像(畳)
    const Texture BackScreen3{ U"image/tatami.jpg" };

    /// <summary>
   /// 状態
   /// </summary>
    enum class SetUpStatus
    {
        AudioSetUp,      //音量調整
        SelectMusic,      //BGM,音声変更
        Back,            //タイトルへ戻る
    };

    //現在の状態
    SetUpStatus currentStatus;


    //メニューの定義---------------------------------------------------------------------------------------------------------------
    //箱の情報定義
    mutable BoxDraw audioSetUpMenu;
    mutable BoxDraw soundLevelSetUpMenu;
    mutable BoxDraw backMenu;

    //最初のメニューの幅と高さ
    const Size MenuBoxSize = { 320,100 };

    //始点
    const int MenuStartPoint = 100;

    //間隔数値
    const int MenuSpace = 100;
    //------------------------------------------------------------------------------------------------------------------------------

    /// <summary>
    /// 選択できる四角の処理
    /// </summary>
    void ChangeScene(BoxDraw boxdraw, SetUpStatus titleStatus);



public:

    SetUp(const InitData& init)
        : IScene(init)
    {
        Initialize();
    }
    ~SetUp();

    void update() override;

    void draw() const override;

    void Initialize();
};
