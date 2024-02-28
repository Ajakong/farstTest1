#include <DxLib.h>
#include <cassert>
#include "../Input.h"
#include "../Application.h"
#include "SceneManager.h"
#include "GameOverScene.h"
#include "TitleScene.h"
#include "../FileSystem/FileManager.h"
#include "../FileSystem/File.h"

GameOverScene::GameOverScene(SceneManager& mgr) :
	Scene(mgr)
{
	auto& fileMgr = m_manager.GetFileManager();
	m_imgFile = fileMgr.LoadGraphic(L"./Data/Image/gameOver.png");
	m_btnImg = fileMgr.LoadGraphic(L"./Data/Image/UI/xbox_buttons.png", true);
	m_frame = 60;
	m_updateFunc = &GameOverScene::FadeInUpdate;
	m_drawFunc = &GameOverScene::FadeDraw;
}

GameOverScene::~GameOverScene()
{
}

void GameOverScene::Update(Input& input)
{
	(this->*m_updateFunc)(input);
}

void GameOverScene::Draw()
{
	(this->*m_drawFunc)();
}

void GameOverScene::FadeInUpdate(Input&)
{
	m_frame--;
	if (m_frame <= 0)
	{
		m_updateFunc = &GameOverScene::NormalUpdate;
		m_drawFunc = &GameOverScene::NormalDraw;
	}
}

void GameOverScene::NormalUpdate(Input& input)
{
	m_btnFrame++;
	if (input.IsTriggered("OK"))
	{
		m_updateFunc = &GameOverScene::FadeOutUpdate;
		m_drawFunc = &GameOverScene::FadeDraw;
	}
}

void GameOverScene::FadeOutUpdate(Input&)
{
	m_frame++;
	if (60 <= m_frame)
	{
		m_manager.ChangeScene(std::make_shared<TitleScene>(m_manager));
	}
}

void GameOverScene::FadeDraw()
{
	DrawString(10, 100, L"GameOverScene", 0xffffff);
	DrawGraph(100, 100, m_imgFile->GetHandle(), true);

	int alpha = static_cast<int>(255 * (static_cast<float>(m_frame) / 60.0f));
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, 640, 480, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void GameOverScene::NormalDraw()
{
	DrawString(10, 100, L"GameOverScene", 0xffffff);
	DrawGraph(100, 100, m_imgFile->GetHandle(), true);
	auto& app = Application::GetInstance();
	auto size = app.GetWindowSize();
	int idx = m_btnFrame / 10 % 3;
	constexpr int kButtonSize = 16;
	constexpr float kBtnScale = 3.0f;
	DrawRectRotaGraph(size.w / 2, (kButtonSize * kBtnScale),// ‰æ–Ê‚Ì¶‰º
		idx * kButtonSize, 0,// Œ³‰æ‘œØ‚èŽæ‚è¶ã
		kButtonSize, kButtonSize,// Ø‚èŽæ‚èƒTƒCƒY
		kBtnScale, //Šg‘å—¦
		0.0,
		m_btnImg->GetHandle(), true);
}
