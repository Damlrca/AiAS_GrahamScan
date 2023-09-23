## AiAS_GrahamScan

Лабораторная работа по курсу "Алгоритмы и анализ сложности".
Алгоритм Грэхема: с использованием быстрой сортировки и с использованием сортировки, основанной на АВЛ-дереве.

#### Постановка задачи (Построение выпуклой оболочки n точек на плоскости):
Для точек $a_1, ..., a_n$, где $n\geq1$, $a_i=(a_{i,1},a_{i,2})\in R^2$ при $i=1,...,n$, указать вершины $b_1,...,b_m$ выпуклой оболочки $Conv(a_1,...,a_n)$ в порядке их встречи при движении по ее границе.

#### Цель лабораторной работы:
Сравнение и анализ двух алгоритмов, решающих задачу: алгоритм Грэхема с использованием быстрой сортировки, алгоритм Грэхема с использованием сортировки, основанной на АВЛ-дереве.

#### План лабораторной работы:

1. Первая программа: чтение из файла входных данных, на выходе - два файла с результатами работы алгоритмов и временем их работы.
2. Вторая программа: проведение экспериментов:
	- Генератор тестов для проведения экспериментов, в котором можно выбрать:
		- Кол-во точек $n$ в исходном массиве $a$,
		- Натуральные числа $q$ и $w$,
		- Режимы: (1) псевдослучайные точки в прямоугольнике со сторонами $q$ и $w$, (2) псеводслучаные точки на границе (на сторонах) этого прямоуголника.
	- Провести следующие эксперименты:
		- $q = 10^6, w = 10^6$, $n = 1, ..., 10^6+1$ с шагом $10^4$ в режимах (1) и (2). Построить графики $T_A(n)$ и $T_B(n)$.
		- $q = w = 0, ..., 10^6$ с шагом $10^4$, $n = 10^6$ в режимах (1) и (2). Построить графики $T_A(q)$ и $T_B(q)$.
3. Отчет, состоящий из следующих разделов:
	- Описание алгоритмов,
	- Обоснование теоретических оценок временной сложности алгоритмов,
	- Описание реализующих алгоритмы программ,
	- Проведенные эксперименты (и графики результатов),
	- Выводы.

#### Структура репозитория:

- /Utils:
	- Utils - общие функции, необходимые для реализации алгоритмов.
	- Utils_IO - функции для ввода-вывода
	- Utils_TestGen - функции для генерации тестов
- /QuickSort
	- QuickSort - реализация быстрой сортировки
- /AVLTree
	- AVLTree - реализация класса АВЛ-дерева
- /GrahamScan
	- GrahamScan - реализация алгоритма Грэхема
- /Program1
	- Program1 - реализация первой программы
- /Program2
	- Program2 - реализация второй программы
- /TestingSorts
	- TestingSorts - тестировние сортировок
- /GraphPlotter
	- GraphPlotter - программа на python для построения графиков
