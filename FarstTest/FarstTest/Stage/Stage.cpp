#include "Stage.h"
#include"DxLib.h"
#include"../Game/Camera.h"
#include<string>
#include"../FileSystem/File.h"
#include"../FileSystem/FileManager.h"
#include<cassert>

namespace
{
	constexpr float stageScale = 2.0f;
}
Stage::Stage(const wchar_t* basepath, FileManager& fileManager, Camera& camera):
	m_camera(camera),
	m_fileManager(fileManager)
{
	LoadStage(basepath);

}

void Stage::Draw()
{
	for (int i = 0; i < m_data[0].size(); i++)
	{
		int xidx = i % m_mapSize.w;
		int yidx = i / m_mapSize.h;
		auto chipNo = m_data[0][i];
		if (chipNo == 0)
		{
			continue;
		}
		DrawRectRotaGraph2(xidx * 16 * stageScale, yidx * 16 * stageScale,16 / 2,
			(chipNo%16)*16*stageScale,
			(chipNo / 16) * 16 * stageScale,
			16,16, 16 / 2,0,
			stageScale, m_chipImg->GetHandle(), true);
	}
}

void Stage::LoadStage(const wchar_t* basepath)
{
	std::wstring path = basepath;
	path += L".fmf";
	//plutinumのfmfファイルについて参照
	struct Header
	{
		uint8_t id[4];//配列なので一つ一つは8
		uint32_t size;
		uint32_t mwidth;
		uint32_t mheight;
		uint8_t chipW;
		uint8_t chipH;
		uint8_t layerCount;
		uint8_t bitCount;
	};

	int handle=FileRead_open(path.c_str());
	assert(handle != 0);
	Header header;
	FileRead_read(&header, sizeof(header), handle);

	m_data.resize(header.layerCount);
	MapData_t tmpdata(header.layerCount);

	for (auto& layer : tmpdata)
	{
		m_data.resize(header.mwidth * header.mheight);
		FileRead_read(layer.data(), sizeof(uint8_t) * layer.size(), handle);


	}
	for (int lidx = 0; lidx < tmpdata.size(); lidx++)
	{
		m_data[lidx].resize(tmpdata[lidx].size());
		for (int i = 0; i < tmpdata[lidx].size(); i++)
		{
			int xidxS = i % header.mwidth;
			int yidxS = i / header.mwidth;
			int xidxD = i % header.mheight;
			int yidxD = i / header.mheight;

			m_data[lidx][xidxD * header.mheight + yidxD] =
				tmpdata[lidx][yidxS * header.mwidth + xidxS];
		}
	}

	FileRead_close(handle);
}

void Stage::LoadMapChip(const wchar_t* basepath)
{
	std::wstring path = basepath;
	path += L".png";
	
	m_chipImg = m_fileManager.LoadGraphic(path);
}

const MapData_t& Stage::GetData() const
{
	// TODO: return ステートメントをここに挿入します
	return m_data;
}
