//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
// SPDX-FileCopyrightText: Copyright (c) 2022 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
//
//===----------------------------------------------------------------------===//

// <cuda/std/iterator>

// reverse_iterator

// requires RandomAccessIterator<Iter>
//   unspecified operator[](difference_type n) const;

#include <cuda/std/iterator>
#include <cuda/std/cassert>

#include "test_macros.h"
#include "test_iterators.h"

template <class It>
__host__ __device__
void
test(It i, typename cuda::std::iterator_traits<It>::difference_type n,
     typename cuda::std::iterator_traits<It>::value_type x)
{
    typedef typename cuda::std::iterator_traits<It>::value_type value_type;
    const cuda::std::reverse_iterator<It> r(i);
    value_type rr = r[n];
    assert(rr == x);
}

int main(int, char**)
{
    const char* s = "1234567890";
    test(random_access_iterator<const char*>(s+5), 4, '1');
    test(s+5, 4, '1');

#if TEST_STD_VER > 14
    {
    constexpr const char *p = "123456789";
    typedef cuda::std::reverse_iterator<const char *> RI;
    constexpr RI it1 = cuda::std::make_reverse_iterator(p + 5);
    static_assert(it1[0] == '5', "");
    static_assert(it1[4] == '1', "");
    }
#endif

  return 0;
}
