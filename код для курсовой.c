#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <stdlib.h>
#define PI 3.14159265358979323846
#define SCREENW 60
#define SCREENH 40

typedef double (*TFunc)(double);

double Y(double x) {
	double y;
	if (x == 0) {
		return INFINITY; // Значение при x = 0
	}
	y = cos(2.0 / x) - 2.0 * sin(1.0 / x) + (1.0 / x); 
	return y;
}

double V(double x) {
	double v;
	if (x > PI) {
		v = pow(fabs(cos(x)), x);
		return v;
	}
	if (x <= PI) {
		v = pow(x, cos(x));
		return v;
	}
	return 0; 
}

void plot(double x0, double x1, TFunc f) {
	char screen[SCREENW][SCREENH];
	double x, y[SCREENW];
	double ymin = 0, ymax = 0;
	double hx, hy;
	int i, j;
	int xz, yz;

	hx = (x1 - x0) / (SCREENW - 1);

	for (i = 0, x = x0; i < SCREENW; ++i, x += hx) {
		y[i] = f(x);
		if (y[i] < ymin) ymin = y[i];
		if (y[i] > ymax) ymax = y[i];
	}

	hy = (ymax - ymin) / (SCREENH - 1);
	yz = (int)floor(ymax / hy + 0.5);
	xz = (int)floor((0. - x0) / hx + 0.5);

	for (j = 0; j < SCREENH; ++j)
		for (i = 0; i < SCREENW; ++i) {
			if (j == yz && i == xz) screen[i][j] = '+';
			else if (j == yz) screen[i][j] = '-';
			else if (i == xz) screen[i][j] = '|';
			else screen[i][j] = ' ';
		}

	for (i = 0; i < SCREENW; ++i) {
		j = (int)floor((ymax - y[i]) / hy + 0.5);
		screen[i][j] = '*';
	}

	for (j = 0; j < SCREENH; ++j) {
		for (i = 0; i < SCREENW; ++i) putchar(screen[i][j]);
		putchar('\n');
	}
}
void tabul(double xn, double xk, double h, double (*function)(double), char sn, char sk, int outputChoice) {
	if (h == 0) { // Проверка на нулевой шаг
		printf("Шаг не может быть равен нулю\n");
		return;
	}

	if (outputChoice != 1 && outputChoice != 2) {
		printf("Некорректный выбор вывода результатов\n");
		return;
	}

	if (outputChoice == 1) {
		// Вывод на консоль
		printf("+--------+------------+\n");
		printf("|   x    |    f(x)    |\n");
		printf("+--------+------------+\n");
	}

	FILE* file = NULL; // Указатель на файл
	char filename[] = "results.txt"; // Имя файла для сохранения

	if (outputChoice == 2) {
		printf("результаты выведены в файл с названием 'results.txt' расположенный в корневой папке\n");
		// Открытие файла для записи
		file = fopen(filename, "w");

		if (file == NULL) {
			printf("Ошибка при открытии файла\n");
			return;
		}

		// Верхние границы таблицы для файла
		fprintf(file, "+--------+------------+\n");
		fprintf(file, "|   x    |    f(x)    |\n");
		fprintf(file, "+--------+------------+\n");
	}

	// Табулирование функции
	if (sn == '[' && sk == ']') {
		for (double x = xn; x <= xk; x += h) {
			double result = function(x);
			if (outputChoice == 1) {
				printf("| %lf | %lf |\n", x, result);
			}
			else {
				fprintf(file, "| %lf | %lf |\n", x, result);
			}
		}
	}
	else if (sn == '[' && sk == ')') {
		for (double x = xn; x < xk; x += h) {
			double result = function(x);
			if (outputChoice == 1) {
				printf("| %lf | %lf |\n", x, result);
			}
			else {
				fprintf(file, "| %lf | %lf |\n", x, result);
			}
		}
	}
	else if (sn == '(' && sk == ']') {
		for (double x = xn + h; x <= xk; x += h) {
			double result = function(x);
			if (outputChoice == 1) {
				printf("| %lf | %lf |\n", x, result);
			}
			else {
				fprintf(file, "| %lf | %lf |\n", x, result);
			}
		}
	}
	else if (sn == '(' && sk == ')') {
		for (double x = xn + h; x < xk; x += h) {
			double result = function(x);
			if (outputChoice == 1) {
				printf("| %lf | %lf |\n", x, result);
			}
			else {
				fprintf(file, "| %lf | %lf |\n", x, result);
			}
		}
	}

	// Нижние границы таблицы
	if (outputChoice == 1) {
		printf("+--------+------------+\n");
	}
	else {
		fprintf(file, "+--------+------------+\n");
	}

	if (file != NULL) {
		fclose(file); // Закрытие файла
	}
}


