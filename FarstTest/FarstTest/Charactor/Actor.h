#pragma once
#include "../Geometry.h"

class FileManager;
class Camera;

/// <summary>
/// �Q�[�����ɔz�u�����\������\�����N���X
/// </summary>
class Actor
{
public:
	Actor(FileManager& fileManager, const Camera& camera, const Position2& pos = {});
	virtual ~Actor();
	/// <summary>
	/// ������Ԃ̍X�V
	/// </summary>
	virtual void Update() = 0;
	/// <summary>
	/// ���݂̃A�N�^�[��\������
	/// </summary>
	virtual void Draw() = 0;

	/// <summary>
	/// ���W���w�肷��
	/// </summary>
	/// <param name="pos">���W</param>
	void SetPosition(const Position2& pos);

	const Position2& GetPosition();

protected:
	FileManager& m_fileManager;
	Position2 m_pos;	// �\�����錻�݂̍��W
	const Camera& m_camera;
};

