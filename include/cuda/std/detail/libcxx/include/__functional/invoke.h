// -*- C++ -*-
//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
// SPDX-FileCopyrightText: Copyright (c) 2022 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCUDACXX___FUNCTIONAL_INVOKE_H
#define _LIBCUDACXX___FUNCTIONAL_INVOKE_H

#ifndef __cuda_std__
#include <__config>
#endif // __cuda_std__

#include "../__type_traits/add_lvalue_reference.h"
#include "../__type_traits/apply_cv.h"
#include "../__type_traits/conditional.h"
#include "../__type_traits/decay.h"
#include "../__type_traits/enable_if.h"
#include "../__type_traits/integral_constant.h"
#include "../__type_traits/is_base_of.h"
#include "../__type_traits/is_core_convertible.h"
#include "../__type_traits/is_member_function_pointer.h"
#include "../__type_traits/is_member_object_pointer.h"
#include "../__type_traits/is_reference_wrapper.h"
#include "../__type_traits/is_same.h"
#include "../__type_traits/is_void.h"
#include "../__type_traits/nat.h"
#include "../__type_traits/remove_cv.h"
#include "../__utility/declval.h"
#include "../__utility/forward.h"

#if defined(_LIBCUDACXX_USE_PRAGMA_GCC_SYSTEM_HEADER)
#pragma GCC system_header
#endif

// TODO: Disentangle the type traits and _CUDA_VSTD::invoke properly

_LIBCUDACXX_BEGIN_NAMESPACE_STD

struct __any
{
    _LIBCUDACXX_INLINE_VISIBILITY __any(...);
};

template <class _MP, bool _IsMemberFunctionPtr, bool _IsMemberObjectPtr>
struct __member_pointer_traits_imp
{
};

template <class _Rp, class _Class, class ..._Param>
struct __member_pointer_traits_imp<_Rp (_Class::*)(_Param...), true, false>
{
    typedef _Class _ClassType;
    typedef _Rp _ReturnType;
    typedef _Rp (_FnType) (_Param...);
};

template <class _Rp, class _Class, class ..._Param>
struct __member_pointer_traits_imp<_Rp (_Class::*)(_Param..., ...), true, false>
{
    typedef _Class _ClassType;
    typedef _Rp _ReturnType;
    typedef _Rp (_FnType) (_Param..., ...);
};

template <class _Rp, class _Class, class ..._Param>
struct __member_pointer_traits_imp<_Rp (_Class::*)(_Param...) const, true, false>
{
    typedef _Class const _ClassType;
    typedef _Rp _ReturnType;
    typedef _Rp (_FnType) (_Param...);
};

template <class _Rp, class _Class, class ..._Param>
struct __member_pointer_traits_imp<_Rp (_Class::*)(_Param..., ...) const, true, false>
{
    typedef _Class const _ClassType;
    typedef _Rp _ReturnType;
    typedef _Rp (_FnType) (_Param..., ...);
};

template <class _Rp, class _Class, class ..._Param>
struct __member_pointer_traits_imp<_Rp (_Class::*)(_Param...) volatile, true, false>
{
    typedef _Class volatile _ClassType;
    typedef _Rp _ReturnType;
    typedef _Rp (_FnType) (_Param...);
};

template <class _Rp, class _Class, class ..._Param>
struct __member_pointer_traits_imp<_Rp (_Class::*)(_Param..., ...) volatile, true, false>
{
    typedef _Class volatile _ClassType;
    typedef _Rp _ReturnType;
    typedef _Rp (_FnType) (_Param..., ...);
};

template <class _Rp, class _Class, class ..._Param>
struct __member_pointer_traits_imp<_Rp (_Class::*)(_Param...) const volatile, true, false>
{
    typedef _Class const volatile _ClassType;
    typedef _Rp _ReturnType;
    typedef _Rp (_FnType) (_Param...);
};

template <class _Rp, class _Class, class ..._Param>
struct __member_pointer_traits_imp<_Rp (_Class::*)(_Param..., ...) const volatile, true, false>
{
    typedef _Class const volatile _ClassType;
    typedef _Rp _ReturnType;
    typedef _Rp (_FnType) (_Param..., ...);
};

