#pragma once
#include<memory>
#include<vector>
class File;
class FileManager;

class BackGround
{
private:
	float m_scrollX;

	std::shared_ptr<File> m_bg1;
	std::shared_ptr<File> m_bg2;
	std::shared_ptr<File> m_ground;
	std::vector<File> m_houses;
	FileManager& m_fileManager;
	void BackDraw(int index);
public:
	BackGround(FileManager& fileManager);
	void Update();
	void Draw();


};

