// Platform specific staff

#ifndef _PLATFORM_H_
#define _PLATFORM_H_

#include "Platform/TargetPlatforms.h"

#ifdef ENGINE_TARGET_WIN32

#include "Platform/win.h"

#else // !ENGINE_TARGET_WIN32

#	include <sys/types.h>
#	define MAX_PATH 512
#	define __forceinline

typedef unsigned int UINT;
typedef u_int8_t BYTE;
typedef u_int16_t WORD;
typedef u_int32_t DWORD;
typedef int64_t __int64;

typedef struct _SYSTEMTIME {
	WORD wYear;
	WORD wMonth;
	WORD wDayOfWeek;
	WORD wDay;
	WORD wHour;
	WORD wMinute;
	WORD wSecond;
	WORD wMilliseconds;
} SYSTEMTIME;

#define MAKELONG(a, b) ((long)(((WORD)(a & 0xffff)) | ((DWORD)((WORD)(b & 0xffff))) << 16))

int strcpy_s(char* Dst, size_t DstSize, const char* Src);
int strcat_s(char* Dst, size_t DstSize, const char* Src);
int memcpy_s(void* Dst, size_t DstSize, const void* Src, size_t MaxCount);
int memmove_s(void* Dst, size_t DstSize, const void* Src, size_t MaxCount);
int sscanf_s(const char* Src, const char* Format, ...);
int sprintf_s(char* DstBuf, size_t DstSize, const char* Format, ...);

#endif // ENGINE_TARGET_*

#ifdef ENGINE_TARGET_IPHONE
#include "Platform/iphone.h"
#import <ios/Classes/Common.h>
#endif

#ifdef ENGINE_TARGET_MACOS
#include "Platform/mac.h"
#import <ios/Classes/Common.h>
#endif

#ifdef ENGINE_TARGET_LINUX
#include "../android/jni/android/android.h"
#include <stdint.h>
#endif

#endif // _PLATFORM_H_
