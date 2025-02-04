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
	int x;
	int y;
	const char* shape;
};

int main()
{
	Obj objects[OBJ_COUNT];
	for (int i = 0; i < OBJ_COUNT; i++)
	{
		objects[i].x = rand() % 40;
		objects[i].y = 0;
		objects[i].shape = "ขอ";

	}

	while (true)
	{
		system("cls");

		for (int i = 0; i < OBJ_COUNT; i++)
		{
			objects[i].y++;
		}

		for (int i = 0; i < OBJ_COUNT; i++)
		{
			SetPosition(objects[i].x, objects[i].y);
			printf(objects[i].shape);
		}

		Sleep(50);
	}
	return 0;
}