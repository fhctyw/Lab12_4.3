#include "pch.h"
#include "CppUnitTest.h"
#include "..\Lab12_4.3\main.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Friend* f;
			size_t cnt;
			get_from_file("C:\\Users\\Arsen\\Desktop\\Arsen\\2 семестр\\ПКР\\Лаби\\Lab12_4.3\\Lab12_4.3\\t", f, cnt);
			Assert::AreEqual((size_t)3, cnt);
		}
	};
}
