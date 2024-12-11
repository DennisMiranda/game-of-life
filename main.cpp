#include <iostream>
#include <vector>
#include <fstream>
#include <conio.h> // Para kbhit() y getch()
#include <string>

using namespace std;

int contarVecinos(const vector<vector<int>> &tablero, int x, int y, int filas, int columnas); // Para contar vecinos vivos.
vector<vector<int>> siguienteGeneracion(const vector<vector<int>> &tablero, int filas, int columnas);
void guardarEstadisticas(int generacion, const vector<vector<int>> &tablero, int filas, int columnas);
void imprimirTablero(const vector<vector<int>> &tablero, int &generacion);
void editarTablero(vector<vector<int>> &tablero);
void cargarTableroDesdeArchivo(vector<vector<int>> &tablero, const string &archivo, int filas, int columnas);
void manejarPausa(bool &enEjecucion);

bool esEnteroPositivo(const std::string &entrada);
int leerEnteroPositivo(const std::string &mensaje);
void LimpiarPantalla();

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

void imprimirTablero(const vector<vector<int>> &tablero, int &generacion)
{
    //  LimpiarPantalla();

    cout << "Generación: " << generacion << endl;

    for (const auto &filas : tablero)
    {
        for (const auto &celulas : filas)
        {
            cout << (celulas ? "■ " : ". ");
        }
        cout << endl;
    }
}

void editarTablero(vector<vector<int>> &tablero)
{

    int cantidadVivas = 0;

    cout << "Ingresa la cantidad de celulas vivas: ";
    cin >> cantidadVivas;

    for (int i = 0; i < cantidadVivas; ++i)
    {
        int x, y;
        cout << "Ingrese la coordenada " << i + 1 << " (x y) de la celula viva: ";
        cin >> x >> y;
        tablero.push_back({x, y});
    }

    ofstream archivoEditado("Coordenadas.txt");
    if (archivoEditado.is_open())
    {
        for (size_t i = 0; i < tablero.size(); ++i)
        {
            archivoEditado << tablero[i][0] << " " << tablero[i][1] << endl;
        }
        archivoEditado.close();
        cout << "\nLas coordenadas fueron guardadas en 'Coordenadas.txt'." << endl;
    }
    else
    {
        cout << "No se pudo abrir el archivo para escribir." << endl;
    }
}

void cargarTableroDesdeArchivo(vector<vector<int>> &tablero, const string &archivo, int filas, int columnas)
{
    ifstream file(archivo); // Abrimos el archivo de entrada
    if (!file.is_open())
    {
        cerr << "Error al abrir el archivo." << endl;
        return;
    }

    int x, y;
    while (file >> x >> y)
    { // Leemos las coordenadas de dos en dos (x, y)
        if (x >= 0 && x < filas && y >= 0 && y < columnas)
        {
            tablero[x][y] = 1; // Marcamos la célula como viva
        }
    }

    file.close(); // Cerramos el archivo
}

// Función para manejar el estado de pausa
void manejarPausa(bool &enEjecucion)
{
    if (kbhit())
    {                         // Detecta si hay una tecla presionada
        char tecla = getch(); // Captura la tecla
        if (tecla == 'p')
        { // Si la tecla es 'p', cambia el estado
            enEjecucion = !enEjecucion;
            cout << (enEjecucion ? "Juego reanudado.\n" : "Juego en pausa. Presiona 'p' para reanudar.\n");
        }
    }
}

bool esEnteroPositivo(const std::string &entrada)
{
    // Verificar que la cadena no esté vacía y que todos sus caracteres sean dígitos
    if (entrada.empty())
        return false;
    for (char c : entrada)
    {
        if (!std::isdigit(c))
            return false;
    }
    return true;
}

int leerEnteroPositivo(const std::string &mensaje)
{
    std::string entrada;
    int numero;

    while (true)
    {
        std::cout << mensaje;
        std::cin >> entrada;

        if (esEnteroPositivo(entrada))
        {
            numero = std::stoi(entrada); // Convertir a entero
            if (numero > 0)              // Verificar que sea positivo
                return numero;
        }
        std::cout << "Por favor, ingrese un número entero positivo válido." << std::endl;
    }
}

void LimpiarPantalla()
{
    std::cout << "\033[2J\033[1;1H" << std::flush;
} // Limpia y posiciona el cursor