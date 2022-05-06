#include <xanadu-core/filesystem.h>



// constructor
xanadu::filesystem::directory::directory() noexcept = default;

// constructor
xanadu::filesystem::directory::directory(const directory& _Other) noexcept = default;

// constructor
xanadu::filesystem::directory::directory(directory&& _Other) noexcept = default;

// destructor
xanadu::filesystem::directory::~directory() noexcept = default;





// operators overload =
xanadu::filesystem::directory& xanadu::filesystem::directory::operator = (const directory& _Other) noexcept = default;

// operators overload =
xanadu::filesystem::directory& xanadu::filesystem::directory::operator = (directory&& _Other) noexcept = default;
