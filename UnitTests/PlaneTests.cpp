#include "pch.h"
#include "CppUnitTest.h"
#include "..//CommonUtilities/Plane.h"
#include "..//CommonUtilities/PlaneVolume.h"
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace CommonUtilities;

namespace PlanesTests
{
	TEST_CLASS(Planes)
	{
		TEST_METHOD(CopyConstructor)
		{
			Vector3<float> point0 = { 1.2f, 0, 0 };
			Vector3<float> point1 = { 0.2f, -1.f, 0 };
			Vector3<float> point2 = { 0.3f, 0.4f, 0 };
			Plane<float> plane(point0, point1, point2);
			Plane<float> copy = plane;

			Assert::AreEqual(plane.GetNormal().x, copy.GetNormal().x);
			Assert::AreEqual(plane.GetNormal().y, copy.GetNormal().y);
			Assert::AreEqual(plane.GetNormal().z, copy.GetNormal().z);
		}
		TEST_METHOD(ConstructorWithNormal)
		{
			Vector3<float> point0 = { 1.2f, 0.f, 3.f };
			Vector3<float> point1 = { 2.2f, 0.f, 2.4f };
			Vector3<float> point2 = { 3.2f, 0.f, 10.f };

			Plane<float> explicitPlane(point0, { 0, -1.f, 0 });
			Plane<float> implicitPlane(point0, point1, point2);
			
			Assert::AreEqual(explicitPlane.GetNormal().x, implicitPlane.GetNormal().x);
			Assert::AreEqual(explicitPlane.GetNormal().y, implicitPlane.GetNormal().y);
			Assert::AreEqual(explicitPlane.GetNormal().z, implicitPlane.GetNormal().z);
		}

		TEST_METHOD(InitWith3Points)
		{
			Vector3<float> point = { 3.f, 0.f, 1.f };

			Plane<float> explicitPlane(point, { 0, -1.f, 0 });
		}
	};

	TEST_CLASS(PlaneVolumes)
	{
		TEST_METHOD(IsInside)
		{
			Vector3<float> point0{ -1.f, 1.f, 0.f };
			Vector3<float> point1{ 1.f, 1.f, 2.f };
			Vector3<float> point2{ -1.f, 1.f, -2.f };

			Vector3<float> point3{ -1.f, -1.f, 0.f };
			Vector3<float> point4{ 1.f, -1.f, 2.f };
			Vector3<float> point5{ -1.f, -1.f, -2.f };

			Plane<float> plane0(point0, point1, point2);
			Plane<float> plane1(point5, point4, point3);

			PlaneVolume<float> pv;
			pv.AddPlane(plane0);
			pv.AddPlane(plane1);

			Assert::IsTrue(pv.IsInside({ 0.f, 0.f, 0.f }));
			Assert::IsFalse(pv.IsInside({ 0.f, 10.f, 0.f }));
		}
	};
}