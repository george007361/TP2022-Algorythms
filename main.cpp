﻿// Общие требования для всех задач
// Ввод/вывод отделены от решения.
// Не должно быть утечек памяти.
// Задача 1. «Представление графа».(5 баллов)
// Обязательная задача
// Дан базовый интерфейс для представления ориентированного графа:
// struct IGraph {
// virtual ~IGraph() {}
	
// 	// Добавление ребра от from к to.
// virtual void AddEdge(int from, int to) = 0;

// 	virtual int VerticesCount() const  = 0;

// virtual std::vector<int> GetNextVertices(int vertex) const = 0;
// virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
// };

// Необходимо написать несколько реализаций интерфейса:
// ListGraph, хранящий граф в виде массива списков смежности,
// MatrixGraph, хранящий граф в виде матрицы смежности,
// SetGraph, хранящий граф в виде массива хэш-таблиц/сбалансированных деревьев поиска,
// ArcGraph, хранящий граф в виде одного массива пар {from, to}.
// Также необходимо реализовать конструктор, принимающий const IGraph&. Такой конструктор должен скопировать переданный граф в создаваемый объект.
// Для каждого класса создавайте отдельные h и cpp файлы.
// Число вершин графа задается в конструкторе каждой реализации.

#include <iostream>

#include "ListGraph/ListGraph.h"
#include "MatrixGraph/MatrixGraph.h"
#include "SetGraph/SetGraph.h"
#include "ArcGraph/ArcGraph.h"

 bool testGraph(const int count)
 {
     ListGraph listG(count);
     listG.AddEdge(0, count - 1);
     for (int i = 1; i < count; i++)
     {
         listG.AddEdge(i - 1, i);
     }

     MatrixGraph matrixG(listG);
     SetGraph setG(matrixG);
     ArcGraph arcG(setG);

     arcG.equal(listG);

     return true;
 }

int main()
{
    std::cout << testGraph(8);
    return EXIT_SUCCESS;
}
