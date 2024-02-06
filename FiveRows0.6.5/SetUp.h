#pragma once
#include"Base.h"

class SetUp : public App::Scene
{
private:
    //����Ή摜
    Texture WhiteStoneTex{ U"image/white.png" };

    //����Ή摜
    Texture BlackStoneTex{ U"image/black.png" };

    //�w�i�摜(�D�F)
    const Texture BackScreen{ U"image/SetUpBack.jpg" };
    
    //�w�i�摜(�I�����W)
    const Texture BackScreen2{ U"image/SetUpBack2.jpg" };

    //�w�i�摜(��)
    const Texture BackScreen3{ U"image/tatami.jpg" };

    /// <summary>
   /// ���
   /// </summary>
    enum class SetUpStatus
    {
        AudioSetUp,      //���ʒ���
        SelectMusic,      //BGM,�����ύX
        Back,            //�^�C�g���֖߂�
    };

    //���݂̏��
    SetUpStatus currentStatus;


    //���j���[�̒�`---------------------------------------------------------------------------------------------------------------
    //���̏���`
    mutable BoxDraw audioSetUpMenu;
    mutable BoxDraw soundLevelSetUpMenu;
    mutable BoxDraw backMenu;

    //�ŏ��̃��j���[�̕��ƍ���
    const Size MenuBoxSize = { 320,100 };

    //�n�_
    const int MenuStartPoint = 100;

    //�Ԋu���l
    const int MenuSpace = 100;
    //------------------------------------------------------------------------------------------------------------------------------

    /// <summary>
    /// �I���ł���l�p�̏���
    /// </summary>
    void ChangeScene(BoxDraw boxdraw, SetUpStatus titleStatus);



public:

    SetUp(const InitData& init)
        : IScene(init)
    {
        Initialize();
    }
    ~SetUp();

    void update() override;

    void draw() const override;

    void Initialize();
};
