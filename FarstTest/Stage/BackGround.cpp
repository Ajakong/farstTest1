#include"Dxlib.h"
#include "BackGround.h"
#include"../FileSystem/File.h"
#include"../FileSystem/FileManager.h"
#include"../Geometry.h"
#include"../Application.h"

namespace
{
	constexpr float background_scale = 2.0f;
}


void BackGround::BackDraw(int index)
{
	Size wsize = Application::GetInstance().GetWindowSize();
	Size bg1size;
	Size bg2size;
	GetGraphSize(m_bg1->GetHandle(), &bg1size.w, &bg1size.h);
	GetGraphSize(m_bg2->GetHandle(), &bg2size.w, &bg2size.h);

	int scrollFg = (int)m_scrollX % (int)(bg2size.w * background_scale);
	int scrollBg1 = (int)(m_scrollX*0.5) % (int)(bg1size.w * background_scale);
	int scrollBg2 = (int)(m_scrollX * 0.25) % (int)(bg1size.w * background_scale);
	for (int index = 0; index < 2; index++)
	{
		//Å”w–Ê
		DrawRotaGraph2(-scrollBg2 + index * bg1size.w * background_scale,
			wsize.h - bg1size.h * background_scale,
			0, 0,
			background_scale,
			0.0f,
			m_bg1->GetHandle(), true);

	}
	for (int index = 0; index < 2; index++)
	{
		//”w–Ê
		DrawRotaGraph2(scrollFg + index * bg2size.w * background_scale,
			wsize.h - bg2size.h * background_scale
			, 0, 0
			, background_scale
			, 0.0f
			, m_bg2->GetHandle()
			, true);
	}
	//‘O–Ê
	//‚¢‚­‚Â•K—v‚È‚Ì‚©ŒvŽZ
	Size gsize;
	GetGraphSize(m_ground->GetHandle(), &gsize.w, &gsize.h);
	auto gnum =( wsize.w / (gsize.w * background_scale)) + 1;
	for (int index = 0; index < 2; index++)
	{
		//”w–Ê
		DrawRotaGraph2(-scrollFg + index * bg2size.w * background_scale,
			wsize.h - gsize.h * background_scale
			, 0, 0
			, background_scale
			, 0.0f
			, m_ground->GetHandle()
			, true);
	}
	
}

BackGround::BackGround(FileManager& fileManager) :
	m_fileManager(fileManager)
{
	m_bg1=m_fileManager.LoadGraphic(L"Bg/background.png");
	m_bg2=m_fileManager.LoadGraphic(L"Bg/middleground.png");
	m_scrollX = 0.0f;
	m_ground= m_fileManager.LoadGraphic(L"Bg/ground.png");
	m_houses.push_back(m_fileManager.LoadGraphic(L"Bg/house-a.png"));
}

void BackGround::Update()
{
	m_scrollX += 0.5f;
}

void BackGround::Draw()
{
	BackDraw(0);
	BackDraw(1);

}
