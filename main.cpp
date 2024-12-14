#include <iostream>
#include <vector>
#include <fstream>
#include <conio.h> // Para kbhit() y getch()
#include <string>
#include <chrono>
#include <thread>
#include <cctype> // Para std::isdigit

using namespace std;

int contarVecinos(const vector<vector<int>> &tablero, int x, int y, int filas, int columnas); // Para contar vecinos vivos.
vector<vector<int>> siguienteGeneracion(const vector<vector<int>> &tablero, int filas, int columnas);
void guardarEstadisticas(int generacion, const vector<vector<int>> &tablero, int filas, int columnas);
void imprimirTablero(const vector<vector<int>> &tablero, int &generacion);
void editarTablero(vector<vector<int>> &tablero);
void cargarTableroDesdeArchivo(vector<vector<int>> &tablero, const string &archivo, int filas, int columnas);
void manejarPausa(bool &enEjecucion);
bool esEnteroPositivo(const string &entrada);
int leerEnteroPositivo(const string &mensaje);
void LimpiarPantalla();

int main()
{
    int opcion = 0;

    do
    {
        cout << "  JUEGO DE LA VIDA " << endl;
        cout << "\n--- Menú ---\n";
        cout << "1. Jugar Juego de la vida\n";
        cout << "2. Personalizar Coordenadas\n";
        cout << "3. Salir\n";

        string entrada;
        cout << "Seleccione una opción (1-3): ";
        cin >> entrada;

        // Validar que la entrada sea un número entero positivo
        if (!esEnteroPositivo(entrada) || entrada.size() > 1 || (entrada[0] < '1' || entrada[0] > '3'))
        {
            cout << "Por favor, ingrese un número válido (1, 2 o 3)." << endl;
            continue;
        }

        opcion = stoi(entrada); // Convertir la entrada a entero

        switch (opcion)
        {
        case 1:
        {
            int generacion = 0;
            int filas = leerEnteroPositivo("Ingrese el número de filas (entero positivo): ");
            int columnas = leerEnteroPositivo("Ingrese el número de columnas (entero positivo): ");
            vector<vector<int>> tablero(filas, vector<int>(columnas, 0));
            cargarTableroDesdeArchivo(tablero, "Coordenadas.txt", filas, columnas);

            while (true)
            {
                generacion++;
                imprimirTablero(tablero, generacion);                    // Llamada a la función que imprimirá el tablero.
                tablero = siguienteGeneracion(tablero, filas, columnas); // Llamada para calcular la siguiente generación.
                this_thread::sleep_for(chrono::milliseconds(500));       // Pausa entre generaciones

                if (generacion == 20)
                    break;
            }

            guardarEstadisticas(generacion, tablero, filas, columnas);

            break;
        }
        case 2:
        {
            int filas = leerEnteroPositivo("Ingrese el número de filas (entero positivo): ");
            int columnas = leerEnteroPositivo("Ingrese el número de columnas (entero positivo): ");
            vector<vector<int>> tablero(filas, vector<int>(columnas, 0));
            editarTablero(tablero);

            break;
        }
        case 3:
            cout << "\nSaliendo del programa." << endl;
            break;
        }

    } while (opcion != 3);

    return 0;
}


int contarVecinos(const vector<vector<int>> &tablero, int x, int y, int filas, int columnas)
{
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
    vector<vector<int>> nuevoTablero(filas, vector<int>(columnas, 0));

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
    LimpiarPantalla();

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
    ifstream file(archivo);
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

    file.close();
}

void manejarPausa(bool &enEjecucion)
{
    if (kbhit())
    {                         // Detecta si hay una tecla presionada
        char tecla = getch(); // Captura la tecla
        if (tecla == 'p')
        { // Si la tecla es 'p',cambia el estado
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
        if (!isdigit(c))
            return false;
    }
    return true;
}

int leerEnteroPositivo(const string &mensaje)
{
    string entrada;
    int numero;

    while (true)
    {
        std::cout << mensaje;
        std::cin >> entrada;

        if (esEnteroPositivo(entrada))
        {
            numero = stoi(entrada); // Convertir a entero
            if (numero > 0)         // Verificar que sea positivo
                return numero;
        }
        cout << "Por favor, ingrese un número entero positivo válido." << endl;
    }
}

void LimpiarPantalla()
{
    cout << "\033[2J\033[1;1H" << flush;
}