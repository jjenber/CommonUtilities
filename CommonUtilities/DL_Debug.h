#pragma once
#include <fstream>
#include <cassert>

#define GET_DL_ASSERT(_1, NAME, ...) NAME
#define DL_ASSERT(...) GET_DL_ASSERT(__VA_ARGS__, DL_ASSERT_M, DL_ASSERT_M_STATEMENT)(__VA_ARGS__)
#define DL_ASSERT_M (_assertMessage) DL_ASSERT_M_STATEMENT(true, _assertMessage)
#define DL_ASSERT_M_STATEMENT(_aBoolStatement, _aAssertMessage) Debug::GetInstance()->PrintMessage(_aAssertMessage + DL_META_INFO_FORMATTED); assert(_aBoolStatement)

#define DL_PRINT(_aPrintMessage) (Debug::GetInstance()->PrintMessage(_aPrintMessage))
#define DL_DEBUG(_aMessage, ...) (Debug::GetInstance()->PrintMessageFormat(_aMessage, ...))

#define DL_META_INFO_FORMATTED std::string(__FUNCTION__) + " @Line: " + std::to_string(__LINE__) + ".\n" + __FILE__; // TODO: sstream this
#define LOG_TIME_FORMAT "%H:%M:%S"

namespace DL_Debug
{
	class Debug
	{
	public:
		static Debug* GetInstance();
		static void Create(const std::string& aFile = "DebugLogger.txt");
		static void Destroy();

		void AssertMessage(bool aStatement, const char* aFileName, int aLine, const char* aFunctionName, const char* aMessage);
		void PrintMessage(const char* aMessage);
		void PrintMessageFormat(const char* aMessage, ...);
		void DebugMessage(const int aLine, const char* aFileName, const char* aFormattedString, ...);
	private:
		std::string GetTimeStamp() const;

		Debug() = default;
		~Debug() = default;
		static Debug* ourInstance;
		std::ofstream myFile;
	};
}