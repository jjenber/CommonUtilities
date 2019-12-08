#pragma once
#include <fstream>
#include <stdarg.h>
#include <string>
#include "DL_assert.h"

#define EXPAND(_ARG) _ARG
#define GET_DL_ASSERT(_1,_2,NAME,...) NAME
#define DL_ASSERT(...) EXPAND(GET_DL_ASSERT(__VA_ARGS__, DL_ASSERT_M_STATEMENT, DL_ASSERT_M)(__VA_ARGS__))
#define DL_ASSERT_M(_ASSERTMESSAGE) Debug::GetInstance()->AssertMessage(false, _ASSERTMESSAGE, DL_META_INFO_CSTR)
#define DL_ASSERT_M_STATEMENT(_STATEMENT, _ASSERTMESSAGE) Debug::GetInstance()->AssertMessage(_STATEMENT, _ASSERTMESSAGE, DL_META_INFO_CSTR)

#define DL_PRINT(_PRINTMESSAGE)      (Debug::GetInstance()->PrintMessage(_PRINTMESSAGE))
#define DL_DEBUG(_PRINTMESSAGE, ...) (Debug::GetInstance()->PrintMessageFormat(_PRINTMESSAGE, ...))

#define DL_META_INFO_CSTR (std::string(__FUNCTION__) + "() (at " + __FILE__ + ":" + std::to_string(__LINE__) + ")").c_str() // TODO: sstream this
#define LOG_TIME_FORMAT "%H:%M:%S"

namespace DL_Debug
{
	class Debug
	{
	public:
		static Debug*		GetInstance();
		static void			Create(const std::string& aFile = "DebugLogger.txt");
		static void			Destroy();

		void				AssertMessage(bool aStatement, const char* aFileName, int aLine, const char* aFunctionName, const char* aMessage);
		void				AssertMessage(bool aStatement, const char* aMessage, const char* aDLMetaInfo);
		void				PrintMessage(const char* aMessage);
		void				PrintMessageFormat(const char* aMessage, ...);
		void				DebugMessage(const int aLine, const char* aFileName, const char* aFormattedString, ...);
		void				DebugMessage(const char* aDLMetaInfo, const char* aFormattedString, ...);
	private:
		std::string			GetTimeStamp() const;

		Debug()				= default;
		~Debug()			= default;
		static Debug*		ourInstance;
		std::ofstream		myFile;
	};
}