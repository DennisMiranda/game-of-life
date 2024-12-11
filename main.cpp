#include <iostream>
#include <vector>
#include <fstream>

using namespace std;


int contarVecinos(const vector<vector<int>> &tablero, int x, int y, int filas, int columnas); // Para contar vecinos vivos.
vector<vector<int>> siguienteGeneracion(const vector<vector<int>> &tablero, int filas, int columnas);

void guardarEstadisticas(int generacion, const vector<vector<int>> &tablero, int filas, int columnas);


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


vector<vector<int>> siguienteGeneracion(const vector<vector<int>> &tablero, int filas, int columnas)
{
    vector<vector<int>> nuevoTablero(filas, vector<int>(columnas, 0)); // Usar tamaño de tablero

    for (int i = 0; i < filas; ++i)
    {
        for (int j = 0; j < columnas; ++j)
        {
            int vecinos = contarVecinos(tablero, i, j, filas, columnas);

            // Aplicar las reglas del Juego de la Vida
            if (tablero[i][j] == 1)
            { // Célula viva
                if (vecinos == 2 || vecinos == 3)
                {
                    nuevoTablero[i][j] = 1; // Permanece viva
                }
            }
            else
            { // Célula muerta
                if (vecinos == 3)
                {
                    nuevoTablero[i][j] = 1; // Revive
                }
            }
        }
    }

    return nuevoTablero;
}

void guardarEstadisticas(int generacion, const vector<vector<int>> &tablero, int filas, int columnas)
{
    ofstream file("estadisticasprueba.txt", ios::app);
    if (file.is_open())
    {
        file << "Generación: " << generacion << endl;
        int celulasvivas = 0;
        for (int i = 0; i < filas; ++i)
        {
            for (int j = 0; j < columnas; ++j)
            {
                if (tablero[i][j] == 1)
                {
                    celulasvivas++;
                }
            }
        }
        file << "Células vivas: " << celulasvivas << endl;
        file << "--------------------------\n";
        file.close();
    }
}    