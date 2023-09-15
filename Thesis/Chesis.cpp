#include"Chesis.h"

ChesisCheck::ChesisCheck(const std::string& origTxtPath, const std::string& orig_addTxtPath, const std::string& ansTxtPath) :
	origTxt(origTxtPath), orig_addTxt(orig_addTxtPath), ansTxt(ansTxtPath, std::ios::out | std::ios::app),
	origTxtPath(origTxtPath), orig_addTxtPath(orig_addTxtPath), ansTxtPath(ansTxtPath)
{
destroy = true;
	if (!origTxt.is_open() || !orig_addTxt.is_open() || !ansTxt.is_open()) {
	
		cerr << "�ļ���ʧ�ܣ������ļ�·����" << std::endl;
		throw runtime_error("�ļ���ʧ��");
		
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
	cout << "���·����" << endl;
	for (int i = 0; i < argc; i++)
	{
		ansTxt << argv[i] << endl;

		cout << "�����в���:argv[" << i << "]:" << argv[i] << endl;
	}
}

void ChesisCheck::Start(bool start)
{
	destroy=start;
	CalRunTime();
	Res();
}
//2.�Ľ�2
/*float ChesisCheck::CalEditDIstance(wstring str1, wstring str2, int len1, int len2)
{

	vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1));//len1��len2�еĶ�ά���飬��¼״ֵ̬��
	//��ʼ��
	//���ö�̬�滮����������㷨����༭����
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

	// KMP �㷨
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
	catch (const std::exception& e) {
		std::cerr << "�����쳣: " << e.what() << std::endl;
		// �����쳣��������緵��һ���ض��Ĵ�������׳��µ��쳣
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

		//���Ϊ������ѭ��
		if (str1.empty() || str2.empty())
			continue;
		//���ļ��ڵ����ݽ��б���ת��
		wstring t1 = TransUTF8toUnicode(str1);
		wstring t2 = TransUTF8toUnicode(str2);


		float ed = CalEditDIstance(t1, t2);
		ans = 1.0 - 1.0 * ed / max(t1.size(), t2.size());

		ansArray.push_back(ans);
	}
	end = clock();
	cout << "����ʱ�䣺" << 1.0 * (end - start) / CLOCKS_PER_SEC << "s\n";
	destroy = true;
}

void ChesisCheck::Res()
{
#if 0	//���õ������������
	for (auto iter = ansArray.begin(); iter != ansArray.end(); iter++) {
		res += *iter;
	}
#else 
	//���ۼ���
	float accumulator = accumulate(ansArray.begin(), ansArray.end(), 0.0f);

#endif
	float res = accumulator / ansArray.size(); // ������

	cout << "�ı�������=" << setprecision(4) << res * 100 << "%\n";

	ansTxt << "�ı�������=" << setprecision(4) << res * 100 << "%" << '\n' << endl;
	cout << "����ɹ�!" << endl;
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
	//ʹ��std::unique_ptr������̬�����wchar_t������ڴ档
	// ͨ��ʹ������ָ�룬ȷ���ں�������ʱ�Զ��ͷ��ڴ棬�������ֶ��ͷ��ڴ�ķ����Ϳ��ܵ��ڴ�й©����,������ߴ����Ч�ʺͿɿ��ԡ�
	wstring ans;
	int size = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
	if (size > 0) {
		unique_ptr<wchar_t[]> buffer(new wchar_t[size]);
		if (MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, buffer.get(), size) > 0) {
			ans = buffer.get();
		}
		else {
			// ת��ʧ�ܣ��׳��쳣���߽�������������
			throw runtime_error("ת��UTF-8��Unicodeʧ��");
		}
	}
	else {
		// ת��ʧ�ܣ��׳��쳣���߽�������������
		throw runtime_error("��ȡת�����ַ�������ʧ��");
	}
	return ans;
#endif
}


