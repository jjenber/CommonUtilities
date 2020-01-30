#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "../CommonUtilities/Intersection.h"

using Vector3f = CommonUtilities::Vector3<float>;
using Vector3d = CommonUtilities::Vector3<double>;
using Spheref = CommonUtilities::Sphere<float>;
using Sphered = CommonUtilities::Sphere<double>;

namespace Assignment9Intersections
{
	TEST_CLASS(SphereTests)
	{
	public:
		TEST_METHOD(IsInside)
		{
			// Checking the Sphere<float> IsInside() function.
			Spheref sphereF(Vector3f(100.f, 100.f, 100.f), 10.f);

			Assert::IsTrue(sphereF.IsInside(Vector3f(100.f, 100.f, 100.f)), L"Point(100, 100, 100) should be inside of Sphere<float> at (100, 100, 100) with radius 10.");
			Assert::IsTrue(sphereF.IsInside(Vector3f(110.f, 100.f, 100.f)), L"Point(110, 100, 100) should be inside of Sphere<float> at (100, 100, 100) with radius 10.");
			Assert::IsTrue(sphereF.IsInside(Vector3f(100.f, 110.f, 100.f)), L"Point(100, 110, 100) should be inside of Sphere<float> at (100, 100, 100) with radius 10.");
			Assert::IsTrue(sphereF.IsInside(Vector3f(100.f, 100.f, 110.f)), L"Point(100, 100, 110) should be inside of Sphere<float> at (100, 100, 100) with radius 10.");

			Assert::IsFalse(sphereF.IsInside(Vector3f(111.f, 100.f, 100.f)), L"Point(111, 100, 100) should not be inside of Sphere<float> at (100, 100, 100) with radius 10.");
			Assert::IsFalse(sphereF.IsInside(Vector3f(100.f, 111.f, 100.f)), L"Point(100, 111, 100) should not be inside of Sphere<float> at (100, 100, 100) with radius 10.");
			Assert::IsFalse(sphereF.IsInside(Vector3f(100.f, 100.f, 111.f)), L"Point(100, 100, 111) should not be inside of Sphere<float> at (100, 100, 100) with radius 10.");

			Assert::IsFalse(sphereF.IsInside(Vector3f(107.8f, 107.8f, 100.f)), L"Point(107.8, 107.8, 100) should not be inside of Sphere<float> at (100, 100, 100) with radius 10.");
			Assert::IsFalse(sphereF.IsInside(Vector3f(107.8f, 100.f, 107.8f)), L"Point(107.8, 100, 107.8f) should not be inside of Sphere<float> at (100, 100, 100) with radius 10.");
			Assert::IsFalse(sphereF.IsInside(Vector3f(100.f, 107.8f, 107.8f)), L"Point(100, 107.8, 107.8) should not be inside of Sphere<float> at (100, 100, 100) with radius 10.");

			// Checking the Sphere<double> IsInside() function.
			Sphered sphereD(Vector3d(100.f, 100.f, 100.f), 10.f);

			Assert::IsTrue(sphereD.IsInside(Vector3d(100.f, 100.f, 100.f)), L"Point(100, 100, 100) should be inside of Sphere<double> at (100, 100, 100) with radius 10.");
			Assert::IsTrue(sphereD.IsInside(Vector3d(110.f, 100.f, 100.f)), L"Point(110, 100, 100) should be inside of Sphere<double> at (100, 100, 100) with radius 10.");
			Assert::IsTrue(sphereD.IsInside(Vector3d(100.f, 110.f, 100.f)), L"Point(100, 110, 100) should be inside of Sphere<double> at (100, 100, 100) with radius 10.");
			Assert::IsTrue(sphereD.IsInside(Vector3d(100.f, 100.f, 110.f)), L"Point(100, 100, 110) should be inside of Sphere<double> at (100, 100, 100) with radius 10.");

			Assert::IsFalse(sphereD.IsInside(Vector3d(111.f, 100.f, 100.f)), L"Point(111, 100, 100) should not be inside of Sphere<double> at (100, 100, 100) with radius 10.");
			Assert::IsFalse(sphereD.IsInside(Vector3d(100.f, 111.f, 100.f)), L"Point(100, 111, 100) should not be inside of Sphere<double> at (100, 100, 100) with radius 10.");
			Assert::IsFalse(sphereD.IsInside(Vector3d(100.f, 100.f, 111.f)), L"Point(100, 100, 111) should not be inside of Sphere<double> at (100, 100, 100) with radius 10.");

			Assert::IsFalse(sphereD.IsInside(Vector3d(107.8f, 107.8f, 100.f)), L"Point(107.8, 107.8, 100) should not be inside of Sphere<double> at (100, 100, 100) with radius 10.");
			Assert::IsFalse(sphereD.IsInside(Vector3d(107.8f, 100.f, 107.8f)), L"Point(107.8, 100, 107.8f) should not be inside of Sphere<double> at (100, 100, 100) with radius 10.");
			Assert::IsFalse(sphereD.IsInside(Vector3d(100.f, 107.8f, 107.8f)), L"Point(100, 107.8, 107.8) should not be inside of Sphere<double> at (100, 100, 100) with radius 10.");
		}
	};
}