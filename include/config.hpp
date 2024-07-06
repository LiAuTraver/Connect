#pragma once

#ifndef implements
#define implements :
#endif

#ifndef extends
#define extends :
#endif

#ifndef abstract
#define abstract
#endif

#ifndef interface
#define interface class
#endif

#define CONNECT_INLINE inline
#if __has_cpp_attribute(maybe_unused)
#define CONNECT_MAYBE_UNUSED [[maybe_unused]]
#else
#define CONNECT_MAYBE_UNUSED
#endif
#if defined(__GNUC__) || defined(__clang__)
#define CONNECT_FORCE_INLINE inline __attribute__((always_inline))
#elifdef FORCEINLINE
#define CONNECT_FORCE_INLINE FORCEINLINE
#else
#define CONNECT_FORCE_INLINE CONNECT_INLINE
#endif

#ifndef _NODISCARD
#define _NODISCARD [[nodiscard]]
#endif

#define CONNECT_CONSTEXPR constexpr

#define CONNECT_NAMESPACE_BEGIN namespace Connect {
#define CONNECT_NAMESPACE_END }

#define CONNECT_OPT_1 1
#define CONNECT_OPT_2 0
#define CONNECT_NAMESPACE_DETAILS_INLINE 1

#if CONNECT_OPT_1 == 1 && CONNECT_OPT_2 == 0
#define CONNECT_OPT_1_NAMESPACE_BEGIN inline namespace opt1 {
#define CONNECT_OPT_1_NAMESPACE_END }
#define CONNECT_OPT_2_NAMESPACE_BEGIN namespace opt2 {
#define CONNECT_OPT_2_NAMESPACE_END }
#elif CONNECT_OPT_1 == 0 && CONNECT_OPT_2 == 1
#define CONNECT_OPT_1_NAMESPACE_BEGIN namespace opt1 {
#define CONNECT_OPT_1_NAMESPACE_END }
#define CONNECT_OPT_2_NAMESPACE_BEGIN inline namespace opt2 {
#define CONNECT_OPT_2_NAMESPACE_END }
#else
#error "Choose one opt namespace to apply."
#endif

#if CONNECT_NAMESPACE_DETAILS_INLINE == 0
#define CONNECT_NAMESPACE_DETAILS_BEGIN namespace details {
#define CONNECT_NAMESPACE_DETAILS_END }
#elif CONNECT_NAMESPACE_DETAILS_INLINE == 1
#define CONNECT_NAMESPACE_DETAILS_BEGIN inline namespace details {
#define CONNECT_NAMESPACE_DETAILS_END }
#else
#error
#endif
