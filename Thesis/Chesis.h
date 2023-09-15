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
#include <numeric>//�ۼ���ͷ�ļ�
using namespace std;
class ChesisCheck
{
public:
	ChesisCheck() {}
	ChesisCheck(const std::string& origTxtPath, const std::string& orig_addTxtPath, const std::string& ansTxtPath);
	~ChesisCheck();
	void Init(int argc, char* argv[],bool start=true);//��ʼ��
	//��ʼ����
	void Start(bool start=true);
	//����༭����
	float CalEditDIstance(const wstring& str1, const wstring& str2);
	//��������ʱ��
	void CalRunTime();
	//���ؽ��
	void Res();
	//�ַ���ת������
	wstring TransUTF8toUnicode(const string& str);
	bool destroy = false;
private:
	fstream origTxt;//ԭ��
	fstream orig_addTxt;//��Ϯ
	fstream ansTxt;//��
	string origTxtPath;
	string orig_addTxtPath;
	string ansTxtPath;
	//��vector�����涯̬�滮�㷨�ķ���ֵ
	vector<float> ansArray;
	int similar = 0;//���ƶ�
	float ans = 0;
	float res = 0;//������

	string str1;
	string str2;
	
};

#endif // !CHESIS_H_

