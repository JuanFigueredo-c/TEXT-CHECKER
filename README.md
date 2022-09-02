# CORRECTOR DE TEXTO

## CONVENCIONES

Nombres de variables: ejemploEjemplo (camelCase) \
Nombres de funciones: ejemplo_ejemplo (snake_case)\
Nombres de struct: Ejemplo \
Idioma: Ingles 

## COMPILACION DEL PROGRAMA

Para la compilacion del programa se pueden correr las siguientes lineas:
```
make
```
  o 
```
gcc -o main main.c glist.c hash_table.c dict.c word_functions.c utils.c io.c
```

## CORRECCION DE TEXTO

Para la correccion de texto se debe correr el programa con la siguiente linea:
```
./main archivo_input.txt archivo_output.txt
```
Siendo 'archivo_intput.txt' el nombre del archivo de texto que contiene el texto a corregir.
Este archivo debe existir en el directorio en el cual se encuentra el programa. \
El argumento 'archivo_output.txt' refiere al nombre del archivo de salida que contendra \
las correcciones del texto, y se escribira en el directorio en el cual se encuentre \
el programa.

## ELIMINACION DE ARCHIVOS GENERADOS

Para eliminar los archivos generados por el uso del programa se debe correr la linea: 
```
make clean
```

 \
 \
Programa realizado por Juan Bautista Figueredo.