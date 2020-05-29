#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

void readMatrix_file(int Matrix[10][10])
{
	const int n = 10;

	FILE* file;
	char name[11];
	do {
		printf("\nВведите название файла: ");
		scanf("%s", name);

		file = fopen(name, "r");
	} while (file == NULL);

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			fscanf(file, "%d", &Matrix[i][j]);
	fclose(file);
}

void print_matrix(int Matrix[10][10])
{
	const int n = 10;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			printf("%d\t", Matrix[i][j]);
		printf("\n");
	}
}

void task3()
{
	printf("\n В матрице размером 10х10 упорядочить строки по не убыванию значений наименьших элементов строк методом выбора.\n Удалить те строки, в которых есть повторяющиеся элементы. \n");

	do {
		printf(" 1 - Данные о задаче \n 2 - Решение задачи \n 0 - Назад \nВыбор: ");
		int choice;
		scanf("%d", &choice);

		switch (choice) 
		{
		case 0:
			return;
			break;
		case 1:
			printf("\n В матрице размером 10х10 упорядочить строки по не убыванию значений наименьших элементов строк методом выбора.\n Удалить те строки, в которых есть повторяющиеся элементы. \n");
			break;
		case 2:
			int Matrix[10][10];
			const int n = 10;
			printf("\n 1 - Считать матрицу из файла \n 2 - Сгенерировать случайные значения \n 3 - Ввести значения с клавиатуры \nВыбор: ");

			int choice_2_2;
			scanf("%d", &choice_2_2);

			switch (choice_2_2)
			{
			case 1:
				printf("\nЗначения считываются построчно. \n");
				system("pause");
				readMatrix_file(Matrix); // заполянем массив из файла
				break;
			case 2:
				for (int i = 0; i < n; i++)  // рандомим массив
					for (int j = 0; j < n; j++)
						Matrix[i][j] = -30 + rand() % 100;
				break;
			case 3:
				printf("\nВведите массив "); // вводим массив ручками
				for (int i = 0; i < n; i++) 
					for (int j = 0; j < n; j++) {
						printf("\n [%d][%d]: ", i + 1, j + 1);
						scanf("%d", &Matrix[i][j]);
					}
				break;
			}

			printf("\n Матрица: \n");
			print_matrix(Matrix);

			break;
		}
	} while (true);
}