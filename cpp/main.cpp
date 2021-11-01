#include <SFML/Graphics.hpp>
#include "../hpp/mapa.hpp"
#include "../hpp/mundo.hpp"
#include "../hpp/taxi.hpp"
#include "../hpp/nodo.hpp"
#include "../hpp/benchmark.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>

// Compilación para depuración: g++ -g -Wall ./cpp/main.cpp ./cpp/taxi.cpp ./cpp/mundo.cpp ./cpp/mapa.cpp ./cpp/nodo.cpp -o Taxi -lsfml-graphics -lsfml-window -lsfml-system

int MenuDefault (int &dimX, int &dimY, Mundo &MainWorld) {

  int chrono = -1;
  while (chrono != 0 && chrono != 1){
    std::cout << "¿Quiere realizar un benchmark? (Si = 1, No = 0): ";
    std::cin >> chrono;
    if (chrono != 0 && chrono != 1) {
      std::cout << "Opción incorrecta. Vuelva a introducirla" << std::endl;
    }
  }

  if (chrono) {
    Benchmark();
    return 2;
  }
  
  int opcion, numObstaculos;                                                      // En el caso en el que el programa se abra sin especificar un archivo con el mundo
  std::cout << "No se ha especificado un fichero del cual leer, por tanto se introduciran los obstaculos de manera aleatoria." << std::endl;
  std::cout << "Introduzca las dimensiones de la matriz X*Y" << std::endl;
  do {                                                                // Recogida del tamaño del mundo
    std::cout << "Dimension X: ";
    std::cin >> dimX;
    std::cout << "Dimension Y: ";
    std::cin >> dimY;
    if (dimX <= 0 || dimY <= 0) {
      std::cout << "El valor no puede ser menor o igual que cero" << std::endl;
    }
  } while (dimX <= 0 || dimY <= 0);

  MainWorld.Resize(dimX, dimY);                                       // Establecemos el tamaño del mundo

  std::cout << "Introduzca el numero de obstaculos a colocar o -1 para elegir uno aleatorio: ";
  std::cin >> opcion;
  while (opcion < -1 || opcion > (dimX*dimY - 2)) {                   // Elegimos el número de obstáculos que se colocarán aleatoriamente en el mundo
      std::cout << "Cantidad de obstaculos no permitida, escoja otra cantidad o seleccione -1 para poner un numero aleatorio" << std::endl;
      std::cin >> opcion;
  }
  if (opcion == -1) {                                                 // Genera un numero aleatorio entre 0 y dimX*dimY
    numObstaculos = (rand() % dimX*dimY + 0) - 2;                     // (-2 para que haya espacio para el taxi y el destino, una casilla cada una)
    std::cout << "Elegidos " << numObstaculos << " nº de obstaculos" << std::endl;
    MainWorld.Random(numObstaculos);                                  // Se colocan numObstaculos obstáculos de manera aleatoria en el mundo                    
  }
  else {                                                              // Se usa el número de obstáculos elegido por el usuario
    numObstaculos = opcion;
    std::cout << "Elegidos " << numObstaculos << " nº de obstaculos" << std::endl;
    MainWorld.Random(numObstaculos);                                  // Se colocan numObstaculos obstáculos de manera aleatoria en el mundo
  }
  return 0;
}

int MenuArchivo(int &dimX, int &dimY, Mundo &MainWorld, char* argv[]) {    
                                                            // En el caso en el que se especifique un archivo del cual leer al ejecutar
  std::ifstream Archivo;                                              // el programa, se lee dicho archivo y se crea un mundo con él
  Archivo.open(argv[1]);
                                                                      // El archivo debe contener una matriz de ceros y unos del estilo:
  if(Archivo.fail()) {                                                // 001101100101010
                                                                      // 111011001001001            Donde: 0 = carretera / vacío
    return -1;                                                        // 000100001000000                   1 = obstáculo
  }                                                                   //       ...

  MainWorld.Load(Archivo);                                            // Se carga el archivo en el mundo
  dimX = MainWorld.GetDimensionX();                                   // Pasamos a las variables de la dimensión del mundo, el tamaño de la matriz
  dimY = MainWorld.GetDimensionY();

  Archivo.close();
  return 0;
}

