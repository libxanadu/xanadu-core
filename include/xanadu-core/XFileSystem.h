#ifndef			_XANADU_CORE_FILESYSTEM_H_
#define			_XANADU_CORE_FILESYSTEM_H_

#include <xanadu-core/XString.h>


/// <summary>
/// Xanadu's file system
/// </summary>
namespace XFileSystem
{
	// Path processing operation
	class _XCOREAPI_ path
	{
	public:
		using				_Elem = char;

	private:
		static constexpr wchar_t	preferred_separator = '/';
		XString			_filesystem_path;

	public:
		// constructor
		path() noexcept;

		// constructor
		path(const _Elem* _Path) noexcept;

		// constructor
		path(const XString& _Path) noexcept;

		// constructor
		path(const XFileSystem::path& _Path) noexcept;

		// constructor
		path(XFileSystem::path&& _Path) noexcept;

		// destructor
		virtual ~path() noexcept;

	public:
		// operator overload =
		XFileSystem::path& operator = (const _Elem* _Path) noexcept;

		// operator overload =
		XFileSystem::path& operator = (const XString& _Path) noexcept;

		// operator overload =
		XFileSystem::path& operator = (const XFileSystem::path& _Path) noexcept;

		// operator overload =
		XFileSystem::path& operator = (XFileSystem::path&& _Path) noexcept;

	public:
		// operator overload +=
		XFileSystem::path& operator += (const _Elem* _Path) noexcept;

		// operator overload +=
		XFileSystem::path& operator += (const XString& _Path) noexcept;

		// operator overload +=
		XFileSystem::path& operator += (const XFileSystem::path& _Path) noexcept;

	public:
		// operator overload +
		XFileSystem::path operator + (const _Elem* _Path) const noexcept;

		// operator overload +
		XFileSystem::path operator + (const XString& _Path) const noexcept;

		// operator overload +
		XFileSystem::path operator + (const XFileSystem::path& _Path) const noexcept;

	public:
		// operator overload /=
		XFileSystem::path& operator /= (const _Elem* _Path) noexcept;

		// operator overload /=
		XFileSystem::path& operator /= (const XString& _Path) noexcept;

		// operator overload /=
		XFileSystem::path& operator /= (const XFileSystem::path& _Path) noexcept;

	public:
		// operator overload /
		XFileSystem::path operator / (const _Elem* _Path) const noexcept;

		// operator overload /
		XFileSystem::path operator / (const XString& _Path) const noexcept;

		// operator overload /
		XFileSystem::path operator / (const XFileSystem::path& _Path) const noexcept;

	public:
		// operator overload ==
		bool operator == (const _Elem* _Path)const noexcept;

		// operator overload ==
		bool operator == (const XString& _Path)const noexcept;

		// operator overload ==
		bool operator == (const XFileSystem::path& _Path)const noexcept;

		// operator overload !=
		bool operator != (const _Elem* _Path)const noexcept;

		// operator overload !=
		bool operator != (const XString& _Path)const noexcept;

		// operator overload !=
		bool operator != (const XFileSystem::path& _Path)const noexcept;

		// operator overload <
		bool operator < (const _Elem* _Path)const noexcept;

		// operator overload <
		bool operator < (const XString& _Path)const noexcept;

		// operator overload <
		bool operator < (const XFileSystem::path& _Path)const noexcept;

		// operator overload >
		bool operator > (const _Elem* _Path) const noexcept;

		// operator overload >
		bool operator > (const XString& _Path) const noexcept;

		// operator overload >
		bool operator > (const XFileSystem::path& _Path) const noexcept;

		// operator overload <=
		bool operator <= (const _Elem* _Path) const noexcept;

		// operator overload <=
		bool operator <= (const XString& _Path) const noexcept;

		// operator overload <=
		bool operator <= (const XFileSystem::path& _Path) const noexcept;

		// operator overload >=
		bool operator >= (const _Elem* _Path) const noexcept;

		// operator overload >=
		bool operator >= (const XString& _Path) const noexcept;

		// operator overload >=
		bool operator >= (const XFileSystem::path& _Path) const noexcept;

	public:
		// appends elements to the path with a directory separator
		XFileSystem::path& append(const _Elem* _Path) noexcept;

		// appends elements to the path with a directory separator
		XFileSystem::path& append(const XString& _Path) noexcept;

		// appends elements to the path with a directory separator
		XFileSystem::path& append(const XFileSystem::path& _Path) noexcept;

	public:
		// concatenates two paths without introducing a directory separator
		XFileSystem::path& concat(const _Elem* _Path) noexcept;

		// concatenates two paths without introducing a directory separator
		XFileSystem::path& concat(const XString& _Path) noexcept;

		// concatenates two paths without introducing a directory separator
		XFileSystem::path& concat(const XFileSystem::path& _Path) noexcept;

	public:
		// string
		virtual XString& data() noexcept;

		// string
		virtual const XString& data() const noexcept;

		// checks if the path is exist
		virtual bool exist() const noexcept;

		// checks if the path is empty
		virtual bool empty() const noexcept;

		// clear
		virtual void clear() noexcept;

	public:
		// format
		virtual void format() noexcept final;

		// format
		static XFileSystem::path format(const XFileSystem::path& _Path) noexcept;

	public:
		// returns the filepath path component
		virtual XString filePath() const noexcept;

		// returns the directory path component
		virtual XString directory() const noexcept;

		// returns the filename path component
		virtual XString fileName() const noexcept;

		// returns the stem path component
		virtual XString stem() const noexcept;

		// returns the file extension path component
		virtual XString extension() const noexcept;

		// returns the file extension path component
		virtual XString suffix() const noexcept;

