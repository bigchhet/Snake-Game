
#include <iostream>
#include <conio.h>
#include<Windows.h>

using namespace std;

//variables for the project
bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void SetUp() 
{
	#pragma region Default Settings
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
	#pragma endregion
}

void Draw() 
{
	#pragma region Map Border
	//clears the console
	system("cls");

	//display top border of map
	for (int i = 0; i < width + 2; i++)
	{
		cout << "#";
	}
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			//prints left wall
			if (j == 0)
			{
				cout << "#";
			}
		
			//prints the head of snake
			if (i == y && j == x)
			{
				cout << "O";
			}

			//prints fruit for snake
			else if (i == fruitY && j == fruitX)
			{
				cout << "F";
			}

			//prints spaces for actual game area and adds tail to snake body
			else
			{
				bool printTail = false;
				//draws tail onto snake
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						printTail = true;
					}		
				}
				if (!printTail)
				{
					//prints spaces for game
					cout << " ";
				}
			}

			//prints right wall
			if (j == width - 1)
			{
				cout << "#";

			}
		}
		cout << endl;		
	}

	//display bottom border of map
	for (int i = 0; i < width + 2; i++)
	{
		cout << "#";
	}

	cout << endl;
	cout << "SCORE: " << score << endl;
#pragma endregion
}

void Input() 
{
	#pragma region Controller
	//creating controller for snake
	if (_kbhit())
	{
		switch (_getch())
		{
			case 'a':
			{
				dir = LEFT;
				break;
			}

			case 'd':
			{
				dir = RIGHT;
				break;
			}

			case 'w':
			{
				dir = UP;
				break;
			}

			case 's':
			{
				dir = DOWN;
				break;
			}

			case 'x':
			{
				gameOver = true;
				break;
			}
		}
	}
	#pragma endregion	
}

void Logic() 
{
	#pragma region Tail Logic

		//remembers location of tail
		int prevX = tailX[0];
		int prevY = tailY[0];
		int prev2X, prev2Y;
		//ensures the tail folloqs the head of snake
		tailX[0] = x;
		tailY[0] = y;

		//moving the tail
		for (int i = 1; i < nTail; i++)
		{
			//remembers current position of tail
			prev2X = tailX[i];
			prev2Y = tailY[i];
			//exchangin positions
			tailX[i] = prevX;
			tailY[i] = prevY;
			//updating position
			prevX = prev2X;
			prevY = prev2Y;
		}
	#pragma endregion

	#pragma region Direction Change Logic
	switch (dir)
	{
		case LEFT:
		{
			x--;
			break;
		}

		case RIGHT:
		{
			x++;
			break;
		}

		case UP:
		{
			y--;
			break;
		}

		case DOWN:
		{
			y++;
			break;
		}

		default:
		{
			break;
		}
	}
	#pragma endregion

	#pragma region Hitting own tail Logic
	for (int i = 0; i < nTail; i++)
	{
		if (tailX[i] == x && tailY[i] == y)
		{
			gameOver = true;
		}
	}
	#pragma endregion

	#pragma region Out Of bounds Logic
		if (x > width || x < 0 || y > height || y < 0)
		{
			gameOver = true;
		}
	#pragma endregion

	#pragma region Eating Fruit Logic
		if (x == fruitX && y == fruitY)
		{
			//scoreboard increase
			score += 10;
			//places the fruit in another random location
			fruitX = rand() % width;
			fruitY = rand() % height;
			//once snake eats fruit, the tail grows by 1
			nTail++;
		}
	#pragma endregion

}

int main()
{
	SetUp();
	while (!gameOver)
	{
		Draw();
		#pragma region stop wall spazz and insane speed
		if (dir == LEFT || dir == RIGHT)
		{
			Sleep(5);
		}

		Sleep(100);

		if (dir == UP || dir == DOWN)
		{
			Sleep(60);
		}
	#pragma endregion
		Input();
		Logic();
	}

	system("cls");
	cout << "YOU HAVE LOST" << endl;
	cout << "FINAL SCORE: " << score << endl;
	return 0;
}