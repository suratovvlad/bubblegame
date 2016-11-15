#ifndef _TYPES_H_
#define _TYPES_H_

#include <cstdint>
#include <cstdio>
#include <cmath>

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <limits>
#include <typeindex>

extern "C" {
	#include <png.h>

	#include <lua.h>
	#include <lauxlib.h>
	#include <lualib.h>
}

#include "Platform/TargetPlatforms.h"

// на MacOS отключаем системный макрос check, иначе будет конфликт с luabind и boost
#if defined(ENGINE_TARGET_MACOS)
#if defined(check)
#undef check
#endif // check
#endif

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wconversion"
#endif

#include <boost/smart_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/cast.hpp>
#include <boost/pool/pool_alloc.hpp>
#include <boost/pool/object_pool.hpp>
#include <boost/intrusive/list.hpp>
#include <boost/asio.hpp>
#include <boost/config.hpp>

#ifdef ENGINE_TARGET_WIN32
#	define WIN32_LEAN_AND_MEAN
#	define NOMINMAX 1
#	include <windows.h>

#ifndef EDITOR_MODE
#	if defined(_DEBUG)
#		define _CRTDBG_MAP_ALLOC
#		include <stdlib.h>
#		include <crtdbg.h>
#	endif
#endif

#endif // ENGINE_TARGET_WIN32

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#if defined(__OBJC__)
#undef nil
#define nil _nil
#endif

#include <luabind/luabind.hpp>
#include <luabind/operator.hpp>
#include <luabind/adopt_policy.hpp>

#if defined(__OBJC__)
#undef nil
#define nil __null
#endif

#include <pugixml.hpp>
#include "../rapidxml/rapidxml.hpp"

#include "EngineAssert.h"
#include "Core/Log.h"

// на MacOSX инклудим файл с виртуальными кодами клавиш
#ifdef ENGINE_TARGET_MACOS
#include <signal.h>
#include <sys/stat.h>
#include <mach/mach_time.h>
#include <unistd.h>
#include <glob.h>
#include <OpenGL/OpenGL.h>
#include <OpenGL/glu.h>
#include <AGL/agl.h>
#include "Core/KeyCodes_mac.h"
#endif //ENGINE_TARGET_MACOS

#ifdef ENGINE_TARGET_LINUX
#   include <sys/stat.h>
#   include <sys/types.h>
#   include <errno.h>
#endif

#ifdef ENGINE_TARGET_ANDROID
#include <jni.h>
#include <android/log.h>
#include <GLES/gl.h>
#include <GLES/glext.h>
#endif // ENGINE_TARGET_ANDROID

#if defined(ENGINE_TARGET_IPHONE)
#include <sys/stat.h>
#endif // ENGINE_TARGET_IPHONE

#if defined(ENGINE_TARGET_IPHONE) || defined(ENGINE_TARGET_MACOS)
#	include <OpenAL/al.h>
#	include <OpenAL/alc.h>
#else
#	include <al.h>
#	include <alc.h>
#endif

// Disable some annoying warnings
//
#if defined(_MSC_VER)
// warning C4244: conversion from 'float' to 'int', possible loss of data
// warning C4800: forcing value to bool 'true' or 'false' (performance warning)
// warning C4305: truncation from 'double' to 'float'
#pragma warning(disable: 4244 4305 4800)
#elif defined(__clang__) || defined(__llvm__)
#pragma clang diagnostic ignored "-Wdouble-promotion"
#pragma clang diagnostic ignored "-Wfloat-conversion"
#pragma clang diagnostic ignored "-Wunused"
#pragma clang diagnostic ignored "-Wshadow"
#pragma clang diagnostic ignored "-Wparentheses"
#else
#pragma GCC diagnostic ignored "-Wdouble-promotion"
//#pragma GCC diagnostic ignored "-Wfloat-conversion"
#pragma GCC diagnostic ignored "-Wunused"
#pragma GCC diagnostic ignored "-Wshadow"
#pragma GCC diagnostic ignored "-Wparentheses"
#endif

#endif //_TYPES_H_
