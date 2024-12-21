# Juego de la Vida en C++

## Video del Juego de la Vida


Puedes verlo haciendo clic en la imagen.
Un video sobre el Juego de la Vida. 
[![Juego de la Vida](https://img.youtube.com/vi/omMcrvVGTMs/maxresdefault.jpg)](https://youtu.be/omMcrvVGTMs?si=H_4s3ekWBQBgb6yf)


Este proyecto implementa el **Juego de la Vida** de Conway en C++.

## Descripción

El **Juego de la Vida** es un autómata celular inventado por el matemático John Conway. Es un modelo matemático que simula la evolución de un conjunto de células (representadas como una cuadrícula). Cada célula puede estar viva o muerta, y en cada iteración, su estado depende del número de células vecinas vivas. El juego tiene un conjunto de reglas simples que determinan cómo cambian las células a lo largo del tiempo.

## Reglas del Juego

1. **Supervivencia**: Una célula viva con dos o tres vecinos vivos sigue viva en la siguiente iteración.
2. **Muerte por soledad**: Una célula viva con menos de dos vecinos vivos muere (por soledad).
3. **Muerte por sobrepoblación**: Una célula viva con más de tres vecinos vivos muere (por sobrepoblación).
4. **Nacimiento**: Una célula muerta con exactamente tres vecinos vivos se "revive" (nace).

## Estructura del Proyecto

El código está escrito en C++ y se organiza en un solo archivo principal `.cpp`. El juego utiliza archivos de texto para cargar las coordenadas iniciales del tablero y los valores de las celdas. La simulación se actualiza en cada iteración y se muestra en la consola.

### Archivos del Proyecto

- `main.cpp`: Contiene el código principal del juego y su ejecución.
- `coordenadas1.txt` , `coordenadas2.txt` y `coordenadas3.txt`: son las predeterminadas.
- `.gitignore` se usa para decirle a Git qué archivos y carpetas no deben ser incluidos en el repositorio. Esto es útil para evitar subir archivos temporales, archivos de configuración local o cualquier archivo generado automáticamente que no sea relevante para el código fuente.
- `coordenadas.txt`: Archivo de texto con las coordenadas Personzlizadas iniciales de las células vivas.
- `configuracionTablero.txt`: Archivo de texto con parámetros opcionales como el tamaño del tablero o el número de iteraciones.

## Coordenadas Sugeridas

A continuación, se presentan algunas figuras clásicas para usar como configuración inicial en el Juego de la Vida.

### Figura Pentadecathlon

Estas coordenadas forman un patrón llamado **Pentadecathlon**, que es un ciclo estable con 15 celdas.
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

### Figura Nave Espacial Pesada

Este patrón, llamado **Nave Espacial Pesada**, es un tipo de nave que se mueve en la cuadrícula.

```
0 1
0 2
0 3
0 4
0 5
1 0
1 5
2 5
3 0
3 4
4 2
4 3
```


### Figura Glider Gun

El **Glider Gun** es una figura que produce un "desplazamiento" (un glider) que se mueve por la cuadrícula.

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


---

### Explicación:

1. **Figura Pentadecathlon**: Un ciclo estable que se mantiene en su forma sin cambiar con el paso del tiempo.
2. **Figura Nave Espacial Pesada**: Se mueve por la cuadrícula en cada ciclo.
3. **Figura Glider Gun**: Produce un glider que se mueve a través de la cuadrícula.

---


## Juego de la Vida Animado

Mira cómo evoluciona:

![I-Column](https://upload.wikimedia.org/wikipedia/commons/f/fb/I-Column.gif) ![Pulsar](https://upload.wikimedia.org/wikipedia/commons/0/07/Game_of_life_pulsar.gif) ![LWSS](https://upload.wikimedia.org/wikipedia/commons/3/37/Game_of_life_animated_LWSS.gif)










