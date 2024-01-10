#include <DxLib.h>
#include <cassert>
#include "Charactor.h"
#include "../FileSystem/FileManager.h"
#include "../FileSystem/File.h"

Charactor::Charactor(FileManager& fileManager, std::wstring fileNameBase) :
	Actor(fileManager)
{
	Init(fileNameBase);
}

Charactor::Charactor(FileManager& fileManager, std::wstring fileNameBase, const Position2& pos, float scale) :
	Actor(fileManager, pos),
	m_drawScale(scale)
{
	Init(fileNameBase);
}

Charactor::~Charactor()
{
}

void Charactor::ChangeAnimation(const std::string& animName)
{
}

void Charactor::Update()
{
	m_frame++;
}

void Charactor::Draw()
{
	auto it = m_cutTable.begin();
	for (int i = 0; i < (m_frame / m_currentAnimInterval) % m_cutTable.size(); i++)
	{
		it++;
	}
	const auto& rc = it->second;
	DrawRectRotaGraph(m_pos.x + rc.offsetX * m_drawScale, m_pos.y + rc.offsetY * m_drawScale,
		rc.x, rc.y, rc.w, rc.h,
		m_drawScale, 0,
		m_imgFile->GetHandle(), true);
}


void Charactor::Init(const std::wstring& fileNameBase)
{
	m_imgFile = m_fileManager.LoadGraphic(fileNameBase + L".png");
	auto cutDataName = fileNameBase + L".dat";
	LoadCutData(cutDataName.c_str(), m_cutTable);
}

void Charactor::LoadCutData(const wchar_t* dataPath, CutTable_t& cutTable)
{
	int handle = FileRead_open(dataPath);
	assert(handle != 0);
	int cutNum = 0;
	FileRead_read(&cutNum, sizeof(cutNum), handle);
	cutTable.clear();

	for (int i = 0; i < cutNum; i++)
	{
		// •¶Žš—ñ‚Ì’·‚³‚ð’²¸
		byte strLen = 0;
		FileRead_read(&strLen, sizeof(strLen), handle);
		// •¶Žš—ñ‚Ì’²¸
		std::string orgName;
		orgName.resize(strLen);
		FileRead_read(orgName.data(), sizeof(char) * orgName.size(), handle);
		// ƒJƒbƒgî•ñ‚Ì’²¸
		CutRect cutRect = {};
		FileRead_read(&cutRect, sizeof(cutRect), handle);

		// î•ñ‚Ì“Ç‚Ýž‚Ý
		cutTable[orgName] = cutRect;
	}

	FileRead_close(handle);
}
