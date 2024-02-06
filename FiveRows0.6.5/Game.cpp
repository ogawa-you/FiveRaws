#include "Game.h"


Game::~Game()
{
	
}

void Game::Initialize()
{
    //初期定義

    gomoku.Initialize();
}


void Game::update()
{
    gomoku.GameManagement(getData().currentMode,getData().CPUColor);

    if(gomoku.isFinishGame)changeScene(SceneName::Title);
}

void Game::draw() const
{
	gomoku.BoardDraw();//五目並べの描画
}