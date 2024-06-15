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

#if defined(__GNUC__) || defined (__clang__)
#define CONNECT_FORCE_INLINE inline __attribute__((always_inline))
#else
#define CONNECT_FORCE_INLINE inline
#endif

#define CONNECT_INLINE inline
#ifndef _NODISCARD
#define _NODISCARD [[nodiscard]]
#endif

#define CONNECT_IMAGES_FOLDER ":/Resources/images/"
#define CONNECT_IMAGE_PATH(image) CONNECT_IMAGES_FOLDER image

#define CONNECT_CONSTEXPR constexpr

#define CONNECT_NAMESPACE_BEGIN namespace Connect{
#define CONNECT_NAMESPACE_END }