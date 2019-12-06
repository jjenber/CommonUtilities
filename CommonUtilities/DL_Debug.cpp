#include "DL_Debug.h"
#include <cassert>
#include <chrono>
#include <ctime>
#include <fstream>
#include <stdarg.h>
#include <string>

namespace DL_Debug
{
	Debug* Debug::ourInstance = nullptr;
	Debug* Debug::GetInstance()
	{
		return ourInstance;
	}

	void Debug::Create(const std::string& aFile)
	{
		assert(ourInstance == nullptr && "There is already an instance of Debug.");
		ourInstance = new Debug();
		ourInstance->myFile.open(aFile);
	}
	void Debug::Destroy()
	{
		assert(ourInstance != nullptr && "No DL_DEBUG created!");
		ourInstance->myFile.close();
		delete ourInstance;
		ourInstance = nullptr;
	}

	void Debug::AssertMessage(bool aStatement, const char* aFileName, int aLine, const char* aFunctionName, const char* aMessage)
	{
		PrintMessage((std::string(aMessage) + aFileName + aFunctionName + std::to_string(aLine)).c_str());
		assert(aStatement);
	}

	void Debug::PrintMessage(const char* aMessage)
	{
		ourInstance->myFile << GetTimeStamp() << (aMessage) << std::endl;
	}

	void Debug::PrintMessageFormat(const char* aMessage, ...)
	{
		char buffer[256];
		va_list args;
		va_start(args, aMessage);
		std::vsnprintf(buffer, sizeof(buffer), aMessage, args);
		va_end(args);

		PrintMessage({ buffer });
	}

	void Debug::DebugMessage(const int aLine, const char* aFileName, const char* aFormattedString, ...)
	{
		aLine; aFileName; aFormattedString;
	}

	std::string Debug::GetTimeStamp() const
	{
		const auto now = std::chrono::system_clock::now();
		const auto time_T = std::chrono::system_clock::to_time_t(now);
		char timeBuffer[26];
		ctime_s(timeBuffer, size_t(26), &time_T);
		std::string str(std::begin(timeBuffer) + 11, std::end(timeBuffer) - 7);
		return std::string("[") + str + "] ";
	}
}