#include <windows.h>
#include <winuser.h>
#include <string>
#include <iostream>

using namespace std;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance,
                    PSTR lpCmdLine, int nCmdShow)
{
    HWND hWnd = FindWindow(TEXT("Shell_traywnd"), TEXT(""));

	UINT flag;
	string cmdOption{lpCmdLine};
	if (cmdOption == "show")
	{
		flag = SWP_SHOWWINDOW;
	}
	else if (cmdOption == "hide")
	{
		flag = SWP_HIDEWINDOW;
	}
	else
	{
	  exit(1);
	}
	SetWindowPos(hWnd, 0, 0, 0, 0, 0, flag);

    return 0;
}
