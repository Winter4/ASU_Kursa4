#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

void readArray_file(int* X, int* Y, int N)
{
	FILE* file;
	char name[11];
	do {
		printf("\n������� �������� �����: ");
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
	printf("\n�������: \n");
	for (int i = 0; i < 4; i++)
		printf("(%d, %d)\t", sqrX[i], sqrY[i]);

	printf("\n�����: ");
	for (int i = 0; i < N; i++)
		printf("\n%d - (%d, %d)", i + 1, X[i], Y[i]);
	printf("\n");
}

void nearest_dot(int* X, int* Y, int N, int sqrX[4], int sqrY[4], int choice)
{
	float distance = INT_MIN;
	int dotI, sqrI; // ����� ����� � ������� ��������, ������� ����� � �������� ������
	for (int i = 0; i < N; i++) 
		for (int j = 0; j < 4; j++) {
			float d = sqrt(powf(X[i] - sqrX[j], 2.0) + powf(Y[i] - sqrY[i], 2.0)); // ��������� distance
			if (d > distance) {
				distance = d;
				dotI = i;
				sqrI = j;
			}
		}

	switch (choice)
	{
	case 2:
		printf("\n����� %d ��������� � ������� �������� %d. ���������� - %.1f.", dotI + 1, sqrI + 1, distance);
		break;
	case 1:
		char name[11];

		printf("\n ������� �������� �����: ");
		scanf("%s", name);

		FILE* file = fopen(name, "w");

		fprintf(file, "The dot �%d is the nearest to sqr's top �%d. Distance = %.1f.", dotI + 1, sqrI + 1, distance);

		fclose(file);
		break;
	}
}

void task2()
{

	printf("\n ������ ���������� �������� � ���������� N �����.\n ���������� ����� �� �����, � ����� ������� �������� ����� ����� �����. \n");
	
	do {
		printf(" 1 - ������ � ������ \n 2 - ������� ������ \n 0 - ����� \n�����: ");

		int choice;
		scanf("%d", &choice);

		switch (choice) {
		case 0:
			return;
			break;
		case 1:
			printf("\n ������ ���������� �������� � ���������� N �����.\n ���������� ����� �� �����, � ����� ������� �������� ����� ����� �����. \n");
			break;
		case 2:
			int N;
			printf("\n������� N: ");
			scanf("%d", &N);

			int* X = new int[N]; // ������� �����
			int* Y = new int[N];
			int sqrX[4] = { 3, 3, 6, 6 }, sqrY[4] = { 1, 4, 4, 1 }; // ������� ������ ��������

			printf("\n 1 - ������� ���������� �� ����� \n 2 - ������������� ��������� �������� \n 3 - ������ �������� � ���������� \n�����: ");

			int choice_2_2;
			scanf("%d", &choice_2_2);

			switch (choice_2_2)
			{
			case 1:
				printf("\n���������� ������ ���� �������� ������ (X Y). \n");
				system("pause");
				readArray_file(X, Y, N); // ��������� ������ �� �����
				break;
			case 2:
				for (int i = 0; i < N; i++) { // �������� ������
					X[i] = -30 + rand() % 100;
					Y[i] = -30 + rand() % 100;
				}
				break;
			case 3:
				printf("\n������� ������ \n"); // ������ ������ �������
				for (int i = 0; i < N; i++) {
					printf(" %d - X Y: ", i + 1);
					scanf("%d%d", &X[i], &Y[i]);
				}
				break;
			}
			print_dots(X, Y, N, sqrX, sqrY);

			printf("\n 1 - ������� ��������� � ���� \n 2 - ������� ��������� � ������� \n�����: ");
			int choice_2_3;
			scanf("%d", &choice_2_3);

			nearest_dot(X, Y, N, sqrX, sqrY, choice_2_3);

			delete[] X; // ������� ������
			delete[] Y;

			printf("\n");
			system("pause");
			return;
			break;
		}
	} while (true);
}
