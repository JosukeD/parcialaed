#include <iostream>
#include <vector>

#define INF 10000000 // Definir un valor grande para representar el infinito

void floydWarshall(int** graph, int n) {
    int** dist = new int*[n];
    for (int i = 0; i < n; ++i) {
        dist[i] = new int[n];
        for (int j = 0; j < n; ++j) {
            dist[i][j] = graph[i][j];
        }
    }

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Imprimir la matriz de distancias
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (dist[i][j] == INF) {
                std::cout << "INF ";
            } else {
                std::cout << dist[i][j] << " ";
            }
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < n; ++i) {
        delete[] dist[i];
    }
    delete[] dist;
}

int main() {
    int n = 4;
    int** graph = new int*[n];
    for (int i = 0; i < n; ++i) {
        graph[i] = new int[n];
    }

    // Inicializar la matriz del grafo con valores
    graph[0][0] = 0;   graph[0][1] = 3;   graph[0][2] = INF; graph[0][3] = 7;
    graph[1][0] = 8;   graph[1][1] = 0;   graph[1][2] = 2;   graph[1][3] = INF;
    graph[2][0] = 5;   graph[2][1] = INF; graph[2][2] = 0;   graph[2][3] = 1;
    graph[3][0] = 2;   graph[3][1] = INF; graph[3][2] = INF; graph[3][3] = 0;

    floydWarshall(graph, n);

    for (int i = 0; i < n; ++i) {
        delete[] graph[i];
    }
    delete[] graph;

    return 0;
}
