#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
#define getch() _getch()

void setcursor(bool visible) {
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}

void setcolor(int fg, int bg) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}

void gotoxy(int x, int y) {
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void draw_ship(int x, int y) {
	gotoxy(x, y);
	setcolor(9, 0);
	printf("<-0->");
}

void erase_ship(int x, int y) {
	gotoxy(x, y);
	setcolor(2, 0);
	printf("     ");
}

void draw_bullet(int x, int y) {
	gotoxy(x, y);
	setcolor(12, 0);
	printf("^");
}

void clear_bullet(int x, int y) {
	gotoxy(x, y);
	setcolor(0, 0);
	printf(" ");
}

void draw_star() {
	int x, y;
	x = 9 + rand() % 61;
	y = 1 + rand() % 4;
	//printf("%d %d\n", x, y);
	gotoxy(x, y);
	setcolor(6, 0);
	printf("*");
}

void draw_group_star() {
	for (int i = 0; i < 20; i++) {
		draw_star();
	}
}

void draw_score(int score) {
	gotoxy(80, 2);
	setcolor(2, 0);
	printf("score : %d", score);
}

char cursor(int x, int y) {
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	char buf[2]; COORD c = { x,y }; DWORD num_read;
	if (!ReadConsoleOutputCharacter(hStd, (LPTSTR)buf, 1, c, (LPDWORD)&num_read)) {
		return '\0';
	}
	else {
		return buf[0];
	}
}

int main() {
	char ch = ' ';
	char c;
	int x = 38, y = 20;
	int bx, by, i;
	int bullet = 0;
	int score = 0;

	srand(time(NULL));
	setcursor(0);
	draw_group_star();
	draw_ship(x, y);
	draw_score(score);

	do {
		if (_kbhit()) {
			ch = _getch();
			if (ch == 'a') {
				erase_ship(x, y);
				draw_ship(--x, y);
			}
			if (ch == 's') {
				erase_ship(x, y);
				draw_ship(++x, y); 
			}
			if (bullet != 1 && ch == ' ') {
				bullet = 1;
				bx = x + 2;
				by = y - 1;
			}
			fflush(stdin);
		}
		if (bullet == 1) {
			clear_bullet(bx,by);
			if (by == 1) {
				bullet = 0;
			}
			else {
				by--;
				c = cursor(bx, by);
				if (c == '*') {
					bullet = 0;
					clear_bullet(bx, by);
					Beep(900, 100);
					draw_score(++score);
					draw_star();
				}
				else {
					draw_bullet(bx, by);
				}
				
			}
		}


		Sleep(100);
	} while (ch != 'x');
	
	return 0;
}