		// Convert to native delimiter
		virtual XString native() const noexcept;

		// checks whether the given path refers to a directory
		virtual bool isDirectory() const noexcept;

		// checks whether the given path refers to a file
		virtual bool isFile() const noexcept;

	public:
		// checks whether path refers to existing file system object
		static bool exist(const XFileSystem::path& _Path) noexcept;

		// checks whether the given path refers to a directory
		static bool isDirectory(const XFileSystem::path& _Path) noexcept;

		// checks whether the given path refers to a file
		static bool isFile(const XFileSystem::path& _Path) noexcept;

		// returns the size of a path
		static unsigned long long size(const XFileSystem::path& _Path) noexcept;

		// 后缀匹配
		static bool suffixMatch(const XFileSystem::path& _Path, const XString& _Suffix) noexcept;

		// 修复	\/:*?"<>|
		static XFileSystem::path repair(const XFileSystem::path& _Path) noexcept;

		// 修复空格
		static XFileSystem::path spaceRepair(const XFileSystem::path& _Path) noexcept;

		// Check whether the name meets the specification
		static bool isCorrect(const XString& _FileName) noexcept;

	public:
		// remove
		static bool remove(const XFileSystem::path& _Path, const std::function<bool(const XFileSystem::path& _Path)>& _Lambda) noexcept;
	};

	// typedef
	typedef const std::function<bool(uint64_t _Progress, uint64_t _Total)>&						_FunctionProgress;
	typedef const std::function<bool(const XFileSystem::path& _Path)>&						_Function1;
	typedef const std::function<bool(const XFileSystem::path& _Source, const XFileSystem::path& _Target)>&		_Function2;

	// file
	class _XCOREAPI_ file
	{
	public:
		// constructor
		file() noexcept;

		// destructor
		virtual ~file() noexcept;

	public:
		// [opt] open
		static HANDLE open(const XFileSystem::path& _Path, const char* _Flags) noexcept;

		// [opt] seek
		static bool seek(HANDLE _Handle, long _Offset, int _Origin = SEEK_SET) noexcept;

		// [opt] offset
		static long long offset(HANDLE _Handle) noexcept;

		// [opt] eof
		static bool eof(HANDLE _Handle) noexcept;

		// [opt] read all
		static bool read(HANDLE _Handle, void* _Buffer, uint64_t _Length) noexcept;

		// [opt] read line
		static XByteArray readLine(HANDLE _Handle) noexcept;

		// [opt] read
		static uint64_t read(void* _Buffer, uint64_t _Size, uint64_t _Count, HANDLE _Handle) noexcept;

		// [opt] write all
		static bool write(HANDLE _Handle, const void* _Buffer, uint64_t _Length) noexcept;

		// [opt] write all
		static bool write(HANDLE _Handle, const XByteArray& _Buffer) noexcept;

		// [opt] write
		static uint64_t write(const void* _Buffer, uint64_t _Size, uint64_t _Count, HANDLE _Handle) noexcept;

		// [opt] flush
		static bool flush(HANDLE _Handle) noexcept;

		// [opt] close
		static bool close(HANDLE _Handle) noexcept;

	public:
		// returns the size of a file
		static uint64_t size(const XFileSystem::path& _Path) noexcept;

		// checks if the path is exist
		static bool exist(const XFileSystem::path& _Path) noexcept;

		// rename
		static bool rename(const XFileSystem::path& _PathOLD, const XFileSystem::path& _PathNEW) noexcept;

		// remove
		static bool remove(const XFileSystem::path& _Path) noexcept;

		// copy
		static bool copy(const XFileSystem::path& _Source, const XFileSystem::path& _Target, _FunctionProgress _Lambda = nullptr) noexcept;

		// move
		static bool move(const XFileSystem::path& _Source, const XFileSystem::path& _Target, _FunctionProgress _Lambda = nullptr) noexcept;

	public:
		// [opt] to bytes
		static XByteArray toBytes(const XFileSystem::path& _Path) noexcept;

		// [opt] from bytes
		static bool fromBytes(const XFileSystem::path& _Path, const void* _Bytes, std::size_t _Length) noexcept;

		// [opt] from bytes
		static bool fromBytes(const XFileSystem::path& _Path, const XByteArray& _Bytes) noexcept;

		// [opt] to bytes
		static XByteArray toBase64(const XFileSystem::path& _Path) noexcept;

		// [opt] from base64
		static bool fromBase64(const XFileSystem::path& _Path, const void* _Base64, std::size_t _Length) noexcept;

		// [opt] from base64
		static bool fromBase64(const XFileSystem::path& _Path, const XByteArray& _Base64) noexcept;
	};

	// directory
	class _XCOREAPI_ directory
	{
	public:
		// constructor
		directory() noexcept;

		// destructor
		virtual ~directory() noexcept;

	public:
		// returns the size of a directory
		static uint64_t size(const XFileSystem::path& _Directory) noexcept;

		// checks if the directory is exist
		static bool exist(const XFileSystem::path& _Directory) noexcept;

		// create
		static bool create(const XFileSystem::path& _Directory, int _Mode = 0755) noexcept;

		// traverse
		static bool traverse(const XFileSystem::path& _Directory, _Function1 _Lambda) noexcept;

		// remove
		static bool remove(const XFileSystem::path& _Directory, _Function1 _Lambda = nullptr) noexcept;

		// copy
		static bool copy(const XFileSystem::path& _Source, const XFileSystem::path& _Target, _Function2 _Lambda = nullptr) noexcept;

		// move
		static bool move(const XFileSystem::path& _Source, const XFileSystem::path& _Target, _Function2 _Lambda = nullptr) noexcept;
	};
}

#endif
