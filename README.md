# Juego de la Vida en C++

## Video del Juego de la Vida



Un video sobre el Juego de la Vida.(click a la imagen)
[![Juego de la Vida](https://img.youtube.com/vi/omMcrvVGTMs/maxresdefault.jpg)](https://youtu.be/omMcrvVGTMs?si=H_4s3ekWBQBgb6yf)


## Descripción

Bienvenido al Juego de la Vida, una simulación de autómata celular inventada por el matemático John Conway. En este juego, las células en un tablero de dos dimensiones nacen, mueren o permanecen vivas según reglas simples que se aplican a cada célula.

## Reglas del Juego

1. **Supervivencia**: Una célula viva con dos o tres vecinos vivos sigue viva en la siguiente iteración.
2. **Muerte por soledad**: Una célula viva con menos de dos vecinos vivos muere (por soledad).
3. **Muerte por sobrepoblación**: Una célula viva con más de tres vecinos vivos muere (por sobrepoblación).
4. **Nacimiento**: Una célula muerta con exactamente tres vecinos vivos se "revive" (nace).

## Estructura del Proyecto

El código está escrito en C++ y se organiza en un solo archivo principal `main.cpp`. El juego utiliza archivos de texto para cargar las coordenadas iniciales del tablero. La simulación se actualiza en cada iteración y se muestra en la consola.

### Archivos del Proyecto

- `main.cpp`: Contiene el código principal del juego y su ejecución.
- `coordenadas1.txt` , `coordenadas2.txt` y `coordenadas3.txt`: son las predeterminadas.
- `.gitignore` se usa para decirle a Git qué archivos y carpetas no deben ser incluidos en el repositorio. Esto es útil para evitar subir archivos temporales, archivos de configuración local o cualquier archivo generado automáticamente que no sea relevante para el código fuente.
- `coordenadas.txt`: Archivo de texto con las coordenadas Personalizadas iniciales de las células vivas.
- `configuracionTablero.txt`: Archivo de texto que guarda el tamaño del tablero, que son filas y columnas.
- `estadisticas.txt`: Archivo de texto que almacena las estadísticas del programa, como el número de generaciones, el número de células vivas y la fecha y hora en que se ejecutó el programa.



## CÓMO JUGAR EL JUEGO DE LA VIDA
Cuando ejecutes el programa, verás el siguiente menú principal:

 ```
  BIENVENIDOS AL JUEGO DE LA VIDA

    Menú    
1. Jugar Game of Life
2. Personalizar Coordenadas
3. Salir

Seleccione una opción (1-3):
```
### Opciones del menú 
#### 1. Jugar Game of Life

Selecciona la opción `1` para iniciar la simulación del juego.
El programa te presentará un menú de patrones donde podrás elegir entre diferentes configuraciones predeterminadas del tablero:
1. Nave Espacial Ligera: Una nave espacial ligera que se desplaza por el tablero.

  ![Nave Ligera](.\docs\1.NaveEspacial.gif)

2. Pistola de Gosper: Un patrón que genera una pistola de Gosper.

  ![Nave Ligera](.\docs\2.PistolaGosper.gif)

3. Estático: Un patrón estático predefinido.

  ![Estatico](.\docs\3.Estatico.gif)

4. Personalizado: Carga una configuración personalizada desde un archivo de texto.
Después de elegir un patrón, el programa comenzará a ejecutar la simulación del Juego de la Vida, mostrando las generaciones en la consola. Cada generación se mostrará en el tablero hasta que no haya más células vivas o se presione la tecla 'S' para salir, este programa tiende a generaciones infinitas.



#### 2. Personalizar Coordenadas
Selecciona la opción `2` para definir las coordenadas iniciales del tablero.
El programa te pedirá que ingreses las dimensiones del tablero (número de filas y columnas) y la cantidad de células vivas.
Luego, podrás ingresar las coordenadas (x, y) de cada célula viva. Las coordenadas se validarán para asegurarse de que estén dentro del rango del tablero.
Después de ingresar las coordenadas, el tablero se guardará en un archivo de texto llamado Coordenadas.txt, que se usará en el futuro para cargar la configuración personalizada en el juego.


#### 3. Salir
Selecciona la opción `3` para cerrar el programa.

### Controles adicionales
Validación de entrada: El programa verifica que solo ingreses opciones válidas (1, 2 o 3). Si introduces algo incorrecto, te pedirá que vuelvas a intentarlo.
Interacción personalizada: Si seleccionas "Personalizar Coordenadas", podrás definir la disposición inicial de las células vivas en el tablero.



## Aqui hay unas Coordenadas sugeridas.

A continuación, se presentan algunas figuras clásicas para usar como configuración inicial en el Juego de la Vida.


### Figura Pentadecathlon

Estas coordenadas forman un patrón llamado **Pentadecathlon**, que es un ciclo estable con 15 celdas. Es un ciclo que se mantiene en su forma sin cambiar con el paso del tiempo.


```
0 1
0 2
1 0
1 3
2 1
2 2
3 1
3 2
4 0
4 3
5 1
5 2
``` 
![Pentadeclathon](.\docs\1.SPenta.gif)


### Figura Glider Gun

El **Glider Gun** es una figura que produce un glider, el cual se desplaza a través de la cuadrícula.



```
1 2
1 5
2 1
3 1
3 5
4 1
4 2
4 3
4 4
```
![Glider Gun](.\docs\2.SGliderGun.gif)

---












