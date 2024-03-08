#pragma once
#include<string>
#include<vector>
#include<iostream>
#include"../Geometry.h"
#include<memory>
using MapData_t = std::vector<std::vector<uint64_t>>;

class Camera;
class File;
class FileManager;


class Stage
{


public:
	/// <summary>
	/// �X�e�[�W�f�[�^�R���X�g���N�^
	/// ���̎��_�Ńx�[�X�p�X(�p�X�̂��ƂɂȂ镶����)��n���Ă���
	/// </summary>
	/// <param name="basepath"></param>
	Stage(const wchar_t* basepath,FileManager& fileManager,Camera& camera);

	void Draw();
private:
	/// <summary>
	/// �x�[�X�p�X��"fmf"��t�����āA�X�e�[�W�f�[�^�����[�h
	/// </summary>
	/// <param name="path"></param>
	void LoadStage(const wchar_t* path);
	/// <summary>
	/// �x�[�X�p�X��png��t�����ă`�b�v��?�������[�h
	/// </summary>
	/// <param name="path"></param>
	void LoadMapChip(const wchar_t* path);

	const MapData_t& GetData() const;

private:
	MapData_t m_data;
	Size m_mapSize;

	Camera& m_camera;
	FileManager& m_fileManager;
	std::shared_ptr<File>m_chipImg;

};

