#include<Siv3D.hpp>
#include"BoxDraw.h"
#pragma once

//近日実装予定
namespace BGM
{

}

namespace EffectSoundSelect
{
    
}

namespace EndGameSoundSelect
{

}


/// <summary>
/// 碁石の現在の色
/// </summary>
enum class GoColor
{
    //空
    None,
    //白
    White,
    //黒
    Black,
};

/// <summary>
/// 設定画面で設定できるプレイヤーが先行か後攻か
/// </summary>
enum class ForwardOrBackward
{
    //先行
    ForWard,
    //後攻
    BackWard,
    //ランダム
    Random
};

/// <summary>
/// PVPかPVCか
/// </summary>
enum class VSPlayerOrCPU
{
    VSPlayer,	//PlayerVSPlayer対戦
    VSCPU		//PlayerVSCPU対戦
};

/// <summary>
/// 全体で使う変数
/// </summary>
struct GameData
{
    //CPUの色
    GoColor CPUColor = {GoColor::Black};

    //プレイヤーの先行後攻を管理する
    ForwardOrBackward currentTurn = {ForwardOrBackward::BackWard};

    //1pプレイか2pプレイかを管理する
    VSPlayerOrCPU currentMode;

    //設置したときの石の音
    Audio StoneSound{ Audio(U"sound/石音.mp3") };

    //BGM
    Audio WABGM{ Audio(U"sound/和風.mp3", Loop::Yes) };

    //音量
    inline static double MainVolume = 1.0;  //メイン音量(すべての音量はこの値に依存する)
    inline static double BGMVolume = 0.1;   //BGMの音量(BGNの値はMainVolume ＊ BGMVolumeの計算結果依存)
    inline static double EffectVolume = 0.1;//効果音の音量(効果音の値はMainVolume * EffectVolumeの計算結果依存)

    //設定画面で使う音量設定
    inline static int selectMainVolume = 5;   //主音量の大きさ
    inline static int selectEffectVolume = 5; //効果音の大きさ
    inline static int selectBGMVolume = 5;  //BGMの大きさ
    
    //未使用
#ifdef _DEBUG
//デバッグモードを切り替えるフラグ
    inline static bool isDebugMode = true;
#else
    //デバッグモードを切り替えるフラグ
    inline static bool isDebugMode = false;
#endif
};


enum class SceneName
{
     Title   // アニメーション付きタイトルロゴ表示
    , Game    // ゲーム本編
    , GameOver // ゲームオーバー
    , GameClear // 開発者や協力者のスタッフロール
    , Credit
    , SetUp //設定
    , SetUpAudio //音楽選択
    , SetUpSelectMusic //音量調整
    , Finish
    , Other// 他に必要のがあれば随時追加する
};

using App = SceneManager<SceneName, GameData>;

