#include "pch.h"
#include "CppUnitTest.h"
#include <JsonUtility/JsonUtility.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace CommonUtilities;
namespace Json
{
	TEST_CLASS(JsonUtilityTest)
	{
		TEST_METHOD(OpenAndRead)
		{
			JsonUtility file;
			bool open =  file.Open("jsontest1.json", false);
			Assert::IsTrue(open);

			int i = file.ParseValue<int>("Test");
			Assert::AreEqual(2, i);
		}
		TEST_METHOD(OpenAndReadArray)
		{
			JsonUtility file;
			bool open = file.Open("jsontest1.json", false);
			std::string msg = file.GetParseErrorMessage();
			Assert::IsTrue(open);

			file.IterateOverArray("Arr", [](const rapidjson::Value& element) {
				Assert::IsTrue(element.IsInt());
				});
		}
	};
}