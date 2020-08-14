// cursor_image.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <windows.h>
LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int drawImage() {
	HWND hWnd = GetConsoleWindow();
	// HDC hdc = GetWindowDC(GetDesktopWindow());
	HDC hdc = GetWindowDC(NULL);

	HPEN hpen1 = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	// 创建绿色、5像素宽度的破折画笔，如果你想创建其他种类的画笔请参阅MSDN
	HPEN hpen2 = CreatePen(PS_DASH, 5, RGB(0, 255, 0));
	// 创建一个实体蓝色画刷
	HBRUSH hbrush1 = CreateSolidBrush(RGB(0, 0, 255));
	// 创造一个透明的画刷，如果你想创建其他种类的画刷请参阅MSDN
	HBRUSH hbrush2 = (HBRUSH)GetStockObject(NULL_BRUSH);

	// 将hpen1和hbrush1选进HDC，并保存HDC原来的画笔和画刷
	HPEN hpen_old = (HPEN)SelectObject(hdc, hpen1);
	HBRUSH hbrush_old = (HBRUSH)SelectObject(hdc, hbrush1);

	// 在(40,30)处画一个宽200像素，高50像素的矩形
	Rectangle(hdc, 40, 30, 40 + 200, 30 + 50);

	// 换hpen1和hbrush1，然后在(40,100)处也画一个矩形，看看有何差别
	SelectObject(hdc, hpen2);
	SelectObject(hdc, hbrush2);
	Rectangle(hdc, 40, 100, 40 + 200, 100 + 50);

	// 画个椭圆看看
	Ellipse(hdc, 40, 200, 40 + 200, 200 + 50);

	// 画个(0,600)到(800,0)的直线看看
	MoveToEx(hdc, 0, 600, NULL);
	LineTo(hdc, 800, 0);

	// 在(700,500)处画个黄点，不过这个点只有一像素大小，你细细的看才能找到
	SetPixel(hdc, 700, 500, RGB(255, 255, 0));

	// 恢复原来的画笔和画刷
	SelectObject(hdc, hpen_old);
	SelectObject(hdc, hbrush_old);

	return 0;
}


int main(int ac, char** pav)
{
	// HINSTANCE hInstance = GetWindowLong(GetDesktopWindow(), 0);
	HINSTANCE hInstance = GetModuleHandle(NULL);
	WNDCLASS wc = {};
	wc.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WindowProc;
	wc.lpszClassName = L"My";
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wc);

	LONG x = -1, y = -1;
	POINT pt = { 0,0 };

	while (true)
	{
		GetCursorPos(&pt);    //获取鼠标当前位置      
		// if ((x != pt.x) || (y != pt.y)) //如果位置与之前的位置不一样则输出新位置
		// {
			// printf("x=%d,y=%d\n", pt.x, pt.y);
		drawImage();
		x = pt.x, y = pt.y;
		// }
		Sleep(100);
	}
	return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	std::cout << "调用了!" << std::endl;
	static int penStyle = PS_SOLID;
	switch (msg)
	{
	case WM_CREATE:
	{

	}
	return 0;
	case WM_COMMAND:
	{

	}
	return 0;
	case WM_LBUTTONDOWN:
	{

	}
	return 0;
	case WM_LBUTTONUP:
	{

	}
	return 0;
	case WM_PAINT:
	{
		drawImage();
	}
	return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}