int Menu2 (int &dimX, int &dimY, int &taxiX, int &taxiY, int &destinoX, int &destinoY, int &mov, int &distancia, Mundo &MainWorld, int& traza) {

  do {                                                                  // Recogemos la posición del taxi en el mundo
    std::cout << "Introduzca la coordenada en donde se situara el taxi" << std::endl << "Posicion del taxi X: ";
    std::cin >> taxiX;
    std::cout << "Posicion del taxi Y: ";
    std::cin >> taxiY;
    if (taxiX < 0 || taxiX >= dimX || taxiY < 0 || taxiY >= dimY || (MainWorld.Status(taxiX, taxiY) == obstaculo_)) {
      std::cout << "Esa casilla no existe o se encuentra obstaculizada" << std::endl;
    }
  } while(taxiX < 0 || taxiX >= dimX || taxiY < 0 || taxiY >= dimY || (MainWorld.Status(taxiX, taxiY) == obstaculo_));

  do {                                                                  // Recogemos la posición del destino en el mundo
    std::cout << "Introduzca la coordenada en donde se situara el destino" << std::endl << "Posicion del destino X: ";
    std::cin >> destinoX;
    std::cout << "Posicion del destino Y: ";
    std::cin >> destinoY;
    if (destinoX < 0 || destinoX >= dimX || destinoY < 0 || destinoY >= dimY || (destinoX == taxiX && destinoY == taxiY) || (MainWorld.Status(destinoX, destinoY) == obstaculo_)) {
      std::cout << "Esa casilla no existe, se encuentra obstaculizada o es la de inicio" << std::endl;
    }
  } while(destinoX < 0 || destinoX >= dimX || destinoY < 0 || destinoY >= dimY || (destinoX == taxiX && destinoY == taxiY) || (MainWorld.Status(destinoX, destinoY) == obstaculo_));

  while (distancia != 0 && distancia != 1)  {
    std::cout << "Introduzca 0 si desea usar la distancia Manhattan como funcion heuristica o 1 si desea la Euclidea: ";
    std::cin >> distancia;
    if (distancia != 0 && distancia != 1) {
      std::cout << "Opción incorrecta. Vuelva a introducirla" << std::endl;
    }
  }

  while (mov != 4 && mov != 8)  {
    std::cout << "Introduzca 4 para que el taxi se mueva en horizontal y vertical u 8 para que se mueva en diagonal tambien: ";
    std::cin >> mov;
    if (mov != 4 && mov != 8) {
      std::cout << "Opción incorrecta. Vuelva a introducirla" << std::endl;
    }
  }

  while (traza != 0 && traza != 1){
    std::cout << "¿Quiere ver la traza del algoritmo? (Si = 1, No = 0): ";
    std::cin >> traza;
    if (traza != 0 && traza != 1) {
      std::cout << "Opción incorrecta. Vuelva a introducirla" << std::endl;
    }
  }
  return 0;
}

