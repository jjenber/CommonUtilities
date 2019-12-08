#include "pch.h"
#include "CppUnitTest.h"
#include "..//CommonUtilities/DL_Debug.h"
#include <fstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace DL_Debug;

namespace DebugLogger
{
	TEST_CLASS(DL_DebugTest)
	{
		TEST_METHOD(MemLeak)
		{
			_CrtMemState memStart;
			_CrtMemState memEnd;
			_CrtMemState memDiff;
			_CrtMemCheckpoint(&memStart);
			{
				Debug::Create();
				auto stream = std::ifstream("DebugLogger.txt");
				Assert::IsTrue(stream.is_open());
				Assert::IsFalse(stream.fail());
				stream.close();
				Debug::Destroy();
			}
			_CrtMemCheckpoint(&memEnd);
			Assert::IsFalse(_CrtMemDifference(&memDiff, &memStart, &memEnd), L"There is a memory leak!");
		}
		TEST_METHOD(CreateLogFileDefaultName)
		{
			remove("DebugLogger.txt");
			Debug::Create();
			auto stream = std::ifstream("DebugLogger.txt");
			Assert::IsTrue(stream.is_open());
			Assert::IsFalse(stream.fail());
			stream.close();
			Debug::Destroy();
		}
		TEST_METHOD(CreateLogFileUserName)
		{
			const char* filename = "TestLog_MyLogfile.txt";
			remove(filename);
			Debug::Create(filename);
			auto stream = std::ifstream(filename);
			Assert::IsTrue(stream.is_open());
			Assert::IsFalse(stream.fail());
			stream.close();
			Debug::Destroy();
		}
	};

	TEST_CLASS(Functions)
	{
		TEST_METHOD(AssertMessageStatement)
		{
			Debug::Create("TestLog_AssertMessageStatement.txt");
			Debug::GetInstance()->AssertMessage(true, "This is a message!", DL_META_INFO_CSTR);
			Debug::GetInstance()->AssertMessage(true, "This is another message!", DL_META_INFO_CSTR);
			Debug::Destroy();
		}

		TEST_METHOD(PrintMessageFormatted)
		{
			Debug::Create("TestLog_PrintMessageFormatted.txt");
			Debug::GetInstance()->PrintMessageFormat("PrintMessageFormatted (float): %f", 2.34f);
			Debug::GetInstance()->PrintMessageFormat("PrintMessageFormatted (int): %i", 4);
			Debug::GetInstance()->PrintMessageFormat("PrintMessageFormatted (double): %f", 0.54363654);
			Debug::Destroy();
		}

		TEST_METHOD(DebugMessage)
		{
			Debug::Create("TestLog_DebugMessage.txt");
			Debug::GetInstance()->DebugMessage(__LINE__, __FILE__, "DebugMessage (float): %f", 2.34f);
			Debug::GetInstance()->DebugMessage(__LINE__, __FILE__, "DebugMessage (int): %i", 4);
			Debug::GetInstance()->DebugMessage(__LINE__, __FILE__, "DebugMessage (double): %f", 0.54363654);
			Debug::Destroy();
		}
	};

	TEST_CLASS(Macros)
	{
		TEST_METHOD(Macro_DL_ASSERT)
		{
			Debug::Create("TestLog_Macro_DL_ASSERT.txt");
			DL_ASSERT(true, "Macro_DL_ASSERT_message_statement");
			Debug::Destroy();
		}

		TEST_METHOD(Macro_DL_PRINT)
		{
			Debug::Create("TestLog_Macro_DL_PRINT.txt");
			DL_PRINT("This is a print macro.");
			DL_PRINT("This is another print macro.");
			Debug::Destroy();
		}

		TEST_METHOD(Macro_DL_DEBUG)
		{
			Debug::Create("TestLog_Macro_DL_DEBUG.txt");
			DL_DEBUG("This is a debug macro (float):%f", 3.5f);
			DL_DEBUG("This is a debug macro (int):%i", 5849);
			DL_DEBUG("This is a debug macro (string):%s", "a string");
			Debug::Destroy();
		}
	};
}