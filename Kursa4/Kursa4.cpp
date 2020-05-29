#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "task1.h"
#include "task2.h"

int main()
{
  setlocale(LC_ALL, "russian");
  
  system("cls");
  printf("Здравствуйте! \n");
  system("pause");

  do {
      system("cls");

      printf("Выберите задачу для решения: \n 1 - Обработка одномерных массивов \n 2 - Геометрия \n 3 - Сортировка матрицы \n 0 - Выход\nВыбор: ");
      int choice;
      scanf("%d", &choice);

      switch (choice)
      {
      case 1:
          task1();
          break;
      case 2:
          task2();
          break;
      case 3:
       //   task3();
          break;
      case 0:
          return 0;
          break;
      }

  } while (true);
}
