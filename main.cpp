#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<iomanip>
#include<numeric>
using namespace std;

float CalEditDIstance(const string& str1, const string& str2);
int main() {
	cout << "���������е��ļ�·����" << endl;

	string fileName[3]; //���ļ�·��;
	for (int i = 0; i < 3; i++) {
		cin >> fileName[i];
	}

	//�����ļ�����
	fstream origTxt;//ԭ��
	fstream orig_addTxt;//��Ϯ
	fstream ansTxt;//��
	//�����ļ�����������
	string str1;
	string str2;
	//��¼ÿһ������ƶ�
	float ans;
	//��¼�ı����о������ƶ�
	vector<float> ansArray;
	
	float sum = 0;
	//��С�༭����
	float ed;

	//���ļ�
	origTxt.open(fileName[0], ios::in);
	orig_addTxt.open(fileName[1], ios::in);
	ansTxt.open(fileName[2], ios::out);

	//����ԭʼ�ļ��ͳ�Ϯ�ļ�
	if (origTxt.is_open() && orig_addTxt.is_open()) {
		while (!origTxt.eof() || !orig_addTxt.eof()) {
			getline(origTxt, str1);
			getline(orig_addTxt, str2);
			if (str1.empty() && str2.empty()) 
				continue;  //  ����Ϊ���У���������
			
			cout << (ed = CalEditDIstance(str1, str2)) << endl;

			ans = 1.0 - 1.0 * ed / max(str1.size(), str2.size());
			//
			cout << ans << endl;
			ansArray.push_back(ans);
		}
	}

	float accumulator = accumulate(ansArray.begin(), ansArray.end(), 0.0f);

	float res = accumulator / ansArray.size(); // ������

	cout << "�ı�������=" << setprecision(4) << res * 100 << "%\n";

	cout << "����ɹ�!" << endl;

	//д�ļ�
	if (ansTxt.is_open()) {
		ansTxt << setprecision(4) << sum * 100 << "%";
		cout << "����ɹ���" << endl;
	}

	origTxt.close();
	orig_addTxt.close();
	ansTxt.close();

	return 0;
}

float CalEditDIstance(const string& str1, const string& str2) {  //������С�༭����
	//
	int len1 = str1.size();
	int len2 = str2.size();

	vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1));

	// KMP �㷨
	vector<int> lps(len1);
	int len = 0;
	int i = 1;
	while (i < len1) {
		if (static_cast<int>(str1[i]) == static_cast<int>(str1[len])) {
			len++;
			lps[i] = len;
			i++;
		}
		else {
			if (len != 0) {
				len = lps[len - 1];
			}
			else {
				lps[i] = 0;
				i++;
			}
		}
	}
	for (int i = 1; i <= len1; i++) {
		for (int j = 1; j <= len2; j++) {
			if (static_cast<int>(str1[i - 1]) == static_cast<int>(str2[j - 1])) {
				dp[i][j] = dp[i - 1][j - 1];
			}
			else {
				dp[i][j] = min(min(dp[i][j - 1], dp[i - 1][j]), dp[i - 1][j - 1]) + 1;
			}
		}
	}
	return dp[len1][len2];
}