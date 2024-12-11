#include "util.h"

#include <conio.h>


int keyControl() {
	int input = _getch();

	if (input == 224)
		input = _getch();
	else if (input == 72)
		return UP;
	else if (input == 80)
		return DOWN;
	else if (input == 77)
		return LEFT;
	else if (input == 75)
		return RIGHT;
	else if (input == 32)
		return SPACE;
}

void titleDraw() {
	cout << "\n\n\n";
	cout << "     ######################################################################################################################\n";
	cout << "     #                                                                                                                    #\n";
	cout << "     #                                                                                                                    #\n";
	cout << "     #          #####  ### #     # ######  #       ####### ######  ###  #####  #    # ### #     # ####### #######         #\n";
	cout << "     #         #     #  #  ##   ## #     # #       #       #     #  #  #     # #   #   #  ##    # #       #     #         #\n";
	cout << "     #         #        #  # # # # #     # #       #       #     #  #  #       #  #    #  # #   # #       #     #         #\n";
	cout << "     #          #####   #  #  #  # ######  #       #####   #     #  #   #####  ###     #  #  #  # #####   #     #         #\n";
	cout << "     #               #  #  #     # #       #       #       #     #  #        # #  #    #  #   # # #       #     #         #\n";
	cout << "     #         #     #  #  #     # #       #       #       #     #  #  #     # #   #   #  #    ## #       #     #         #\n";
	cout << "     #          #####  ### #     # #       ####### ####### ######  ###  #####  #    # ### #     # #       #######         #\n";
	cout << "     #                                                                                                                    #\n";
	cout << "     #                                                                                                               v0.1 #\n";
	cout << "     ######################################################################################################################\n";
	cout << "\n";
}

int menuDraw(int a, int b) {
	int x = a;
	int y = b;
	gotoxy(x - 2, y);
	cout << ">   Check Disk Status";
	gotoxy(x, y + 1);
	cout << " Set Threshold Value";
	gotoxy(x, y + 2);
	cout << "        Exit       ";
	while (TRUE) {
		int n = keyControl();
		switch (n) {
		case UP: {
			if (y > 20) {
				gotoxy(x - 2, y);
				cout << " ";
				gotoxy(x - 2, --y);
				cout << ">";
			}
			break;
		}
		case DOWN: {
			if (y < 22) {
				gotoxy(x - 2, y);
				cout << " ";
				gotoxy(x - 2, ++y);
				cout << ">";
			}
			break;
		}
		case SPACE: {
			return y - 20;
		}
		}
	}
}

void init() {
	system("mode con cols=128 lines=30 | title SimpleDiskInfo");

	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);
}

void gotoxy(int x, int y) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}

void textcolor(int num) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), num);
}