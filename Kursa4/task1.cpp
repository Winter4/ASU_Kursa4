#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

void readArray_file(int* A, int N)
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
		fscanf(file, "%d", &A[i]);
		i++;
	}
	fclose(file);

	for (i; i < N; i++) 
		A[i] = 0;
}

void print_array(int* A, int N)
{
	printf("\n");
	for (int i = 0; i < N; i++)
		printf("%d\t", A[i]);
}

void max_chain(int* A, int N, int choice)
{
	int max = 0, chain = 0, i_max = 0; // max - счетчик, chain - хранит максимальное значение

	for (int i = 0; i < N; i++) {
		if (A[i] > 0) {
			max = 1;
			for (int j = i + 1; j < N; j++)
				if (A[j] > 0)
					max++;
				else break;

			if (max > chain) {
				chain = max;
				i_max = i;
			}
		}
		i += max;
	}

	
	switch (choice)
	{
	case 2:
		printf("\nМаксимальная посл. - %d, начинается с %d элемента. \n", chain, i_max + 1);
		break;
	case 1:
		char name[11];

		printf("\n Введите название файла: ");
		scanf("%s", name);

		FILE* file = fopen(name, "w");

		fprintf(file, "Max chain = %d, starts from %d element.", chain, i_max + 1);

		fclose(file);
		printf("\nSaved!");
		break;
	}
}

void task1()
{
	setlocale(LC_ALL, "russian");

	printf("\n В заданном массиве из N элементов определить максимальную\n последовательность из положительных чисел\n");

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
			printf("\n В заданном массиве из N элементов определить максимальную\n последовательность из положительных чисел\n");
			break;
		case 2:
			int N;
			printf("\nВведите N: ");
			scanf("%d", &N);

			printf("В массиве %d элементов. \n", N);

			int* Array = new int[N]; // выделяем память под массив

			printf("\n 1 - Считать значения элементов из файла \n 2 - Сгенерировать случайные значения \n 3 - Ввести значения с клавиатуры \nВыбор: ");

			int choice_2_2;
			scanf("%d", &choice_2_2);

			switch (choice_2_2)
			{
			case 1:
				readArray_file(Array, N); // заполянем массив из файла
				break;
			case 2:
				for (int i = 0; i < N; i++) // рандомим массив
					Array[i] = -30 + rand() % 100; 
				break;
			case 3:
				printf("Введите массив: "); // вводим массив ручками
				for (int i = 0; i < N; i++) {
					printf("\n%d: ", i + 1);
					scanf("%d", &Array[i]);
				}
				break;
			}
		
			print_array(Array, N);
			printf("\n");

			printf("\n 1 - Вывести результат в файл \n 2 - Вывести результат в консоль \nВыбор: ");
			int choice_2_3;
			scanf("%d", &choice_2_3);
			
			max_chain(Array, N, choice_2_3);

			delete[] Array; // очищаем память

			printf("\n");
			system("pause");
			return;
			break;


		}
	} while (true);
}