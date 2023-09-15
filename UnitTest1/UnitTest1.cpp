#include "pch.h"
#include "CppUnitTest.h"
#include"../Thesis/Chesis.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			ChesisCheck chesischeck;
			string s1 = "adh";
			string s2 = "Dhg";
			wstring t1 = chesischeck.TransUTF8toUnicode(s1);
			wstring t2 = chesischeck.TransUTF8toUnicode(s2);
			auto len1 = t1.size();
			auto len2 = t2.size();
			float f = chesischeck.CalEditDIstance(t1, t2);
			Assert::AreEqual(f, (float)2, L"testwarning");
		}
		TEST_METHOD(TestMethod2)
		{
			ChesisCheck chesischeck;
			string s1 = "。";
			string s2 = "";
			wstring t1 = chesischeck.TransUTF8toUnicode(s1);
			wstring t2 = chesischeck.TransUTF8toUnicode(s2);
			auto len1 = t1.size();
			auto len2 = t2.size();
			float f = chesischeck.CalEditDIstance(t1, t2);
			Assert::AreEqual(f, (float)0, L"testwarning");
		}
		TEST_METHOD(TestMethod3)
		{
			ChesisCheck chesischeck;
			string s1 = "。";
			wstring w = chesischeck.TransUTF8toUnicode(s1);
			bool isEmpty = w.empty();
			Assert::AreEqual(isEmpty, (bool)false, L"testwarning");
		}
		//判断两个相同的字符之间求的编辑距离是否为0
		TEST_METHOD(TestMethod4)
		{
			ChesisCheck chesischeck;
			string str1 = "abc";
			string str2 = "abc";
			wstring wstr1 = chesischeck.TransUTF8toUnicode(str1);
			wstring wstr2 = chesischeck.TransUTF8toUnicode(str2);
			float res = chesischeck.CalEditDIstance(wstr1, wstr2);
			Assert::AreEqual(res, (float)0, L"testwarning");
		}
		//测试两个相同的字符运算时间是否为0
		TEST_METHOD(TestMethod5)
		{
			clock_t start, end;
			start = clock();
			ChesisCheck chesischeck;
			string str1 = "abc";
			string str2 = "abc";
			float ans = 0;
			wstring wstr1 = chesischeck.TransUTF8toUnicode(str1);
			wstring wstr2 = chesischeck.TransUTF8toUnicode(str2);	

			end = clock();
			ans = 1.0 * (end - start) / CLOCKS_PER_SEC;
			Assert::AreEqual(ans, (float)0, L"testwarning");
		}
		TEST_METHOD(TestMethod6)
		{
			ChesisCheck chesischeck;
			chesischeck.CalRunTime();
			bool x = chesischeck.destroy;
			Assert::AreEqual(x, (bool)true, L"testwarning");
		}
		TEST_METHOD(TestMethod7)
		{
			ChesisCheck* chesischeck=new ChesisCheck;
			chesischeck->~ChesisCheck();
			bool x = chesischeck->destroy;
			Assert::AreEqual(x, (bool)true, L"testwarning");
		}
		TEST_METHOD(TestMethod8)
		{
			ChesisCheck chesischeck;
			chesischeck.Start(true);
			bool x = chesischeck.destroy;
			Assert::AreEqual(x, (bool)true, L"testwarning");
		}
		//是否调用构造函数
		TEST_METHOD(TestMethod9)
		{
			string str[3] = { "D:\\testProject\\qiyeProject\\Thesis\\Thesis\\orig.txt","D:\\testProject\\qiyeProject\\Thesis\\Thesis\\orig_0.8_add.txt", "D:\\testProject\\qiyeProject\\Thesis\\Thesis\\ans.txt" };
			ChesisCheck chesischeck(str[0],str[1],str[2]);

			bool x = chesischeck.destroy;
			Assert::AreEqual(x, (bool)true, L"testwarning");
		}
		//init函数是否执行
		TEST_METHOD(TestMethod10)
		{
			int a = 3;
			char* y[5] = { "1","2","3" };
			ChesisCheck chesischeck;
			chesischeck.Init(a,y,true);
			bool x = chesischeck.destroy;
			Assert::AreEqual(x, (bool)true, L"testwarning");
		}
	};
}
