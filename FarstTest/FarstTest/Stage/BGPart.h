#pragma once
#include"../Geometry.h"
#include<memory>
class File;
class FileManager;
class BackGround;
class Camera;

class BGPart
{
	friend BackGround;
private:
	Vector2 m_rate = { 1.0f,1.0f };//”wŒi‚ÌˆÚ“®Š„‡
	Vector2 m_scrollVal = { 0.0f,0.0f };

	float m_scale=1.0f;//”wŒi‚ÌŠg‘å—¦
	std::shared_ptr<File>m_file;
	FileManager* m_fileManager;


public:
	bool operator<(const BGPart& inval)const;
	BGPart(FileManager* fmng,const wchar_t* filename,float scale,const Vector2& rate,int priority=-1);
	
	~BGPart();
	void Update();
	void Draw(const Camera& camera);
	int m_priority = -1;//•\¦‡”Ô
};

