#pragma once
#include <vector>
#include <memory>
#include"BGPart.h"

class File;
class FileManager;
class Camera;

/// <summary>
/// �w�i�R���g���[���N���X
/// </summary>
class Background
{
public:
	Background(FileManager& fileManager,const Camera& camera);

	void AddBGPart(const wchar_t* path, float scale, const Vector2& rate, int priority = -1);

	void Update();
	void Draw();

	void Ready();//�����Ŕw�i�p�[�c���\�[�g���邾��

private:
	void BackDraw();

private:
	FileManager& m_fileManager;
	const Camera& m_camera;


	/*std::shared_ptr<File> m_bg1;
	std::shared_ptr<File> m_bg2;*/
	std::shared_ptr<File> m_ground;
	std::vector<std::shared_ptr<File>> m_houses;

	float m_scrollX;
	float m_scrollY;

	std::vector<BGPart> m_parts;//�w�i�̕��i
};

