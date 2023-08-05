#include <iostream>
#include <Windows.h>

using namespace std;

// Initialize Variables
bool snakeGame;
enum game { MAIN, START};
int menu = 0;
game mode;
const int width = 25;
const int height = 25;
// User variables
int x, y, spd = 1;
int tailX[625], tailY[625], tailLength;
// Tail Coordinates
int fposX, fposY, sposX, sposY;
// Target variables
int targetX, targetY;
int score = 0;
enum directions {STOP = 0, UP, DOWN, LEFT, RIGHT};
directions dir;

void game_Over()
{
	score = 0;
	tailLength = 0;
	mode = MAIN;
}

void game_Setup()
{
	snakeGame = true;
	mode = MAIN;
}

void main_Menu()
{
	system("cls");
	cout << "This is the Main Menu." << endl;
	if (menu == 0)
	{
		cout << ">> Play The Game." << endl;
		cout << "Options" << endl;
		cout << "End Game" << endl;
	}
	else if (menu == 1)
	{
		cout << "Play The Game." << endl;
		cout << ">> Options" << endl;
		cout << "End Game" << endl;
	}
	else if (menu == 2)
	{
		cout << "Play The Game." << endl;
		cout << "Options" << endl;
		cout << ">> End Game" << endl;
	}

	if (GetAsyncKeyState(VK_RETURN))
	{
		switch (menu)
		{
		case 0 :
			mode = START;
			break;
		case 1 :
			return;
			break;
		case 2 :
			exit(0);
			break;
		}
	}
	else if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A') || GetAsyncKeyState('a'))
	{
		dir = STOP;
	}
	else if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D') || GetAsyncKeyState('d'))
	{
		dir = STOP;
	}
	else if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S') || GetAsyncKeyState('s'))
	{
		dir = STOP;
		menu++;
		Sleep(200);
	}
	else if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W') || GetAsyncKeyState('w'))
	{
		dir = STOP;
		menu--;
		Sleep(200);
	}

	if (menu <= -1)
	{
		menu = 2;
	}
	else if (menu >= 3)
	{
		menu = 0;
	}
}

void normal_Setup()
{
	dir = STOP;
	x = rand() % width;
	y = rand() % height;
	targetX = rand() % width;
	targetY = rand() % height;
	// Error when target and player are on top
	if (x == targetX && y == targetY)
	{
		x = rand() % width;
		y = rand() % height;
		targetX = rand() % width;
		targetY = rand() % height;
	}

	while ((fposX == targetX && fposY == targetY) || (sposX == targetX && sposY == targetY))
	{
		targetX = rand() % width;
		targetY = rand() % height;
	}
	score = 0;
}

void game_Window()
{
	system("cls");

	// Top border
	for (int i = 0; i < width; i++)
	{
		cout << "*";
	}
	cout << endl;

	// Body
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0 || j == width - 1)
			{
				cout << "*";
			}
			else if (i == y && j == x)
			{
				cout << "S";
			}
			else if (i == targetY && j == targetX)
			{
				cout << "O";
			}
			else
			{
				bool tail = false;
				for (int k = 0; k < tailLength; k++)
				{
					if (j == tailX[k] && i == tailY[k])
					{
						cout << "s";
						tail = true;
					}
				}
				if (!tail)
				{
					cout << " ";
				}
			}
		}
		cout << endl;
	}

	// Bottom border
	for (int i = 0; i < width; i++)
	{
		cout << "*";
	}
	cout << endl;
	cout << "Score: " << score;
}

void game_Input()
{
	if (mode == START)
	{
		if ((GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A') || GetAsyncKeyState('a')) && dir != RIGHT)
		{
			dir = LEFT;
		}
		else if ((GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D') || GetAsyncKeyState('d')) && dir != LEFT)
		{
			dir = RIGHT;
		}
		else if ((GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S') || GetAsyncKeyState('s')) && dir != UP)
		{
			dir = DOWN;
		}
		else if ((GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W') || GetAsyncKeyState('w')) && dir != DOWN)
		{
			dir = UP;
		}
		else if (GetAsyncKeyState(VK_RETURN))
		{
			return;
		}
	}
}

void game_Program()
{
	fposX = tailX[0];
	fposY = tailY[0];
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < tailLength; i++)
	{
		sposX = tailX[i];
		sposY = tailY[i];
		tailX[i] = fposX;
		tailY[i] = fposY;
		fposX = sposX;
		fposY = sposY;
	}

	switch (dir)
	{
	case LEFT :
		x -= spd;
		break;
	case UP :
		y -= spd;
		break;
	case DOWN :
		y += spd;
		break;
	case RIGHT :
		x += spd;
		break;
	}

	// Snake Hits Border
	if (x < 0 || x > width - 1 || y < 0 || y > height - 1)
	{
		game_Over();
	}

	// Snake Hits Tail
	for (int i = 0; i < tailLength; i++)
	{
		if (x == tailX[i] && y == tailY[i])
		{
			game_Over();
		}
	}

	// Snake Hits Target
	if (x == targetX && y == targetY)
	{
		score++;
		tailLength++;
		targetX = rand() % width;
		targetY = rand() % height;
	}
}

int main()
{
	game_Setup();
	while (snakeGame)
	{
		if (mode == MAIN)
		{
			main_Menu();
		}
		else if (mode == START)
		{
			normal_Setup();
			while (mode == START)
			{
				game_Window();
				game_Input();
				game_Program();
				Sleep(30);
			}
		}
	}

	return 0;
}