#if defined(_LIBCUDACXX_HAS_REFERENCE_QUALIFIED_FUNCTIONS)

template <class _Rp, class _Class, class ..._Param>
struct __member_pointer_traits_imp<_Rp (_Class::*)(_Param...) &, true, false>
{
    typedef _Class& _ClassType;
    typedef _Rp _ReturnType;
    typedef _Rp (_FnType) (_Param...);
};

template <class _Rp, class _Class, class ..._Param>
struct __member_pointer_traits_imp<_Rp (_Class::*)(_Param..., ...) &, true, false>
{
    typedef _Class& _ClassType;
    typedef _Rp _ReturnType;
    typedef _Rp (_FnType) (_Param..., ...);
};

template <class _Rp, class _Class, class ..._Param>
struct __member_pointer_traits_imp<_Rp (_Class::*)(_Param...) const&, true, false>
{
    typedef _Class const& _ClassType;
    typedef _Rp _ReturnType;
    typedef _Rp (_FnType) (_Param...);
};

template <class _Rp, class _Class, class ..._Param>
struct __member_pointer_traits_imp<_Rp (_Class::*)(_Param..., ...) const&, true, false>
{
    typedef _Class const& _ClassType;
    typedef _Rp _ReturnType;
    typedef _Rp (_FnType) (_Param..., ...);
};

template <class _Rp, class _Class, class ..._Param>
struct __member_pointer_traits_imp<_Rp (_Class::*)(_Param...) volatile&, true, false>
{
    typedef _Class volatile& _ClassType;
    typedef _Rp _ReturnType;
    typedef _Rp (_FnType) (_Param...);
};

template <class _Rp, class _Class, class ..._Param>
struct __member_pointer_traits_imp<_Rp (_Class::*)(_Param..., ...) volatile&, true, false>
{
    typedef _Class volatile& _ClassType;
    typedef _Rp _ReturnType;
    typedef _Rp (_FnType) (_Param..., ...);
};

template <class _Rp, class _Class, class ..._Param>
struct __member_pointer_traits_imp<_Rp (_Class::*)(_Param...) const volatile&, true, false>
{
    typedef _Class const volatile& _ClassType;
    typedef _Rp _ReturnType;
    typedef _Rp (_FnType) (_Param...);
};

template <class _Rp, class _Class, class ..._Param>
struct __member_pointer_traits_imp<_Rp (_Class::*)(_Param..., ...) const volatile&, true, false>
{
    typedef _Class const volatile& _ClassType;
    typedef _Rp _ReturnType;
    typedef _Rp (_FnType) (_Param..., ...);
};

template <class _Rp, class _Class, class ..._Param>
struct __member_pointer_traits_imp<_Rp (_Class::*)(_Param...) &&, true, false>
{
    typedef _Class&& _ClassType;
    typedef _Rp _ReturnType;
    typedef _Rp (_FnType) (_Param...);
};

template <class _Rp, class _Class, class ..._Param>
struct __member_pointer_traits_imp<_Rp (_Class::*)(_Param..., ...) &&, true, false>
{
    typedef _Class&& _ClassType;
    typedef _Rp _ReturnType;
    typedef _Rp (_FnType) (_Param..., ...);
};

template <class _Rp, class _Class, class ..._Param>
struct __member_pointer_traits_imp<_Rp (_Class::*)(_Param...) const&&, true, false>
{
    typedef _Class const&& _ClassType;
    typedef _Rp _ReturnType;
    typedef _Rp (_FnType) (_Param...);
};

template <class _Rp, class _Class, class ..._Param>
struct __member_pointer_traits_imp<_Rp (_Class::*)(_Param..., ...) const&&, true, false>
{
    typedef _Class const&& _ClassType;
    typedef _Rp _ReturnType;
    typedef _Rp (_FnType) (_Param..., ...);
};

