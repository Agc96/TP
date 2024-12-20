# Cuestionario

## Pregunta 1 (7 puntos)

Verifique que ha escrito correctamente el programa, para esto compile el proyecto [Mayús + F11]. Anote lo que aparece en la ventana de Salida del proyecto en la primera corrida (sin correcciones). Si es que aparecen errores explique por qué se producen. Luego corrija el proyecto hasta que se ejecute correctamente. 

Verifique que su programa se ejecute adecuadamente. Presione [F6] e ingrese los valores que se piden. Use los datos de la ecuación f1(x) dados en el ejemplo. Observará que debe obtener como resultado: 

```
Área bajo la curva = 40.132466
Longitud de la curva = 31.039346
```

## Pregunta 2 (2 puntos)

Indique cuáles son los resultados para f2(x).

```
Área bajo la curva = ?
Longitud de la curva = ?
```

Escriba los valores del área y la longitud (incluya todos los decimales que aparecen) en ese orden y separados por un punto y coma (;)

## Pregunta 3 (3 puntos)

Las bibliotecas o librerías en C están clasificadas por el tipo de trabajo que realizan, ¿Para qué se están usando las siguientes librerías en el programa?

```C
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
```

## Pregunta 4 (2 puntos)

En el ciclo iterativo con salida controlada justifique el uso de la constante simbólica PRECISION y de la función fabs() ¿Qué pasa si el programador decide comparar directamente los valores con el operador == ? 

## Pregunta 5 (1 punto)

Afine los datos de salida, para que muestre resultados tal y como se aprecian en la figura, con solo 3 decimales y un ancho apropiado, no use \t para la solución. Importa el formato. Los datos son referenciales.

```
  Area    Longitud
19.042      46.259
```

## Pregunta 6 (3 puntos)

Escribir los comentarios necesarios para el programa, de manera que ayuden a cualquier programador a usar el proyecto adecuadamente solo leyendo esta documentación. Se tomará en cuenta para la calificación el uso de comentarios relevantes. 

Los cambios debe realizarlos en el proyecto.

## Pregunta 7 (1 punto)

Analice los resultados del programa para la función:

f(x) = 3x^3 - 8.5x^2 + 7x

En el intervalo [0, 2]

Sin embargo, en lugar de producir el resultado esperado, donde el área de la curva se aproxime o sea igual a 3.333 y longitud de la curva se aproxime o sea igual a 5.650

Produce:

```
  Area    Longitud
 3.352       5.556
```

Explique por qué el programa muestra estos resultados, deduzca que valor se debería afinar y por qué valor debe cambiar.

## Pregunta 8 (1 punto)

Tomando en cuenta los cambios realizado en la pregunta anterior, sin modificar el programa y empleando únicamente las opciones de depuración del NetBeans como [Ctrl + F5], la ventana de Variables, etc. Indique lo siguiente:

Mientras más trapecios se utilicen mejor será la aproximación ¿Cuántos trapecios se utilizan cuando el  valor del área es 3.3359375?

f(x) = 3x^3 - 8.5x^2 + 7x

En el intervalo [0, 2]
