#pragma once
#include"Base.h"

class Title : public App::Scene
{
private:
    //�摜����
    const Texture TitleName{ U"image/Title3.png" };
    const Texture TitlePng{ U"image/title.png" };
    const Texture RedPin{ U"image/Red.png" };
    const Texture Makimono{ U"image/makimono.png" };
    const Texture kumo{ U"image/kumo4.png" };
    const Texture kumo2{ U"image/kumo5.png" };


    /// <summary>
    /// ���
    /// </summary>
    enum class TitleStatus
    {
        //�ܖڕ���1p
        FiveRows1P, 
        //�ܖڕ���2p
        FiveRows2P,
        //�ݒ�
        SetUp,                
    };

    //���j���[�̒�`----------------------------------------------------------------------------------------------------------------
    //���̏���`
    mutable BoxDraw fiveRows1pBox;
    mutable BoxDraw fiveRows2pBox;
    mutable BoxDraw setUpBox;

    //�ŏ��̃��j���[�̕��ƍ���
    const Size MenuBoxSize = { 220,80 };

    //�n�_
    const int MenuStartPoint = 300;

    //�Ԋu���l
    const int MenuSpace = 60;
    //------------------------------------------------------------------------------------------------------------------------------

    //���݂̏��
    TitleStatus currentStatus;

    double move = 0;
    double move2 = 0;

    bool turn = false;
    bool turn2 = false;

    Font font20{ 20 };

    /// <summary>
    /// �I���ł���l�p�̏���
    /// </summary>
    void ChangeScene(BoxDraw boxdraw, TitleStatus titleStatus);

public:

    Title(const InitData& init)
        : IScene(init)
    {
        Initialize();
    }
    ~Title();

    void update() override;

    void draw() const override;

    /// <summary>
    /// ������
    /// </summary>
    /// <param name="init"></param>
    void Initialize();
};