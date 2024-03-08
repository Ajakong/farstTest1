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
	/// ステージデータコンストラクタ
	/// この時点でベースパス(パスのもとになる文字列)を渡しておく
	/// </summary>
	/// <param name="basepath"></param>
	Stage(const wchar_t* basepath,FileManager& fileManager,Camera& camera);

	void Draw();
private:
	/// <summary>
	/// ベースパスに"fmf"を付加して、ステージデータをロード
	/// </summary>
	/// <param name="path"></param>
	void LoadStage(const wchar_t* path);
	/// <summary>
	/// ベースパスにpngを付加してチップで?他をロード
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

