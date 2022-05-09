#include <xanadu-core/stream.h>



// constructor
xanadu::stream::stream() noexcept = default;

// constructor
xanadu::stream::stream(const stream& _Other) noexcept = default;

// constructor
xanadu::stream::stream(stream&& _Other) noexcept = default;

// destructor
xanadu::stream::~stream() noexcept = default;





// operator overload =
xanadu::stream& xanadu::stream::operator = (const stream& _Other) noexcept = default;

// operator overload =
xanadu::stream& xanadu::stream::operator = (stream&& _Other) noexcept = default;
