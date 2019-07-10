#include <iostream>
#include <conio.h>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>
#include <Windows.h>

using namespace std;

void SetColor(int col)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), col);
}
void SetColor_Background(int text, int background)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}
void SetPos(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void Size_Console(int x, int y)
{
	HANDLE out_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD crd = { x, y };
	SMALL_RECT src = { 0, 0, crd.X , crd.Y };
	SetConsoleWindowInfo(out_handle, true, &src);
	SetConsoleScreenBufferSize(out_handle, crd);
}
void CONSOLE_INFO()
{
	HANDLE  hout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD  size{ 77,25 };//символов строки, строк (если больше чем видимых, скрываются под ползунком прокрутки)
	SetConsoleScreenBufferSize(hout, size);//размер буфера
	////////////////////Меняем шрифт для отображения символов Unicode, можно пропустить - если у вас установлен нужный
	CONSOLE_FONT_INFOEX cfi; //https://docs.microsoft.com/en-us/windows/console/console-font-infoex
	cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 10;
	cfi.dwFontSize.Y = 18;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;//400;
	wcscpy_s(cfi.FaceName, L"Terminal");
	SetCurrentConsoleFontEx(hout, false, &cfi);
}
void InvisibleСursor(bool $CCI)
{
	void *handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(handle, &structCursorInfo);
	structCursorInfo.bVisible = $CCI;
	SetConsoleCursorInfo(handle, &structCursorInfo);
}

string filename1 = "Word_Base.txt";
class  BinaryTree;

void Change_Word(BinaryTree &obj, int edit_pos);
void Show_Menu_Prog(BinaryTree &obj);
void Navigate_The_Alphabet(BinaryTree &obj);
void View_Edit_Words(BinaryTree &obj, string alph);