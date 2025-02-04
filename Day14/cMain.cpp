#include <stdio.h>
#include <Windows.h>

#pragma region Enum
enum Color
{
	Black,
	DarkBlue,
	DarkGreen,
	DarkCyan,
	DarkRed,
	DarkMagenta,
	DarkYellow,
	Gray,
	DarkGray,
	Blue,
	Green,
	Cyan,
	Red,
	Magenta,
	Yellow,
	White,
};
#pragma endregion


//���� �ٲٱ�
void ChangeColor(Color color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}


void SetPosition(int x, int y)
{
	COORD pos;
	pos.X = x * 2;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

#define OBJ_COUNT 10


struct Obj
{
	bool act;
	int x;
	int y;
	const char* shape;
};

int hp = 3;

int main()
{
	Obj objects[OBJ_COUNT];
	for (int i = 0; i < OBJ_COUNT; i++)
	{
		objects[i].act = false;
		objects[i].x = rand() % 40;
		objects[i].y = 1;
		objects[i].shape = "��";

	}

	Obj player;
	player.x = 15;
	player.y = 30;
	player.shape = "��";

	while (true)
	{
		system("cls");

		if (GetAsyncKeyState(VK_LEFT))
		{
			player.x--;

		}
		if (GetAsyncKeyState(VK_RIGHT))
		{
			player.x++;

		}


		for (int i = 0; i < OBJ_COUNT; i++)
		{
			if (!objects[i].act)
			{
				objects[i].act = true;
				objects[i].x = rand() % 40;
				objects[i].y = 1;
				break;

			}
		}

		for (int i = 0; i < OBJ_COUNT; i++)
		{
			if (objects[i].act)
			{

				objects[i].y++;

				if (objects[i].y >= 30)
				{
					objects[i].act = false;
				}

				if (player.x == objects[i].x && player.y == objects[i].y)
				{
					hp--;

				}

			}
		}

	


		ChangeColor(Green);
		for (int i = 0; i < OBJ_COUNT; i++)
		{
			SetPosition(objects[i].x, objects[i].y);
			printf(objects[i].shape);
		}


		ChangeColor(White);
		SetPosition(player.x, player.y);
		printf(player.shape);


		ChangeColor(Red);
		for (int i = 0; i < hp; i++)
		{
			SetPosition(30 + i, 0);
			printf("��");

		}

		Sleep(50);
	}
	return 0;
}