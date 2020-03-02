#include "pch.h"
#include "CppUnitTest.h"
#include "..//CommonUtilities/Stack.h"
#include <string>
#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace CommonUtilities;

namespace StackTest
{
	TEST_CLASS(Constructors)
	{
	public:
		TEST_METHOD(Push)
		{
			Stack<int> stackI;
			Stack<std::string> stackS;

			stackI.Push(0);
			stackI.Push(1);
			stackI.Push(2);

			Assert::AreEqual(2, stackI.Pop());
			Assert::AreNotEqual(0, stackI.Pop());
			Assert::AreEqual(0, stackI.Pop());
			Assert::AreEqual(0, stackI.GetSize());

			stackS.Push("0");
			stackS.Push("1");
			stackS.Push("2");

			Assert::AreEqual(3, stackS.GetSize());
			Assert::AreEqual("2", stackS.Pop().c_str());
			Assert::AreEqual("1", stackS.Pop().c_str());
			Assert::AreEqual("0", stackS.Pop().c_str());

		}
	};
}