#include "SetUp.h"

void SetUp::ChangeScene(BoxDraw boxdraw,SetUpStatus setUpStatus)
{
	//RECT型に変更
	Rect rect = { boxdraw.pos,boxdraw.size };

	if (rect.mouseOver())
	{
		//マウスオーバーしたらステータスを変更
		currentStatus = setUpStatus;

		//左クリックで状態遷移
		if (MouseL.down())
		{
			switch (currentStatus)
			{
			case SetUp::SetUpStatus::AudioSetUp:
				getData().StoneSound.playOneShot(GameData::MainVolume * GameData::EffectVolume);
				changeScene(SceneName::SetUpAudio);
				break;
			case SetUp::SetUpStatus::SelectMusic:
				getData().StoneSound.playOneShot(GameData::MainVolume * GameData::EffectVolume);
				changeScene(SceneName::SetUpSelectMusic);
				break;
			case SetUp::SetUpStatus::Back:
				getData().StoneSound.playOneShot(GameData::MainVolume * GameData::EffectVolume);
				changeScene(SceneName::Title);
				break;
			default:
				break;
			}
		}
	}
}

SetUp::~SetUp()
{

}

void SetUp::Initialize()
{
	//音量設定メニュー設定
	audioSetUpMenu.Set(MenuBoxSize, U"音量設定",MenuStartPoint, MenuSpace, 0);

	//BGMメニュー設定
	soundLevelSetUpMenu.Set(MenuBoxSize, U"その他設定", MenuStartPoint, MenuSpace,1);

	//戻るメニュー設定
	backMenu.Set(MenuBoxSize, U"戻る", MenuStartPoint, MenuSpace, 2);
	//----------------------------------------------------------------------------------------------------------------------------

	//最初になにが選ばれてるか
	currentStatus = SetUpStatus::AudioSetUp;
}

void SetUp::update()
{
	//BGM,声変更メニュー処理
	ChangeScene(audioSetUpMenu, SetUpStatus::AudioSetUp);

	//音量設定メニュー処理
	ChangeScene(soundLevelSetUpMenu, SetUpStatus::SelectMusic);

	//戻るメニュー処理
	ChangeScene(backMenu, SetUpStatus::Back);
}

void SetUp::draw()const
{
	//背景描画
	BackScreen3.resized(1280).draw();

	//BGM,声変更メニュー描画
	audioSetUpMenu.DrawBoxStoneVer();

	//音量設定メニュー描画
	soundLevelSetUpMenu.DrawBoxStoneVer();

	//戻るメニュー描画
	backMenu.DrawBoxStoneVer();
}



