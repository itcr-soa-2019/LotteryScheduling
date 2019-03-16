# LotteryScheduling
Instituto Tecnológico de Costa Rica

Sistemas Operativos Avanzados, 2019

Proyecto 1: "Lottery Scheduling"


### Compilación
Para compilar el programa se debe ejecutar el comando make en la raíz del proyecto.

```sh
$ make
```

El make va a generar un archivo lottery dentro de la carpeta bin.


### Ejecución
Para correr el programa desde la raiz del proyecto se deben ejecutar los siguientes comandos.

```sh
$ cd bin
$ ./lottery
```

Si el ./lottery realiza fuera de bin el ejecutable lottery no encuentra el archivo execution.conf y no es posible cargar desde el archivo la configuración de los hilos.
