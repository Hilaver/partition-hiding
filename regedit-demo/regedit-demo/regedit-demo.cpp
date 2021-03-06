// regedit-demo.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <tchar.h>

using namespace std;


int main()
{
	HKEY hKey = NULL;
	TCHAR *subKey;
	LONG lReturned = 0;
	DWORD dwMusk = 0x00;

	char volLetter[512];
	
	printf("输入要隐藏的盘符(如C,D,F):");

	scanf_s("%s",volLetter,sizeof(volLetter));

	for (int i = 0; i < strlen(volLetter); i++) {
		if ((volLetter[i] >= 'a'&&volLetter[i] <= 'z') || (volLetter[i] >= 'A'&&volLetter[i] <= 'Z')) {
			dwMusk |= (1 << (volLetter[i] >= 'a' ? volLetter[i] - 'a' : volLetter[i] - 'A'));
		}
	}


	if (RegCreateKeyEx(HKEY_CURRENT_USER,
		_T("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer"),
		0,
		NULL,
		REG_OPTION_NON_VOLATILE,
		KEY_ALL_ACCESS,
		NULL,
		&hKey,
		NULL) != ERROR_SUCCESS)
	{
		printf("创建/打开注册表键失败[%d]\n", GetLastError());
		getchar();
		return -1;
	}
	lReturned = RegSetValueEx(hKey, _T("NoDrives"), 0, REG_DWORD, (LPBYTE)&dwMusk, (DWORD)sizeof(dwMusk));
	if (lReturned != ERROR_SUCCESS)
	{
		//
		// 写入注册表退出标志位失败
		//
		printf("更新注册表键失败[%d]\n", GetLastError());
		getchar();
		return -1;
	}

	RegCloseKey(hKey);
	printf("注册表修改成功\n");

	system("taskkill -im explorer.exe -f");
	system("ping -n 2 127.0.0.1 > nul");
	system("start c:\\windows\\explorer.exe");

	printf("重启资源管理器\n");
	printf("修改成功\n");

	getchar();
	getchar();



}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