template <class _Rp, class _Class, class ..._Param>
struct __member_pointer_traits_imp<_Rp (_Class::*)(_Param...) volatile&&, true, false>
{
    typedef _Class volatile&& _ClassType;
    typedef _Rp _ReturnType;
    typedef _Rp (_FnType) (_Param...);
};

template <class _Rp, class _Class, class ..._Param>
struct __member_pointer_traits_imp<_Rp (_Class::*)(_Param..., ...) volatile&&, true, false>
{
    typedef _Class volatile&& _ClassType;
    typedef _Rp _ReturnType;
    typedef _Rp (_FnType) (_Param..., ...);
};

template <class _Rp, class _Class, class ..._Param>
struct __member_pointer_traits_imp<_Rp (_Class::*)(_Param...) const volatile&&, true, false>
{
    typedef _Class const volatile&& _ClassType;
    typedef _Rp _ReturnType;
    typedef _Rp (_FnType) (_Param...);
};

template <class _Rp, class _Class, class ..._Param>
struct __member_pointer_traits_imp<_Rp (_Class::*)(_Param..., ...) const volatile&&, true, false>
{
    typedef _Class const volatile&& _ClassType;
    typedef _Rp _ReturnType;
    typedef _Rp (_FnType) (_Param..., ...);
};

#endif // defined(_LIBCUDACXX_HAS_REFERENCE_QUALIFIED_FUNCTIONS)

template <class _Rp, class _Class>
struct __member_pointer_traits_imp<_Rp _Class::*, false, true>
{
    typedef _Class _ClassType;
    typedef _Rp _ReturnType;
};

template <class _MP>
struct __member_pointer_traits
    : public __member_pointer_traits_imp<__remove_cv_t<_MP>,
                    is_member_function_pointer<_MP>::value,
                    is_member_object_pointer<_MP>::value>
{
//     typedef ... _ClassType;
//     typedef ... _ReturnType;
//     typedef ... _FnType;
};

template <class _DecayedFp>
struct __member_pointer_class_type {};

template <class _Ret, class _ClassType>
struct __member_pointer_class_type<_Ret _ClassType::*> {
  typedef _ClassType type;
};

template <class _Fp, class _A0,
         class _DecayFp = __decay_t<_Fp>,
         class _DecayA0 = typename decay<_A0>::type,
         class _ClassT = typename __member_pointer_class_type<_DecayFp>::type>
using __enable_if_bullet1 = __enable_if_t
    <
        is_member_function_pointer<_DecayFp>::value
        && is_base_of<_ClassT, _DecayA0>::value
    >;

template <class _Fp, class _A0,
         class _DecayFp = __decay_t<_Fp>,
         class _DecayA0 = typename decay<_A0>::type>
using __enable_if_bullet2 = __enable_if_t
    <
        is_member_function_pointer<_DecayFp>::value
        && __is_reference_wrapper<_DecayA0>::value
    >;

template <class _Fp, class _A0,
         class _DecayFp = __decay_t<_Fp>,
         class _DecayA0 = typename decay<_A0>::type,
         class _ClassT = typename __member_pointer_class_type<_DecayFp>::type>
using __enable_if_bullet3 =__enable_if_t
    <
        is_member_function_pointer<_DecayFp>::value
        && !is_base_of<_ClassT, _DecayA0>::value
        && !__is_reference_wrapper<_DecayA0>::value
    >;

template <class _Fp, class _A0,
         class _DecayFp = __decay_t<_Fp>,
         class _DecayA0 = typename decay<_A0>::type,
         class _ClassT = typename __member_pointer_class_type<_DecayFp>::type>
using __enable_if_bullet4 = __enable_if_t
    <
        is_member_object_pointer<_DecayFp>::value
        && is_base_of<_ClassT, _DecayA0>::value
    >;

template <class _Fp, class _A0,
         class _DecayFp = __decay_t<_Fp>,
         class _DecayA0 = typename decay<_A0>::type>
using __enable_if_bullet5 = __enable_if_t
    <
        is_member_object_pointer<_DecayFp>::value
        && __is_reference_wrapper<_DecayA0>::value
    >;

