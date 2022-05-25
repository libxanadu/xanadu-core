#include <xanadu-core/stream.h>



// constructor
x::stream::stream() noexcept = default;

// constructor
x::stream::stream(const stream& _Other) noexcept = default;

// constructor
x::stream::stream(stream&& _Other) noexcept = default;

// destructor
x::stream::~stream() noexcept = default;





// operator overload =
x::stream& x::stream::operator = (const stream& _Other) noexcept = default;

// operator overload =
x::stream& x::stream::operator = (stream&& _Other) noexcept = default;
