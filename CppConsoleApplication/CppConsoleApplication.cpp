#pragma comment(lib,"user32")
#pragma comment(lib,"gdi32")


#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <atlimage.h>


HWND WINAPI GetConsoleWindow();
void HideTheCursor() {
    CONSOLE_CURSOR_INFO cciCursor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (GetConsoleCursorInfo(hStdOut, &cciCursor)) {
        cciCursor.bVisible = FALSE;
        SetConsoleCursorInfo(hStdOut, &cciCursor);
    }
}
void ShowTheCursor() {
    CONSOLE_CURSOR_INFO cciCursor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (GetConsoleCursorInfo(hStdOut, &cciCursor)) {
        cciCursor.bVisible = TRUE;
        SetConsoleCursorInfo(hStdOut, &cciCursor);
    }
}
int main() {
    HWND  hwnd;
    HDC   hdc;
    HFONT hfont;
    HBITMAP hbm;
    HDC hdcBits;
    BITMAP bm;
    CImage Image;


    system("color F0");
    system("cls");
    HideTheCursor();
    hwnd = GetConsoleWindow();
    // hdc = GetDC(hwnd);
    hdc = GetDC(GetDesktopWindow());

    Image.Load(L"C:\\Users\\Ken\\Desktop\\arrow_l.png");
    hbm = Image.Detach();


    //hbm=LoadImage(0,"C:\\Windows\\1.jpg",IMAGE_BITMAP,0,0,LR_DEFAULTSIZE|LR_LOADFROMFILE);
    if (hbm) {
        hdcBits = CreateCompatibleDC(hdc);
        GetObject(hbm, sizeof(BITMAP), &bm);
        SelectObject(hdcBits, hbm);
        BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, hdcBits, 0, 0, SRCCOPY);
        BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, hdcBits, 0, 0, SRCCOPY);
        DeleteDC(hdcBits);
        DeleteObject(hbm);
    }
    hfont = CreateFont(24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, L"华文楷体");
    SelectObject(hdc, hfont);
    SetTextColor(hdc, RGB(255, 255, 255));
    SetBkMode(hdc, TRANSPARENT);
    TextOut(hdc, 210, 30, L"这个背景是泡泡", 14);
    DeleteObject(hfont);
    ReleaseDC(hwnd, hdc);
    _getch();
    system("color 07");
    system("cls");
    ShowTheCursor();
    return 0;
}