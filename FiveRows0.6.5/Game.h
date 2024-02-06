#pragma once
#include"Base.h"
#include"FiveRows.h"

class Game : public App::Scene
{
private:

    FiveRows gomoku;

public:

    Game(const InitData& init)
        : IScene(init)
    {
        Initialize();
    }
    ~Game();

    void update() override;

    void draw() const override;

    void Initialize();//‰Šú‰»
};


