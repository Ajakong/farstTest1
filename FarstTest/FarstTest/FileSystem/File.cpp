#include "File.h"

File::File(FileManager& manager) :
	m_manager(manager)
{
}

File::~File()
{
	// 何もしない
}

int File::GetHandle() const
{
	return m_handle;
}
