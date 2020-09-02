#include "pch.h"
#include "DL_Debug.h"
#include "DL_StackWalker.h"
#include <assert.h>
#include <cstdarg>
#include <iostream>
#include <Windows.h>
#include <filesystem>
#include <sstream>
#define GET_DATE_AND_TIME "_" __DATE__ "_" __TIME__
#pragma warning(disable:6285)
namespace DL_Debug
{
	Debug* Debug::ourInstance = nullptr;
	::std::ofstream Debug::ourGeneralLog;
	::std::map<::std::string, ::std::ofstream> Debug::ourFilterLogs;

	Debug::Debug(::std::string aDateAndTimeString)
	{
#ifndef _RETAIL
		wchar_t buffer[MAX_PATH];
		GetModuleFileName(NULL, buffer, MAX_PATH);
		::std::wstring::size_type pos = ::std::wstring(buffer).find_last_of(L"\\/");
		::std::wstring logDir = ::std::wstring(buffer).substr(0, pos);
		logDir += L"/Logs/";
		CreateDirectory(logDir.c_str(), NULL);

		std::filesystem::path path = ::std::filesystem::current_path().parent_path() ;
		::std::string generalFileName;
		generalFileName = path.string();
		generalFileName += "\\Bin\\Logs\\";
		generalFileName += "General_log";
		generalFileName += ".log";
 		ourGeneralLog.open(generalFileName); 

		assert((ourGeneralLog.is_open()) && "Failed to open or create the debug file.");
#endif
	}
	Debug::~Debug()
	{
	}

	void Debug::SetConsoleColor(int aColor)
	{
		HANDLE  hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		if (!hConsole)
		{
			return;
		}
		SetConsoleTextAttribute(hConsole, static_cast<WORD>(aColor));
	}

	bool Debug::Create()
	{
		assert((ourInstance == nullptr) && "Debugger already created");

		::std::string dateAndTime = GET_DATE_AND_TIME;

		for (size_t i = 0; i < dateAndTime.length(); ++i)
		{
			if (dateAndTime[i] == ' ')
			{
				if (dateAndTime[i + 1] == ' ')
				{
					dateAndTime.replace(i, 2, "-");
				}
				else
				{
					dateAndTime.replace(i, 1, "-");
				}
			}
			else if (dateAndTime[i] == ':')
			{
				dateAndTime.replace(i, 1, "-");
			}
		}

		dateAndTime = dateAndTime.substr(0, dateAndTime.length() - 3);

		ourInstance = new Debug(dateAndTime);
		if (ourInstance == nullptr)
		{
			return false;
		}

#ifdef _DEBUG
		//if (CU::CommandLineManager::GetInstance().HasParameter("debugLogEntry"))
		//{
		//	ourInstance->myShouldDebugLogEntry = true;
		//	::std::string logEntryDebugArgument = CU::CommandLineManager::GetInstance().GetArgumentOf("debugLogEntry");
		//	if (logEntryDebugArgument.length() > 0)
		//	{
		//		logEntryDebugArgument = logEntryDebugArgument.substr(logEntryDebugArgument.find_first_of(']') + 1);
		//
		//		ourInstance->myLogEntryToDebug = logEntryDebugArgument;
		//	}
		//}
#endif

		return true;
	}

	bool Debug::Destroy()
	{
		ourGeneralLog.close();

		for (auto& log : ourFilterLogs)
		{
			log.second.close();
		}

		//CU::SafeDelete(ourInstance);
		delete ourInstance;
		ourInstance = nullptr;
		return true;
	}

	Debug* Debug::GetInstance()
	{
		assert(ourInstance != nullptr && "Don't forget to use Create() on the Debugger");
		return ourInstance;
	}

	void Debug::AssertMessage(const char* aFileName, int aLine, const char* aFunctionName, const char* aMessage)
	{
		ourGeneralLog << "-------------------------ASSERT-------------------------" << ::std::endl;
		ourGeneralLog << "File: " << aFileName << ::std::endl;
		ourGeneralLog << "Line: " << aLine << ::std::endl;
		ourGeneralLog << "Function: " << aFunctionName << ::std::endl;
		ourGeneralLog << "Message: " << aMessage << ::std::endl;
		ourGeneralLog << ::std::endl;

		ourGeneralLog << "\t>>>>>>>>>>---------------CALLSTACK---------------<<<<<<<<<<" << ::std::endl;
		StackWalker stackWalker;
		stackWalker.ShowCallstack();

		ourGeneralLog.flush();

		/*Need to include windows.h for this
		::std::string commandAndFolderToOpen = "explorer ";

		char working_directory[MAX_PATH + 1];
		GetCurrentDirectoryA(sizeof(working_directory), working_directory);
		commandAndFolderToOpen += working_directory;

		system(commandAndFolderToOpen.c_str());*/
	}

