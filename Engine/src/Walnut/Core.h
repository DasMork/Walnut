#pragma once

#ifdef WN_PLATFORM_WINDOWS
#ifdef WN_BUILD_DLL
#define WALNUT_API __declspec(dllexport)
#else
#define WALNUT_API __declspec(dllimport)
#endif
#else
#error Walnut only supports Windows at the moment!
#endif

#ifdef WN_ENABLE_ASSERTS
#define WN_ASSERT(x, ...){if(!(x)){WN_FATAL("Assertion failed: {0}", __VA_ARGS__); __debugbreak();}}
#define WN_CORE_ASSERT(x, ...){if(!(x)){WN_CORE_FATAL("Assertion failed: {0}", __VA_ARGS__); __debugbreak();}}
#else
#define WN_ASSERT(x, ...)
#define WN_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)