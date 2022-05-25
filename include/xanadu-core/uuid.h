#ifndef			_XANADU_CORE_UUID_H_
#define			_XANADU_CORE_UUID_H_

#include <xanadu-core/header.h>
#include <xanadu-core/string.h> // NOLINT(modernize-deprecated-headers)


/// namespace xanadu
namespace x
{
	/// class uuid
	class _XCOREAPI_ uuid
	{
	public:
		// 输出类型
		typedef enum STRING_FORMAT
		{
			// {00000000-0000-0000-0000-000000000000}	38-Size
			WithBraces			= 38,

			// 00000000-0000-0000-0000-000000000000		36-Size
			WithoutBraces			= 36,

			// 00000000000000000000000000000000		32-Size
			HexDigitsOnly			= 32
		}STRING_FORMAT;

	private:
		uint32_t			_uuid_data_1;
		uint16_t			_uuid_data_2;
		uint16_t			_uuid_data_3;
		uint8_t				_uuid_data_4[8];

	public:
		// constructor
		uuid() noexcept;

		// constructor
		uuid(uint32_t _D1, uint16_t _D2, uint16_t _D3, uint8_t _D41, uint8_t _D42, uint8_t _D43, uint8_t _D44, uint8_t _D45, uint8_t _D46, uint8_t _D47, uint8_t _D48) noexcept;

		// constructor
		explicit uuid(const char* _UUID) noexcept;

		// constructor
		explicit uuid(const x::string& _UUID) noexcept;

		// constructor
		uuid(const x::uuid& _Object) noexcept;

		// constructor
		uuid(x::uuid&& _Object) noexcept;

		// destructor
		virtual ~uuid() noexcept;

	public:
		// operator overload =
		uuid& operator = (const x::uuid& _Object) noexcept;

		// operator overload =
		uuid& operator = (x::uuid&& _Object) noexcept;

	private:
		// 从字符串格式化
		virtual bool formatString(const x::string& _UUID) noexcept final;

	public:
		// 更换一个新的UUID
		virtual void update() noexcept final;

	public:
		// 创建一个UUID
		static uuid createUuid() noexcept;

	public:
		// 从字符串格式化
		static uuid fromString(const x::string& _UUID) noexcept;

		// 转换为字符串
		virtual x::string toString() const noexcept final;

		// 转换为字符串
		virtual x::string toString(STRING_FORMAT _Format) const noexcept final;
	};
}

#endif
