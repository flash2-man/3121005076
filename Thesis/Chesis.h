#pragma once
#pragma once
#ifndef CHESIS_H_
#define CHESIS_H_
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<iomanip>
#include<time.h>
#include<codecvt>
#include<locale>
#include<Windows.h>
#include <numeric>//累加器头文件
using namespace std;
class ChesisCheck
{
public:
	ChesisCheck() {}
	ChesisCheck(const std::string& origTxtPath, const std::string& orig_addTxtPath, const std::string& ansTxtPath);
	~ChesisCheck();
	void Init(int argc, char* argv[],bool start=true);//初始化
	//开始函数
	void Start(bool start=true);
	//计算编辑距离
	float CalEditDIstance(const wstring& str1, const wstring& str2);
	//计算运行时间
	void CalRunTime();
	//返回结果
	void Res();
	//字符集转化编码
	wstring TransUTF8toUnicode(const string& str);
	bool destroy = false;
private:
	fstream origTxt;//原文
	fstream orig_addTxt;//抄袭
	fstream ansTxt;//答案
	string origTxtPath;
	string orig_addTxtPath;
	string ansTxtPath;
	//用vector来储存动态规划算法的返回值
	vector<float> ansArray;
	int similar = 0;//相似度
	float ans = 0;
	float res = 0;//查重率

	string str1;
	string str2;
	
};

#endif // !CHESIS_H_