	void Debug::DebugMessage(const char* aFile, const int aLine, const char* aFileName, const char* aFormattedMessage, ...)
	{
		aFile;
		ourGeneralLog << "-------------------------DEBUG--------------------------" << ::std::endl;
		ourGeneralLog << "File: " << aFileName << ::std::endl;
		ourGeneralLog << "Line: " << aLine << ::std::endl;
		ourGeneralLog << "Message: ";

		char buffer[256];
		va_list args;
		va_start(args, aFormattedMessage);
		vsprintf_s(buffer, aFormattedMessage, args);
		perror(buffer);
		va_end(args);

		ourGeneralLog << buffer << ::std::endl;

		ourGeneralLog << ::std::endl;
		ourGeneralLog.flush();
	}

	void Debug::PrintMessage(const char* aMessage)
	{
		ourGeneralLog << "-------------------------PRINT--------------------------" << ::std::endl;
		ourGeneralLog << aMessage << ::std::endl;
		ourGeneralLog << ::std::endl;
		ourGeneralLog.flush();
	}

	void Debug::PrintCallstackMessage(const char* aMessage)
	{
		ourGeneralLog << "\t" << aMessage;
		ourGeneralLog.flush();
	}

	void Debug::WriteLog(const char* aLog, const char* aType, const int aConsoleColor, const char* aFormat...)
	{
		if (ourFilterLogs.find(aLog) == ourFilterLogs.end())
		{
			return;
		}

		::std::string argumentsCombinedString;
		va_list args;
		va_start(args, aFormat);

		while (*aFormat != '\0')
		{
			if (*aFormat == '%')
			{
				++aFormat;

				switch (*aFormat)
				{
				case 'p':
				{
					char* charStringArg = va_arg(args, char*);
					argumentsCombinedString += charStringArg;
					break;
				}

				case 's':
				{
					::std::string stringArg = va_arg(args, ::std::string);
					argumentsCombinedString += stringArg;
					break;
				}
				case 'w':
				{
					::std::wstring stringArg = va_arg(args, ::std::wstring);
					argumentsCombinedString += std::string(stringArg.begin(),stringArg.end());
					break;
				}
				case 'i':
				{
					int intArg = va_arg(args, int);
					argumentsCombinedString += ::std::to_string(intArg);;
					break;
				}
				case 'f':
				{
					float floatArg = va_arg(args, float);
					argumentsCombinedString += ::std::to_string(floatArg);
					break;
				}
				case 'u':
				{
					unsigned int uIntArg = va_arg(args, unsigned int);
					argumentsCombinedString += ::std::to_string(uIntArg);
					break;
				}

				default:
				{
					argumentsCombinedString += "[UNKNOWN VA_ARGS FORMAT]";
					break;
				}
				}

				++aFormat;
			}
			else
			{
				argumentsCombinedString += "[MISSING % FORMAT PREFIX]";
				break;
			}
		}

		va_end(args);

		SYSTEMTIME t;
		GetLocalTime(&t);
		char currentTime[MAX_PATH];
		wsprintfA(currentTime,
			"%02d:%02d:%02d",
			t.wHour, t.wMinute, t.wSecond);



		::std::stringstream logEntryStream;
		logEntryStream << "[" << aLog << "][" << aType << "] " << argumentsCombinedString;

#ifdef _DEBUG
		if (myShouldDebugLogEntry)
		{
			::std::string logEntryWithoutTime = logEntryStream.str();
			if (logEntryWithoutTime == myLogEntryToDebug)
			{
				assert(false && "Found and stopped program on debugLogEntry argument");
			}
		}
#endif
		logEntryStream.str(::std::string());
		logEntryStream << "[" << currentTime << "][" << aLog << "][" << aType << "] " << argumentsCombinedString;
		::std::string logEntry = logEntryStream.str();
		ourFilterLogs[aLog] << logEntry << ::std::endl;
		ourFilterLogs[aLog].flush();

		SetConsoleColor(aConsoleColor);
		::std::cout << logEntry << ::std::endl;
		SetConsoleColor(CONSOLE_TEXT_COLOR_WHITE);
	}

	void Debug::ActivateFilterLog(const ::std::string& aLogName)
	{
#ifndef _RETAIL
		if (ourFilterLogs.find(aLogName) != ourFilterLogs.end())
		{
			return;
		}
		std::filesystem::path path = ::std::filesystem::current_path().parent_path();
		::std::string logFileName;
		logFileName = path.string();
		logFileName += "\\Bin\\Logs\\";
		logFileName += aLogName;
		logFileName += "_log";
		logFileName += ".log";
		ourFilterLogs[aLogName].open(logFileName);
#else 
		aLogName;
#endif
	}

	void Debug::DeactivateFilterLog(const ::std::string& aLogName)
	{
		if (ourFilterLogs.find(aLogName) == ourFilterLogs.end())
		{
			return;
		}

		ourFilterLogs[aLogName].close();
		ourFilterLogs.erase(aLogName);
	}
}