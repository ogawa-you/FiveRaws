#pragma once
#include"Base.h"

class SetUpSelectMusic : public App::Scene
{
private:
    Font font20{ 20 };
       
    Texture BackScreenTex{ U"image/irori.jpg" };

    RoundRect backBox{ 200, 150, 824, 476, 10 };//ÉQÅ[ÉWÇÃîwåiÇÃî†ÇÃèÓïÒ

    GoColor debugGoColor;

    mutable size_t index;

    mutable bool isPrecedence = false;

   bool isClick = false;

   Circle hitBox[3];

public:

    SetUpSelectMusic(const InitData& init)
        : IScene(init)
    {
        Initialize();
    }
    ~SetUpSelectMusic();

    void update() override;

    void draw() const override;

    void Initialize();
};


