#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <string>

extern "C"
{
#include <corecrt.h>

	_ACRTIMP void __cdecl _wassert(
		_In_z_ wchar_t const* _Message,
		_In_z_ wchar_t const* _File,
		_In_   unsigned       _Line
	);

#define DL_ASSERT(aExpression) (void)(																										\
		(!!(aExpression)) ||																				/*If false, print and crash*/	\
			(DL_Debug::Debug::GetInstance()->AssertMessage(__FILE__,__LINE__,__FUNCTION__, #aExpression),	/*Assert Message*/				\
			_wassert(_CRT_WIDE(#aExpression), _CRT_WIDE(__FILE__), (unsigned)(__LINE__))					/*Crash program*/				\
			,0)																								/*Evaluates this*/				\
	)

#define DL_CRASH(aMessage) (void)(																										\
		(DL_Debug::Debug::GetInstance()->AssertMessage(__FILE__,__LINE__,__FUNCTION__, #aMessage),		/*Assert Message*/				\
		_wassert(_CRT_WIDE(#aMessage), _CRT_WIDE(__FILE__), (unsigned)(__LINE__))						/*Crash program*/				\
		,0)																								/*Evaluates this*/				\
	)
};

#define DL_DEBUG( ... )  DL_Debug::Debug::GetInstance()->DebugMessage(__FILE__, __LINE__,__FUNCTION__,__VA_ARGS__);

#define DL_PRINT(aMessage)  DL_Debug::Debug::GetInstance()->PrintMessage(aMessage);

#define DL_PRINT_CALLSTACK(aMessage)  DL_Debug::Debug::GetInstance()->PrintCallstackMessage(aMessage);

#define DL_WRITELOG(log, ...)  DL_Debug::Debug::GetInstance()->WriteLog(log,__VA_ARGS__);

#ifdef USE_FILTERLOG  
#define ENGINE_ERROR_LOG(...) DL_WRITELOG("Engine", "ERROR", CONSOLE_TEXT_COLOR_RED, __VA_ARGS__)
#define RESOURCE_ERROR_LOG(...) DL_WRITELOG("Resource","ERROR", CONSOLE_TEXT_COLOR_RED, __VA_ARGS__)
#define GAMEPLAY_ERROR_LOG(...) DL_WRITELOG("Gameplay","ERROR", CONSOLE_TEXT_COLOR_RED, __VA_ARGS__)

#define ENGINE_INFO_LOG(...) DL_WRITELOG("Engine", "INFO", CONSOLE_TEXT_COLOR_GREEN, __VA_ARGS__)
#define RESOURCE_INFO_LOG(...) DL_WRITELOG("Resource","INFO", CONSOLE_TEXT_COLOR_BLUE, __VA_ARGS__)
#define GAMEPLAY_INFO_LOG(...) DL_WRITELOG("Gameplay","INFO", CONSOLE_TEXT_COLOR_YELLOW, __VA_ARGS__)

#define ENGINE_ERROR_LOG_RETURN_FALSE_IF_FAILED(result, ...)  if(FAILED(result)){ENGINE_ERROR_LOG(__VA_ARGS__); return false;}
#define RESOURCE_ERROR_LOG_RETURN_FALSE_IF_FAILED(result,...) if(FAILED(result)){RESOURCE_ERROR_LOG(__VA_ARGS__); return false;}
#define GAMEPLAY_ERROR_LOG_RETURN_FALSE_IF_FAILED(result,...) if(FAILED(result)){GAMEPLAY_ERROR_LOG(__VA_ARGS__); return false;}

#define ENGINE_ERROR_LOG_RETURN_NULLPTR_IF_FAILED(result, ...)  if(FAILED(result)){ENGINE_ERROR_LOG(__VA_ARGS__); return nullptr;}
#define RESOURCE_ERROR_LOG_RETURN_NULLPTR_IF_FAILED(result,...) if(FAILED(result)){RESOURCE_ERROR_LOG(__VA_ARGS__); return nullptr;}
#define GAMEPLAY_ERROR_LOG_RETURN_NULLPTR_IF_FAILED(result,...) if(FAILED(result)){GAMEPLAY_ERROR_LOG(__VA_ARGS__); return nullptr;}

#else
#define ENGINE_ERROR_LOG(...) 
#define RESOURCE_ERROR_LOG(...)
#define GAMEPLAY_ERROR_LOG(...)
#define ENGINE_INFO_LOG(...)
#define RESOURCE_INFO_LOG(...)
#define GAMEPLAY_INFO_LOG(...)

#define ENGINE_ERROR_LOG_RETURN_FALSE_IF_FAILED(result, ...) 
#define RESOURCE_ERROR_LOG_RETURN_FALSE_IF_FAILED(result,...)
#define GAMEPLAY_ERROR_LOG_RETURN_FALSE_IF_FAILED(result,...)
#define ENGINE_ERROR_LOG_RETURN_NULLPTR_IF_FAILED(result, ...) 
#define RESOURCE_ERROR_LOG_RETURN_NULLPTR_IF_FAILED(result,...)
#define GAMEPLAY_ERROR_LOG_RETURN_NULLPTR_IF_FAILED(result,...)
#endif

#define CONSOLE_TEXT_COLOR_GREEN 10
#define CONSOLE_TEXT_COLOR_BLUE 11
#define CONSOLE_TEXT_COLOR_RED 12
#define CONSOLE_TEXT_COLOR_YELLOW 14
#define CONSOLE_TEXT_COLOR_WHITE 15

namespace DL_Debug
{
	class Debug
	{
	public:
		static bool Create();
		static bool Destroy();
		static Debug* GetInstance();

		void AssertMessage(const char* aFileName, int aLine, const char* aFunctionName, const char* aString);
		void DebugMessage(const char* aFile, const int aLine, const char* aFileName, const char* aFormattedString, ...);
		void PrintMessage(const char* aString);
		void PrintCallstackMessage(const char* aString);
		void WriteLog(const char* aLog, const char* aType, const int aConsoleColor, const char* aFormat...);

		void ActivateFilterLog(const ::std::string& aLogName);
		void DeactivateFilterLog(const ::std::string& aLogName);

	private:
		Debug(::std::string aDateAndTimeString);
		~Debug();

		void SetConsoleColor(int aColor);

		static Debug* ourInstance;
		static ::std::ofstream ourGeneralLog;
		static ::std::map<::std::string, ::std::ofstream> ourFilterLogs;

#ifdef _DEBUG
		bool myShouldDebugLogEntry = false;
		::std::string myLogEntryToDebug;
#endif
	};
}