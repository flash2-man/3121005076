#include"Chesis.h"

ChesisCheck::ChesisCheck(const std::string& origTxtPath, const std::string& orig_addTxtPath, const std::string& ansTxtPath) :
	origTxt(origTxtPath), orig_addTxt(orig_addTxtPath), ansTxt(ansTxtPath, std::ios::out | std::ios::app),
	origTxtPath(origTxtPath), orig_addTxtPath(orig_addTxtPath), ansTxtPath(ansTxtPath)
{
destroy = true;
	if (!origTxt.is_open() || !orig_addTxt.is_open() || !ansTxt.is_open()) {
	
		cerr << "文件打开失败，请检查文件路径。" << std::endl;
		throw runtime_error("文件打开失败");
		
	}
}

ChesisCheck::~ChesisCheck()
{
	destroy = true;
	origTxt.close();
	orig_addTxt.close();
	ansTxt.close();
}

void ChesisCheck::Init(int argc, char* argv[],bool start)
{
	destroy = start;
	cout << "输出路径：" << endl;
	for (int i = 0; i < argc; i++)
	{
		ansTxt << argv[i] << endl;

		cout << "命令行参数:argv[" << i << "]:" << argv[i] << endl;
	}
}

void ChesisCheck::Start(bool start)
{
	destroy=start;
	CalRunTime();
	Res();
}
//2.改进2
/*float ChesisCheck::CalEditDIstance(wstring str1, wstring str2, int len1, int len2)
{

	vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1));//len1行len2列的二维数组，记录状态值。
	//初始化
	//采用动态规划的最长子序列算法来求编辑距离
	for (int i = 1; i <= len1; i++)
	{
		dp[i][0] = i;
	}
	for (int j = 1; j <= len2; j++)
	{
		dp[0][j] = j;
	}
	for (int i = 1; i <= len1; i++)
	{
		for (int j = 1; j <= len2; j++)
		{
			if (str2[j - 1] == str1[i - 1])
				dp[i][j] = dp[i - 1][j - 1];
			else
				dp[i][j] = min(min(dp[i][j - 1], dp[i - 1][j]), dp[i - 1][j - 1]) + 1;
		}
	}
	return dp[len1][len2];
}*/
float ChesisCheck::CalEditDIstance(const wstring& str1, const wstring& str2)
{
#if 0
	int len1 = str1.size();
	int len2 = str2.size();

	vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1));

	// KMP 算法
	vector<int> lps(len1);
	int len = 0;
	int i = 1;
	while (i < len1) {
		if (str1[i] == str1[len]) {
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
			if (str1[i - 1] == str2[j - 1]) {
				dp[i][j] = dp[i - 1][j - 1];
			}
			else {
				dp[i][j] = min(min(dp[i][j - 1], dp[i - 1][j]), dp[i - 1][j - 1]) + 1;
			}
		}
	}

	return dp[len1][len2];
#else
	try {
		auto len1 = str1.size();
		auto len2 = str2.size();

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
	catch (const std::exception& e) {
		std::cerr << "发生异常: " << e.what() << std::endl;
		// 处理异常情况，例如返回一个特定的错误码或抛出新的异常
		throw;
	}

#endif
}


void ChesisCheck::CalRunTime()
{
	clock_t start, end;
	start = clock();
	while (!origTxt.eof() || !orig_addTxt.eof()) {

		getline(origTxt, str1);
		getline(orig_addTxt, str2);

		//如果为空跳出循环
		if (str1.empty() || str2.empty())
			continue;
		//将文件内的内容进行编码转化
		wstring t1 = TransUTF8toUnicode(str1);
		wstring t2 = TransUTF8toUnicode(str2);


		float ed = CalEditDIstance(t1, t2);
		ans = 1.0 - 1.0 * ed / max(t1.size(), t2.size());

		ansArray.push_back(ans);
	}
	end = clock();
	cout << "运行时间：" << 1.0 * (end - start) / CLOCKS_PER_SEC << "s\n";
	destroy = true;
}

void ChesisCheck::Res()
{
#if 0	//采用迭代器进行输出
	for (auto iter = ansArray.begin(); iter != ansArray.end(); iter++) {
		res += *iter;
	}
#else 
	//用累加器
	float accumulator = accumulate(ansArray.begin(), ansArray.end(), 0.0f);

#endif
	float res = accumulator / ansArray.size(); // 查重率

	cout << "文本查重率=" << setprecision(4) << res * 100 << "%\n";

	ansTxt << "文本查重率=" << setprecision(4) << res * 100 << "%" << '\n' << endl;
	cout << "输入成功!" << endl;
}

wstring ChesisCheck::TransUTF8toUnicode(const string& str)
{
#if 0
	/*wstring ans;
	int size = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
	if (size > 0) {
		wchar_t* buffer = new wchar_t[size];
		MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, buffer, size);
		ans = buffer;
		delete[] buffer;
	}
	return ans;*/
#else 
	//使用std::unique_ptr来管理动态分配的wchar_t数组的内存。
	// 通过使用智能指针，确保在函数返回时自动释放内存，避免了手动释放内存的繁琐和可能的内存泄漏问题,可以提高代码的效率和可靠性。
	wstring ans;
	int size = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
	if (size > 0) {
		unique_ptr<wchar_t[]> buffer(new wchar_t[size]);
		if (MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, buffer.get(), size) > 0) {
			ans = buffer.get();
		}
		else {
			// 转换失败，抛出异常或者进行其他错误处理
			throw runtime_error("转换UTF-8到Unicode失败");
		}
	}
	else {
		// 转换失败，抛出异常或者进行其他错误处理
		throw runtime_error("获取转换后字符串长度失败");
	}
	return ans;
#endif
}


