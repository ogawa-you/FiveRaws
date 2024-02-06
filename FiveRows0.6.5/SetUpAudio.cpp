#include "SetUpAudio.h"


SetUpAudio::~SetUpAudio()
{

}

void SetUpAudio::Initialize()
{
	firstGauge.Set(firstGaugeRect,GameData::selectMainVolume,U"Žå‰¹—Ê");
	secondGauge.Set(secondGgaugeRect, GameData::selectEffectVolume,U"Œø‰Ê‰¹");
	thirdGauge.Set(thirdGaugeRect, GameData::selectBGMVolume,U"BGM");

	firstGauge.AudioSet(getData().StoneSound, GameData::MainVolume * GameData::EffectVolume);
	secondGauge.AudioSet(getData().StoneSound, GameData::MainVolume * GameData::EffectVolume);
	thirdGauge.AudioSet(getData().StoneSound, GameData::MainVolume * GameData::EffectVolume);
}

void SetUpAudio::update()
{
	if (SimpleGUI::ButtonAt(U"Back", Vec2(50, 30)))
	{
		getData().StoneSound.playOneShot(GameData::MainVolume * GameData::EffectVolume);
		changeScene(SceneName::SetUp);
	}

	firstGauge.CreateGauge();
	secondGauge.CreateGauge();
	thirdGauge.CreateGauge();

	GameData::selectMainVolume = firstGauge.selectVolume;
	GameData::selectEffectVolume = secondGauge.selectVolume;
	GameData::selectBGMVolume = thirdGauge.selectVolume;
}


void SetUpAudio::draw() const
{
	BackScreenTex.resized(1280).draw();

	SimpleGUI::ButtonAt(U"Back", Vec2(50, 30));

	RoundRect ( backBox ).draw(Palette::White).drawFrame(2, Palette::Black);

	RoundRect (backBox.x + 5, backBox.y + 5, backBox.w - 10, backBox.h - 10, 5).drawFrame(3, Palette::Black);

	RoundRect (backBox.x + 2, backBox.y + 2, backBox.w - 4, backBox.h - 4, 10).drawFrame(2, Palette::Lightgrey);

	firstGauge.GaugeDraw();
	secondGauge.GaugeDraw();
	thirdGauge.GaugeDraw();
}