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


enum ObjType
{
	Heart,
	Poo,
	Guard,
};

#pragma endregion


//색깔 바꾸기
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

#define OBJ_COUNT 50
#define BULLET_COUNT 10


struct Obj
{
	bool act;
	int x;
	int y;
	const char* shape;
	Color color;
	ObjType type;
};

int hp = 3;
int spawnTime = 0;
int spawnMaxTime = 30;

int guardTime = 0;

int main()
{
	Obj objects[OBJ_COUNT];
	for (int i = 0; i < OBJ_COUNT; i++)
	{
		objects[i].act = false;
	}

	Obj player;
	player.x = 15;
	player.y = 30;
	player.shape = "♠";

	Obj bullets[BULLET_COUNT];
	for (int i = 0; i < BULLET_COUNT; i++)
	{
		bullets[i].act = false;
		bullets[i].x = i;
		bullets[i].y = player.y + 1;
		bullets[i].color = Blue;
		bullets[i].shape = "●";
	}


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

		if (GetAsyncKeyState(VK_SPACE))
		{
			for (int i = 0; i < BULLET_COUNT; i++)
			{
				if (!bullets[i].act)
				{
					bullets[i].x = player.x;
					bullets[i].y = player.y - 1;
					bullets[i].act = true;
					break;
				}
			}
		}

		spawnTime++;
		if (spawnTime >= spawnMaxTime)
		{
			spawnTime = 0;
			spawnMaxTime--;


			for (int i = 0; i < OBJ_COUNT; i++)
			{
				if (!objects[i].act)
				{
					objects[i].act = true;
					objects[i].x = rand() % 40;
					objects[i].y = 1;
					objects[i].type = (ObjType)(rand() % 3); // 0~1
					switch (objects[i].type)
					{
					case Heart:
						objects[i].shape = "♥";
						objects[i].color = Red;
						break;
					case Poo:
						objects[i].shape = "♨";
						objects[i].color = Green;
						break;
					case Guard:
						objects[i].shape = "◎";
						objects[i].color = Yellow;
					default:
						break;
					}
					break;

				}
			}
		}

		if (guardTime > 0)
		{
			guardTime--;
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
					switch (objects[i].type)
					{
					case Heart:
						hp++;
						break;

					case Poo:
						if (guardTime != 0)
						{
							hp--;
						}
						break;

					case Guard:
						guardTime += 10;
						break;
					default:
						break;
					}

				}

			}
		}

	
		for (int i = 0; i < BULLET_COUNT; i++)
		{
			if (bullets[i].act)
			{
				bullets[i].y--;
				if (bullets[i].y <= 0)
				{
					bullets[i].act = false;
					bullets[i].x = i;
					bullets[i].y = player.y + 1;
				}


				for (int j = 0; j < OBJ_COUNT; j++)
				{
					if (objects[j].act)
					{
						if (bullets[i].x == objects[j].x)
						{
							if (bullets[i].y == objects[j].y || bullets[i].y + 1 == objects[j].y)
							{
								objects[j].act = false;
								bullets[i].act = false;
								bullets[i].x = i;
								bullets[i].y = player.y + 1;
							}

						}

					}

				}
			}

		}

		//========================= 그리기 ============================//

	
		for (int i = 0; i < OBJ_COUNT; i++)
		{
			if (objects[i].act)
			{
				ChangeColor(objects[i].color);
				SetPosition(objects[i].x, objects[i].y);
				printf(objects[i].shape);
			}
			
		}

		for (int i = 0; i < BULLET_COUNT; i++)
		{
			ChangeColor(bullets[i].color);
			SetPosition(bullets[i].x, bullets[i].y);
			printf(bullets[i].shape);

		}


		ChangeColor(White);
		SetPosition(player.x, player.y);
		printf(player.shape);


		ChangeColor(Red);
		for (int i = 0; i < hp; i++)
		{
			SetPosition(30 + i, 0);
			printf("♥");

		}

		Sleep(50);
	}
	return 0;
}