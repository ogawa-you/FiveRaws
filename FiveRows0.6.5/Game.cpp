#include "Game.h"


Game::~Game()
{
	
}

void Game::Initialize()
{
    //������`

    gomoku.Initialize();
}


void Game::update()
{
    gomoku.GameManagement(getData().currentMode,getData().CPUColor);

    if(gomoku.isFinishGame)changeScene(SceneName::Title);
}

void Game::draw() const
{
	gomoku.BoardDraw();//�ܖڕ��ׂ̕`��
}