int main(int argc, char *argv[]) {

  int dimX, dimY, taxiX, taxiY, destinoX, destinoY;
  Mundo MainWorld;                                                      // una variable opción para elegir a través del menú y nuestro mundo principal.
                                                                        
  if (argc != 2) {                                                      // En el caso en el que el programa se abra sin especificar un archivo con el mundo
    if (MenuDefault(dimX, dimY, MainWorld) == 2) {
      return 0;
    }
  }
  else {                                                                // En el caso en el que se especifique un archivo del cual leer al ejecutar
    if (MenuArchivo(dimX, dimY, MainWorld, argv) == -1) {
      std::cout << "Error al abrir el archivo" << argv[1] << std::endl;
      return -1;
    }
  }

  MainWorld.PrintMundo();

  int mov = -1;
  int distancia = -1;
  int traza = -1;
  Menu2(dimX, dimY, taxiX, taxiY, destinoX, destinoY, mov, distancia, MainWorld, traza);

  Taxi MainTaxi(MainWorld, taxiX, taxiY, destinoX, destinoY); // Creamos la clase Taxi con el mundo y las coordenadas especificadas

  std::vector<std::vector<int>> Camino;
  if (mov == 4) {
    if (traza) {
      Camino = MainTaxi.CaminoMinimo4Traza(distancia);       // Calculamos el camino mínimo entre las coordenadas de inicio y destino
    }
    else {
      Camino = MainTaxi.CaminoMinimo4(distancia, 0);
    }
    if (Camino.size() == 0) {                                             
      std::cout << "El taxi no puede llegar a su destino" << std::endl;   // Si el camino nos llega vacío significa que no hay manera de que el taxi
      return -1;                                                          // llegue al destino de ninguna forma
    }
  }
  else {
    if (traza) {
      Camino = MainTaxi.CaminoMinimo8Traza(distancia);       // Calculamos el camino mínimo entre las coordenadas de inicio y destino
    }
    else {
      Camino = MainTaxi.CaminoMinimo8(distancia, 0);
    }
    if (Camino.size() == 0) {                                             
      std::cout << "El taxi no puede llegar a su destino" << std::endl;   // Si el camino nos llega vacío significa que no hay manera de que el taxi
      return -1;                                                          // llegue al destino de ninguna forma
    }
  }

  sf::RenderWindow window(sf::VideoMode(1000, 800), "Mapa");            // Abrimos una ventana nueva
  sf::View vista(sf::Vector2f((dimY*32)/2, (dimX*32)/2), sf::Vector2f(window.getSize().x, window.getSize().y));
  window.setView(vista);

  int level[dimX*dimY] = {0}; 
  int levelPath[dimX*dimY] = {0};                                       // Creamos los 3 arrays de enteros que usaremos para dibujar en pantalla
  int levelBordes[8][dimX*dimY] = {0};
  std::vector<std::vector<std::vector<int>>> levelMatrizBordes;

  MainTaxi.Representacion(MainWorld, level);                            // Obtenemos un array de enteros con el mundo para representarlo en ventana
  levelMatrizBordes = MainTaxi.Representacion(MainWorld);               // Obtenemos los array de enteros con los bordes de casilla para representarlo en
  for (int i = 0; i < levelMatrizBordes.size(); i++) {                  // ventana, la función devuelve un array de matrices así que la convertiremos con
    ConvertToArray(levelMatrizBordes[i], levelBordes[i]);               // ConvertToArray() para obtener el array de enteros
  }

  MainTaxi.Representacion(Camino, dimX, dimY, levelPath);               // Obtenemos un array de enteros con el camino para representarlo en ventana

  Mapa background;                                                      // Creamos y cargamos un mapa con el mundo
  if (!background.load("./sprites/casillas.png", sf::Vector2u(32, 32), level, dimY, dimX)) {
    return -1;
  }
  Mapa path;                                                            // Creamos y cargamos un mapa con el camino
  if (!path.load("./sprites/camino.png", sf::Vector2u(32, 32), levelPath, dimY, dimX)) {
    return -1;
  }
  Mapa bordes[8];
  for (int i = 0; i < 8; i++) {                                         // Creamos y cargamos los 8 mapas de bordes de casilla
    if (!bordes[i].load("./sprites/bordes.png", sf::Vector2u(32, 32), levelBordes[i], dimY, dimX)) {
      return -1;
    }
  }

  sf::Vector2f oldPos;
  bool mover = false;
  while (window.isOpen()) {                                             // Mientras la ventana esté abierta...

    sf::Event event;                                                    // Creamos un evento que manejar
    while (window.pollEvent(event)) {                                   // Si se ha recogido un evento...
      switch (event.type) {
        case (sf::Event::Closed):                                        // Si el evento es el de cerrar la ventana, la cerramos
          window.close();
          break;
        case (sf::Event::MouseWheelScrolled):
          if (!mover) {
            if (event.mouseWheelScroll.delta < 0)
              vista.zoom(1.1);
            else if (event.mouseWheelScroll.delta > 0)
              vista.zoom(0.9);
            window.setView(vista);
          }
          break;
        case (sf::Event::MouseButtonPressed):
          if (event.mouseButton.button == 0) {
            mover = true;
            oldPos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
          }
          break;
        case (sf::Event::MouseButtonReleased):
          if (event.mouseButton.button == 0)
            mover = false;
          break;
        case (sf::Event::MouseMoved):
          if (mover) {
            const sf::Vector2f newPos = window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
            const sf::Vector2f deltaPos = oldPos - newPos;
            vista.setCenter(vista.getCenter() + deltaPos);
            window.setView(vista);
            oldPos = window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
          }
          break;
        case (sf::Event::Resized):
          vista.setSize(window.getSize().x, window.getSize().y);
          window.setView(vista);
          break;
      }
    }

    window.clear();                                                     // Limpiamos lo dibujado en ventana
    window.draw(background);                                            // Dibujamos el fondo en ventana
    for (int i = 0; i < 8; i++) {
      window.draw(bordes[i]);                                           // Dibujamos los bordes de césped de las casillas
    }
    window.draw(path);                                                  // Dibujamos (encima del fondo) el camino en la ventana
    window.display();                                                   // Representamos en pantalla lo dibujado
  }
  return 0;
}                                                                       // FIN
