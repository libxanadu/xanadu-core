#ifndef			_XANADU_CORE_FS_FILE_TYPE_H_
#define			_XANADU_CORE_FS_FILE_TYPE_H_

#include <xanadu-core/header.h>


// namespace xanadu::filesystem
namespace xanadu::filesystem
{
	// ENUM CLASS file_type
	typedef enum class file_type
	{
		none,
		not_found,
		regular,
		directory,
		symlink,
		block,
		character,
		fifo,
		socket,
		unknown,
		junction
	}file_type;
}


#endif
