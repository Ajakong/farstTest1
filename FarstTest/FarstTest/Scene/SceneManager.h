#pragma once
#include <memory>
#include <list>
class Input;
class Scene;
class FileManager;
/// <summary>
/// �e�V�[���̑J�ڂ��R���g���[������N���X
/// </summary>
class SceneManager
{
private:
	std::list<std::shared_ptr<Scene>> m_scenes;
	FileManager& m_fileManager;
public:
	SceneManager(FileManager& fileManager);
	~SceneManager();
	/// <summary>
	/// �����Ă���V�[����Update�֐����Ăяo��
	/// </summary>
	/// <param name="input">���̓N���X</param>
	void Update(Input& input);
	/// <summary>
	/// �����Ă���V�[���̕`��Draw�֐����Ăяo��
	/// </summary>
	void Draw();

	/// <summary>
	/// ���ݖ����Ŏ��s���̃V�[���������Ŏw�肳�ꂽ�V�[���ɐ؂�ւ���
	/// </summary>
	/// <param name="nextScene">���̃V�[��</param>
	void ChangeScene(std::shared_ptr<Scene> nextScene);

	/// <summary>
	/// ���݂̃V�[���̏�ɃV�[����������܂�
	/// </summary>
	/// <param name="scene">��ɏ���������V�[��</param>
	void PushScene(std::shared_ptr<Scene> scene);

	/// <summary>
	/// ���݂̖����V�[�����|�b�v���܂��B
	/// </summary>
	void PopScene();

	/// <summary>
	/// �t�@�C���}�l�[�W����Ԃ�
	/// </summary>
	/// <returns>�t�@�C���}�l�[�W��</returns>
	FileManager& GetFileManager();
};

