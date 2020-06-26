#include "pch.h"
#include "CppUnitTest.h"
#include <JsonUtility/JsonUtility.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace CommonUtilities;
namespace Json
{
	TEST_CLASS(JsonUtilityTest)
	{
		TEST_METHOD(Write)
		{
			JsonUtility file;
			bool open = file.Open("jsonWriteTest.json", true);
			auto d = file.GetParseErrorMessage();
			Assert::IsTrue(open);
			
			file.WriteValue("teststring", 7);
			file.WriteValue("teststring2", 8);
			file.WriteValue("TestingAString", std::string("Testing"));
			file.WriteValue("TestingAStringAgain", std::string("Testing2"));
			file.WriteValue("TestingAStringAgain2", std::string("Testing2"));
			const char* s = "d";
			file.WriteValue("TestingLiteral", s);
			file.WriteValue("TestingLiteralInline", "inline");
			file.SaveDocument();
			file.Delete();
		}
		TEST_METHOD(Erase)
		{
			JsonUtility file;
			bool open = file.Open("jsonWriteTest.json", true);
			file.WriteValue("testinteger", 7);

			Assert::IsTrue(file.HasMember("testinteger"));
			file.EraseValue("testinteger");
		}
		TEST_METHOD(Clear)
		{
			JsonUtility file;
			bool open = file.Open("jsonWriteTest.json", true);
			file.WriteValue("testinteger", 7);

			Assert::IsTrue(file.HasMember("testinteger"));
			file.Clear();
		}
		TEST_METHOD(Delete)
		{
			JsonUtility file;
			file.Open("jsontest.json", true);
			file.Delete();

			JsonUtility file1;
			file1.Open("jsonWriteTest.json", true);
			
		}
	};
}