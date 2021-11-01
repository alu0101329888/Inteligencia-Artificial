#include "../hpp/taxi.hpp"
#include "../hpp/mapa.hpp"
#include <chrono>

Taxi::Taxi(Mundo mainWorld, int coordX, int coordY, int destX, int destY){      // Constructor por defecto
  world = mainWorld;
  taxiX = coordX;
  taxiY = coordY;
  destinoX = destX;
  destinoY = destY;
}

Taxi::~Taxi(){                                                                  // Destructor
}

void Taxi::PrintMundo() {                                                       // Representa el mundo por consola con el taxi en él
  std::vector<std::vector<int>> malla;
  malla = world.GetRejilla();
  malla[taxiX][taxiY] = taxi_;
  for(int i = 0; i < malla.size(); i++) {
    for (int j = 0; j < malla[0].size(); j++){
      std::cout << malla[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

bool Taxi::MovLegal(int movX, int movY) {                                       // Devuelve true o false si la casilla especificada existe y está vacía
  if(movX >= world.GetDimensionX() || movY >= world.GetDimensionY() || movX < 0 || movY < 0){
    return false;
  }
  if (world.Status(movX, movY) == obstaculo_) {
    return false;
  }
  return true;
}

bool Taxi::MovDer(std::vector<int> coord) {                                     // Devuelve true o false si un mov. hacia la derecha desde la casilla
  int nextpos = coord[1];                                                       // especificada es legal o no
  nextpos++;                                     
  if(MovLegal(coord[0], nextpos))
    return true;
  return false;
}

bool Taxi::MovIzq(std::vector<int> coord) {                                     // Devuelve true o false si un mov. hacia la izquierda desde la casilla
  int nextpos = coord[1];                                                       // especificada es legal o no
  nextpos--;
  if(MovLegal(coord[0], nextpos))
    return true;
  return false;
}

bool Taxi::MovArriba(std::vector<int> coord) {                                  // Devuelve true o false si un mov. hacia arriba desde la casilla
  int nextpos = coord[0];                                                       // especificada es legal o no
  nextpos--;
  if(MovLegal(nextpos, coord[1]))
    return true;
  return false;
}

bool Taxi::MovAbajo(std::vector<int> coord) {                                   // Devuelve true o false si un mov. hacia abajo desde la casilla
  int nextpos = coord[0];                                                       // especificada es legal o no
  nextpos++;
  if(MovLegal(nextpos, coord[1]))
    return true;
  return false;
}

bool Taxi::MovAbajoIzq(std::vector<int> coord) {                                   // Devuelve true o false si un mov. hacia abajo desde la casilla
  int nextpos0 = coord[0];
  int nextpos1 = coord[1];                                                     // especificada es legal o no
  nextpos0++;
  nextpos1--;
  if(MovLegal(nextpos0, nextpos1))
    return true;
  return false;
}

bool Taxi::MovAbajoDer(std::vector<int> coord) {                                   // Devuelve true o false si un mov. hacia abajo desde la casilla
  int nextpos0 = coord[0];
  int nextpos1 = coord[1];                                                       // especificada es legal o no
  nextpos0++;
  nextpos1++;
  if(MovLegal(nextpos0, nextpos1))
    return true;
  return false;
}

bool Taxi::MovArribaDer(std::vector<int> coord) {                                  // Devuelve true o false si un mov. hacia arriba desde la casilla
  int nextpos0 = coord[0];                                                       // especificada es legal o no
  int nextpos1 = coord[1];
  nextpos0--;
  nextpos1++;
  if(MovLegal(nextpos0, nextpos1))
    return true;
  return false;
}

bool Taxi::MovArribaIzq(std::vector<int> coord) {                                  // Devuelve true o false si un mov. hacia arriba desde la casilla
  int nextpos0 = coord[0];                                                       // especificada es legal o no
  int nextpos1 = coord[1];
  nextpos0--;
  nextpos1--;
  if(MovLegal(nextpos0, nextpos1))
    return true;
  return false;
}

int* Taxi::Representacion(Mundo matriz, int level[]) {
                                          
  int contador = 0;

  for (int i = 0; i < matriz.GetDimensionX(); i++) {                             // Pasamos la matriz a el array de enteros "level" donde las casillas de
    for (int j = 0; j < matriz.GetDimensionY(); j++) {                           // carretera (0) se mantienen como 0 pero las casillas de obstáculos (1)
      if (matriz.GetRejilla()[i][j] == obstaculo_) {                             // se mantienen como 1, 2 o 3 siendo éstos unos índices que se usarán
        level[contador] = (rand() % 3) + 1;                                       // posteriormente para elegir una textura de obstáculo a representar
      }                                                                 
      else {                                                            
        level[contador] = vacio_;                                       
      }
      contador++;
    }
  }
  return level;
}

int* Taxi::Representacion(std::vector<std::vector<int>> camino, int dimensionX, int dimensionY, int levelPath[]) {
  
  for (int i = 0; i < camino.size(); i++) {                                       // Pasamos el vector con el camino mínimo calculado y lo pasamos a un
    levelPath[(camino[i][0]*dimensionY) + camino[i][1]] = 1;                      // array de enteros donde las casillas que no son parte del camino
  }                                                                               // valen 0 y las que si son parte del camino valen 1
  return levelPath;
}

std::vector<std::vector<std::vector<int>>> Taxi::Representacion(Mundo matriz) {

  std::vector<std::vector<std::vector<int>>> levelBordes(8);
  for (int i = 0; i < 8; i++) {                                                   // Recibimos 8 matrices que usaremos para 8 sprites distintos ya que en cada
    levelBordes[i].resize(matriz.GetDimensionX());                                // casilla pueden dibujarse hasta un máximo de dichos 8 sprites
    for (int j = 0; j < matriz.GetDimensionX(); j++) {
      levelBordes[i][j].resize(matriz.GetDimensionY());
      for (int k = 0; k < matriz.GetDimensionY(); k++) {
        levelBordes[i][j][k] = 0;
      }
    }
  }
  std::vector<int> coord(2, 0);

  for (coord[0] = 0; coord[0] < matriz.GetDimensionX(); coord[0]++) {
    for (coord[1] = 0; coord[1] < matriz.GetDimensionY(); coord[1]++) {           // Dada la posición de cada casilla se establecerá en cada mapa el número
      if (!matriz.Status(coord[0], coord[1])) {                                   // de sprite correspondiente y devolvemos el array de matrices
        if (matriz.Status(coord[0] + 1, coord[1]))
          levelBordes[0][coord[0]][coord[1]] = 1;
        if (matriz.Status(coord[0] - 1, coord[1]))
          levelBordes[1][coord[0]][coord[1]] = 2;
        if (matriz.Status(coord[0], coord[1] + 1))
          levelBordes[2][coord[0]][coord[1]] = 3;
        if (matriz.Status(coord[0], coord[1] - 1))
          levelBordes[3][coord[0]][coord[1]] = 4;
        if (matriz.Status(coord[0], coord[1] - 1) && matriz.Status(coord[0] + 1, coord[1]))
          levelBordes[4][coord[0]][coord[1]] = 5;
        if (matriz.Status(coord[0], coord[1] - 1) && matriz.Status(coord[0] - 1, coord[1]))
          levelBordes[5][coord[0]][coord[1]] = 6;
        if (matriz.Status(coord[0], coord[1] + 1) && matriz.Status(coord[0] - 1, coord[1]))
          levelBordes[6][coord[0]][coord[1]] = 7;
        if (matriz.Status(coord[0], coord[1] + 1) && matriz.Status(coord[0] + 1, coord[1]))
          levelBordes[7][coord[0]][coord[1]] = 8;
      }
      else if (matriz.Status(coord[0], coord[1])) {
        if (!matriz.Status(coord[0], coord[1] - 1) && !matriz.Status(coord[0] + 1, coord[1]) && !matriz.Status(coord[0] + 1, coord[1] - 1))
          levelBordes[6][coord[0] + 1][coord[1] - 1] = 7;
        if (!matriz.Status(coord[0], coord[1] - 1) && !matriz.Status(coord[0] - 1, coord[1]) && !matriz.Status(coord[0] - 1, coord[1] - 1))
          levelBordes[7][coord[0] - 1][coord[1] - 1] = 8;
        if (!matriz.Status(coord[0], coord[1] + 1) && !matriz.Status(coord[0] - 1, coord[1]) && !matriz.Status(coord[0] - 1, coord[1] + 1))
          levelBordes[4][coord[0] - 1][coord[1] + 1] = 5;
        if (!matriz.Status(coord[0], coord[1] + 1) && !matriz.Status(coord[0] + 1, coord[1]) && !matriz.Status(coord[0] + 1, coord[1] + 1))
          levelBordes[5][coord[0] + 1][coord[1] + 1] = 6;
      }
    }
  }
  return levelBordes;
}

void Taxi::ActualizarHorVer(std::vector<std::vector<Nodo>>& matrizNodos, std::vector<int> nodoActual, bool distancia, int x, int y) {
  matrizNodos[nodoActual[0] + x][nodoActual[1] + y].set_h(Heuristica(distancia, nodoActual[0] + x, nodoActual[1] + y));
  matrizNodos[nodoActual[0] + x][nodoActual[1] + y].set_coste(1 + matrizNodos[nodoActual[0]][nodoActual[1]].get_g());
  matrizNodos[nodoActual[0] + x][nodoActual[1] + y].set_padre(nodoActual[0], nodoActual[1]);
}

void Taxi::ActualizarDiagonal(std::vector<std::vector<Nodo>>& matrizNodos, std::vector<int> nodoActual, bool distancia, int x, int y) {
  matrizNodos[nodoActual[0] + x][nodoActual[1] + y].set_h(Heuristica(distancia, nodoActual[0] + x, nodoActual[1] + y));
  matrizNodos[nodoActual[0] + x][nodoActual[1] + y].set_coste(sqrt(pow(1, 2) + pow(1, 2)) + matrizNodos[nodoActual[0]][nodoActual[1]].get_g());
  matrizNodos[nodoActual[0] + x][nodoActual[1] + y].set_padre(nodoActual[0], nodoActual[1]);
}

void Taxi::VecinoArriba (std::vector<int>& nodoActual, std::vector<std::vector<int>>& cerrada, std::vector<std::vector<int>>& abierta, std::vector<std::vector<Nodo>>& matrizNodos, bool distancia) {
  if (MovArriba(nodoActual)) {
    bool pertenece = 0;
    for (int i = 0; i < cerrada.size(); i++) {
      if ((nodoActual[0] - 1 == cerrada[i][0]) && (nodoActual[1] == cerrada[i][1])) {
        pertenece = 1;
      }
    }
    if (pertenece == 0) {
      for (int i = 0; i < abierta.size(); i++) {
        if ((nodoActual[0] - 1 == abierta[i][0]) && (nodoActual[1] == abierta[i][1])) {
          pertenece = 1;
        }
      }
      if (pertenece) {
        if (matrizNodos[nodoActual[0] - 1][nodoActual[1]].get_g() > 1 + matrizNodos[nodoActual[0]][nodoActual[1]].get_g()) {
          ActualizarHorVer(matrizNodos, nodoActual, distancia, -1, 0);
        }
      }
      else {
        ActualizarHorVer(matrizNodos, nodoActual, distancia, -1, 0);
        std::vector<int> aux {nodoActual[0] - 1, nodoActual[1]};
        abierta.push_back(aux);
      }
    }
  }
  else {
    if (nodoActual[0] - 1 >= world.GetDimensionX() || nodoActual[1] >= world.GetDimensionY() || nodoActual[0] - 1 < 0 || nodoActual[1] < 0) {
      return;
    }
    else {
      matrizNodos[nodoActual[0] - 1][nodoActual[1]].set_obstaculo();
    }
  }
}

void Taxi::VecinoDer (std::vector<int>& nodoActual, std::vector<std::vector<int>>& cerrada, std::vector<std::vector<int>>& abierta, std::vector<std::vector<Nodo>>& matrizNodos, bool distancia) {
  if (MovDer(nodoActual)) {
    bool pertenece = 0;
    for (int i = 0; i < cerrada.size(); i++) {
      if ((nodoActual[0] == cerrada[i][0]) && (nodoActual[1] + 1 == cerrada[i][1])) {
          pertenece = 1;
      }
    }
    if (pertenece == 0) {
      for (int i = 0; i < abierta.size(); i++) {
        if (nodoActual[0] == abierta[i][0] && nodoActual[1] + 1 == abierta[i][1]) {
          pertenece = 1;
        }
      }
      if (pertenece) {
        if (matrizNodos[nodoActual[0]][nodoActual[1] + 1].get_g() > 1 + matrizNodos[nodoActual[0]][nodoActual[1]].get_g()) {
          ActualizarHorVer(matrizNodos, nodoActual, distancia, 0, 1);
        }
      }
      else {
        ActualizarHorVer(matrizNodos, nodoActual, distancia, 0, 1);
        std::vector<int> aux {nodoActual[0], nodoActual[1] + 1};
        abierta.push_back(aux);
      }
    }
  }
  else {
    if (nodoActual[0] >= world.GetDimensionX() || nodoActual[1] + 1 >= world.GetDimensionY() || nodoActual[0] < 0 || nodoActual[1] + 1 < 0) {
      return;
    }
    else {
      matrizNodos[nodoActual[0]][nodoActual[1] + 1].set_obstaculo();
    }
  }
}

void Taxi::VecinoAbajo (std::vector<int>& nodoActual, std::vector<std::vector<int>>& cerrada, std::vector<std::vector<int>>& abierta, std::vector<std::vector<Nodo>>& matrizNodos, bool distancia) {
  if (MovAbajo(nodoActual)) {
    bool pertenece = 0;
    for (int i = 0; i < cerrada.size(); i++) {
      if ((nodoActual[0] + 1 == cerrada[i][0]) && (nodoActual[1] == cerrada[i][1])) {
        pertenece = 1;
      }
    }
    if (pertenece == 0) {
      for (int i = 0; i < abierta.size(); i++) {
        if (nodoActual[0] + 1 == abierta[i][0] && nodoActual[1] == abierta[i][1]) {
          pertenece = 1;
        }
      }
      if (pertenece) {
        if (matrizNodos[nodoActual[0] + 1][nodoActual[1]].get_g() > 1 + matrizNodos[nodoActual[0]][nodoActual[1]].get_g()) {
          ActualizarHorVer(matrizNodos, nodoActual, distancia, 1, 0);
        }
      }
      else {
        ActualizarHorVer(matrizNodos, nodoActual, distancia, 1, 0);
        std::vector<int> aux {nodoActual[0] + 1, nodoActual[1]};
        abierta.push_back(aux);
      }
    }
  }
  else {
    if (nodoActual[0] + 1 >= world.GetDimensionX() || nodoActual[1] >= world.GetDimensionY() || nodoActual[0] + 1 < 0 || nodoActual[1] < 0) {
      return;
    }
    else {
      matrizNodos[nodoActual[0] + 1][nodoActual[1]].set_obstaculo();
    }
  }
}

void Taxi::VecinoIzq (std::vector<int>& nodoActual, std::vector<std::vector<int>>& cerrada, std::vector<std::vector<int>>& abierta, std::vector<std::vector<Nodo>>& matrizNodos, bool distancia) {
  if (MovIzq(nodoActual)) {
    bool pertenece = 0;
    for (int i = 0; i < cerrada.size(); i++) {
      if ((nodoActual[0] == cerrada[i][0]) && (nodoActual[1] - 1 == cerrada[i][1])) {
        pertenece = 1;
      }
    }
    if (pertenece == 0) {
      for (int i = 0; i < abierta.size(); i++) {
        if (nodoActual[0] == abierta[i][0] && nodoActual[1] - 1 == abierta[i][1]) {
          pertenece = 1;
        }
      }
      if (pertenece) {
        if (matrizNodos[nodoActual[0]][nodoActual[1] - 1].get_g() > 1 + matrizNodos[nodoActual[0]][nodoActual[1]].get_g()) {
          ActualizarHorVer(matrizNodos, nodoActual, distancia, 0, -1);
        }
      }
      else {
        ActualizarHorVer(matrizNodos, nodoActual, distancia, 0, -1);
        std::vector<int> aux {nodoActual[0], nodoActual[1] - 1};
        abierta.push_back(aux);
      }
    }
  }
  else {
    if (nodoActual[0] >= world.GetDimensionX() || nodoActual[1] - 1 >= world.GetDimensionY() || nodoActual[0] < 0 || nodoActual[1] - 1 < 0) {
      return;
    }
    else {
      matrizNodos[nodoActual[0]][nodoActual[1] - 1].set_obstaculo();
    }
  }
}

void Taxi::VecinoArribaDer (std::vector<int>& nodoActual, std::vector<std::vector<int>>& cerrada, std::vector<std::vector<int>>& abierta, std::vector<std::vector<Nodo>>& matrizNodos, bool distancia) {
  if (MovArribaDer(nodoActual)) {
    bool pertenece = 0;
    for (int i = 0; i < cerrada.size(); i++) {
      if ((nodoActual[0] - 1 == cerrada[i][0]) && (nodoActual[1] + 1 == cerrada[i][1])) {
        pertenece = 1;
      }
    }
    if (pertenece == 0) {
      for (int i = 0; i < abierta.size(); i++) {
        if (nodoActual[0] - 1 == abierta[i][0] && nodoActual[1] + 1 == abierta[i][1]) {
          pertenece = 1;
        }
      }
      if (pertenece) {
        if (matrizNodos[nodoActual[0] - 1][nodoActual[1] + 1].get_g() > 1.414 + matrizNodos[nodoActual[0]][nodoActual[1]].get_g()) {
          ActualizarDiagonal(matrizNodos, nodoActual, distancia, -1, +1);
        }
      }
      else {
        ActualizarDiagonal(matrizNodos, nodoActual, distancia, -1, +1);
        std::vector<int> aux {nodoActual[0] - 1, nodoActual[1] + 1};
        abierta.push_back(aux);
      }
    }
  }
  else {
    if (nodoActual[0] - 1 >= world.GetDimensionX() || nodoActual[1] + 1 >= world.GetDimensionY() || nodoActual[0] - 1 < 0 || nodoActual[1] + 1 < 0) {
      return;
    }
    else {
      matrizNodos[nodoActual[0] - 1][nodoActual[1] + 1].set_obstaculo();
    }
  }
}

void Taxi::VecinoArribaIzq (std::vector<int>& nodoActual, std::vector<std::vector<int>>& cerrada, std::vector<std::vector<int>>& abierta, std::vector<std::vector<Nodo>>& matrizNodos, bool distancia) {
  if (MovArribaIzq(nodoActual)) {
    bool pertenece = 0;
    for (int i = 0; i < cerrada.size(); i++) {
      if ((nodoActual[0] - 1 == cerrada[i][0]) && (nodoActual[1] - 1 == cerrada[i][1])) {
        pertenece = 1;
      }
    }
    if (pertenece == 0) {
      for (int i = 0; i < abierta.size(); i++) {
        if (nodoActual[0] - 1 == abierta[i][0] && nodoActual[1] - 1 == abierta[i][1]) {
          pertenece = 1;
        }
      }
      if (pertenece) {
        if (matrizNodos[nodoActual[0] - 1][nodoActual[1] - 1].get_g() > 1.414 + matrizNodos[nodoActual[0]][nodoActual[1]].get_g()) {
          ActualizarDiagonal(matrizNodos, nodoActual, distancia, -1, -1);
        }
      }
      else {
        ActualizarDiagonal(matrizNodos, nodoActual, distancia, -1, -1);
        std::vector<int> aux {nodoActual[0] - 1, nodoActual[1] - 1};
        abierta.push_back(aux);
      }
    }
  }
  else {
    if (nodoActual[0] - 1 >= world.GetDimensionX() || nodoActual[1] - 1 >= world.GetDimensionY() || nodoActual[0] - 1 < 0 || nodoActual[1] - 1 < 0) {
      return;
    }
    else {
      matrizNodos[nodoActual[0] - 1][nodoActual[1] - 1].set_obstaculo();
    }
  }
}

void Taxi::VecinoAbajoDer (std::vector<int>& nodoActual, std::vector<std::vector<int>>& cerrada, std::vector<std::vector<int>>& abierta, std::vector<std::vector<Nodo>>& matrizNodos, bool distancia) {
  if (MovAbajoDer(nodoActual)) {
    bool pertenece = 0;
    for (int i = 0; i < cerrada.size(); i++) {
      if ((nodoActual[0] + 1 == cerrada[i][0]) && (nodoActual[1] + 1 == cerrada[i][1])) {
        pertenece = 1;
      }
    }
    if (pertenece == 0) {
      for (int i = 0; i < abierta.size(); i++) {
        if (nodoActual[0] + 1 == abierta[i][0] && nodoActual[1] + 1 == abierta[i][1]) {
          pertenece = 1;
        }
      }
      if (pertenece) {
        if (matrizNodos[nodoActual[0] + 1][nodoActual[1] + 1].get_g() > 1.414 + matrizNodos[nodoActual[0]][nodoActual[1]].get_g()) {
          ActualizarDiagonal(matrizNodos, nodoActual, distancia, +1, +1);
        }
      }
      else {
        ActualizarDiagonal(matrizNodos, nodoActual, distancia, +1, +1);
        std::vector<int> aux {nodoActual[0] + 1, nodoActual[1] + 1};
        abierta.push_back(aux);
      }
    }
  }
  else {
    if (nodoActual[0] + 1 >= world.GetDimensionX() || nodoActual[1] + 1 >= world.GetDimensionY() || nodoActual[0] + 1 < 0 || nodoActual[1] + 1 < 0) {
      return;
    }
    else {
      matrizNodos[nodoActual[0] + 1][nodoActual[1] + 1].set_obstaculo();
    }
  }
}

void Taxi::VecinoAbajoIzq (std::vector<int>& nodoActual, std::vector<std::vector<int>>& cerrada, std::vector<std::vector<int>>& abierta, std::vector<std::vector<Nodo>>& matrizNodos, bool distancia) {
  if (MovAbajoIzq(nodoActual)) {
      bool pertenece = 0;
      for (int i = 0; i < cerrada.size(); i++) {
        if ((nodoActual[0] + 1 == cerrada[i][0]) && (nodoActual[1] - 1 == cerrada[i][1])) {
          pertenece = 1;
        }
      }
      if (pertenece == 0) {
        for (int i = 0; i < abierta.size(); i++) {
          if (nodoActual[0] + 1 == abierta[i][0] && nodoActual[1] - 1 == abierta[i][1]) {
            pertenece = 1;
          }
        }
        if (pertenece) {
          if (matrizNodos[nodoActual[0] + 1][nodoActual[1] - 1].get_g() > 1.414 + matrizNodos[nodoActual[0]][nodoActual[1]].get_g()) {
            ActualizarDiagonal(matrizNodos, nodoActual, distancia, +1, -1);
          }
        }
        else {
          ActualizarDiagonal(matrizNodos, nodoActual, distancia, +1, -1);
          std::vector<int> aux {nodoActual[0] + 1, nodoActual[1] - 1};
          abierta.push_back(aux);
        }
      }
    }
    else {
      if (nodoActual[0] + 1 >= world.GetDimensionX() || nodoActual[1] - 1 >= world.GetDimensionY() || nodoActual[0] + 1 < 0 || nodoActual[1] - 1 < 0) {
        return;
      }
      else {
        matrizNodos[nodoActual[0] + 1][nodoActual[1] - 1].set_obstaculo();
      }
    }
}

int* ConvertToArray (std::vector<std::vector<int>> level, int levelArray[]) {
  int contador = 0;
  for (int i = 0; i < level.size(); i++) {
    for (int j = 0; j < level[0].size(); j++) {
      levelArray[contador] = level[i][j];
      contador++;
    }
  }
  return levelArray;
}

std::vector<std::vector<int>> Taxi::CaminoMinimo4(bool distancia, bool benchmark) {

  std::vector<std::vector<Nodo>> matrizNodos;
  std::vector<std::vector<int>> abierta;
  std::vector<std::vector<int>> cerrada;

  std::vector<int> nodoActual {taxiX, taxiY};

  Nodo nodoStart(0, 0, taxiX, taxiY);

  nodoStart.set_h(Heuristica(distancia, taxiX, taxiY));

  matrizNodos.resize(world.GetDimensionX());
  for (int i = 0; i < matrizNodos.size(); i++) {
    matrizNodos[i].resize(world.GetDimensionY());
  }
  
  matrizNodos[taxiX][taxiY] = nodoStart;

  abierta.push_back(nodoActual);

  sf::Vector2f oldPos;
  bool mover = false;

  int benchmarkCounter = 0;

  while ((nodoActual[0] != destinoX || nodoActual[1] != destinoY) && !abierta.empty()) {
    benchmarkCounter++;
    float f = INFINITY;
    float h = INFINITY;
    std::vector<int> nodoSiguiente(2);
    for (int i = 0; i < abierta.size(); i++) {
      /*if (matrizNodos[abierta[i][0]][abierta[i][1]].get_h() < h) {
        h = matrizNodos[abierta[i][0]][abierta[i][1]].get_h();
        nodoSiguiente[0] = abierta[i][0];
        nodoSiguiente[1] = abierta[i][1];
      }*/
      if ((matrizNodos[abierta[i][0]][abierta[i][1]].get_h() + matrizNodos[abierta[i][0]][abierta[i][1]].get_g()) < f) {
        f = (matrizNodos[abierta[i][0]][abierta[i][1]].get_h() + matrizNodos[abierta[i][0]][abierta[i][1]].get_g());
        nodoSiguiente[0] = abierta[i][0];
        nodoSiguiente[1] = abierta[i][1];
      }
    }
    for (int i = 0; i < abierta.size(); i++) {
      if (abierta[i][0] == nodoSiguiente[0] && abierta[i][1] == nodoSiguiente[1]) {
        abierta.erase(abierta.begin() + i);
      }
    }
    cerrada.push_back(nodoSiguiente);
    nodoActual = nodoSiguiente;

    VecinoArriba(nodoActual, cerrada, abierta, matrizNodos, distancia);
    VecinoDer(nodoActual, cerrada, abierta, matrizNodos, distancia);
    VecinoAbajo(nodoActual, cerrada, abierta, matrizNodos, distancia);
    VecinoIzq(nodoActual, cerrada, abierta, matrizNodos, distancia);
  }
    
  std::vector<std::vector<int>> caminoMinimo(0);
  if (nodoActual[0] != destinoX && nodoActual[1] != destinoY) {
    if (benchmark) {
      std::cout << benchmarkCounter << " nodos analizados | " << caminoMinimo.size() << " nodos de longitud de camino minimo | ";
    }
    return caminoMinimo;
  }
  caminoMinimo.push_back(nodoActual);                                                      // Creamos el vector con el camino mínimo empezando por el destino

  do {                                                                                     // Metemos por orden los predecesores de cada casilla en orden inverso
    caminoMinimo.push_back(matrizNodos[nodoActual[0]][nodoActual[1]].get_padre());         // dentro del vector hasta llegar a la casilla de inicio del taxi
    nodoActual[0] = caminoMinimo[caminoMinimo.size() - 1][0];
    nodoActual[1] = caminoMinimo[caminoMinimo.size() - 1][1];
  } while (nodoActual[0] != taxiX || nodoActual[1] != taxiY);
  
  if (benchmark) {
    std::cout << benchmarkCounter << " nodos analizados | " << caminoMinimo.size() << " nodos de longitud de camino minimo | ";
  }
  return caminoMinimo;
}

std::vector<std::vector<int>> Taxi::CaminoMinimo8(bool distancia, bool benchmark) {

  std::vector<std::vector<Nodo>> matrizNodos;
  std::vector<std::vector<int>> abierta;
  std::vector<std::vector<int>> cerrada;

  std::vector<int> nodoActual {taxiX, taxiY};

  Nodo nodoStart(0, 0, taxiX, taxiY);

  nodoStart.set_h(Heuristica(distancia, taxiX, taxiY));

  matrizNodos.resize(world.GetDimensionX());
  for (int i = 0; i < matrizNodos.size(); i++) {
    matrizNodos[i].resize(world.GetDimensionY());
  }
  
  matrizNodos[taxiX][taxiY] = nodoStart;

  abierta.push_back(nodoActual);

  sf::Vector2f oldPos;
  bool mover = false;

  int benchmarkCounter = 0;

  while ((nodoActual[0] != destinoX || nodoActual[1] != destinoY) && !abierta.empty()) {
    benchmarkCounter++;
    float f = INFINITY;
    float h = INFINITY;
    std::vector<int> nodoSiguiente(2);
    for (int i = 0; i < abierta.size(); i++) {
      /*if (matrizNodos[abierta[i][0]][abierta[i][1]].get_h() < h) {
        h = matrizNodos[abierta[i][0]][abierta[i][1]].get_h();
        nodoSiguiente[0] = abierta[i][0];
        nodoSiguiente[1] = abierta[i][1];
      }*/
      if ((matrizNodos[abierta[i][0]][abierta[i][1]].get_h() + matrizNodos[abierta[i][0]][abierta[i][1]].get_g()) < f) {
        f = (matrizNodos[abierta[i][0]][abierta[i][1]].get_h() + matrizNodos[abierta[i][0]][abierta[i][1]].get_g());
        nodoSiguiente[0] = abierta[i][0];
        nodoSiguiente[1] = abierta[i][1];
      }
    }
    for (int i = 0; i < abierta.size(); i++) {
      if (abierta[i][0] == nodoSiguiente[0] && abierta[i][1] == nodoSiguiente[1]) {
        abierta.erase(abierta.begin() + i);
      }
    }
    cerrada.push_back(nodoSiguiente);
    nodoActual = nodoSiguiente;

    VecinoArriba(nodoActual, cerrada, abierta, matrizNodos, distancia);
    VecinoDer(nodoActual, cerrada, abierta, matrizNodos, distancia);
    VecinoAbajo(nodoActual, cerrada, abierta, matrizNodos, distancia);
    VecinoIzq(nodoActual, cerrada, abierta, matrizNodos, distancia);
    VecinoArribaDer(nodoActual, cerrada, abierta, matrizNodos, distancia);
    VecinoArribaIzq(nodoActual, cerrada, abierta, matrizNodos, distancia);
    VecinoAbajoDer(nodoActual, cerrada, abierta, matrizNodos, distancia);
    VecinoAbajoIzq(nodoActual, cerrada, abierta, matrizNodos, distancia);
  }

  std::vector<std::vector<int>> caminoMinimo(0);
  if (nodoActual[0] != destinoX && nodoActual[1] != destinoY) {
    if (benchmark) {
      std::cout << benchmarkCounter << " nodos analizados | " << caminoMinimo.size() << " nodos de longitud de camino minimo | ";
    }
    return caminoMinimo;
  }
  caminoMinimo.push_back(nodoActual);                                                      // Creamos el vector con el camino mínimo empezando por el destino

  do {                                                                                     // Metemos por orden los predecesores de cada casilla en orden inverso
    caminoMinimo.push_back(matrizNodos[nodoActual[0]][nodoActual[1]].get_padre());         // dentro del vector hasta llegar a la casilla de inicio del taxi
    nodoActual[0] = caminoMinimo[caminoMinimo.size() - 1][0];
    nodoActual[1] = caminoMinimo[caminoMinimo.size() - 1][1];
  } while (nodoActual[0] != taxiX || nodoActual[1] != taxiY);
  
  if (benchmark) {
    std::cout << benchmarkCounter << " nodos analizados | " << caminoMinimo.size() << " nodos de longitud de camino minimo | ";
  }
  return caminoMinimo;
}

std::vector<std::vector<int>> Taxi::CaminoMinimo4Traza(bool distancia) {

  std::vector<std::vector<Nodo>> matrizNodos;
  std::vector<std::vector<int>> abierta;
  std::vector<std::vector<int>> cerrada;

  std::vector<int> nodoActual {taxiX, taxiY};

  Nodo nodoStart(0, 0, taxiX, taxiY);

  nodoStart.set_h(Heuristica(distancia, taxiX, taxiY));

  matrizNodos.resize(world.GetDimensionX());
  for (int i = 0; i < matrizNodos.size(); i++) {
    matrizNodos[i].resize(world.GetDimensionY());
  }
  
  matrizNodos[taxiX][taxiY] = nodoStart;

  abierta.push_back(nodoActual);

  int level[world.GetDimensionX()*world.GetDimensionY()] = {0}; 
  int levelPath[world.GetDimensionX()*world.GetDimensionY()] = {0};
  int levelBordes[8][world.GetDimensionX()*world.GetDimensionY()] = {0};
  std::vector<std::vector<std::vector<int>>> levelMatrizBordes;
  sf::RenderWindow window(sf::VideoMode(1000, 800), "Mapa");            // Abrimos una ventana nueva
  sf::View vista(sf::Vector2f((world.GetDimensionY()*32)/2, (world.GetDimensionX()*32)/2), sf::Vector2f(window.getSize().x, window.getSize().y));
  window.setView(vista);

  Representacion(world, level);                            // Obtenemos un array de enteros con el mundo para representarlo en ventana
  levelMatrizBordes = Representacion(world);               // Obtenemos los array de enteros con los bordes de casilla para representarlo en
  for (int i = 0; i < levelMatrizBordes.size(); i++) {     // ventana, la función devuelve un array de matrices así que la convertiremos con
    ConvertToArray(levelMatrizBordes[i], levelBordes[i]);
  }
  Mapa background;                                                      // Creamos y cargamos un mapa con el mundo
  if (!background.load("./sprites/casillas.png", sf::Vector2u(32, 32), level, world.GetDimensionY(), world.GetDimensionX())) {
  }
  Mapa bordes[8];
  for (int i = 0; i < 8; i++) {                                         // Creamos y cargamos los 8 mapas de bordes de casilla
    if (!bordes[i].load("./sprites/bordes.png", sf::Vector2u(32, 32), levelBordes[i], world.GetDimensionY(), world.GetDimensionX())) {
    }
  }

  sf::Vector2f oldPos;
  bool mover = false;

  while ((nodoActual[0] != destinoX || nodoActual[1] != destinoY) && !abierta.empty() && window.isOpen()) {
    float f = INFINITY;
    float h = INFINITY;
    std::vector<int> nodoSiguiente(2);
    for (int i = 0; i < abierta.size(); i++) {
      /*if (matrizNodos[abierta[i][0]][abierta[i][1]].get_h() < h) {
        h = matrizNodos[abierta[i][0]][abierta[i][1]].get_h();
        nodoSiguiente[0] = abierta[i][0];
        nodoSiguiente[1] = abierta[i][1];
      }*/
      if ((matrizNodos[abierta[i][0]][abierta[i][1]].get_h() + matrizNodos[abierta[i][0]][abierta[i][1]].get_g() + 1) < f) {
        f = (matrizNodos[abierta[i][0]][abierta[i][1]].get_h() + matrizNodos[abierta[i][0]][abierta[i][1]].get_g() + 1);
        nodoSiguiente[0] = abierta[i][0];
        nodoSiguiente[1] = abierta[i][1];
      }
    }
    for (int i = 0; i < abierta.size(); i++) {
      if (abierta[i][0] == nodoSiguiente[0] && abierta[i][1] == nodoSiguiente[1]) {
        abierta.erase(abierta.begin() + i);
      }
    }
    cerrada.push_back(nodoSiguiente);
    nodoActual = nodoSiguiente;

    VecinoArriba(nodoActual, cerrada, abierta, matrizNodos, distancia);
    VecinoDer(nodoActual, cerrada, abierta, matrizNodos, distancia);
    VecinoAbajo(nodoActual, cerrada, abierta, matrizNodos, distancia);
    VecinoIzq(nodoActual, cerrada, abierta, matrizNodos, distancia);
    
    Traza(nodoActual, matrizNodos, levelPath, window, mover, vista, oldPos, bordes, background);
  }
    
  std::vector<std::vector<int>> caminoMinimo;
  if (nodoActual[0] != destinoX && nodoActual[1] != destinoY) {
    return caminoMinimo;
  }
  caminoMinimo.push_back(nodoActual);                                                      // Creamos el vector con el camino mínimo empezando por el destino

  do {                                                                                     // Metemos por orden los predecesores de cada casilla en orden inverso
    caminoMinimo.push_back(matrizNodos[nodoActual[0]][nodoActual[1]].get_padre());         // dentro del vector hasta llegar a la casilla de inicio del taxi
    nodoActual[0] = caminoMinimo[caminoMinimo.size() - 1][0];
    nodoActual[1] = caminoMinimo[caminoMinimo.size() - 1][1];
  } while (nodoActual[0] != taxiX || nodoActual[1] != taxiY);
  return caminoMinimo;
}

std::vector<std::vector<int>> Taxi::CaminoMinimo8Traza(bool distancia) {

  std::vector<std::vector<Nodo>> matrizNodos;
  std::vector<std::vector<int>> abierta;
  std::vector<std::vector<int>> cerrada;

  std::vector<int> nodoActual {taxiX, taxiY};

  Nodo nodoStart(0, 0, taxiX, taxiY);

  nodoStart.set_h(Heuristica(distancia, taxiX, taxiY));

  matrizNodos.resize(world.GetDimensionX());
  for (int i = 0; i < matrizNodos.size(); i++) {
    matrizNodos[i].resize(world.GetDimensionY());
  }
  
  matrizNodos[taxiX][taxiY] = nodoStart;

  abierta.push_back(nodoActual);

  int level[world.GetDimensionX()*world.GetDimensionY()] = {0}; 
  int levelPath[world.GetDimensionX()*world.GetDimensionY()] = {0};
  int levelBordes[8][world.GetDimensionX()*world.GetDimensionY()] = {0};
  std::vector<std::vector<std::vector<int>>> levelMatrizBordes;
  sf::RenderWindow window(sf::VideoMode(1000, 800), "Mapa");            // Abrimos una ventana nueva
  sf::View vista(sf::Vector2f((world.GetDimensionY()*32)/2, (world.GetDimensionX()*32)/2), sf::Vector2f(window.getSize().x, window.getSize().y));
  window.setView(vista);
  Representacion(world, level);                            // Obtenemos un array de enteros con el mundo para representarlo en ventana
  levelMatrizBordes = Representacion(world);               // Obtenemos los array de enteros con los bordes de casilla para representarlo en
  for (int i = 0; i < levelMatrizBordes.size(); i++) {                  // ventana, la función devuelve un array de matrices así que la convertiremos con
    ConvertToArray(levelMatrizBordes[i], levelBordes[i]);
  }
  Mapa background;                                                      // Creamos y cargamos un mapa con el mundo
  if (!background.load("./sprites/casillas.png", sf::Vector2u(32, 32), level, world.GetDimensionY(), world.GetDimensionX())) {
  }
  Mapa bordes[8];
  for (int i = 0; i < 8; i++) {                                         // Creamos y cargamos los 8 mapas de bordes de casilla
    if (!bordes[i].load("./sprites/bordes.png", sf::Vector2u(32, 32), levelBordes[i], world.GetDimensionY(), world.GetDimensionX())) {
    }
  }

  sf::Vector2f oldPos;
  bool mover = false;

  while ((nodoActual[0] != destinoX || nodoActual[1] != destinoY) && !abierta.empty() && window.isOpen()) {
    float f = INFINITY;
    float h = INFINITY;
    std::vector<int> nodoSiguiente(2);
    for (int i = 0; i < abierta.size(); i++) {
      /*if (matrizNodos[abierta[i][0]][abierta[i][1]].get_h() < h) {
        h = matrizNodos[abierta[i][0]][abierta[i][1]].get_h();
        nodoSiguiente[0] = abierta[i][0];
        nodoSiguiente[1] = abierta[i][1];
      }*/
      if ((matrizNodos[abierta[i][0]][abierta[i][1]].get_h() + matrizNodos[abierta[i][0]][abierta[i][1]].get_g() + 1) < f) {
        f = (matrizNodos[abierta[i][0]][abierta[i][1]].get_h() + matrizNodos[abierta[i][0]][abierta[i][1]].get_g() + 1);
        nodoSiguiente[0] = abierta[i][0];
        nodoSiguiente[1] = abierta[i][1];
      }
    }
    for (int i = 0; i < abierta.size(); i++) {
      if (abierta[i][0] == nodoSiguiente[0] && abierta[i][1] == nodoSiguiente[1]) {
        abierta.erase(abierta.begin() + i);
      }
    }
    cerrada.push_back(nodoSiguiente);
    nodoActual = nodoSiguiente;

    VecinoArriba(nodoActual, cerrada, abierta, matrizNodos, distancia);
    VecinoDer(nodoActual, cerrada, abierta, matrizNodos, distancia);
    VecinoAbajo(nodoActual, cerrada, abierta, matrizNodos, distancia);
    VecinoIzq(nodoActual, cerrada, abierta, matrizNodos, distancia);
    VecinoArribaDer(nodoActual, cerrada, abierta, matrizNodos, distancia);
    VecinoArribaIzq(nodoActual, cerrada, abierta, matrizNodos, distancia);
    VecinoAbajoDer(nodoActual, cerrada, abierta, matrizNodos, distancia);
    VecinoAbajoIzq(nodoActual, cerrada, abierta, matrizNodos, distancia);

    Traza(nodoActual, matrizNodos, levelPath, window, mover, vista, oldPos, bordes, background);
  }

  std::vector<std::vector<int>> caminoMinimo;
  if (nodoActual[0] != destinoX && nodoActual[1] != destinoY) {
    return caminoMinimo;
  }
  caminoMinimo.push_back(nodoActual);                                                      // Creamos el vector con el camino mínimo empezando por el destino

  do {                                                                                     // Metemos por orden los predecesores de cada casilla en orden inverso
    caminoMinimo.push_back(matrizNodos[nodoActual[0]][nodoActual[1]].get_padre());         // dentro del vector hasta llegar a la casilla de inicio del taxi
    nodoActual[0] = caminoMinimo[caminoMinimo.size() - 1][0];
    nodoActual[1] = caminoMinimo[caminoMinimo.size() - 1][1];
  } while (nodoActual[0] != taxiX || nodoActual[1] != taxiY);
  
  return caminoMinimo;
}


float Taxi::Heuristica(bool distancia, int coordx, int coordy) {

  if (distancia == 0) {
    float manhattan = ((abs(coordx - destinoX)) + (abs(coordy - destinoY)) * 1.1);
    return manhattan;
  }
  else {
    float euclidea = (sqrt(pow((coordx - destinoX), 2) + pow((coordy - destinoY), 2)) * 1.5);
    return euclidea;
  }
}

void Taxi::Traza (std::vector<int>& nodoActual, std::vector<std::vector<Nodo>>& matrizNodos, int levelPath[], sf::RenderWindow& window, bool& mover, sf::View& vista, sf::Vector2f& oldPos, Mapa bordes[], Mapa& background) {

    std::vector<std::vector<int>> caminoMinimo;
    std::vector<int> nodoAuxiliar = nodoActual;
    caminoMinimo.push_back(nodoAuxiliar);
    do {                                                                                     // Metemos por orden los predecesores de cada casilla en orden inverso
      caminoMinimo.push_back(matrizNodos[nodoAuxiliar[0]][nodoAuxiliar[1]].get_padre());         // dentro del vector hasta llegar a la casilla de inicio del taxi
      nodoAuxiliar[0] = caminoMinimo[caminoMinimo.size() - 1][0];
      nodoAuxiliar[1] = caminoMinimo[caminoMinimo.size() - 1][1];
    } while (nodoAuxiliar[0] != taxiX || nodoAuxiliar[1] != taxiY);
    Representacion(caminoMinimo, world.GetDimensionX(), world.GetDimensionY(), levelPath);
    Mapa path;                                                            // Creamos y cargamos un mapa con el camino
    if (!path.load("./sprites/camino.png", sf::Vector2u(32, 32), levelPath, world.GetDimensionY(), world.GetDimensionX())) {
    }

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

void Taxi::BenchmarkSet(Mundo mainWorld, int coordX, int coordY, int destX, int destY) {
  world = mainWorld;
  taxiX = coordX;
  taxiY = coordY;
  destinoX = destX;
  destinoY = destY;
}
