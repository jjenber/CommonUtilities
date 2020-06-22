#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include <Shapes/Intersection.h>

namespace CU = CommonUtilities;

using Vector3f = CommonUtilities::Vector3<float>;
using Vector3d = CommonUtilities::Vector3<double>;
using Spheref = CommonUtilities::Sphere<float>;
using Sphered = CommonUtilities::Sphere<double>;
using AABB3Df = CommonUtilities::AABB3D<float>;
using AABB3Dd = CommonUtilities::AABB3D<double>;
using Rayf = CommonUtilities::Ray<float>;
using Rayd = CommonUtilities::Ray<double>;
using Planef = CommonUtilities::Plane<float>;
using Planed = CommonUtilities::Plane<double>;

#define IntersectionPlaneRay IntersectionPlaneRay
#define IntersectionAABBRay IntersectionAABBRay
#define IntersectionSphereRay IntersectionSphereRay



namespace Assignment9Intersections
{		
	TEST_CLASS(IntersectionTests)
	{
	public:
		
		TEST_METHOD(PlaneRay)
		{
			// Testing Plane<float> vs Ray<float> intersection.
			Planef xyPlaneF(Vector3f(0.0f, 0.0f, 5.0f), Vector3f(0.0f, 0.0f, 1.0f));
			Planef xzPlaneF(Vector3f(0.0f, 5.0f, 0.0f), Vector3f(0.0f, 1.0f, 0.0f));
			Planef yzPlaneF(Vector3f(5.0f, 0.0f, 0.0f), Vector3f(1.0f, 0.0f, 0.0f));

			Rayf xRay1F(Vector3f(0.0f, 0.0f, 5.0f), Vector3f(1.0f, 0.0f, 0.0f));
			Rayf xRay2F(Vector3f(0.0f, 5.0f, 0.0f), Vector3f(1.0f, 0.0f, 0.0f));
			Rayf yRay1F(Vector3f(0.0f, 0.0f, 5.0f), Vector3f(0.0f, 1.0f, 0.0f));
			Rayf yRay2F(Vector3f(5.0f, 0.0f, 0.0f), Vector3f(0.0f, 1.0f, 0.0f));
			Rayf zRay1F(Vector3f(0.0f, 5.0f, 0.0f), Vector3f(0.0f, 0.0f, 1.0f));
			Rayf zRay2F(Vector3f(5.0f, 0.0f, 0.0f), Vector3f(0.0f, 0.0f, 1.0f));

			Vector3f outPointF;

			// Test xy-plane.
			Assert::IsFalse(CU::IntersectionPlaneRay(xyPlaneF, xRay2F, outPointF), L"xy-plane at z=5 should not be intersected by Ray<float> parallell to x going through (0, 5, 0.0f).");
			Assert::IsFalse(CU::IntersectionPlaneRay(xyPlaneF, yRay2F, outPointF), L"xy-plane at z=5 should be intersected by Ray<float> parallell to y going through (5, 0, 0.0f).");
			Assert::IsTrue(CU::IntersectionPlaneRay(xyPlaneF, zRay1F, outPointF), L"xy-plane at z=5 should be intersected by Ray<float> parallell to z going through (0, 5, 0.0f).");
			Assert::IsTrue(CU::IntersectionPlaneRay(xyPlaneF, zRay2F, outPointF), L"xy-plane at z=5 should be intersected by Ray<float> parallell to z going through (5, 0, 0.0f).");

			// Test xz-plane.
			Assert::IsFalse(CU::IntersectionPlaneRay(xzPlaneF, xRay1F, outPointF), L"xz-plane at y=5 should not be intersected by Ray<float> parallell to x going through (0, 0, 5)");
			Assert::IsTrue(CU::IntersectionPlaneRay(xzPlaneF, yRay1F, outPointF), L"xz-plane at y=5 should be intersected by Ray<float> parallell to y going through (0, 0, 5).");
			Assert::IsTrue(CU::IntersectionPlaneRay(xzPlaneF, yRay2F, outPointF), L"xz-plane at y=5 should be intersected by Ray<float> parallell to y going through (5, 0, 0.0f).");
			Assert::IsFalse(CU::IntersectionPlaneRay(xzPlaneF, zRay2F, outPointF), L"xz-plane at y=5 should not be intersected by Ray<float> parallell to z going through (5, 0, 0.0f).");

			// Test yz-plane.
			Assert::IsTrue(CU::IntersectionPlaneRay(yzPlaneF, xRay1F, outPointF), L"yz-plane at x=5 should be intersected by Ray<float> parallell to x going through (0, 0, 5)");
			Assert::IsTrue(CU::IntersectionPlaneRay(yzPlaneF, xRay2F, outPointF), L"yz-plane at x=5 should be intersected by Ray<float> parallell to x going through (0, 5, 0.0f).");
			Assert::IsFalse(CU::IntersectionPlaneRay(yzPlaneF, yRay1F, outPointF), L"yz-plane at x=5 should be intersected by Ray<float> parallell to y going through (0, 0, 5).");
			Assert::IsFalse(CU::IntersectionPlaneRay(yzPlaneF, zRay1F, outPointF), L"yz-plane at x=5 should be intersected by Ray<float> parallell to z going through (0, 5, 0.0f).");

			// Test for Ray<float> inside planes.
			Assert::IsTrue(CU::IntersectionPlaneRay(xyPlaneF, xRay1F, outPointF), L"xy-plane at z=5 should be intersected by Ray<float> parallell to x going through (0, 0, 5) - the Ray<float> is _in_ the plane");
			Assert::IsTrue(CU::IntersectionPlaneRay(xyPlaneF, yRay1F, outPointF), L"xy-plane at z=5 should be intersected by Ray<float> parallell to y going through (0, 0, 5) - the Ray<float> is _in_ the plane");
			Assert::IsTrue(CU::IntersectionPlaneRay(xzPlaneF, xRay2F, outPointF), L"xz-plane at y=5 should be intersected by Ray<float> parallell to x going through (0, 5, 0.0f) - the Ray<float> is _in_ the plane");
			Assert::IsTrue(CU::IntersectionPlaneRay(xzPlaneF, zRay1F, outPointF), L"xz-plane at y=5 should be intersected by Ray<float> parallell to z going through (0, 5, 0.0f) - the Ray<float> is _in_ the plane");
			Assert::IsTrue(CU::IntersectionPlaneRay(yzPlaneF, yRay2F, outPointF), L"yz-plane at x=5 should not be intersected by Ray<float> parallell to y going through (5, 0, 0.0f) - the Ray<float> is _in_ the plane");
			Assert::IsTrue(CU::IntersectionPlaneRay(yzPlaneF, zRay2F, outPointF), L"yz-plane at x=5 should not be intersected by Ray<float> parallell to z going through (5, 0, 0.0f) - the Ray<float> is _in_ the plane");

			// Testing Plane<double> vs Ray<double> intersection.
			Planed xyPlaneD(Vector3d(0.0, 0.0, 5.0), Vector3d(0.0, 0.0, 1.0));
			Planed xzPlaneD(Vector3d(0.0, 5.0, 0.0), Vector3d(0.0, 1.0, 0.0));
			Planed yzPlaneD(Vector3d(5.0, 0.0, 0.0), Vector3d(1.0, 0.0, 0.0));

			Rayd xRay1D(Vector3d(0.0, 0.0, 5.0), Vector3d(1.0, 0.0, 0.0));
			Rayd xRay2D(Vector3d(0.0, 5.0, 0.0), Vector3d(1.0, 0.0, 0.0));
			Rayd yRay1D(Vector3d(0.0, 0.0, 5.0), Vector3d(0.0, 1.0, 0.0));
			Rayd yRay2D(Vector3d(5.0, 0.0, 0.0), Vector3d(0.0, 1.0, 0.0));
			Rayd zRay1D(Vector3d(0.0, 5.0, 0.0), Vector3d(0.0, 0.0, 1.0));
			Rayd zRay2D(Vector3d(5.0, 0.0, 0.0), Vector3d(0.0, 0.0, 1.0));

			Vector3d outPointD;

			// Test xy-plane.
			Assert::IsFalse(CU::IntersectionPlaneRay(xyPlaneD, xRay2D, outPointD), L"xy-plane at z=5 should not be intersected by Ray<double> parallell to x going through (0.0, 5.0, 0.0).");
			Assert::IsFalse(CU::IntersectionPlaneRay(xyPlaneD, yRay2D, outPointD), L"xy-plane at z=5 should be intersected by Ray<double> parallell to y going through (5.0, 0.0, 0.0).");
			Assert::IsTrue(CU::IntersectionPlaneRay(xyPlaneD, zRay1D, outPointD), L"xy-plane at z=5 should be intersected by Ray<double> parallell to z going through (0.0, 5.0, 0.0).");
			Assert::IsTrue(CU::IntersectionPlaneRay(xyPlaneD, zRay2D, outPointD), L"xy-plane at z=5 should be intersected by Ray<double> parallell to z going through (5.0, 0.0, 0.0).");

			// Test xz-plane.
			Assert::IsFalse(CU::IntersectionPlaneRay(xzPlaneD, xRay1D, outPointD), L"xz-plane at y=5 should not be intersected by Ray<double> parallell to x going through (0.0, 0.0, 5.0)");
			Assert::IsTrue(CU::IntersectionPlaneRay(xzPlaneD, yRay1D, outPointD), L"xz-plane at y=5 should be intersected by Ray<double> parallell to y going through (0.0, 0.0, 5.0).");
			Assert::IsTrue(CU::IntersectionPlaneRay(xzPlaneD, yRay2D, outPointD), L"xz-plane at y=5 should be intersected by Ray<double> parallell to y going through (5.0, 0.0, 0.0).");
			Assert::IsFalse(CU::IntersectionPlaneRay(xzPlaneD, zRay2D, outPointD), L"xz-plane at y=5 should not be intersected by Ray<double> parallell to z going through (5.0, 0.0, 0.0).");

			// Test yz-plane.
			Assert::IsTrue(CU::IntersectionPlaneRay(yzPlaneD, xRay1D, outPointD), L"yz-plane at x=5 should be intersected by Ray<double> parallell to x going through (0.0, 0.0, 5.0)");
			Assert::IsTrue(CU::IntersectionPlaneRay(yzPlaneD, xRay2D, outPointD), L"yz-plane at x=5 should be intersected by Ray<double> parallell to x going through (0.0, 5.0, 0.0).");
			Assert::IsFalse(CU::IntersectionPlaneRay(yzPlaneD, yRay1D, outPointD), L"yz-plane at x=5 should be intersected by Ray<double> parallell to y going through (0.0, 0.0, 5.0).");
			Assert::IsFalse(CU::IntersectionPlaneRay(yzPlaneD, zRay1D, outPointD), L"yz-plane at x=5 should be intersected by Ray<double> parallell to z going through (0.0, 5.0, 0.0).");

			// Test for Ray<double> inside planes.
			Assert::IsTrue(CU::IntersectionPlaneRay(xyPlaneD, xRay1D, outPointD), L"xy-plane at z=5 should be intersected by Ray<double> parallell to x going through (0.0, 0.0, 5.0) - the Ray<double> is _in_ the plane");
			Assert::IsTrue(CU::IntersectionPlaneRay(xyPlaneD, yRay1D, outPointD), L"xy-plane at z=5 should be intersected by Ray<double> parallell to y going through (0.0, 0.0, 5.0) - the Ray<double> is _in_ the plane");
			Assert::IsTrue(CU::IntersectionPlaneRay(xzPlaneD, xRay2D, outPointD), L"xz-plane at y=5 should be intersected by Ray<double> parallell to x going through (0.0, 5.0, 0.0) - the Ray<double> is _in_ the plane");
			Assert::IsTrue(CU::IntersectionPlaneRay(xzPlaneD, zRay1D, outPointD), L"xz-plane at y=5 should be intersected by Ray<double> parallell to z going through (0.0, 5.0, 0.0) - the Ray<double> is _in_ the plane");
			Assert::IsTrue(CU::IntersectionPlaneRay(yzPlaneD, yRay2D, outPointD), L"yz-plane at x=5 should not be intersected by Ray<double> parallell to y going through (5.0, 0.0, 0.0) - the Ray<double> is _in_ the plane");
			Assert::IsTrue(CU::IntersectionPlaneRay(yzPlaneD, zRay2D, outPointD), L"yz-plane at x=5 should not be intersected by Ray<double> parallell to z going through (5.0, 0.0, 0.0) - the Ray<double> is _in_ the plane");
		}

		TEST_METHOD(AABBRay)
		{
			// Testing AABB3D<float> vs Ray<float> intersection.
			AABB3Df aabbF(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(30.0f, 30.0f, 30.0f));

			Rayf xRayLeftOutF;
			xRayLeftOutF.InitWithOriginAndDirection(Vector3f(15.0f, 15.0f, 31.0f), Vector3f(1.0f, 0.0f, 0.0f));
			Rayf xRayLeftFTestNeg;
			xRayLeftFTestNeg.InitWithOriginAndDirection(Vector3f(-15.0f, 15.0f, 30.0f), Vector3f(1.0f, 0.0f, 0.0f));
			Rayf xRayLeftFTest;
			xRayLeftFTest.InitWithOriginAndDirection(Vector3f(10.0f, 15.0f, 30.0f), Vector3f(1.0f, 0.0f, 0.0f));
			Rayf xRayMiddleF;
			xRayMiddleF.InitWithOriginAndDirection(Vector3f(15.0f, 15.0f, 15.0f), Vector3f(1.0f, 0.0f, 0.0f));
			Rayf xRayRightF;
			xRayRightF.InitWithOriginAndDirection(Vector3f(15.0f, 15.0f, 0.0f), Vector3f(1.0f, 0.0f, 0.0f));
			Rayf xRayRightOutF;
			xRayRightOutF.InitWithOriginAndDirection(Vector3f(15.0f, 15.0f, -1.0f), Vector3f(1.0f, 0.0f, 0.0f));

			Rayf yRayLeftOutF;
			yRayLeftOutF.InitWithOriginAndDirection(Vector3f(-1.0f, 15.0f, 15.0f), Vector3f(0.0f, 1.0f, 0.0f));
			Rayf yRayLeftF;
			yRayLeftF.InitWithOriginAndDirection(Vector3f(0.0f, 15.0f, 15.0f), Vector3f(0.0f, 1.0f, 0.0f));
			Rayf yRayMiddleF;
			yRayMiddleF.InitWithOriginAndDirection(Vector3f(15.0f, 15.0f, 15.0f), Vector3f(0.0f, 1.0f, 0.0f));
			Rayf yRayRightF;
			yRayRightF.InitWithOriginAndDirection(Vector3f(30.0f, 15.0f, 15.0f), Vector3f(0.0f, 1.0f, 0.0f));
			Rayf yRayRightOutF;
			yRayRightOutF.InitWithOriginAndDirection(Vector3f(31.0f, 15.0f, 15.0f), Vector3f(0.0f, 1.0f, 0.0f));

			Rayf zRayLeftOutF;
			zRayLeftOutF.InitWithOriginAndDirection(Vector3f(-1.0f, 15.0f, 15.0f), Vector3f(0.0f, 0.0f, 1.0f));
			Rayf zRayLeftF;
			zRayLeftF.InitWithOriginAndDirection(Vector3f(0.0f, 15.0f, 15.0f), Vector3f(0.0f, 0.0f, 1.0f));
			Rayf zRayMiddleF;
			zRayMiddleF.InitWithOriginAndDirection(Vector3f(15.0f, 15.0f, 15.0f), Vector3f(0.0f, 0.0f, 1.0f));
			Rayf zRayRightF;
			zRayRightF.InitWithOriginAndDirection(Vector3f(30.0f, 15.0f, 15.0f), Vector3f(0.0f, 0.0f, 1.0f));
			Rayf zRayRightOutF;
			zRayRightOutF.InitWithOriginAndDirection(Vector3f(31.0f, 15.0f, 15.0f), Vector3f(0.0f, 0.0f, 1.0f));

			Assert::IsTrue(CU::IntersectionAABBRay(aabbF, xRayLeftFTestNeg), L"Ray<float> parallell to x going through point (15.0f, 15.0f, 30.0f) should intersect AABB3D<float>(0.0f, 0.0f, 0.0f) to (30.0f, 30.0f, 30.0f)");
			Assert::IsTrue(CU::IntersectionAABBRay(aabbF, xRayLeftFTest), L"Ray<float> parallell to x going through point (15.0f, 15.0f, 30.0f) should intersect AABB3D<float>(0.0f, 0.0f, 0.0f) to (30.0f, 30.0f, 30.0f)");
			
			Assert::IsFalse(CU::IntersectionAABBRay(aabbF, xRayLeftOutF), L"Ray<float> parallell to x going through point (15.0f, 15.0f, 31.0f) should not intersect AABB3D<float>(0.0f, 0.0f, 0.0f) to (30.0f, 30.0f, 30.0f)");
			Assert::IsTrue(CU::IntersectionAABBRay(aabbF, xRayMiddleF), L"Ray<float> parallell to x going through point (15.0f, 15.0f, 15.0f) should intersect AABB3D<float>(0.0f, 0.0f, 0.0f) to (30.0f, 30.0f, 30.0f)");
			Assert::IsTrue(CU::IntersectionAABBRay(aabbF, xRayRightF), L"Ray<float> parallell to x going through point (15.0f, 15.0f, 0.0f) should intersect AABB3D<float>(0.0f, 0.0f, 0.0f) to (30.0f, 30.0f, 30.0f)");
			Assert::IsFalse(CU::IntersectionAABBRay(aabbF, xRayRightOutF), L"Ray<float> parallell to x going through point (15.0f, 15.0f, -1.0f) should not intersect AABB3D<float>(0.0f, 0.0f, 0.0f) to (30.0f, 30.0f, 30.0f)");

			Assert::IsFalse(CU::IntersectionAABBRay(aabbF, yRayLeftOutF), L"Ray<float> parallell to y going through point (31.0f, 15.0f, 15.0f) should not intersect AABB3D<float>(0.0f, 0.0f, 0.0f) to (30.0f, 30.0f, 30.0f)");
			Assert::IsTrue(CU::IntersectionAABBRay(aabbF, yRayLeftF), L"Ray<float> parallell to y going through point (30.0f, 15.0f, 15.0f) should intersect AABB3D<float>(0.0f, 0.0f, 0.0f) to (30.0f, 30.0f, 30.0f)");
			Assert::IsTrue(CU::IntersectionAABBRay(aabbF, yRayMiddleF), L"Ray<float> parallell to y going through point (15.0f, 15.0f, 15.0f) should intersect AABB3D<float>(0.0f, 0.0f, 0.0f) to (30.0f, 30.0f, 30.0f)");
			Assert::IsTrue(CU::IntersectionAABBRay(aabbF, yRayRightF), L"Ray<float> parallell to y going through point (0.0f, 15.0f, 15.0f) should intersect AABB3D<float>(0.0f, 0.0f, 0.0f) to (30.0f, 30.0f, 30.0f)");
			Assert::IsFalse(CU::IntersectionAABBRay(aabbF, yRayRightOutF), L"Ray<float> parallell to y going through point (-1.0f, 15.0f, 15.0f) should not intersect AABB3D<float>(0.0f, 0.0f, 0.0f) to (30.0f, 30.0f, 30.0f)");

			Assert::IsFalse(CU::IntersectionAABBRay(aabbF, zRayLeftOutF), L"Ray<float> parallell to z going through point (31.0f, 15.0f, 15.0f) should not intersect AABB3D<float>(0.0f, 0.0f, 0.0f) to (30.0f, 30.0f, 30.0f)");
			Assert::IsTrue(CU::IntersectionAABBRay(aabbF, zRayLeftF), L"Ray<float> parallell to z going through point (30.0f, 15.0f, 15.0f) should intersect AABB3D<float>(0.0f, 0.0f, 0.0f) to (30.0f, 30.0f, 30.0f)");
			Assert::IsTrue(CU::IntersectionAABBRay(aabbF, zRayMiddleF), L"Ray<float> parallell to z going through point (15.0f, 15.0f, 15.0f) should intersect AABB3D<float>(0.0f, 0.0f, 0.0f) to (30.0f, 30.0f, 30.0f)");
			Assert::IsTrue(CU::IntersectionAABBRay(aabbF, zRayRightF), L"Ray<float> parallell to z going through point (0.0f, 15.0f, 15.0f) should intersect AABB3D<float>(0.0f, 0.0f, 0.0f) to (30.0f, 30.0f, 30.0f)");
			Assert::IsFalse(CU::IntersectionAABBRay(aabbF, zRayRightOutF), L"Ray<float> parallell to z going through point (-1.0f, 15.0f, 15.0f) should not intersect AABB3D<float>(0.0f, 0.0f, 0.0f) to (30.0f, 30.0f, 30.0f)");

			// Testing AABB3D<double> vs Ray<double> intersection.
			AABB3Dd aabbD(Vector3d(0.0, 0.0, 0.0), Vector3d(30.0, 30.0, 30.0));

			Rayd xRayLeftOutD;
			xRayLeftOutD.InitWithOriginAndDirection(Vector3d(15.0, 15.0, 31.0), Vector3d(1.0, 0.0, 0.0));

			Rayd xRayLeftD;
			xRayLeftD.InitWithOriginAndDirection(Vector3d(15.0, 15.0, 30.0), Vector3d(1.0, 0.0, 0.0));

			Rayd xRayMiddleD;
			xRayMiddleD.InitWithOriginAndDirection(Vector3d(15.0, 15.0, 15.0), Vector3d(1.0, 0.0, 0.0));

			Rayd xRayRightD;
			xRayRightD.InitWithOriginAndDirection(Vector3d(15.0, 15.0, 0.0), Vector3d(1.0, 0.0, 0.0));

			Rayd xRayRightOutD;
			xRayRightOutD.InitWithOriginAndDirection(Vector3d(15.0, 15.0, -1.0), Vector3d(1.0, 0.0, 0.0));

			Rayd yRayLeftOutD;
			yRayLeftOutD.InitWithOriginAndDirection(Vector3d(-1.0, 15.0, 15.0), Vector3d(0.0, 1.0, 0.0));

			Rayd yRayLeftD;
			yRayLeftD.InitWithOriginAndDirection(Vector3d(0.0, 15.0, 15.0), Vector3d(0.0, 1.0, 0.0));

			Rayd yRayMiddleD;
			yRayMiddleD.InitWithOriginAndDirection(Vector3d(15.0, 15.0, 15.0), Vector3d(0.0, 1.0, 0.0));

			Rayd yRayRightD;
			yRayRightD.InitWithOriginAndDirection(Vector3d(30.0, 15.0, 15.0), Vector3d(0.0, 1.0, 0.0));

			Rayd yRayRightOutD;
			yRayRightOutD.InitWithOriginAndDirection(Vector3d(31.0, 15.0, 15.0), Vector3d(0.0, 1.0, 0.0));

			Rayd zRayLeftOutD;
			zRayLeftOutD.InitWithOriginAndDirection(Vector3d(-1.0, 15.0, 15.0), Vector3d(0.0, 0.0, 1.0));

			Rayd zRayLeftD;
			zRayLeftD.InitWithOriginAndDirection(Vector3d(0.0, 15.0, 15.0), Vector3d(0.0, 0.0, 1.0));

			Rayd zRayMiddleD;
			zRayMiddleD.InitWithOriginAndDirection(Vector3d(15.0, 15.0, 15.0), Vector3d(0.0, 0.0, 1.0));

			Rayd zRayRightD;
			zRayRightD.InitWithOriginAndDirection(Vector3d(30.0, 15.0, 15.0), Vector3d(0.0, 0.0, 1.0));

			Rayd zRayRightOutD;
			zRayRightOutD.InitWithOriginAndDirection(Vector3d(31.0, 15.0, 15.0), Vector3d(0.0, 0.0, 1.0));

			Assert::IsFalse(CU::IntersectionAABBRay(aabbD, xRayLeftOutD), L"Ray<double> parallell to x going through point (15.0, 15.0, 31.0) should not intersect AABB3D<double>(0.0, 0.0, 0.0) to (30.0, 30.0, 30.0)");
			Assert::IsTrue(CU::IntersectionAABBRay(aabbD, xRayLeftD), L"Ray<double> parallell to x going through point (15.0, 15.0, 30.0) should intersect AABB3D<double>(0.0, 0.0, 0.0) to (30.0, 30.0, 30.0)");
			Assert::IsTrue(CU::IntersectionAABBRay(aabbD, xRayMiddleD), L"Ray<double> parallell to x going through point (15.0, 15.0, 15.0) should intersect AABB3D<double>(0.0, 0.0, 0.0) to (30.0, 30.0, 30.0)");
			Assert::IsTrue(CU::IntersectionAABBRay(aabbD, xRayRightD), L"Ray<double> parallell to x going through point (15.0, 15.0, 0.0) should intersect AABB3D<double>(0.0, 0.0, 0.0) to (30.0, 30.0, 30.0)");
			Assert::IsFalse(CU::IntersectionAABBRay(aabbD, xRayRightOutD), L"Ray<double> parallell to x going through point (15.0, 15.0, -1.0) should not intersect AABB3D<double>(0.0, 0.0, 0.0) to (30.0, 30.0, 30.0)");

			Assert::IsFalse(CU::IntersectionAABBRay(aabbD, yRayLeftOutD), L"Ray<double> parallell to y going through point (31.0, 15.0, 15.0) should not intersect AABB3D<double>(0.0, 0.0, 0.0) to (30.0, 30.0, 30.0)");
			Assert::IsTrue(CU::IntersectionAABBRay(aabbD, yRayLeftD), L"Ray<double> parallell to y going through point (30.0, 15.0, 15.0) should intersect AABB3D<double>(0.0, 0.0, 0.0) to (30.0, 30.0, 30.0)");
			Assert::IsTrue(CU::IntersectionAABBRay(aabbD, yRayMiddleD), L"Ray<double> parallell to y going through point (15.0, 15.0, 15.0) should intersect AABB3D<double>(0.0, 0.0, 0.0) to (30.0, 30.0, 30.0)");
			Assert::IsTrue(CU::IntersectionAABBRay(aabbD, yRayRightD), L"Ray<double> parallell to y going through point (0.0, 15.0, 15.0) should intersect AABB3D<double>(0.0, 0.0, 0.0) to (30.0, 30.0, 30.0)");
			Assert::IsFalse(CU::IntersectionAABBRay(aabbD, yRayRightOutD), L"Ray<double> parallell to y going through point (-1.0, 15.0, 15.0) should not intersect AABB3D<double>(0.0, 0.0, 0.0) to (30.0, 30.0, 30.0)");

			Assert::IsFalse(CU::IntersectionAABBRay(aabbD, zRayLeftOutD), L"Ray<double> parallell to z going through point (31.0, 15.0, 15.0) should not intersect AABB3D<double>(0.0, 0.0, 0.0) to (30.0, 30.0, 30.0)");
			Assert::IsTrue(CU::IntersectionAABBRay(aabbD, zRayLeftD), L"Ray<double> parallell to z going through point (30.0, 15.0, 15.0) should intersect AABB3D<double>(0.0, 0.0, 0.0) to (30.0, 30.0, 30.0)");
			Assert::IsTrue(CU::IntersectionAABBRay(aabbD, zRayMiddleD), L"Ray<double> parallell to z going through point (15.0, 15.0, 15.0) should intersect AABB3D<double>(0.0, 0.0, 0.0) to (30.0, 30.0, 30.0)");
			Assert::IsTrue(CU::IntersectionAABBRay(aabbD, zRayRightD), L"Ray<double> parallell to z going through point (0.0, 15.0, 15.0) should intersect AABB3D<double>(0.0, 0.0, 0.0) to (30.0, 30.0, 30.0)");
			Assert::IsFalse(CU::IntersectionAABBRay(aabbD, zRayRightOutD), L"Ray<double> parallell to z going through point (-1.0, 15.0, 15.0) should not intersect AABB3D<double>(0.0, 0.0, 0.0) to (30.0, 30.0, 30.0)");
		}

		TEST_METHOD(SphereRay)
		{
			// Testing Sphere<float> vs Ray<float> intersection.
			Spheref sphereF(Vector3f(100.0f, 100.0f, 100.0f), 10.0f);

			Vector3f xDirF(1.0f, 0.0f, 0.0f);
			Vector3f yDirF(0.0f, 1.0f, 0.0f);
			Vector3f zDirF(0.0f, 0.0f, 1.0f);

			Rayf xLeftOutF;
			Rayf xLeftF;
			Rayf xCenterF;
			Rayf xRightF;
			Rayf xRightOutF;

			xLeftOutF.InitWithOriginAndDirection(Vector3f(0.0f, 89.0f, 100.0f), xDirF);
			xLeftF.InitWithOriginAndDirection(Vector3f(0.0f, 90.0f, 100.0f), xDirF);
			xCenterF.InitWithOriginAndDirection(Vector3f(0.0f, 100.0f, 100.0f), xDirF);
			xRightF.InitWithOriginAndDirection(Vector3f(0.0f, 110.0f, 100.0f), xDirF);
			xRightOutF.InitWithOriginAndDirection(Vector3f(0.0f, 111.0f, 100.0f), xDirF);

			Rayf yLeftOutF;
			Rayf yLeftF;
			Rayf yCenterF;
			Rayf yRightF;
			Rayf yRightOutF;

			yLeftOutF.InitWithOriginAndDirection(Vector3f(89.0f, 0.0f, 100.0f), yDirF);
			yLeftF.InitWithOriginAndDirection(Vector3f(90.0f, 0.0f, 100.0f), yDirF);
			yCenterF.InitWithOriginAndDirection(Vector3f(100.0f, 0.0f, 100.0f), yDirF);
			yRightF.InitWithOriginAndDirection(Vector3f(110.0f, 0.0f, 100.0f), yDirF);
			yRightOutF.InitWithOriginAndDirection(Vector3f(111.0f, 0.0f, 100.0f), yDirF);

			Rayf zLeftOutF;
			Rayf zLeftF;
			Rayf zCenterF;
			Rayf zRightF;
			Rayf zRightOutF;

			zLeftOutF.InitWithOriginAndDirection(Vector3f(89.0f, 100.0f, 00.0f), zDirF);
			zLeftF.InitWithOriginAndDirection(Vector3f(90.0f, 100.0f, 00.0f), zDirF);
			zCenterF.InitWithOriginAndDirection(Vector3f(100.0f, 100.0f, 00.0f), zDirF);
			zRightF.InitWithOriginAndDirection(Vector3f(110.0f, 100.0f, 00.0f), zDirF);
			zRightOutF.InitWithOriginAndDirection(Vector3f(111.0f, 100.0f, 00.0f), zDirF);

			Assert::IsFalse(CU::IntersectionSphereRay(sphereF, xLeftOutF), L"Ray<float> parallell to x going through point (0.0f, 89.0f, 100.0f) should not intersect Sphere<float> at (100.0f, 100.0f, 100.0f) with radius 10.0f.0f.");
			Assert::IsTrue(CU::IntersectionSphereRay(sphereF, xLeftF), L"Ray<float> parallell to x going through point (0.0f, 90.0f, 100.0f) should intersect Sphere<float> at (100.0f, 100.0f, 100.0f) with radius 10.0f.");
			Assert::IsTrue(CU::IntersectionSphereRay(sphereF, xCenterF), L"Ray<float> parallell to x going through point (0.0f, 100.0f, 100.0f) should intersect Sphere<float> at (100.0f, 100.0f, 100.0f) with radius 10.0f.");
			Assert::IsTrue(CU::IntersectionSphereRay(sphereF, xRightF), L"Ray<float> parallell to x going through point (0.0f, 110.0f, 100.0f) should intersect Sphere<float> at (100.0f, 100.0f, 100.0f) with radius 10.0f.");
			Assert::IsFalse(CU::IntersectionSphereRay(sphereF, xRightOutF), L"Ray<float> parallell to x going through point (0.0f, 111.0f, 100.0f) should not intersect Sphere<float> at (100.0f, 100.0f, 100.0f) with radius 10.0f.");

			Assert::IsFalse(CU::IntersectionSphereRay(sphereF, yLeftOutF), L"Ray<float> parallell to y going through point (89.0f, 0.0f, 100.0f) should not intersect Sphere<float> at (100.0f, 100.0f, 100.0f) with radius 10.0f.");
			Assert::IsTrue(CU::IntersectionSphereRay(sphereF, yLeftF), L"Ray<float> parallell to y going through point (90.0f, 0.0f, 100.0f) should intersect Sphere<float> at (100.0f, 100.0f, 100.0f) with radius 10.0f.");
			Assert::IsTrue(CU::IntersectionSphereRay(sphereF, yCenterF), L"Ray<float> parallell to y going through point (100.0f, 0.0f, 100.0f) should intersect Sphere<float> at (100.0f, 100.0f, 100.0f) with radius 10.0f.");
			Assert::IsTrue(CU::IntersectionSphereRay(sphereF, yRightF), L"Ray<float> parallell to y going through point (110.0f, 0.0f, 100.0f) should intersect Sphere<float> at (100.0f, 100.0f, 100.0f) with radius 10.0f.");
			Assert::IsFalse(CU::IntersectionSphereRay(sphereF, yRightOutF), L"Ray<float> parallell to y going through point (111.0f, 0.0f, 100.0f) should not intersect Sphere<float> at (100.0f, 100.0f, 100.0f) with radius 10.0f.");

			Assert::IsFalse(CU::IntersectionSphereRay(sphereF, yLeftOutF), L"Ray<float> parallell to z going through point (89.0f, 100.0f, 0.0f) should not intersect Sphere<float> at (100.0f, 100.0f, 100.0f) with radius 10.0f.");
			Assert::IsTrue(CU::IntersectionSphereRay(sphereF, yLeftF), L"Ray<float> parallell to z going through point (90.0f, 100.0f, 0.0f) should intersect Sphere<float> at (100.0f, 100.0f, 100.0f) with radius 10.0f.");
			Assert::IsTrue(CU::IntersectionSphereRay(sphereF, yCenterF), L"Ray<float> parallell to z going through point (100.0f, 100.0f, 0.0f) should intersect Sphere<float> at (100.0f, 100.0f, 100.0f) with radius 10.0f.");
			Assert::IsTrue(CU::IntersectionSphereRay(sphereF, yRightF), L"Ray<float> parallell to z going through point (110.0f, 100.0f, 0.0f) should intersect Sphere<float> at (100.0f, 100.0f, 100.0f) with radius 10.0f.");
			Assert::IsFalse(CU::IntersectionSphereRay(sphereF, yRightOutF), L"Ray<float> parallell to z going through point (111.0f, 100.0f, 0.0f) should not intersect Sphere<float> at (100.0f, 100.0f, 100.0f) with radius 10.0f.");

			// Testing Sphere<double> vs Ray<double> intersection.
			Sphered sphereD(Vector3d(100.0, 100.0, 100.0), 10.0);

			Vector3d xDirD(1.0, 0.0, 0.0);
			Vector3d yDirD(0.0, 1.0, 0.0);
			Vector3d zDirD(0.0, 0.0, 1.0);

			Rayd xLeftOutD;
			Rayd xLeftD;
			Rayd xCenterD;
			Rayd xRightD;
			Rayd xRightOutD;

			xLeftOutD.InitWithOriginAndDirection(Vector3d(0.0, 89.0, 100.0), xDirD);
			xLeftD.InitWithOriginAndDirection(Vector3d(0.0, 90.0, 100.0), xDirD);
			xCenterD.InitWithOriginAndDirection(Vector3d(0.0, 100.0, 100.0), xDirD);
			xRightD.InitWithOriginAndDirection(Vector3d(0.0, 110.0, 100.0), xDirD);
			xRightOutD.InitWithOriginAndDirection(Vector3d(0.0, 111.0, 100.0), xDirD);

			Rayd yLeftOutD;
			Rayd yLeftD;
			Rayd yCenterD;
			Rayd yRightD;
			Rayd yRightOutD;

			yLeftOutD.InitWithOriginAndDirection(Vector3d(89.0, 0.0, 100.0), yDirD);
			yLeftD.InitWithOriginAndDirection(Vector3d(90.0, 0.0, 100.0), yDirD);
			yCenterD.InitWithOriginAndDirection(Vector3d(100.0, 0.0, 100.0), yDirD);
			yRightD.InitWithOriginAndDirection(Vector3d(110.0, 0.0, 100.0), yDirD);
			yRightOutD.InitWithOriginAndDirection(Vector3d(111.0, 0.0, 100.0), yDirD);

			Rayd zLeftOutD;
			Rayd zLeftD;
			Rayd zCenterD;
			Rayd zRightD;
			Rayd zRightOutD;

			zLeftOutD.InitWithOriginAndDirection(Vector3d(89.0, 100.0, 00.0), zDirD);
			zLeftD.InitWithOriginAndDirection(Vector3d(90.0, 100.0, 00.0), zDirD);
			zCenterD.InitWithOriginAndDirection(Vector3d(100.0, 100.0, 00.0), zDirD);
			zRightD.InitWithOriginAndDirection(Vector3d(110.0, 100.0, 00.0), zDirD);
			zRightOutD.InitWithOriginAndDirection(Vector3d(111.0, 100.0, 00.0), zDirD);

			Assert::IsFalse(CU::IntersectionSphereRay(sphereD, xLeftOutD), L"Ray<double> parallell to x going through point (0.0, 89.0, 100.0) should not intersect Sphere<double> at (100.0, 100.0, 100.0) with radius 10.0.0.");
			Assert::IsTrue(CU::IntersectionSphereRay(sphereD, xLeftD), L"Ray<double> parallell to x going through point (0.0, 90.0, 100.0) should intersect Sphere<double> at (100.0, 100.0, 100.0) with radius 10.0.");
			Assert::IsTrue(CU::IntersectionSphereRay(sphereD, xCenterD), L"Ray<double> parallell to x going through point (0.0, 100.0, 100.0) should intersect Sphere<double> at (100.0, 100.0, 100.0) with radius 10.0.");
			Assert::IsTrue(CU::IntersectionSphereRay(sphereD, xRightD), L"Ray<double> parallell to x going through point (0.0, 110.0, 100.0) should intersect Sphere<double> at (100.0, 100.0, 100.0) with radius 10.0.");
			Assert::IsFalse(CU::IntersectionSphereRay(sphereD, xRightOutD), L"Ray<double> parallell to x going through point (0.0, 111.0, 100.0) should not intersect Sphere<double> at (100.0, 100.0, 100.0) with radius 10.0.");

			Assert::IsFalse(CU::IntersectionSphereRay(sphereD, yLeftOutD), L"Ray<double> parallell to y going through point (89.0, 0.0, 100.0) should not intersect Sphere<double> at (100.0, 100.0, 100.0) with radius 10.0.");
			Assert::IsTrue(CU::IntersectionSphereRay(sphereD, yLeftD), L"Ray<double> parallell to y going through point (90.0, 0.0, 100.0) should intersect Sphere<double> at (100.0, 100.0, 100.0) with radius 10.0.");
			Assert::IsTrue(CU::IntersectionSphereRay(sphereD, yCenterD), L"Ray<double> parallell to y going through point (100.0, 0.0, 100.0) should intersect Sphere<double> at (100.0, 100.0, 100.0) with radius 10.0.");
			Assert::IsTrue(CU::IntersectionSphereRay(sphereD, yRightD), L"Ray<double> parallell to y going through point (110.0, 0.0, 100.0) should intersect Sphere<double> at (100.0, 100.0, 100.0) with radius 10.0.");
			Assert::IsFalse(CU::IntersectionSphereRay(sphereD, yRightOutD), L"Ray<double> parallell to y going through point (111.0, 0.0, 100.0) should not intersect Sphere<double> at (100.0, 100.0, 100.0) with radius 10.0.");

			Assert::IsFalse(CU::IntersectionSphereRay(sphereD, yLeftOutD), L"Ray<double> parallell to z going through point (89.0, 100.0, 0.0) should not intersect Sphere<double> at (100.0, 100.0, 100.0) with radius 10.0.");
			Assert::IsTrue(CU::IntersectionSphereRay(sphereD, yLeftD), L"Ray<double> parallell to z going through point (90.0, 100.0, 0.0) should intersect Sphere<double> at (100.0, 100.0, 100.0) with radius 10.0.");
			Assert::IsTrue(CU::IntersectionSphereRay(sphereD, yCenterD), L"Ray<double> parallell to z going through point (100.0, 100.0, 0.0) should intersect Sphere<double> at (100.0, 100.0, 100.0) with radius 10.0.");
			Assert::IsTrue(CU::IntersectionSphereRay(sphereD, yRightD), L"Ray<double> parallell to z going through point (110.0, 100.0, 0.0) should intersect Sphere<double> at (100.0, 100.0, 100.0) with radius 10.0.");
			Assert::IsFalse(CU::IntersectionSphereRay(sphereD, yRightOutD), L"Ray<double> parallell to z going through point (111.0f, 100.0f, 0.0f) should not intersect Sphere<double> at (100.0f, 100.0f, 100.0f) with radius 10.0f.");
		}
	};
}