#include <DxLib.h>
#include <cassert>
#include "../Input.h"
#include "../Application.h"
#include "SceneManager.h"
#include "GamePlayingScene.h"
#include "GameOverScene.h"
#include "PauseScene.h"
#include "../FileSystem/FileManager.h"
#include "../FileSystem/File.h"
#include "../Charactor/ControllerCharactor.h"
#include"../Charactor/Charactor.h"
#include "../Charactor/Actor.h"
#include"../Stage/BackGround.h"


GamePlayingScene::GamePlayingScene(SceneManager& manager) :
	Scene(manager)
{
	auto& fileMgr = m_manager.GetFileManager();
	m_imgFile = fileMgr.LoadGraphic(L"./Image/game.png");
	m_btnImg = fileMgr.LoadGraphic(L"./Image/UI/xbox_buttons.png", true);
	
	m_hero = std::make_shared<ControllerCharactor>(fileMgr, L"./Image/Charctor/hero",PlayerType::hero,1 ,Position2{ 220, 240 }, 3.0f);
	m_monk = std::make_shared<ControllerCharactor>(fileMgr, L"./Image/Charctor/monk",PlayerType::hero,2, Position2{ 420, 240 }, 2.0f);
	m_monk->SetOrigin(1);

	std::string animName = "adventurer-run-";
	m_hero->ChangeAnimation(animName);
	animName = "jump";
	m_monk->ChangeAnimation(animName);

	m_actors.push_back(m_hero);
	m_actors.push_back(m_monk);

	m_backGround = std::make_shared<BackGround>(fileMgr);

	m_frame = 60;
	m_updateFunc = &GamePlayingScene::FadeInUpdate;
	m_drawFunc = &GamePlayingScene::FadeDraw;

	//m_fileNames =
	//{
	//	"adventurer-air-attack-3-end-00.png",
	//	"adventurer-air-attack-3-end-01.png",
	//	"adventurer-air-attack-3-end-02.png",
	//	"adventurer-air-attack1-00.png",
	//	"adventurer-air-attack1-01.png",
	//	"adventurer-air-attack1-02.png",
	//	"adventurer-air-attack1-03.png",
	//	"adventurer-air-attack2-00.png",
	//	"adventurer-air-attack2-01.png",
	//	"adventurer-air-attack2-02.png",
	//	"adventurer-air-attack3-loop-00.png",
	//	"adventurer-air-attack3-loop-01.png",
	//	"adventurer-air-attack3-rdy-00.png",
	//	"adventurer-attack1-00.png",
	//	"adventurer-attack1-01.png",
	//	"adventurer-attack1-02.png",
	//	"adventurer-attack1-03.png",
	//	"adventurer-attack1-04.png",
	//	"adventurer-attack2-00.png",
	//	"adventurer-attack2-01.png",
	//	"adventurer-attack2-02.png",
	//	"adventurer-attack2-03.png",
	//	"adventurer-attack2-04.png",
	//	"adventurer-attack2-05.png",
	//	"adventurer-attack3-00.png",
	//	"adventurer-attack3-01.png",
	//	"adventurer-attack3-02.png",
	//	"adventurer-attack3-03.png",
	//	"adventurer-attack3-04.png",
	//	"adventurer-attack3-05.png",
	//	"adventurer-cast-00.png",
	//	"adventurer-cast-01.png",
	//	"adventurer-cast-02.png",
	//	"adventurer-cast-03.png",
	//	"adventurer-cast-loop-00.png",
	//	"adventurer-cast-loop-01.png",
	//	"adventurer-cast-loop-02.png",
	//	"adventurer-cast-loop-03.png",
	//	"adventurer-crnr-clmb-00.png",
	//	"adventurer-crnr-clmb-01.png",
	//	"adventurer-crnr-clmb-02.png",
	//	"adventurer-crnr-clmb-03.png",
	//	"adventurer-crnr-clmb-04.png",
	//	"adventurer-crnr-grb-00.png",
	//	"adventurer-crnr-grb-01.png",
	//	"adventurer-crnr-grb-02.png",
	//	"adventurer-crnr-grb-03.png",
	//	"adventurer-crnr-jmp-00.png",
	//	"adventurer-crnr-jmp-01.png",
	//	"adventurer-crouch-00.png",
	//	"adventurer-crouch-01.png",
	//	"adventurer-crouch-02.png",
	//	"adventurer-crouch-03.png",
	//	"adventurer-die-00.png",
	//	"adventurer-die-01.png",
	//	"adventurer-die-02.png",
	//	"adventurer-die-03.png",
	//	"adventurer-die-04.png",
	//	"adventurer-die-05.png",
	//	"adventurer-die-06.png",
	//	"adventurer-fall-00.png",
	//	"adventurer-fall-01.png",
	//	"adventurer-hurt-00.png",
	//	"adventurer-hurt-01.png",
	//	"adventurer-hurt-02.png",
	//	"adventurer-idle-00.png",
	//	"adventurer-idle-01.png",
	//	"adventurer-idle-02.png",
	//	"adventurer-idle-03.png",
	//	"adventurer-idle-2-00.png",
	//	"adventurer-idle-2-01.png",
	//	"adventurer-idle-2-02.png",
	//	"adventurer-idle-2-03.png",
	//	"adventurer-items-00.png",
	//	"adventurer-items-01.png",
	//	"adventurer-items-02.png",
	//	"adventurer-jump-00.png",
	//	"adventurer-jump-01.png",
	//	"adventurer-jump-02.png",
	//	"adventurer-jump-03.png",
	//	"adventurer-ladder-climb-00.png",
	//	"adventurer-ladder-climb-01.png",
	//	"adventurer-ladder-climb-02.png",
	//	"adventurer-ladder-climb-03.png",
	//	"adventurer-run-00.png",
	//	"adventurer-run-01.png",
	//	"adventurer-run-02.png",
	//	"adventurer-run-03.png",
	//	"adventurer-run-04.png",
	//	"adventurer-run-05.png",
	//	"adventurer-slide-00.png",
	//	"adventurer-slide-01.png",
	//	"adventurer-smrslt-00.png",
	//	"adventurer-smrslt-01.png",
	//	"adventurer-smrslt-02.png",
	//	"adventurer-smrslt-03.png",
	//	"adventurer-stand-00.png",
	//	"adventurer-stand-01.png",
	//	"adventurer-stand-02.png",
	//	"adventurer-swrd-drw-00.png",
	//	"adventurer-swrd-drw-01.png",
	//	"adventurer-swrd-drw-02.png",
	//	"adventurer-swrd-drw-03.png",
	//	"adventurer-swrd-shte-00.png",
	//	"adventurer-swrd-shte-01.png",
	//	"adventurer-swrd-shte-02.png",
	//	"adventurer-swrd-shte-03.png",
	//	"adventurer-wall-slide-00.png",
	//	"adventurer-wall-slide-01.png",
	//};
}