int main() {
	setlocale(LC_ALL, "rus");
	int argum;
	double znachx, minx, maxx, shag;
	char skobka1, skobka2;
	printf("-----------------------------------\n");
	printf("Программа для работы с функциями.\n");
	printf("Cделала:Распевалова Ирина Сергеевна\n");
	printf("Группа:БИСТ-234\n");
	printf("-----------------------------------\n");

	while (1) {
		printf("введите номер требуемого действия из списка:\n");
		printf("1. Значение функции Y(x) при заданном x\n");
		printf("2. Значение функции V(x) при заданном x\n");
		printf("3. Значение функции Y(x) при заданном интервале/полуинтервале/отрезке с шагом\n");
		printf("4. Значение функции V(x) при заданном интервале/полуинтервале/отрезке с шагом\n");
		printf("5. График функции Y(x) на промежутке\n");
		printf("6. График функции V(x) на промежутке\n");
		printf("7. Завершение работы\n");
		printf(":");
		scanf("%i", &argum);
		getchar();
		int outputChoice;
		switch (argum) {
		case 1:
			printf("Значение x:");
			scanf("%lf", &znachx);
			printf("Y(%lf)=%lf\n", znachx, Y(znachx));
			break;
		case 2:
			printf("Значение x:");
			scanf("%lf", &znachx);
			printf("V(%lf)=%lf\n", znachx, V(znachx));
			break;
		case 3:
			printf("Выберите способ вывода результатов:\n");
			printf("1. Вывести на консоль\n");
			printf("2. Сохранить в файл\n");
			printf("Ваш выбор: ");
			scanf("%d", &outputChoice);
			printf("Введите промежуток в формате [/(x1;x2)/] :");
			scanf(" %c%lf ; %lf%c", &skobka1, &minx, &maxx, &skobka2);
			printf("Введите шаг: ");
			scanf("%lf", &shag);
			printf("Таблица значений Y(x):\n");
			tabul(minx, maxx, shag, Y, skobka1, skobka2, outputChoice);
			break;
		case 4:
			printf("Выберите способ вывода результатов:\n");
			printf("1. Вывести на консоль\n");
			printf("2. Сохранить в файл\n");
			printf("Ваш выбор: ");
			scanf("%d", &outputChoice);
			printf("Введите промежуток в формате [/(x1;x2)/] :");
			scanf(" %c%lf ; %lf%c", &skobka1, &minx, &maxx, &skobka2);
			printf("Введите шаг: ");
			scanf("%lf", &shag);
			printf("Таблица значений V(x):\n");
			tabul(minx, maxx, shag, V, skobka1, skobka2, outputChoice);
			break;
		case 5:
			printf("Введите промежуток в формате 'x1 x2' ");
			scanf("%lf %lf", &minx, &maxx);
			plot(minx, maxx, Y);
			break;
		case 6:
			printf("Введите промежуток в формате 'x1 x2' ");
			scanf("%lf %lf", &minx, &maxx);
			plot(minx, maxx, V);
			break;
		case 7:
			return 0;
		default:
			printf("!Введено отсутствующее значение!\n");
			break;
		}
	}
}