#include "SetUp.h"

void SetUp::ChangeScene(BoxDraw boxdraw,SetUpStatus setUpStatus)
{
	//RECT�^�ɕύX
	Rect rect = { boxdraw.pos,boxdraw.size };

	if (rect.mouseOver())
	{
		//�}�E�X�I�[�o�[������X�e�[�^�X��ύX
		currentStatus = setUpStatus;

		//���N���b�N�ŏ�ԑJ��
		if (MouseL.down())
		{
			switch (currentStatus)
			{
			case SetUp::SetUpStatus::AudioSetUp:
				getData().StoneSound.playOneShot(GameData::MainVolume * GameData::EffectVolume);
				changeScene(SceneName::SetUpAudio);
				break;
			case SetUp::SetUpStatus::SelectMusic:
				getData().StoneSound.playOneShot(GameData::MainVolume * GameData::EffectVolume);
				changeScene(SceneName::SetUpSelectMusic);
				break;
			case SetUp::SetUpStatus::Back:
				getData().StoneSound.playOneShot(GameData::MainVolume * GameData::EffectVolume);
				changeScene(SceneName::Title);
				break;
			default:
				break;
			}
		}
	}
}

SetUp::~SetUp()
{

}

void SetUp::Initialize()
{
	//���ʐݒ胁�j���[�ݒ�
	audioSetUpMenu.Set(MenuBoxSize, U"���ʐݒ�",MenuStartPoint, MenuSpace, 0);

	//BGM���j���[�ݒ�
	soundLevelSetUpMenu.Set(MenuBoxSize, U"���̑��ݒ�", MenuStartPoint, MenuSpace,1);

	//�߂郁�j���[�ݒ�
	backMenu.Set(MenuBoxSize, U"�߂�", MenuStartPoint, MenuSpace, 2);
	//----------------------------------------------------------------------------------------------------------------------------

	//�ŏ��ɂȂɂ��I�΂�Ă邩
	currentStatus = SetUpStatus::AudioSetUp;
}

void SetUp::update()
{
	//BGM,���ύX���j���[����
	ChangeScene(audioSetUpMenu, SetUpStatus::AudioSetUp);

	//���ʐݒ胁�j���[����
	ChangeScene(soundLevelSetUpMenu, SetUpStatus::SelectMusic);

	//�߂郁�j���[����
	ChangeScene(backMenu, SetUpStatus::Back);
}

void SetUp::draw()const
{
	//�w�i�`��
	BackScreen3.resized(1280).draw();

	//BGM,���ύX���j���[�`��
	audioSetUpMenu.DrawBoxStoneVer();

	//���ʐݒ胁�j���[�`��
	soundLevelSetUpMenu.DrawBoxStoneVer();

	//�߂郁�j���[�`��
	backMenu.DrawBoxStoneVer();
}



