#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

void readArray_file(int* X, int* Y, int N)
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

	if (i != N - 1)
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

void nearest_dot(int* X, int* Y, int N, int sqrX[4], int sqrY[4], int choice)
{
	float distance = INT_MIN;
	int dotI, sqrI; // номер точки и вершины квадрата, которые будут в конечном ответе
	for (int i = 0; i < N; i++) 
		for (int j = 0; j < 4; j++) {
			float d = sqrt(powf(X[i] - sqrX[j], 2.0) + powf(Y[i] - sqrY[i], 2.0)); // временный distance
			if (d > distance) {
				distance = d;
				dotI = i;
				sqrI = j;
			}
		}

	switch (choice)
	{
	case 2:
		printf("\nТочка %d ближайшая к вершине квадрата %d. Расстояние - %.1f.", dotI + 1, sqrI + 1, distance);
		break;
	case 1:
		char name[11];

		printf("\n Введите название файла: ");
		scanf("%s", name);

		FILE* file = fopen(name, "w");

		fprintf(file, "The dot №%d is the nearest to sqr's top №%d. Distance = %.1f.", dotI + 1, sqrI + 1, distance);

		fclose(file);
		break;
	}
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
				readArray_file(X, Y, N); // заполянем массив из файла
				break;
			case 2:
				for (int i = 0; i < N; i++) { // рандомим массив
					X[i] = -30 + rand() % 100;
					Y[i] = -30 + rand() % 100;
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

			nearest_dot(X, Y, N, sqrX, sqrY, choice_2_3);

			delete[] X; // очищаем память
			delete[] Y;

			printf("\n");
			system("pause");
			return;
			break;
		}
	} while (true);
}
