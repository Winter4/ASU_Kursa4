#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "windows.h"
#include "conio.h"

void readDots_file(int* X, int* Y, int N)
{
	FILE* file;
	char name[11];
	do {
		printf("\nВведите название файла: ");
		scanf("%s", name);

		file = fopen(name, "r");
	} while (file == NULL);

	int i = 0;
	while (i < N && !(feof(file))) {
		fscanf(file, "%d%d", &X[i], &Y[i]);
		i++;
	}
	fclose(file);

	for (i; i < N; i++) {
		X[i] = -30 + rand() % 100;
		Y[i] = -30 + rand() % 100;
	}
}

void print_dots(int* X, int* Y, int N, int sqrX[4], int sqrY[4])
{
	printf("\nКвадрат: \n");
	for (int i = 0; i < 4; i++)
		printf("(%d, %d)\t", sqrX[i], sqrY[i]);

	printf("\nТочки: ");
	for (int i = 0; i < N; i++)
		printf("\n%d - (%d, %d)", i + 1, X[i], Y[i]);
	printf("\n");
}

void nearest_dot(int* X, int* Y, int N, int sqrX[4], int sqrY[4], int choice, int* dotI, int* sqrI)
{
	float distance = INT_MIN;
	for (int i = 0; i < N; i++) 
		for (int j = 0; j < 4; j++) {
			float d = sqrt(powf(X[i] - sqrX[j], 2.0) + powf(Y[i] - sqrY[j], 2.0)); // временный distance
			if (d > distance) {
				distance = d;
				*dotI = i;
				*sqrI = j;
			}
		}

	switch (choice)
	{
	case 2:
		printf("\nТочка %d ближайшая к вершине квадрата %d. Расстояние - %.1f.", *dotI + 1, *sqrI + 1, distance);
		break;
	case 1:
		char name[11];

		printf("\n Введите название файла: ");
		scanf("%s", name);

		FILE* file = fopen(name, "w");

		fprintf(file, "The dot №%d is the nearest to sqr's top №%d. Distance = %.1f.", *dotI + 1, *sqrI + 1, distance);

		fclose(file);
		printf("\nSaved!");
		break;
	}
}

void scale(float* mx, float* my, int* X, int* Y, int sqrX[4], int sqrY[4], int N)
{
	int x_max = INT_MIN, y_max = INT_MIN;
	for (int i = 0, j = 0; i < N; i++, j++) {
		if (abs(X[i]) > x_max) x_max = abs(X[i]);
		if (abs(Y[i]) > y_max) y_max = abs(Y[i]);

		if (j < 4) {
			if (abs(sqrX[j] > x_max)) x_max = abs(sqrX[j]);
			if (abs(sqrY[j] > y_max)) y_max = abs(sqrY[j]);
		}
	}

	*mx = 640 / (x_max * 2);
	*my = 480 / (y_max * 2);
}

void draw(float mx, float my, int* X, int* Y, int sqrX[4], int sqrY[4], int dotI, int sqrI, int N)
{
	HWND hWnd = GetConsoleWindow(); // системная шляпа
	HDC hDC = GetDC(hWnd);

	HPEN Pen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255)); // ручка 
	SelectObject(hDC, Pen);

	MoveToEx(hDC, 320, 0, 0); // рисуем оси
	LineTo(hDC, 320, 480);

	MoveToEx(hDC, 0, 240, 0);
	LineTo(hDC, 640, 240); // ____

	Pen = CreatePen(PS_SOLID, 1, RGB(0, 255, 255));
	SelectObject(hDC, Pen);

	MoveToEx(hDC, sqrX[0] * mx, sqrY[0] * my, 0); // Рисуем квадрат (без выделения)
	for (int i = 1; i <= 4; i++) {
		if (i == 4) {
			LineTo(hDC, sqrX[0] * mx, sqrY[0] * my);
			break;
		}
		LineTo(hDC, sqrX[i] * mx, sqrY[i] * my);
	}

	for (int i = 0; i < N; i++) // рисуем точки
		Rectangle(hDC, (X[i] + 1) * mx, (Y[i] - 1) * my, (X[i] + 1) * mx, (Y[i] + 1) * my);

	Pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	SelectObject(hDC, Pen);

	Rectangle(hDC, (X[dotI] - 1) * mx, (Y[dotI] - 1) * my, (X[dotI] + 1) * mx, (Y[dotI] + 1) * my); // выделяем точку
	Rectangle(hDC, (sqrX[sqrI] - 1) * mx, (sqrY[sqrI] - 1) * mx, (sqrX[sqrI] + 1) * mx, (sqrY[sqrI] + 1) * mx); // выделяем вершину квадрата
}

void task2()
{

	printf("\n Заданы координаты квадрата и координаты N точек.\n Определить какая из точек, к какой вершине квадрата лежит ближе всего. \n");
	
	do {
		printf(" 1 - Данные о задаче \n 2 - Решение задачи \n 0 - Назад \nВыбор: ");

		int choice;
		scanf("%d", &choice);

		switch (choice) {
		case 0:
			return;
			break;
		case 1:
			printf("\n Заданы координаты квадрата и координаты N точек.\n Определить какая из точек, к какой вершине квадрата лежит ближе всего. \n");
			break;
		case 2:
			int N;
			printf("\nВведите N: ");
			scanf("%d", &N);

			int* X = new int[N]; // массивы точек
			int* Y = new int[N];
			int sqrX[4] = { 3, 3, 6, 6 }, sqrY[4] = { 1, 4, 4, 1 }; // массивы вершин квадрата

			printf("\n 1 - Считать координаты из файла \n 2 - Сгенерировать случайные значения \n 3 - Ввести значения с клавиатуры \nВыбор: ");

			int choice_2_2;
			scanf("%d", &choice_2_2);

			switch (choice_2_2)
			{
			case 1:
				printf("\nКоординаты должны быть записаны парами (X Y). \n");
				system("pause");
				readDots_file(X, Y, N); // заполянем массив из файла
				break;
			case 2:
				for (int i = 0; i < N; i++) { // рандомим массив
					X[i] = -10 + rand() % 10;
					Y[i] = -10 + rand() % 10;
				}
				break;
			case 3:
				printf("\nВведите массив \n"); // вводим массив ручками
				for (int i = 0; i < N; i++) {
					printf(" %d - X Y: ", i + 1);
					scanf("%d%d", &X[i], &Y[i]);
				}
				break;
			}
			print_dots(X, Y, N, sqrX, sqrY);

			printf("\n 1 - Вывести результат в файл \n 2 - Вывести результат в консоль \nВыбор: ");
			int choice_2_3;
			scanf("%d", &choice_2_3);

			int dotI, sqrI; // номер точки и вершины квадрата, которые будут в конечном ответе
			nearest_dot(X, Y, N, sqrX, sqrY, choice_2_3, &dotI, &sqrI);

			printf("\n");
			system("pause");
			system("cls");

			float mx, my; // масштаб по икс и игрк
			scale(&mx, &my, X, Y, sqrX, sqrY, N);
			draw(mx, my, X, Y, sqrX, sqrY, dotI, sqrI, N);

			delete[] X; // очищаем память
			delete[] Y;

			system("pause");
			return;
			break;
		}
	} while (true);
}
