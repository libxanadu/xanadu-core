#ifndef			_XANADU_CORE_FS_COPY_OPTIONS_H_
#define			_XANADU_CORE_FS_COPY_OPTIONS_H_

#include <xanadu-core/header.h>


// namespace xanadu::filesystem
namespace xanadu::filesystem
{
	typedef enum class xanadu_fs_copy_options
	{
		_None = 0x0,

		_Existing_mask      = 0xF,
		_Skip_existing      = 0x1,
		_Overwrite_existing = 0x2,
		_Update_existing    = 0x4,
	}xanadu_fs_copy_options;

	_XANADU_BITMASK_OPS(xanadu_fs_copy_options)

	// ENUM CLASS copy_options
	typedef enum class copy_options
	{
		none = static_cast<int>(xanadu_fs_copy_options::_None),

		_Existing_mask     = static_cast<int>(xanadu_fs_copy_options::_Existing_mask),
		skip_existing      = static_cast<int>(xanadu_fs_copy_options::_Skip_existing),
		overwrite_existing = static_cast<int>(xanadu_fs_copy_options::_Overwrite_existing),
		update_existing    = static_cast<int>(xanadu_fs_copy_options::_Update_existing),

		recursive = 0x10,

		_Symlinks_mask = 0xF00,
		copy_symlinks  = 0x100,
		skip_symlinks  = 0x200,

		_Copy_form_mask   = 0xF000,
		directories_only  = 0x1000,
		create_symlinks   = 0x2000,
		create_hard_links = 0x4000,

		_Unspecified_copy_prevention_tag = 0x10000
	}copy_options;

	_XANADU_BITMASK_OPS(copy_options)
}


#endif
