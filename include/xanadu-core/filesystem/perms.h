#ifndef			_XANADU_CORE_FS_PERMS_H_
#define			_XANADU_CORE_FS_PERMS_H_

#include <xanadu-core/header.h>


// namespace xanadu::filesystem
namespace xanadu::filesystem
{
	// ENUM CLASS perms
	typedef enum class perms
	{
		none = 0,

		owner_read  = 0400,
		owner_write = 0200,
		owner_exec  = 0100,
		owner_all   = 0700,

		group_read  = 0040,
		group_write = 0020,
		group_exec  = 0010,
		group_all   = 0070,

		others_read  = 0004,
		others_write = 0002,
		others_exec  = 0001,
		others_all   = 0007,

		all        = 0777,
		set_uid    = 04000,
		set_gid    = 02000,
		sticky_bit = 01000,
		mask       = 07777,
		unknown    = 0xFFFF,

		_All_write               = owner_write | group_write | others_write,
		_File_attribute_readonly = all & ~_All_write
	}perms;

	/// _XANADU_BITMASK_OPS
	_XANADU_BITMASK_OPS(perms);


	// FUNCTION permissions
	typedef enum class perm_options
	{
		replace = 0x1,
		add = 0x2,
		remove = 0x4,
		nofollow = 0x8
	}perm_options;

	/// _XANADU_BITMASK_OPS
	_XANADU_BITMASK_OPS(perm_options)
}


#endif
