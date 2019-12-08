#include "DL_Debug.h"
#include <chrono>
#include <ctime>

namespace DL_Debug
{
	Debug* Debug::ourInstance = nullptr;
	Debug* Debug::GetInstance()
	{
		return ourInstance;
	}

	void Debug::Create(const std::string& aFile)
	{
		bool b = ourInstance == nullptr && "There is already an instance of Debug.";
		if (b)
		{
			int i = 0;
			(void)i;
		}
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
		AssertMessage(aStatement, aMessage, (std::string(aMessage) + aFileName + aFunctionName + std::to_string(aLine)).c_str());
	}

	void Debug::AssertMessage(bool aStatement, const char* aMessage, const char* aDLmetaInfo)
	{
		PrintMessage((std::string(aMessage) + "\n" + aDLmetaInfo).c_str());
		assert(aStatement && aMessage);
	}

	void Debug::PrintMessage(const char* aMessage)
	{
		PrintTimeStamp();
		ourInstance->myFile << (aMessage) << '\n' << std::endl;
	}

	void Debug::PrintMessageFormat(const char* aMessage, ...)
	{
		va_list args;
		va_start(args, aMessage);
		PrintTimeStamp();
		PrintMessageFormatInternal(aMessage, args);
		va_end(args);
	}

	void Debug::PrintMessageNoFormatting(const char* aString)
	{
		ourInstance->myFile << aString;
	}

	void Debug::DebugMessage(const int aLine, const char* aFileName, const char* aFormattedString, ...)
	{
		va_list args;
		va_start(args, aFormattedString);
		PrintTimeStamp();
		PrintMessageFormatInternal(aFormattedString, args);
		ourInstance->myFile << std::string("(at ") + aFileName + ":" + std::to_string(aLine) + ")\n";
		va_end(args);
	}

	void Debug::PrintTimeStamp() const
	{
		const auto now = std::chrono::system_clock::now();
		const auto time_T = std::chrono::system_clock::to_time_t(now);
		char timeBuffer[26];
		ctime_s(timeBuffer, size_t(26), &time_T);
		std::string str(std::begin(timeBuffer) + 11, std::end(timeBuffer) - 7);
		ourInstance->myFile << '[' << str << "] ";
	}

	void Debug::PrintMessageFormatInternal(const char* aMessage, va_list aArgsList)
	{
		char buffer[256];
		std::vsnprintf(buffer, sizeof(buffer), aMessage, aArgsList);
		ourInstance->myFile << buffer << std::endl;
	}
}