#include <stdio.h>
#include <Windows.h>

void SetPosition(int x, int y)
{
	COORD pos;
	pos.X = x * 2;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

#define OBJ_COUNT 3


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
		objects[i].shape = "♨";

	}

	while (true)
	{
		system("cls");

		//활성화 되어 있지 않다면 하나씩 활성화 시켜주기
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

		//활성화 되어 있으면 내려주는거
		//내려가다가 일정 높이 밑으로 내려가면 비활성화
		for (int i = 0; i < OBJ_COUNT; i++)
		{
			if (objects[i].act)
			{

				objects[i].y++;

				if (objects[i].y >= 30)
				{
					objects[i].act = false;
				}

			}
		}

		//그려주는거
		for (int i = 0; i < OBJ_COUNT; i++)
		{
			SetPosition(objects[i].x, objects[i].y);
			printf(objects[i].shape);
		}

		for (int i = 0; i < hp; i++)
		{
			SetPosition(30 + i, 0);
			printf("♥");

		}

		Sleep(50);
	}
	return 0;
}