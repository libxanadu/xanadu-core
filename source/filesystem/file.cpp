#include <xanadu-core/filesystem.h>



// constructor
xanadu::filesystem::file::file() noexcept = default;

// constructor
xanadu::filesystem::file::file(const file& _Other) noexcept = default;

// constructor
xanadu::filesystem::file::file(file&& _Other) noexcept = default;

// destructor
xanadu::filesystem::file::~file() noexcept = default;





// operators overload =
xanadu::filesystem::file& xanadu::filesystem::file::operator = (const file& _Other) noexcept = default;

// operators overload =
xanadu::filesystem::file& xanadu::filesystem::file::operator = (file&& _Other) noexcept = default;
