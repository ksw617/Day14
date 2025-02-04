#include <stdio.h>
#include <Windows.h>

void SetPosition(int x, int y)
{
	COORD pos;
	pos.X = x * 2;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

#define OBJ_COUNT 30


struct Obj
{
	bool act;
	int x;
	int y;
	const char* shape;
};

int main()
{
	Obj objects[OBJ_COUNT];
	for (int i = 0; i < OBJ_COUNT; i++)
	{
		objects[i].act = false;
		objects[i].x = rand() % 40;
		objects[i].y = 0;
		objects[i].shape = "��";

	}

	while (true)
	{
		system("cls");

		//Ȱ��ȭ �Ǿ� ���� �ʴٸ� �ϳ��� Ȱ��ȭ �����ֱ�
		for (int i = 0; i < OBJ_COUNT; i++)
		{
			if (!objects[i].act)
			{

				objects[i].act = true;
				objects[i].x = rand() % 40;
				objects[i].y = 0;
				break;

			}
		}

		//Ȱ��ȭ �Ǿ� ������ �����ִ°�
		//�������ٰ� ���� ���� ������ �������� ��Ȱ��ȭ
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

		//�׷��ִ°�
		for (int i = 0; i < OBJ_COUNT; i++)
		{
			SetPosition(objects[i].x, objects[i].y);
			printf(objects[i].shape);
		}

		Sleep(50);
	}
	return 0;
}