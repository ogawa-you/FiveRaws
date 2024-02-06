#include "Title.h"

Title::~Title()
{

}

void Title::Initialize()
{

	//五目並べ1pのメニュー設定
	fiveRows1pBox.Set(MenuBoxSize, U"1Pプレイ", MenuStartPoint, MenuSpace, 0);


	//五目並べ2pのメニュー設定
	fiveRows2pBox.Set(MenuBoxSize, U"2Pプレイ",MenuStartPoint,MenuSpace,1);


	//設定のメニュー設定
	setUpBox.Set(MenuBoxSize, U"設定", MenuStartPoint, MenuSpace, 2);
	//----------------------------------------------------------------------------------------------------------------------------

	//最初になにが選ばれてるか
	currentStatus = TitleStatus::FiveRows1P;
}

void Title::update()
{
	getData().WABGM.play();
	
	getData().WABGM.setVolume(GameData::MainVolume * GameData::BGMVolume);

	//五目並べ1Pのメニュー処理
	ChangeScene(fiveRows1pBox, TitleStatus::FiveRows1P);

	//五目並べ2Pのメニュー処理
	ChangeScene(fiveRows2pBox,TitleStatus::FiveRows2P);

	//設定のメニュー処理
	ChangeScene(setUpBox, TitleStatus::SetUp);

	if (move >= 50)
	{
		turn = false;
	}

	if (move <= 0)
	{
		turn = true;
	}
	
	if (move2 >= 40)
	{
		turn2 = false;
	}

	if (move2 <= 0)
	{
		turn2 = true;
	}

	if (turn)
	{
		move += 0.1;
	}
	else
	{
		move -= 0.1;
	}
	
	if (turn2)
	{
		move2 += 0.1;
	}
	else
	{
		move2 -= 0.1;
	}
}

void Title::draw() const
{
	//背景
	TitlePng.scaled(0.8).draw();

	kumo.scaled(1.2).draw(-80 - move,450);
	kumo2.scaled(1.2).draw(760+ move2, 420);
	
	//タイトルの下に巻物画像表示
	Makimono.scaled(0.9).draw(280,0);

	//タイトル表示
	TitleName.scaled(0.5).drawAt(660,140);

	//五目並べ1pのメニュー描画
	fiveRows1pBox.DrawBoxStoneVer();
	
	//五目並べ2pのメニュー描画
	fiveRows2pBox.DrawBoxStoneVer();

	//設定のメニュー描画
	setUpBox.DrawBoxStoneVer();

	//font20(U"move:",move).draw(0, 0);
}

void Title::ChangeScene(BoxDraw boxdraw, TitleStatus titleStatus)
{
	//RECT型に変更
	Rect rect = { boxdraw.pos,boxdraw.size };

	if (rect.mouseOver())
	{
		//マウスオーバーしたらステータスを変更
		currentStatus = titleStatus;

		//左クリックで状態遷移
		if (MouseL.down())
		{
			getData().WABGM.stop();

			switch (currentStatus)
			{
			case Title::TitleStatus::FiveRows1P:
				getData().StoneSound.playOneShot(GameData::MainVolume * GameData::EffectVolume);
				getData().currentMode = VSPlayerOrCPU::VSCPU;
				if (getData().currentTurn == ForwardOrBackward::ForWard)getData().CPUColor = GoColor::White;
				if (getData().currentTurn == ForwardOrBackward::BackWard)getData().CPUColor = GoColor::Black;
				if (getData().currentTurn == ForwardOrBackward::Random)RandomBool() ? getData().CPUColor = GoColor::White : getData().CPUColor = GoColor::Black;
				changeScene(SceneName::Game);
				break;				

			case Title::TitleStatus::FiveRows2P:
				getData().StoneSound.playOneShot(GameData::MainVolume * GameData::EffectVolume);
				getData().currentMode = VSPlayerOrCPU::VSPlayer;
				changeScene(SceneName::Game);
				break;

			case Title::TitleStatus::SetUp:
				getData().StoneSound.playOneShot(GameData::MainVolume * GameData::EffectVolume);
				changeScene(SceneName::SetUp);
				break;

			default:
				break;
			}
		}
	}

}
