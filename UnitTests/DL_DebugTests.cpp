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
			const char* filename = "MyLogfile.txt";
			remove(filename);
			Debug::Create(filename);
			auto stream = std::ifstream(filename);
			Assert::IsTrue(stream.is_open());
			Assert::IsFalse(stream.fail());
			stream.close();
			Debug::Destroy();
			remove(filename);
		}
	};

	TEST_CLASS(Functions)
	{
		TEST_METHOD(AssertMessageStatement)
		{
			Debug::Create();
			//Debug::GetInstance()->AssertMessage(true, "Hello");
			//Debug::GetInstance()->AssertMessage("Hello");
			Debug::Destroy();
		}

		TEST_METHOD(PrintMessageFormatted)
		{
			Debug::Create();
			Debug::GetInstance()->PrintMessageFormat("Hello %f", 2.34);
			Debug::Destroy();
		}
	};

	TEST_CLASS(Macros)
	{
		TEST_METHOD(Macro_DL_ASSERT_message)
		{
			Debug::Create();
			auto s = std::string("This is the message!") + std::string("\n") + __FUNCTION__ + "() (at " + __FILE__ + ":" + std::to_string(__LINE__) + ")\n";
			Debug::GetInstance()->PrintMessage(s.c_str());
			Debug::Destroy();
		}
	};
}