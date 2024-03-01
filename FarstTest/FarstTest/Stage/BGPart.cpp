#include "BGPart.h"
#include"../FileSystem/FileManager.h"
#include"../Application.h"

#include"../Game/Camera.h"
#include"Dxlib.h"
#include"../FileSystem/File.h"

bool BGPart::operator<(const BGPart& inval) const
{
	return  m_priority<inval.m_priority;
}

BGPart::BGPart(FileManager* fmng,const wchar_t* filename, float scale, const Vector2& rate, int priority):
	m_fileManager(fmng),
	m_scale(scale),
	m_rate(rate),
	m_priority(priority)
{
	m_file= m_fileManager->LoadGraphic(filename);
}



BGPart::~BGPart()
{
}

void BGPart::Update()
{
}

void BGPart::Draw(const Camera& camera)
{
	auto& wsize = Application::GetInstance().GetWindowSize();
	Size gsize;
	int handle = m_file->GetHandle();
	GetGraphSize(handle,&gsize.w,&gsize.h);
	auto gnum = (wsize.w * (wsize.w * m_scale));
	const auto& range =camera.GetRange();
	int scrollX = range.Left()*m_rate.x;

	for (int index = 0; index < 2; index++)
	{
		DrawRotaGraph2(
			-scrollX + index * gsize.w *m_scale,
			wsize.h - static_cast<int>(gsize.h * m_scale),
			0, 0,
			m_scale, 0.0, handle, true);
	}
}
