#ifndef			_XANADU_CORE_SETTING_H_
#define			_XANADU_CORE_SETTING_H_

#include <xanadu-core/header.h>
#include <xanadu-core/XString.h>
#include <xanadu-core/XVariant.h>

// Xanadu Setting Private
class XSettingPrivate;

// Xanadu Class Setting
class _XCOREAPI_ XSetting
{
private:
	XSettingPrivate*		_Info;

public:
	// Overload _copy
	XSetting() noexcept;

	// Overload _copy
	XSetting(const XSetting& _Setting) noexcept;

	// destructor
	virtual ~XSetting() noexcept;

public:
	// Overload Operator =
	XSetting& operator = (const XSetting& _Setting) noexcept;

private:
	virtual void _clear() noexcept final;

	virtual void _copy(const XSetting& _Setting) noexcept final;

	virtual XSettingPrivate* _format(const XByteArray& _Bytes) const noexcept final;

	virtual void _append(XSettingPrivate* _Node) noexcept final;

	virtual XSettingPrivate* _find(const XString& _Section, const XString& _Key) const noexcept final;

	virtual void _remove(XSettingPrivate* _Node) noexcept final;

	virtual XSettingPrivate* _section_end(const XString& _Section) noexcept final;

private:
	virtual XByteArray _section(const XSettingPrivate* _Node) const noexcept final;

	virtual XByteArray _left(const XSettingPrivate* _Node) const noexcept final;

	virtual XByteArray _right(const XSettingPrivate* _Node) const noexcept final;

public:
	///加载
	virtual bool load(const XString& _File) noexcept final;

	// 保存
	virtual bool save(const XString& _File) const noexcept final;

public:
	// 增
	virtual bool append(const XString& _Section, const XString& _Key, const XVariant& _Value) noexcept final;

	// 删
	virtual bool remove(const XString& _Section, const XString& _Key) noexcept final;

	// 改
	virtual bool modify(const XString& _Section, const XString& _Key, const XVariant& _Value) noexcept;

	// 查
	virtual XVariant select(const XString& _Section, const XString& _Key, const XVariant& _Default = XVariant()) const noexcept final;

public:
	// 写入
	static bool write(const XString& _File, const XString& _Section, const XString& _Key, const XVariant& _Value) noexcept;

	// 读取
	static XVariant read(const XString& _File, const XString& _Section, const XString& _Key, const XVariant& _Default = XVariant()) noexcept;
};

#endif
