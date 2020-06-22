#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include <Shapes/Intersection.h>

using Vector3f = CommonUtilities::Vector3<float>;
using Vector3d = CommonUtilities::Vector3<double>;
using AABB3Df = CommonUtilities::AABB3D<float>;
using AABB3Dd = CommonUtilities::AABB3D<double>;

namespace Assignment9Intersections
{
	TEST_CLASS(AABB3DTests)
	{
	public:
		TEST_METHOD(IsInside)
		{
			// Checking the AABB3D<float> IsInside() function.
			AABB3Df aabbF(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(30.0f, 30.0f, 30.0f));

			Assert::IsTrue(aabbF.IsInside(Vector3f(15.f, 15.f, 15.f)), L"Center (15.0f, 15.0f, 15.0f) should be inside of AABB<float> (0.0f, 0.0f, 0.0f) to (30.0f, 30.0f, 30.0f)");
			Assert::IsTrue(aabbF.IsInside(Vector3f(0.0f, 0.0f, 0.0f)), L"Corner (0.0f, 0.0f, 0.0f) should be inside of AABB<float> (0.0f, 0.0f, 0.0f) to (30.0f, 30.0f, 30.0f)");
			Assert::IsTrue(aabbF.IsInside(Vector3f(0.0f, 0.0f, 30.0f)), L"Corner (0.0f, 0.0f, 30.0f) should be inside of AABB<float> (0.0f, 0.0f, 0.0f) to (30.0f, 30.0f, 30.0f)");
			Assert::IsTrue(aabbF.IsInside(Vector3f(0.0f, 30.0f, 30.0f)), L"Corner (0.0f, 30.0f, 30.0f) should be inside of AABB<float> (0.0f, 0.0f, 0.0f) to (30.0f, 30.0f, 30.0f)");
			Assert::IsTrue(aabbF.IsInside(Vector3f(0.0f, 30.0f, 0.0f)), L"Corner (0.0f, 30.0f, 0.0f) should be inside of AABB<float> (0.0f, 0.0f, 0.0f) to (30.0f, 30.0f, 30.0f)");
			Assert::IsTrue(aabbF.IsInside(Vector3f(30.0f, 0.0f, 0.0f)), L"Corner (30.0f, 0.0f, 0.0f) should be inside of AABB<float> (0.0f, 0.0f, 0.0f) to (30.0f, 30.0f, 30.0f)");
			Assert::IsTrue(aabbF.IsInside(Vector3f(30.0f, 0.0f, 30.0f)), L"Corner (30.0f, 0.0f, 30.0f) should be inside of AABB<float> (0.0f, 0.0f, 0.0f) to (30.0f, 30.0f, 30.0f)");
			Assert::IsTrue(aabbF.IsInside(Vector3f(30.0f, 30.0f, 30.0f)), L"Corner (30.0f, 30.0f, 30.0f) should be inside of AABB<float> (0.0f, 0.0f, 0.0f) to (30.0f, 30.0f, 30.0f)");
			Assert::IsTrue(aabbF.IsInside(Vector3f(30.0f, 30.0f, 0.0f)), L"Corner (30.0f, 30.0f, 0.0f) should be inside of AABB<float> (0.0f, 0.0f, 0.0f) to (30.0f, 30.0f, 30.0f)");

			Assert::IsFalse(aabbF.IsInside(Vector3f(-1.f, 0.0f, 0.0f)), L"Center (-1.0f, 0.0f, 0.0f) should not be inside of AABB<float> (0.0f, 0.0f, 0.0f) to (30.0f, 30.0f, 30.0f)");
			Assert::IsFalse(aabbF.IsInside(Vector3f(0.0f, -1.f, 0.0f)), L"Center (0.0f, -1.0f, 0.0f) should not be inside of AABB<float> (0.0f, 0.0f, 0.0f) to (30.0f, 30.0f, 30.0f)");
			Assert::IsFalse(aabbF.IsInside(Vector3f(0.0f, 0.0f, -1.f)), L"Center (0.0f, 0.0f, -1.0f) should not be inside of AABB<float> (0.0f, 0.0f, 0.0f) to (30.0f, 30.0f, 30.0f)");
			Assert::IsFalse(aabbF.IsInside(Vector3f(31.f, 0.0f, 0.0f)), L"Center (31.0f, 0.0f, 0.0f) should not be inside of AABB<float> (0.0f, 0.0f, 0.0f) to (30.0f, 30.0f, 30.0f)");
			Assert::IsFalse(aabbF.IsInside(Vector3f(0.0f, 31.f, 0.0f)), L"Center (0.0f, 31.0f, 0.0f) should not be inside of AABB<float> (0.0f, 0.0f, 0.0f) to (30.0f, 30.0f, 30.0f)");
			Assert::IsFalse(aabbF.IsInside(Vector3f(0.0f, 0.0f, 31.f)), L"Center (0.0f, 0.0f, 31.0f) should not be inside of AABB<float> (0.0f, 0.0f, 0.0f) to (30.0f, 30.0f, 30.0f)");

			// Checking the AABB3D<double> IsInside() function.
			AABB3Dd aabbD(Vector3d(0.0, 0.0, 0.0), Vector3d(30.0, 30.0, 30.0));

			Assert::IsTrue(aabbD.IsInside(Vector3d(15.f, 15.f, 15.f)), L"Center (15.0, 15.0, 15.0) should be inside of AABB<double> (0.0, 0.0, 0.0) to (30.0, 30.0, 30.0)");
			Assert::IsTrue(aabbD.IsInside(Vector3d(0.0, 0.0, 0.0)), L"Corner (0.0, 0.0, 0.0) should be inside of AABB<double> (0.0, 0.0, 0.0) to (30.0, 30.0, 30.0)");
			Assert::IsTrue(aabbD.IsInside(Vector3d(0.0, 0.0, 30.0)), L"Corner (0.0, 0.0, 30.0) should be inside of AABB<double> (0.0, 0.0, 0.0) to (30.0, 30.0, 30.0)");
			Assert::IsTrue(aabbD.IsInside(Vector3d(0.0, 30.0, 30.0)), L"Corner (0.0, 30.0, 30.0) should be inside of AABB<double> (0.0, 0.0, 0.0) to (30.0, 30.0, 30.0)");
			Assert::IsTrue(aabbD.IsInside(Vector3d(0.0, 30.0, 0.0)), L"Corner (0.0, 30.0, 0.0) should be inside of AABB<double> (0.0, 0.0, 0.0) to (30.0, 30.0, 30.0)");
			Assert::IsTrue(aabbD.IsInside(Vector3d(30.0, 0.0, 0.0)), L"Corner (30.0, 0.0, 0.0) should be inside of AABB<double> (0.0, 0.0, 0.0) to (30.0, 30.0, 30.0)");
			Assert::IsTrue(aabbD.IsInside(Vector3d(30.0, 0.0, 30.0)), L"Corner (30.0, 0.0, 30.0) should be inside of AABB<double> (0.0, 0.0, 0.0) to (30.0, 30.0, 30.0)");
			Assert::IsTrue(aabbD.IsInside(Vector3d(30.0, 30.0, 30.0)), L"Corner (30.0, 30.0, 30.0) should be inside of AABB<double> (0.0, 0.0, 0.0) to (30.0, 30.0, 30.0)");
			Assert::IsTrue(aabbD.IsInside(Vector3d(30.0, 30.0, 0.0)), L"Corner (30.0, 30.0, 0.0) should be inside of AABB<double> (0.0, 0.0, 0.0) to (30.0, 30.0, 30.0)");

			Assert::IsFalse(aabbD.IsInside(Vector3d(-1.f, 0.0, 0.0)), L"Center (-1.0, 0.0, 0.0) should not be inside of AABB<double> (0.0, 0.0, 0.0) to (30.0, 30.0, 30.0)");
			Assert::IsFalse(aabbD.IsInside(Vector3d(0.0, -1.f, 0.0)), L"Center (0.0, -1.0, 0.0) should not be inside of AABB<double> (0.0, 0.0, 0.0) to (30.0, 30.0, 30.0)");
			Assert::IsFalse(aabbD.IsInside(Vector3d(0.0, 0.0, -1.f)), L"Center (0.0, 0.0, -1.0) should not be inside of AABB<double> (0.0, 0.0, 0.0) to (30.0, 30.0, 30.0)");
			Assert::IsFalse(aabbD.IsInside(Vector3d(31.f, 0.0, 0.0)), L"Center (31.0, 0.0, 0.0) should not be inside of AABB<double> (0.0, 0.0, 0.0) to (30.0, 30.0, 30.0)");
			Assert::IsFalse(aabbD.IsInside(Vector3d(0.0, 31.f, 0.0)), L"Center (0.0, 31.0, 0.0) should not be inside of AABB<double> (0.0, 0.0, 0.0) to (30.0, 30.0, 30.0)");
			Assert::IsFalse(aabbD.IsInside(Vector3d(0.0, 0.0, 31.f)), L"Center (0.0, 0.0, 31.0) should not be inside of AABB<double> (0.0, 0.0, 0.0) to (30.0, 30.0, 30.0)");
		}
	};
}