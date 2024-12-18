#include <iostream>
#include <vector>
#include <fstream>
#include <conio.h> // Para kbhit() y getch()
#include <string>
#include <chrono>
#include <thread>
#include <cctype> // Para isdigit

using namespace std;

int contarVecinos(const vector<vector<int>> &tablero, int x, int y, int filas, int columnas);
vector<vector<int>> siguienteGeneracion(const vector<vector<int>> &tablero, int filas, int columnas);
void guardarEstadisticas(int generacion, const vector<vector<int>> &tablero, int filas, int columnas);
void imprimirTablero(const vector<vector<int>> &tablero, int &generacion);
void editarTablero(vector<vector<int>> &tablero);
void cargarTableroDesdeArchivo(vector<vector<int>> &tablero, const string &archivo, int filas, int columnas);
void manejarPausaAndStop(bool &enEjecucion);
bool esEnteroPositivo(const string &entrada);
int leerEnteroEnRango(int min, int max);
void LimpiarPantalla();
void iniciarJuego();
void cargarConfigDesdeArchivo(const string &archivo, int &filas, int &columnas);

int main()
{
    int opcion = 0;
    bool mostrarBienvenida = true;
    do
    {
        if (mostrarBienvenida)
        {
            cout << "\n  BIENVENIDOS AL JUEGO DE LA VIDA " << endl;
            mostrarBienvenida = false;
        }

        cout << "\n    Menú    \n";
        cout << "1. Jugar Game of life\n";
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
            iniciarJuego();

            break;
        }
        case 2:
        {
            vector<vector<int>> tablero(0, vector<int>(0, 0));
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
    int filas = 0, columnas = 0;

    // Pedir el tamaño de filas y columnas con validación

    cout << "Ingrese  la cantidad de filas: " << endl;
    filas = leerEnteroEnRango(1, 40); // Usamos leerEnteroEnRango para validar el tamaño
    cout << "Ingrese  la cantidad de columnas: " << endl;
    columnas = leerEnteroEnRango(1, 40); // Rango de 1 a 100 como ejemplo

    // Guardar la configuración en un archivo
    ofstream archivoConfigTablero("ConfiguracionTablero.txt");
    if (archivoConfigTablero.is_open())
    {
        archivoConfigTablero << filas << " " << columnas << endl;
        archivoConfigTablero.close();
        cout << "\nEl tablero fue guardado en 'ConfiguracionTablero.txt'." << endl;
    }
    else
    {
        cout << "No se pudo abrir el archivo para escribir." << endl;
    }

    // Pedir la cantidad de células vivas
    cout << "Ingrese  la cantidad de celulas vivas: " << endl;
    cantidadVivas = leerEnteroEnRango(1, filas * columnas); // Validar que esté entre 1 y el número total de celdas

    // Limpiar el buffer de entrada antes de leer con getline
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Pedir las coordenadas de las células vivas
    for (int i = 0; i < cantidadVivas; ++i)
    {
        string entrada;
        int x = -1, y = -1;

        cout << endl;
        bool coordenadaValida = false;

        // Validar las coordenadas
        while (!coordenadaValida)
        {
            cout << "Ingrese la coordenada (x y) de la celula viva " << i + 1 << ": ";

            getline(cin, entrada); // Leer toda la línea

            // Si la entrada está vacía, continuar
            if (entrada.empty())
                continue;

            // Comprobar que el formato sea válido (solo números)
            size_t espacio = entrada.find(" ");
            if (espacio != string::npos)
            {
                string xStr = entrada.substr(0, espacio);
                string yStr = entrada.substr(espacio + 1);

                if (esEnteroPositivo(xStr) && esEnteroPositivo(yStr))
                {
                    x = stoi(xStr);
                    y = stoi(yStr);

                    // Verificar que las coordenadas estén dentro del rango
                    if (x >= 0 && x < filas && y >= 0 && y < columnas)
                    {
                        coordenadaValida = true;
                        tablero.push_back({x, y}); // Guardar las coordenadas
                    }
                    else
                    {
                        cout << "Coordenadas fuera de rango. Intenta de nuevo.\n";
                    }
                }
                else
                {
                    cout << "Solo se permiten números enteros positivos. Intenta de nuevo.\n";
                }
            }
            else
            {
                cout << "Formato incorrecto. Debes ingresar dos números separados por espacio.\n";
            }
        }
    }

    // Guardar las coordenadas en un archivo
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

    tablero.resize(filas, vector<int>(columnas, 0));

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

void manejarPausaAndStop(bool &enEjecucion)
{
    if (kbhit()) // Detecta si hay una tecla presionada
    {
        char tecla = getch(); // Captura la tecla
        if (tecla == 'p')
        { // Si la tecla es 'p',cambia el estado
            enEjecucion = !enEjecucion;
            cout << (enEjecucion ? "Juego reanudado.\n" : "Juego en pausa. Presiona 'p' para reanudar.\n");
        }
        else if (tecla == 's')
        {
            enEjecucion = !enEjecucion;
            cout << (enEjecucion ? "Juego Cancelado!!!. \n" : "Cancelado Volver a Iniciar !!! \n");
             iniciarJuego();
        }
    }
}

bool esEnteroPositivo(const string &entrada)
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

int leerEnteroEnRango(int min, int max)
{
    string entrada;
    int numero = -1;
    bool mostrarValidacion = false;

    while (true)
    {
        if (mostrarValidacion)
        {
            cout << "Ingrese un número entero positivo entre " << min << " y " << max << ": ";
        }
        cin >> entrada;

        if (esEnteroPositivo(entrada))
        {
            numero = stoi(entrada);
            if (numero >= min && numero <= max)
            {
                break;
            }
        }

        cout << "Entrada inválida. Intenta de nuevo.\n";
        mostrarValidacion = true;
    }

    return numero;
}

void LimpiarPantalla()

{
    cout << "\033[2J\033[1;1H" << flush;
}

void iniciarJuego()
{
    int generacion = 1;
    int filas = 0;
    int columnas = 0;
    vector<vector<int>> tablero(filas, vector<int>(columnas, 0));

    // Mostrar el menú antes de la validación
    cout << "\n   Menú de patrones: " << endl
         << "1. Nave Ligera" << endl
         << "2. Pistola de Gosper" << endl
         << "3. Estatico" << endl
         << "4. Personalizado" << endl
         << "Seleccione una opción (1-4): ";

    // Usamos la función leerEnteroEnRango para elegir una opción válida entre 1 y 4
    int figura = leerEnteroEnRango(1, 4);

    switch (figura)
    {
    case 1:
        filas = 15;
        columnas = 20;
        cargarTableroDesdeArchivo(tablero, "Coordenadas1.txt", filas, columnas);
        break;
    case 2:
        filas = 20;
        columnas = 38;
        cargarTableroDesdeArchivo(tablero, "Coordenadas2.txt", filas, columnas);
        break;
    case 3:
        filas = 18;
        columnas = 20;
        cargarTableroDesdeArchivo(tablero, "Coordenadas3.txt", filas, columnas);
        break;
    case 4:
        cargarConfigDesdeArchivo("ConfiguracionTablero.txt", filas, columnas);
        cargarTableroDesdeArchivo(tablero, "Coordenadas.txt", filas, columnas);
        break;
    default:
        // Aunque este caso nunca debería ser alcanzado por la validación previa
        cout << "La opción ingresada no es válida" << endl;
        return;
    }

    bool enEjecucion = true;
    while (true)
    {
        manejarPausaAndStop(enEjecucion);
        if (!enEjecucion)
        {
            this_thread::sleep_for(chrono::milliseconds(500));
            continue;
        }

        imprimirTablero(tablero, generacion);                    // Llamada a la función que imprimirá el tablero.
        tablero = siguienteGeneracion(tablero, filas, columnas); // Llamada para calcular la siguiente generación.
        generacion++;

        this_thread::sleep_for(chrono::milliseconds(500));

        bool existenCelulasVivas = false;
        for (int i = 0; i < filas; i++)
        {
            for (int j = 0; j < columnas; j++)
            {
                if (tablero[i][j] == 1)
                {
                    existenCelulasVivas = true;
                    break;
                }
            }
            if (existenCelulasVivas)
            {
                break;
            }
        }
        if (!existenCelulasVivas || generacion == 50)
        {
            break;
        }
    }
    imprimirTablero(tablero, generacion); // Llamada a la función que imprimirá la última generación
    guardarEstadisticas(generacion, tablero, filas, columnas);
}

void cargarConfigDesdeArchivo(const string &archivo, int &filas, int &columnas)
{
    ifstream archivoConfig(archivo);
    if (!archivoConfig.is_open())
    {
        cerr << "Error al abrir el archivo." << endl;
        return;
    }

    archivoConfig >> filas >> columnas;

    archivoConfig.close();
}