template <class _Fp, class _A0,
         class _DecayFp = __decay_t<_Fp>,
         class _DecayA0 = typename decay<_A0>::type,
         class _ClassT = typename __member_pointer_class_type<_DecayFp>::type>
using __enable_if_bullet6 = __enable_if_t
    <
        is_member_object_pointer<_DecayFp>::value
        && !is_base_of<_ClassT, _DecayA0>::value
        && !__is_reference_wrapper<_DecayA0>::value
    >;

// __invoke forward declarations

// fall back - none of the bullets

template <class ..._Args>
_LIBCUDACXX_INLINE_VISIBILITY __nat __invoke(__any, _Args&& ...__args);

// bullets 1, 2 and 3

template <class _Fp, class _A0, class ..._Args,
          class = __enable_if_bullet1<_Fp, _A0> >
inline _LIBCUDACXX_INLINE_VISIBILITY
_LIBCUDACXX_CONSTEXPR decltype((_CUDA_VSTD::declval<_A0>().*_CUDA_VSTD::declval<_Fp>())(_CUDA_VSTD::declval<_Args>()...))
__invoke(_Fp&& __f, _A0&& __a0, _Args&& ...__args)
    _NOEXCEPT_(noexcept((static_cast<_A0&&>(__a0).*__f)(static_cast<_Args&&>(__args)...)))
    { return           (static_cast<_A0&&>(__a0).*__f)(static_cast<_Args&&>(__args)...); }

template <class _Fp, class _A0, class ..._Args,
          class = __enable_if_bullet2<_Fp, _A0> >
inline _LIBCUDACXX_INLINE_VISIBILITY
_LIBCUDACXX_CONSTEXPR decltype((_CUDA_VSTD::declval<_A0>().get().*_CUDA_VSTD::declval<_Fp>())(_CUDA_VSTD::declval<_Args>()...))
__invoke(_Fp&& __f, _A0&& __a0, _Args&& ...__args)
    _NOEXCEPT_(noexcept((__a0.get().*__f)(static_cast<_Args&&>(__args)...)))
    { return          (__a0.get().*__f)(static_cast<_Args&&>(__args)...); }

template <class _Fp, class _A0, class ..._Args,
          class = __enable_if_bullet3<_Fp, _A0> >
inline _LIBCUDACXX_INLINE_VISIBILITY
_LIBCUDACXX_CONSTEXPR decltype(((*_CUDA_VSTD::declval<_A0>()).*_CUDA_VSTD::declval<_Fp>())(_CUDA_VSTD::declval<_Args>()...))
__invoke(_Fp&& __f, _A0&& __a0, _Args&& ...__args)
    _NOEXCEPT_(noexcept(((*static_cast<_A0&&>(__a0)).*__f)(static_cast<_Args&&>(__args)...)))
    { return          ((*static_cast<_A0&&>(__a0)).*__f)(static_cast<_Args&&>(__args)...); }

// bullets 4, 5 and 6

template <class _Fp, class _A0,
          class = __enable_if_bullet4<_Fp, _A0> >
inline _LIBCUDACXX_INLINE_VISIBILITY
_LIBCUDACXX_CONSTEXPR decltype(_CUDA_VSTD::declval<_A0>().*_CUDA_VSTD::declval<_Fp>())
__invoke(_Fp&& __f, _A0&& __a0)
    _NOEXCEPT_(noexcept(static_cast<_A0&&>(__a0).*__f))
    { return          static_cast<_A0&&>(__a0).*__f; }

template <class _Fp, class _A0,
          class = __enable_if_bullet5<_Fp, _A0> >
inline _LIBCUDACXX_INLINE_VISIBILITY
_LIBCUDACXX_CONSTEXPR decltype(_CUDA_VSTD::declval<_A0>().get().*_CUDA_VSTD::declval<_Fp>())
__invoke(_Fp&& __f, _A0&& __a0)
    _NOEXCEPT_(noexcept(__a0.get().*__f))
    { return          __a0.get().*__f; }

template <class _Fp, class _A0,
          class = __enable_if_bullet6<_Fp, _A0> >
