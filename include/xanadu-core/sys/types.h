#ifndef			_XANADU_CORE_SYS_TYPES_H_
#define			_XANADU_CORE_SYS_TYPES_H_

#include <xanadu-posix/xanadu.h>


// XANADU BITMASK OPERATIONS
#define _XANADU_BITMASK_OPS(_XANADU_BITMASK)										\
	constexpr _XANADU_BITMASK operator&(_XANADU_BITMASK _Left, _XANADU_BITMASK _Right) noexcept {			\
		using _IntTy = unsigned int;										\
		return static_cast<_XANADU_BITMASK>(static_cast<_IntTy>(_Left) & static_cast<_IntTy>(_Right));		\
	}														\
															\
	constexpr _XANADU_BITMASK operator|(_XANADU_BITMASK _Left, _XANADU_BITMASK _Right) noexcept {			\
		using _IntTy = unsigned int;										\
		return static_cast<_XANADU_BITMASK>(static_cast<_IntTy>(_Left) | static_cast<_IntTy>(_Right));		\
	}                                                                                                               \
															\
	constexpr _XANADU_BITMASK operator^(_XANADU_BITMASK _Left, _XANADU_BITMASK _Right) noexcept {			\
		using _IntTy = unsigned int;										\
		return static_cast<_XANADU_BITMASK>(static_cast<_IntTy>(_Left) ^ static_cast<_IntTy>(_Right));		\
	}                                                                                                               \
															\
	constexpr _XANADU_BITMASK& operator&=(_XANADU_BITMASK& _Left, _XANADU_BITMASK _Right) noexcept {		\
		return _Left = _Left & _Right;										\
	}                                                                                                               \
															\
	constexpr _XANADU_BITMASK& operator|=(_XANADU_BITMASK& _Left, _XANADU_BITMASK _Right) noexcept {		\
		return _Left = _Left | _Right;										\
	}                                                                                                               \
															\
	constexpr _XANADU_BITMASK& operator^=(_XANADU_BITMASK& _Left, _XANADU_BITMASK _Right) noexcept {		\
		return _Left = _Left ^ _Right;										\
	}                                                                                                               \
															\
	constexpr _XANADU_BITMASK operator~(_XANADU_BITMASK _Left) noexcept {						\
		using _IntTy = unsigned int;										\
		return static_cast<_XANADU_BITMASK>(~static_cast<_IntTy>(_Left));					\
	}                                                                                                               \
															\
	constexpr bool _Bitmask_includes(_XANADU_BITMASK _Left, _XANADU_BITMASK elem_typeents) noexcept    		\
	{														\
		return (_Left & elem_typeents) != _XANADU_BITMASK{};							\
	}                                                                                                               \
															\
	constexpr bool _Bitmask_includes_all(_XANADU_BITMASK _Left, _XANADU_BITMASK elem_typeents) noexcept		\
	{														\
		return (_Left & elem_typeents) == elem_typeents;							\
	}



#endif
