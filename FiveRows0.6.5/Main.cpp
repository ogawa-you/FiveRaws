#include"Scene.h"


void Main()
{
	//映像出力設定
	Window::Resize(DisplayResolution::HD_1280x720);	//ウィンドウサイズ設定
	Scene::SetBackground(ColorF(0.3, 0.3, 0.3));	//シーンの色を灰色に設定

	//シーン管理
	SceneManager<SceneName, GameData> manager;

	manager.add<Title>(SceneName::Title);
	manager.add<SetUp>(SceneName::SetUp);
	manager.add<Game>(SceneName::Game);
	manager.add<SetUpSelectMusic>(SceneName::SetUpSelectMusic);
	manager.add<SetUpAudio>(SceneName::SetUpAudio);
	manager.add<GameOver>(SceneName::GameOver);
	manager.add<GameClear>(SceneName::GameClear);
	manager.add<Credit>(SceneName::Credit);
	manager.add<Finish>(SceneName::Finish);


	while (System::Update())
	{
		GameData::MainVolume	= GameData::selectMainVolume * 2;
		GameData::EffectVolume	= GameData::selectEffectVolume * 0.01;
		GameData::BGMVolume		= GameData::selectBGMVolume * 0.01;

		if (!manager.update())
		{
			break;
		}
	}
}
