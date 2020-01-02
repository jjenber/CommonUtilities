#include "pch.h"
#include "CppUnitTest.h"
#include "..//CommonUtilities/Line.h"
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace CommonUtilities;

namespace LinesTests
{
	TEST_CLASS(Lines)
	{
		TEST_METHOD(CopyConstructor)
		{
			Line<float> line({ 1.f, -1.f }, { 1.5f, 0 });
			Line<float> copy = line;
			Assert::AreEqual(line.GetNormal().x, copy.GetNormal().x);
			Assert::AreEqual(line.GetNormal().y, copy.GetNormal().y);

			Assert::AreEqual(0.f, line.GetNormal().Dot(Vector2<float>{ 1.f, -1.f } -Vector2<float>{1.5f, 0}));
		}
		TEST_METHOD(Assignment)
		{
			Line<float> line;
			line.InitWith2Points({ 1.f, -1.f }, { 1.5f, 0 });
			Line<float> copy{ {1.2f, -3.f }, { -3.2f, 3.2f } };

			copy = line;
			Assert::AreEqual(line.GetNormal().x, copy.GetNormal().x);
			Assert::AreEqual(line.GetNormal().y, copy.GetNormal().y);
		}

		TEST_METHOD(InitWithPointAndDirection)
		{
			Line<float> line;
			auto direction = Vector2<float>{ 1.5f, 0.f } -Vector2<float>{ 1.f, -1.f};
			line.InitWithPointAndDirection(Vector2<float>{ 1.5f, 0.f }, direction.GetNormalized());

			Assert::AreEqual(0.f, line.GetNormal().Dot(Vector2<float>{ 1.f, -1.f } -Vector2<float>{1.5f, 0}));
		}

		TEST_METHOD(GetDirection)
		{
			Line<float> line;
			auto direction = (Vector2<float>{ 1.5f, 0.f } -Vector2<float>{ 1.f, -1.f}).GetNormalized();
			line.InitWithPointAndDirection(Vector2<float>{ 1.5f, 0.f }, direction);

			/*Assert::AreEqual(direction.x, line.GetDirection().x);
			Assert::AreEqual(direction.y, line.GetDirection().y);*/
		}

		TEST_METHOD(IsInside)
		{
			Line<float> line;
			auto direction = Vector2<float>{ 1.5f, 0.f } -Vector2<float>{ 1.f, -1.f};
			line.InitWithPointAndDirection(Vector2<float>{ 1.5f, 0.f }, direction.GetNormalized());

			// --Rough sketch--!!
			// Normal is pointing "positive left"
			/*              /
			---0----1.0---1.5-----2.0-
						  /
			  normal: \  /
					   \/
					   /
					  /
		   -1.0      X (1, -1)
					/
			*/
			Assert::IsTrue(line.IsInside({ 2.5f, -1.f }));
			Assert::IsFalse(line.IsInside({ 0, -1.f }));
		}
	};
}