#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

void readMatrix_file(int** Matrix)
{
	const int n = 10;

	FILE* file;
	char name[11];
	do {
		printf("\nВведите название файла: ");
		scanf("%s", name);

		file = fopen(name, "r");
	} while (file == NULL);

	int count = 0; // кол-во считанных чисел
	int i = 0, j = 0;
	while (i < n && !(feof(file))) {
		while (j < n && !(feof(file))) {
			fscanf(file, "%d", &Matrix[i][j]);
			j++;
			count++;
		}
		i++;
		j = 0;
	}
	fclose(file);

	i = count / 10;
	j = count % 10;
	for (i; i < n; i++) {
		for (j; j < n; j++)
			Matrix[i][j] = 0;
		j = 0;
	}
}

void print_matrix(int** Matrix)
{
	const int n = 10;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			printf("%6d", Matrix[i][j]);
		printf("\n");
	}
}

void find_mins(int** Matrix, int* mins) 
{
	const int n = 10;
	int min; // temporary

	for (int i = 0; i < n; i++) {	// ищем минимумы в строках
		min = INT_MAX;
		for (int j = 0; j < n; j++)
			if (Matrix[i][j] < min)
				min = Matrix[i][j];

		mins[i] = min;
	}
}

void print_mins(int* mins)
{
	const int n = 10;

	for (int i = 0; i < n; i++)	// выводим массив минимумов
		printf("\n Min %d = %d", i + 1, mins[i]);
}

void sort_strings(int** Matrix, int* mins)
{
	const int n = 10;
	int min;

	find_mins(Matrix, mins);

	int i_min, buf;
	for (int i = 0; i < n; i++) {	// сортировка выбором
		min = INT_MAX;
		for (int j = i; j < n; j++)
			if (mins[j] < min) {
				min = mins[j];
				i_min = j;
			}

		buf = mins[i];
		mins[i] = min;
		mins[i_min] = buf;

		int* pt_buf;
		pt_buf = Matrix[i];
		Matrix[i] = Matrix[i_min];
		Matrix[i_min] = pt_buf;
	}
}

void print_answer_file(int** Matrix, int* mins)
{
	const int n = 10;
	printf("\n Введите название файла: ");
	char name[11];
	scanf("%s", &name);

	FILE* file = fopen(name, "w");

	fprintf(file, "Matrix: \n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			fprintf(file, "%5d", Matrix[i][j]);
		fprintf(file, "\n");
	}
	fprintf(file, "\n");

	fprintf(file, "Mins: \n");
	for (int i = 0; i < n; i++)
		fprintf(file, "\n Min % d = % d", i + 1, mins[i]);

	fclose(file);
	printf("\nSaved!");
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
			int** Matrix;
			const int n = 10;
			Matrix = new int* [n];
			for (int i = 0; i < n; i++)
				Matrix[i] = new int[n];

			int mins[10]; // массив минимальных элементов

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
				printf("\nВведите массив: \n"); // вводим массив ручками
				for (int i = 0; i < n; i++) 
					for (int j = 0; j < n; j++) {
						printf(" [%d][%d]: ", i + 1, j + 1);
						scanf("%d", &Matrix[i][j]);
					}
				break;
			}

			printf("\n Матрица: \n");
			print_matrix(Matrix);

			find_mins(Matrix, &mins[0]);
			print_mins(&mins[0]);

			sort_strings(Matrix, &mins[0]);

			printf("\n\n 1 - Вывести результат в файл \n 2 - Вывести результат в консоль \nВыбор: ");
			int choice_2_3;
			scanf("%d", &choice_2_3);

			switch (choice_2_3)
			{
			case 1:
				print_answer_file(Matrix, &mins[0]);
				break;
			case 2:
				printf("\n Отсортированная матрица: \n");
				print_matrix(Matrix);
				print_mins(&mins[0]);
				break;
			}

			for (int i = 0; i < n; i++)
				delete[] Matrix[i];
			delete Matrix;
			
			printf("\n\n");
			system("pause");
			return;
			break;
		}
	} while (true);
}