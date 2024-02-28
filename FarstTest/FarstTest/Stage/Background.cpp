#include <DxLib.h>
#include "Background.h"
#include "../FileSystem/FileManager.h"
#include "../FileSystem/File.h"
#include "../Application.h"
#include "../Geometry.h"
#include"../Game/Camera.h"

namespace
{
	constexpr double kBackgroundScale = 2.0;
}

Background::Background(FileManager& fileManager, const Camera& camera) :
	m_fileManager(fileManager),
	m_scrollX(0.0f),
	m_scrollY(0.0f),
	camera(camera)
{
	m_bg1 = m_fileManager.LoadGraphic(L"Data/Image/Bg/background.png");
	m_bg2 = m_fileManager.LoadGraphic(L"Data/Image/Bg/middleground.png");
	m_ground = m_fileManager.LoadGraphic(L"Data/Image/Bg/ground.png");
	m_houses.push_back(m_fileManager.LoadGraphic(L"Data/Image/Bg/house-a.png"));
	m_houses.push_back(m_fileManager.LoadGraphic(L"Data/Image/Bg/house-b.png"));
	m_houses.push_back(m_fileManager.LoadGraphic(L"Data/Image/Bg/house-c.png"));
}

void Background::Update()
{
	m_scrollX = camera.GetRange().Left();
	m_scrollY = camera.GetRange().Bottom();
}

void Background::Draw()
{
	BackDraw();
}

void Background::BackDraw()
{
	const auto& wsize = Application::GetInstance().GetWindowSize();
	Size bg1Size;
	Size bg2Size;
	Size gsize;

	GetGraphSize(m_bg1->GetHandle(), &bg1Size.w, &bg1Size.h);
	GetGraphSize(m_bg2->GetHandle(), &bg2Size.w, &bg2Size.h);
	GetGraphSize(m_ground->GetHandle(), &gsize.w, &gsize.h);

	int scrollBG2 = (int)(m_scrollX * 0.25) % (int)(bg1Size.w * kBackgroundScale);
	int scrollBG1 = (int)(m_scrollX * 0.5) % (int)(bg2Size.w * kBackgroundScale);
	int scrollFG = (int)m_scrollX % (int)(gsize.w * kBackgroundScale);

	for (int index = 0; index < 2; index++)
	{
		DrawRotaGraph2(
			-scrollBG2 + index * bg1Size.w * kBackgroundScale,
			wsize.h - static_cast<int>(bg1Size.h * kBackgroundScale),
			0, 0,
			kBackgroundScale, 0.0, m_bg1->GetHandle(), true);
	}

	for (int index = 0; index < 2; index++)
	{
		DrawRotaGraph2(
			-scrollBG1 + index * bg2Size.w * kBackgroundScale,
			wsize.h - static_cast<int>(bg2Size.h * kBackgroundScale),
			0, 0,
			kBackgroundScale, 0.0, m_bg2->GetHandle(), true);
	}

	// ‚¢‚­‚Â•K—v‚È‚Ì‚©ŒvŽZ
	auto gnum = wsize.w / (gsize.w * kBackgroundScale) + 1;

	for (int index = 0; index < gnum; index++)
	{
		DrawRotaGraph2(
			-scrollFG + index * gsize.w * kBackgroundScale,
			wsize.h - static_cast<int>(gsize.h * kBackgroundScale),
			0, 0,
			kBackgroundScale, 0.0, m_ground->GetHandle(), true);
	}

	Size housesSize;
	GetGraphSize(m_houses[0]->GetHandle(), &housesSize.w, &housesSize.h);

	DrawRotaGraph2(
		-m_scrollX + housesSize.w * kBackgroundScale,
		wsize.h - gsize.h - static_cast<int>(housesSize.h * kBackgroundScale),
		0, 0,
		kBackgroundScale, 0.0, m_houses[0]->GetHandle(), true);
}
