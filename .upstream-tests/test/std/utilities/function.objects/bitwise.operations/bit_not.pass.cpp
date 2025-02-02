//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// UNSUPPORTED: c++98, c++03, c++11
// <cuda/std/functional>

// bit_not

#include <cuda/std/functional>
#include <cuda/std/type_traits>
#include <cuda/std/cassert>

int main(int, char**)
{
    typedef cuda::std::bit_not<int> F;
    const F f = F();
#if _LIBCUDACXX_STD_VER <= 14 || defined(_LIBCUDACXX_ENABLE_CXX17_REMOVED_UNARY_BINARY_FUNCTION)
    static_assert((cuda::std::is_same<F::argument_type, int>::value), "" );
    static_assert((cuda::std::is_same<F::result_type, int>::value), "" );
#endif
    assert((f(0xEA95) & 0xFFFF ) == 0x156A);
    assert((f(0x58D3) & 0xFFFF ) == 0xA72C);
    assert((f(0)      & 0xFFFF ) == 0xFFFF);
    assert((f(0xFFFF) & 0xFFFF ) == 0);

    typedef cuda::std::bit_not<> F2;
    const F2 f2 = F2();
    assert((f2(0xEA95)  & 0xFFFF ) == 0x156A);
    assert((f2(0xEA95L) & 0xFFFF ) == 0x156A);
    assert((f2(0x58D3)  & 0xFFFF ) == 0xA72C);
    assert((f2(0x58D3L) & 0xFFFF ) == 0xA72C);
    assert((f2(0)       & 0xFFFF ) == 0xFFFF);
    assert((f2(0L)      & 0xFFFF ) == 0xFFFF);
    assert((f2(0xFFFF)  & 0xFFFF ) == 0);
    assert((f2(0xFFFFL)  & 0xFFFF ) == 0);

    constexpr int foo = cuda::std::bit_not<int> () (0xEA95) & 0xFFFF;
    static_assert ( foo == 0x156A, "" );

    constexpr int bar = cuda::std::bit_not<> () (0xEA95) & 0xFFFF;
    static_assert ( bar == 0x156A, "" );

  return 0;
}
