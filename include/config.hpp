#pragma once

#ifndef DEBUG
#define DEBUG DEBUG
#endif
#ifndef INFO
#define INFO INFO
#endif
#ifndef WARNING
#define WARNING WARNING
#endif
#ifndef ERROR
#define ERROR ERROR
#endif
#ifndef FATAL
#define FATAL FATAL
#endif

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
// for now, fixme
#define CONNECT_MAYBE_UNUSED [[maybe_unused]]
#endif
#if defined(__GNUC__) || defined (__clang__)
#define CONNECT_FORCE_INLINE inline __attribute__((always_inline))
#elifdef FORCEINLINE
#define CONNECT_FORCE_INLINE FORCEINLINE
#else
#define CONNECT_FORCE_INLINE CONNECT_INLINE
#endif

#ifndef _NODISCARD
#define _NODISCARD [[nodiscard]]
#endif

#define CONNECT_IMAGES_FOLDER ":/images/"
#define CONNECT_IMAGE_PATH(image) CONNECT_IMAGES_FOLDER image

#ifndef receivers
#define receivers
#else
#error
#endif

#ifndef senders
#define senders
#else
#error
#endif

#ifndef is
#define is ==
#else
#error
#endif

#define CONNECT_CONSTEXPR constexpr

#define CONNECT_NAMESPACE_BEGIN namespace Connect{
#define CONNECT_NAMESPACE_END }