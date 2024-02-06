#include "SetUpSelectMusic.h"


SetUpSelectMusic::~SetUpSelectMusic()
{

}

void SetUpSelectMusic::Initialize()
{
	if (getData().currentTurn == ForwardOrBackward::ForWard)index = 0;
	if (getData().currentTurn == ForwardOrBackward::BackWard)index = 1;
	if (getData().currentTurn == ForwardOrBackward::Random)index = 2;

	for (int i = 0; i < 3; i++)
	{
		hitBox[i] = { 318,238 + (double)(i * 40),10 };
	}
}

void SetUpSelectMusic::update()
	
{
	//戻るボタン
	if (SimpleGUI::ButtonAt(U"Back", Vec2(50, 30)))
	{
		getData().StoneSound.playOneShot(GameData::MainVolume * GameData::EffectVolume);
		changeScene(SceneName::SetUp);
	}

	//選択した値によって先行後攻ランダムが決まる
	if (index == 0)
	{
		getData().currentTurn = ForwardOrBackward::ForWard;
	}
	if (index == 1)
	{
		getData().currentTurn = ForwardOrBackward::BackWard;
	}
	if (index == 2)
	{
		getData().currentTurn = ForwardOrBackward::Random;
	}

	for (int i = 0; i < 3; i++)
	{
		if (hitBox[i].mouseOver())
		{
			if (MouseL.down())
			{
				getData().StoneSound.playOneShot(GameData::MainVolume * GameData::EffectVolume);
			}
		}
	}
}


void SetUpSelectMusic::draw() const
{
	BackScreenTex.resized(1280).draw();

	SimpleGUI::ButtonAt(U"Back", Vec2(50, 30));

	RoundRect(backBox).draw(Palette::White).drawFrame(2, Palette::Black);

	RoundRect(backBox.x + 5, backBox.y + 5, backBox.w - 10, backBox.h - 10, 5).drawFrame(3, Palette::Black);

	RoundRect(backBox.x + 2, backBox.y + 2, backBox.w - 4, backBox.h - 4, 10).drawFrame(2, Palette::Lightgrey);


	//幅はテキストに合わせる
	SimpleGUI::RadioButtons(index, { U"先行", U"後攻",U"ランダム"}, Vec2{300,220}, unspecified);
	
}
