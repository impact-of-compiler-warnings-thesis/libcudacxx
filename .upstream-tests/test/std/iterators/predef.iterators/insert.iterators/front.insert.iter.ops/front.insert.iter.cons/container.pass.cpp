//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
// SPDX-FileCopyrightText: Copyright (c) 2022 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
//
//===----------------------------------------------------------------------===//

// <cuda/std/iterator>

// nasty_containers is unsupported by nvrtc
// UNSUPPORTED: nvrtc

// front_insert_iterator

// explicit front_insert_iterator(Cont& x);

#include <cuda/std/iterator>
#if defined(_LIBCUDACXX_HAS_LIST)
#include <cuda/std/list>
#endif
#include "nasty_containers.h"

#include "test_macros.h"

template <class C>
__host__ __device__
void
test(C c)
{
    cuda::std::front_insert_iterator<C> i(c);
}

int main(int, char**)
{
#if defined(_LIBCUDACXX_HAS_LIST)
    test(cuda::std::list<int>());
    test(nasty_list<int>());
#endif

  return 0;
}
