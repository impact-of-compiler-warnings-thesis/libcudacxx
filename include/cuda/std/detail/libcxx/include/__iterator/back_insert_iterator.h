// -*- C++ -*-
//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
// SPDX-FileCopyrightText: Copyright (c) 2022 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCUDACXX___ITERATOR_BACK_INSERT_ITERATOR_H
#define _LIBCUDACXX___ITERATOR_BACK_INSERT_ITERATOR_H

#ifndef __cuda_std__
#include <__config>
#include <cstddef>
#endif // __cuda_std__

#include "../__iterator/iterator.h"
#include "../__memory/addressof.h"
#include "../__utility/move.h"

#if defined(_LIBCUDACXX_USE_PRAGMA_GCC_SYSTEM_HEADER)
#pragma GCC system_header
#endif

_LIBCUDACXX_BEGIN_NAMESPACE_STD

template <class _Container>
class _LIBCUDACXX_TEMPLATE_VIS back_insert_iterator
    : public iterator<output_iterator_tag,
                      void,
                      void,
                      void,
                      void>
{
protected:
    _Container* container;
public:
    typedef _Container container_type;

    _LIBCUDACXX_INLINE_VISIBILITY explicit back_insert_iterator(_Container& __x) : container(_CUDA_VSTD::addressof(__x)) {}
    _LIBCUDACXX_INLINE_VISIBILITY back_insert_iterator& operator=(const typename _Container::value_type& __value_)
        {container->push_back(__value_); return *this;}
#ifndef _LIBCUDACXX_CXX03_LANG
    _LIBCUDACXX_INLINE_VISIBILITY back_insert_iterator& operator=(typename _Container::value_type&& __value_)
        {container->push_back(_CUDA_VSTD::move(__value_)); return *this;}
#endif  // _LIBCUDACXX_CXX03_LANG
    _LIBCUDACXX_INLINE_VISIBILITY back_insert_iterator& operator*()     {return *this;}
    _LIBCUDACXX_INLINE_VISIBILITY back_insert_iterator& operator++()    {return *this;}
    _LIBCUDACXX_INLINE_VISIBILITY back_insert_iterator  operator++(int) {return *this;}
};

template <class _Container>
inline _LIBCUDACXX_INLINE_VISIBILITY
back_insert_iterator<_Container>
back_inserter(_Container& __x)
{
    return back_insert_iterator<_Container>(__x);
}

_LIBCUDACXX_END_NAMESPACE_STD

#endif // _LIBCUDACXX___ITERATOR_BACK_INSERT_ITERATOR_H