inline _LIBCUDACXX_INLINE_VISIBILITY
_LIBCUDACXX_CONSTEXPR decltype((*_CUDA_VSTD::declval<_A0>()).*_CUDA_VSTD::declval<_Fp>())
__invoke(_Fp&& __f, _A0&& __a0)
    _NOEXCEPT_(noexcept((*static_cast<_A0&&>(__a0)).*__f))
    { return          (*static_cast<_A0&&>(__a0)).*__f; }

// bullet 7

template <class _Fp, class ..._Args>
inline _LIBCUDACXX_INLINE_VISIBILITY
_LIBCUDACXX_CONSTEXPR decltype(_CUDA_VSTD::declval<_Fp>()(_CUDA_VSTD::declval<_Args>()...))
__invoke(_Fp&& __f, _Args&& ...__args)
    _NOEXCEPT_(noexcept(static_cast<_Fp&&>(__f)(static_cast<_Args&&>(__args)...)))
    { return          static_cast<_Fp&&>(__f)(static_cast<_Args&&>(__args)...); }

// __invokable
template <class _Ret, class _Fp, class ..._Args>
struct __invokable_r
{
  template <class _XFp, class ..._XArgs>
  _LIBCUDACXX_INLINE_VISIBILITY
  static decltype(_CUDA_VSTD::__invoke(_CUDA_VSTD::declval<_XFp>(), _CUDA_VSTD::declval<_XArgs>()...)) __try_call(int);
  
  template <class _XFp, class ..._XArgs>
  _LIBCUDACXX_INLINE_VISIBILITY
  static __nat __try_call(...);

  // FIXME: Check that _Ret, _Fp, and _Args... are all complete types, cv void,
  // or incomplete array types as required by the standard.
  using _Result = decltype(__try_call<_Fp, _Args...>(0));

  using type = __conditional_t<
      _IsNotSame<_Result, __nat>::value,
      __conditional_t<is_void<_Ret>::value, true_type, __is_core_convertible<_Result, _Ret> >,
      false_type>;
  static const bool value = type::value;
};
template <class _Fp, class ..._Args>
using __invokable = __invokable_r<void, _Fp, _Args...>;

template <bool _IsInvokable, bool _IsCVVoid, class _Ret, class _Fp, class ..._Args>
struct __nothrow_invokable_r_imp {
  static const bool value = false;
};

template <class _Ret, class _Fp, class ..._Args>
struct __nothrow_invokable_r_imp<true, false, _Ret, _Fp, _Args...>
{
    typedef __nothrow_invokable_r_imp _ThisT;

    template <class _Tp>
    _LIBCUDACXX_INLINE_VISIBILITY
    static void __test_noexcept(_Tp) _NOEXCEPT;

    static const bool value = noexcept(_ThisT::__test_noexcept<_Ret>(
        _CUDA_VSTD::__invoke(declval<_Fp>(), _CUDA_VSTD::declval<_Args>()...)));
};

template <class _Ret, class _Fp, class ..._Args>
struct __nothrow_invokable_r_imp<true, true, _Ret, _Fp, _Args...>
{
    static const bool value = noexcept(
        _CUDA_VSTD::__invoke(_CUDA_VSTD::declval<_Fp>(), _CUDA_VSTD::declval<_Args>()...));
};

template <class _Ret, class _Fp, class ..._Args>
using __nothrow_invokable_r =
    __nothrow_invokable_r_imp<
            __invokable_r<_Ret, _Fp, _Args...>::value,
            is_void<_Ret>::value,
            _Ret, _Fp, _Args...
    >;

template <class _Fp, class ..._Args>
using __nothrow_invokable =
    __nothrow_invokable_r_imp<
            __invokable<_Fp, _Args...>::value,
            true, void, _Fp, _Args...
    >;

