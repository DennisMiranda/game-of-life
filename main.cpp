#include <iostream>
#include <vector>


using namespace std;


int contarVecinos(const vector<vector<int>> &tablero, int x, int y, int filas, int columnas); // Para contar vecinos vivos.

int main()
{

return 0;
}

int contarVecinos(const vector<vector<int>> &tablero, int x, int y, int filas, int columnas)
{ // para contar vecinos vivos.
    int count = 0;

    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (i == 0 && j == 0)
                continue; // No contar la celda actual

            int nx = x + i;
            int ny = y + j;

            // Verificar límites del tablero
            if (nx >= 0 && ny >= 0 && nx < filas && ny < columnas)
            {
                count += tablero[nx][ny];
            }
        }
    }

    return count;
}





    