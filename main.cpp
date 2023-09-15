#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<iomanip>
#include<numeric>
using namespace std;

float CalEditDIstance(const string& str1, const string& str2);
int main() {
	cout << "请输入所有的文件路径：" << endl;

	string fileName[3]; //存文件路径;
	for (int i = 0; i < 3; i++) {
		cin >> fileName[i];
	}

	//创建文件对象
	fstream origTxt;//原文
	fstream orig_addTxt;//抄袭
	fstream ansTxt;//答案
	//创建文件输入流对象
	string str1;
	string str2;
	//记录每一句的相似度
	float ans;
	//记录文本所有句子相似度
	vector<float> ansArray;
	
	float sum = 0;
	//最小编辑距离
	float ed;

	//打开文件
	origTxt.open(fileName[0], ios::in);
	orig_addTxt.open(fileName[1], ios::in);
	ansTxt.open(fileName[2], ios::out);

	//遍历原始文件和抄袭文件
	if (origTxt.is_open() && orig_addTxt.is_open()) {
		while (!origTxt.eof() || !orig_addTxt.eof()) {
			getline(origTxt, str1);
			getline(orig_addTxt, str2);
			if (str1.empty() && str2.empty()) 
				continue;  //  若都为空行，则跳过。
			
			cout << (ed = CalEditDIstance(str1, str2)) << endl;

			ans = 1.0 - 1.0 * ed / max(str1.size(), str2.size());
			//
			cout << ans << endl;
			ansArray.push_back(ans);
		}
	}

	float accumulator = accumulate(ansArray.begin(), ansArray.end(), 0.0f);

	float res = accumulator / ansArray.size(); // 查重率

	cout << "文本查重率=" << setprecision(4) << res * 100 << "%\n";

	cout << "输入成功!" << endl;

	//写文件
	if (ansTxt.is_open()) {
		ansTxt << setprecision(4) << sum * 100 << "%";
		cout << "输出成功！" << endl;
	}

	origTxt.close();
	orig_addTxt.close();
	ansTxt.close();

	return 0;
}

float CalEditDIstance(const string& str1, const string& str2) {  //计算最小编辑距离
	//
	int len1 = str1.size();
	int len2 = str2.size();

	vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1));

	// KMP 算法
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