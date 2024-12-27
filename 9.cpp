#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <ctime>

#define MAX_VERTICES 10  // Максимальное количество вершин в графе
#define INF 1000000      // Константа для обозначения бесконечности

// 1. Генерация матрицы смежности
void generateAdjacencyMatrix(int matrix[MAX_VERTICES][MAX_VERTICES], int vertices) {
    srand(time(NULL));
    for (int i = 0; i < vertices; i++) {
        for (int j = i; j < vertices; j++) {
            if (i == j) {
                matrix[i][j] = 0;
            } else {
                int edge = rand() % 2; // Случайное ребро 0 или 1
                matrix[i][j] = edge;
                matrix[j][i] = edge;
            }
        }
    }
}

// Вывод матрицы смежности
void printAdjacencyMatrix(int matrix[MAX_VERTICES][MAX_VERTICES], int vertices) {
    std::cout << "Матрица смежности:\n";
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}

// 2. Поиск расстояний от стартовой вершины с помощью BFS для матрицы смежности
void bfsDistanceMatrix(int matrix[MAX_VERTICES][MAX_VERTICES], int vertices, int start) {
    std::vector<int> distance(vertices, INF);
    std::queue<int> queue;

    distance[start] = 0;
    queue.push(start);

    while (!queue.empty()) {
        int current = queue.front();
        queue.pop();

        for (int i = 0; i < vertices; i++) {
            if (matrix[current][i] == 1 && distance[i] == INF) {
                distance[i] = distance[current] + 1;
                queue.push(i);
            }
        }
    }

    std::cout << "\nРасстояния от вершины " << start << " (матрица смежности):\n";
    for (int i = 0; i < vertices; i++) {
        std::cout << "Вершина " << i << ": " << (distance[i] == INF ? -1 : distance[i]) << "\n";
    }
}

// 3. Генерация списка смежности из матрицы смежности
void generateAdjacencyList(int matrix[MAX_VERTICES][MAX_VERTICES], int vertices, std::vector<std::vector<int>> &adjList) {
    adjList.resize(vertices);
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (matrix[i][j] == 1) {
                adjList[i].push_back(j);
            }
        }
    }
}

// 4. Поиск расстояний от стартовой вершины с помощью BFS для списка смежности
void bfsDistanceAdjList(const std::vector<std::vector<int>> &adjList, int vertices, int start) {
    std::vector<int> distance(vertices, INF);
    std::queue<int> queue;

    distance[start] = 0;
    queue.push(start);

    while (!queue.empty()) {
        int current = queue.front();
        queue.pop();

        for (int neighbor : adjList[current]) {
            if (distance[neighbor] == INF) {
                distance[neighbor] = distance[current] + 1;
                queue.push(neighbor);
            }
        }
    }

    std::cout << "\nРасстояния от вершины " << start << " (список смежности):\n";
    for (int i = 0; i < vertices; i++) {
        std::cout << "Вершина " << i << ": " << (distance[i] == INF ? -1 : distance[i]) << "\n";
    }
}

int main() {
    int vertices = MAX_VERTICES;

    // Матрица смежности
    int matrix[MAX_VERTICES][MAX_VERTICES];
    generateAdjacencyMatrix(matrix, vertices);
    printAdjacencyMatrix(matrix, vertices);
    bfsDistanceMatrix(matrix, vertices, 0);

    // Список смежности
    std::vector<std::vector<int>> adjList;
    generateAdjacencyList(matrix, vertices, adjList);
    bfsDistanceAdjList(adjList, vertices, 0);

    return 0;
}
