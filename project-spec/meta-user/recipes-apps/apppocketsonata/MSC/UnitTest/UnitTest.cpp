#include "pch.h"
#include "CppUnitTest.h"



#include "../../files/Utils/ccommonutils.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
            //TODO: 
            //date 	2023-05-23 16:36:21
            Assert::AreEqual( 3, CheckMultiplyOverflow( 1, 3 ) );
            
		}
	};
}