template <class _Fp, class ..._Args>
struct __invoke_of
    : public enable_if<
        __invokable<_Fp, _Args...>::value,
        typename __invokable_r<void, _Fp, _Args...>::_Result>
{
#if defined(__NVCC__) && defined(__CUDACC_EXTENDED_LAMBDA__) && \
   !defined(__CUDA_ARCH__)
  static_assert(!__nv_is_extended_device_lambda_closure_type(_Fp),
                "Attempt to use an extended __device__ lambda in a context "
                "that requires querying its return type in host code. Use a "
                "named function object, a __host__ __device__ lambda, or "
                "cuda::proclaim_return_type instead.");
#endif
};

template <class _Ret, bool = is_void<_Ret>::value>
struct __invoke_void_return_wrapper
{
    template <class ..._Args>
    _LIBCUDACXX_INLINE_VISIBILITY static _Ret __call(_Args&&... __args) {
        return _CUDA_VSTD::__invoke(_CUDA_VSTD::forward<_Args>(__args)...);
    }
};

template <class _Ret>
struct __invoke_void_return_wrapper<_Ret, true>
{
    template <class ..._Args>
    _LIBCUDACXX_INLINE_VISIBILITY static void __call(_Args&&... __args) {
        _CUDA_VSTD::__invoke(_CUDA_VSTD::forward<_Args>(__args)...);
    }
};

#if _LIBCUDACXX_STD_VER > 11

// is_invocable

template <class _Fn, class ..._Args>
struct _LIBCUDACXX_TEMPLATE_VIS is_invocable
    : integral_constant<bool, __invokable<_Fn, _Args...>::value> {};

template <class _Ret, class _Fn, class ..._Args>
struct _LIBCUDACXX_TEMPLATE_VIS is_invocable_r
    : integral_constant<bool, __invokable_r<_Ret, _Fn, _Args...>::value> {};

template <class _Fn, class ..._Args>
_LIBCUDACXX_INLINE_VAR constexpr bool is_invocable_v = is_invocable<_Fn, _Args...>::value;

template <class _Ret, class _Fn, class ..._Args>
_LIBCUDACXX_INLINE_VAR constexpr bool is_invocable_r_v = is_invocable_r<_Ret, _Fn, _Args...>::value;

// is_nothrow_invocable

template <class _Fn, class ..._Args>
struct _LIBCUDACXX_TEMPLATE_VIS is_nothrow_invocable
    : integral_constant<bool, __nothrow_invokable<_Fn, _Args...>::value> {};

template <class _Ret, class _Fn, class ..._Args>
struct _LIBCUDACXX_TEMPLATE_VIS is_nothrow_invocable_r
    : integral_constant<bool, __nothrow_invokable_r<_Ret, _Fn, _Args...>::value> {};

template <class _Fn, class ..._Args>
_LIBCUDACXX_INLINE_VAR constexpr bool is_nothrow_invocable_v = is_nothrow_invocable<_Fn, _Args...>::value;

template <class _Ret, class _Fn, class ..._Args>
_LIBCUDACXX_INLINE_VAR constexpr bool is_nothrow_invocable_r_v = is_nothrow_invocable_r<_Ret, _Fn, _Args...>::value;

template <class _Fn, class... _Args>
struct _LIBCUDACXX_TEMPLATE_VIS invoke_result
    : __invoke_of<_Fn, _Args...>
{
};

template <class _Fn, class... _Args>
using invoke_result_t = typename invoke_result<_Fn, _Args...>::type;

#endif // _LIBCUDACXX_STD_VER > 11

#if _LIBCUDACXX_STD_VER > 14

template <class _Fn, class ..._Args>
_LIBCUDACXX_INLINE_VISIBILITY _LIBCUDACXX_CONSTEXPR_AFTER_CXX17 invoke_result_t<_Fn, _Args...>
invoke(_Fn&& __f, _Args&&... __args)
    noexcept(is_nothrow_invocable_v<_Fn, _Args...>)
{
    return _CUDA_VSTD::__invoke(_CUDA_VSTD::forward<_Fn>(__f), _CUDA_VSTD::forward<_Args>(__args)...);
}

#endif // _LIBCUDACXX_STD_VER > 14

_LIBCUDACXX_END_NAMESPACE_STD

#endif // _LIBCUDACXX___FUNCTIONAL_INVOKE_H
