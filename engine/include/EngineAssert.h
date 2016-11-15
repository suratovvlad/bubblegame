#ifndef __ENGINE_ASSERT_H__
#define __ENGINE_ASSERT_H__

#include <string>

void AssertionFailed(const std::string& message, const std::string& expression, const char* file, int line);

#if !defined(PRODUCTION)

#define Assert(expr) do { if (!(expr)) { AssertionFailed("Assersion failed", #expr, __FILE__, __LINE__); } } while(0)
#define Assert2(expr, message) do { if (!(expr)) { AssertionFailed(message, #expr, __FILE__, __LINE__); } } while(0)
#define Halt(message) AssertionFailed("Halt occured", message, __FILE__, __LINE__)

#else // PRODUCTION

#define Assert(expr) ((void)0)
#define Assert2(expr, message) ((void)0)
#define Halt(message) ((void)0)

#endif // !PRODUCTION

#endif // __ENGINE_ASSERT_H__
