#pragma once
#include <vector>
#include <memory>

class File;
class FileManager;
class Camera;

/// <summary>
/// 背景コントロールクラス
/// </summary>
class Background
{
public:
	Background(FileManager& fileManager,const Camera& camera);

	void Update();
	void Draw();

private:
	void BackDraw();

private:
	FileManager& m_fileManager;
	const Camera& camera;


	std::shared_ptr<File> m_bg1;
	std::shared_ptr<File> m_bg2;
	std::shared_ptr<File> m_ground;
	std::vector<std::shared_ptr<File>> m_houses;

	float m_scrollX;
	float m_scrollY;
};

