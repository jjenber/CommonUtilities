#include "pch.h"
#include "CppUnitTest.h"
#include "..//CommonUtilities/RapidJSON/document.h"
#include "..//CommonUtilities/RapidJSON/istreamwrapper.h"
#include <fstream>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RapidJSON
{
	TEST_CLASS(Create)
	{
		TEST_METHOD(ParseTestObject)
		{
			std::ifstream stream("test.json");
			rapidjson::Document document;
			rapidjson::IStreamWrapper wrapper(stream);
			document.ParseStream(wrapper);
		
			Assert::IsTrue(document.HasMember("hello"));
			Assert::IsTrue(document["hello"].IsString());
			std::string w = document["hello"].GetString();
		}
	};
}