GamePlayingScene::~GamePlayingScene()
{
}

void GamePlayingScene::Update(Input& input)
{
	m_fps = GetFPS();
	(this->*m_updateFunc)(input);
	
}

void GamePlayingScene::Draw()
{
	(this->*m_drawFunc)();
}

void GamePlayingScene::FadeInUpdate(Input& input)
{
	m_frame--;
	if (m_frame <= 0)
	{
		m_updateFunc = &GamePlayingScene::NormalUpdate;
		m_drawFunc = &GamePlayingScene::NormalDraw;
	}
}

void GamePlayingScene::NormalUpdate(Input& input)
{
	if (input.IsTriggered("OK"))
	{
		m_updateFunc = &GamePlayingScene::FadeOutUpdate;
		m_drawFunc = &GamePlayingScene::FadeDraw;
	}
	else if (input.IsTriggered("pause"))
	{
		m_manager.PushScene(std::make_shared<PauseScene>(m_manager));
	}
	m_fps = GetFPS();
	m_btnFrame++;

	m_backGround->Update();

	for (const auto& actor : m_actors)
	{
		actor->Update();
	}
	m_hero->Operate(input);
	m_monk->Operate(input);
}

void GamePlayingScene::FadeOutUpdate(Input& input)
{
	m_frame++;
	if (60 <= m_frame)
	{
		m_manager.ChangeScene(std::make_shared<GameOverScene>(m_manager));
	}
}

void GamePlayingScene::FadeDraw()
{
	DrawString(10, 100, L"GamePlayingScene", 0xffffff);
	DrawGraph(100, 100, m_imgFile->GetHandle(), true);

	int alpha = static_cast<int>(255 * (static_cast<float>(m_frame) / 60.0f));
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, 640, 480, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void GamePlayingScene::NormalDraw()
{
	m_backGround->Draw();

	DrawString(10, 100, L"GamePlayingScene", 0xffffff);
	DrawGraph(100, 100, m_imgFile->GetHandle(), true);
	DrawFormatString(10, 10, 0xffffff, L"fps = %2.2f", m_fps);
	auto& app = Application::GetInstance();
	auto size = app.GetWindowSize();
	int idx = m_btnFrame / 10 % 3;
	constexpr int kButtonSize = 16;
	constexpr float kBtnScale = 3.0f;
	DrawRectRotaGraph(0 + (kButtonSize * kBtnScale) / 2, size.h - (kButtonSize * kBtnScale) / 2,// 画面の左下
	idx * kButtonSize, 0,// 元画像切り取り左上
	kButtonSize, kButtonSize,// 切り取りサイズ
	kBtnScale, //拡大率
	0.0,
	m_btnImg->GetHandle(), true);

	// キャラクターの表示
	// 主人公
	for (auto& actor : m_actors)
	{
		actor->Draw();
	}
}
