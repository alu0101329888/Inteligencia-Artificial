#ifndef TAXI_H
#define TAXI_H

#include "nodo.hpp"
#include "mundo.hpp"
#include "mapa.hpp"

class Taxi {
  private:
  
    int taxiX, taxiY;
    int destinoX, destinoY;
    Mundo world;
    
  public:

    Taxi(Mundo mainWorld, int coordX, int coordY, int destX, int destY);
    ~Taxi();

    void BenchmarkSet(Mundo mainWorld, int coordX, int coordY, int destX, int destY);

    bool MovDer(std::vector<int>);
    bool MovIzq(std::vector<int>);
    bool MovArriba(std::vector<int>);
    bool MovAbajo(std::vector<int>);
    bool MovArribaDer(std::vector<int>);
    bool MovArribaIzq(std::vector<int>);
    bool MovAbajoDer(std::vector<int>);
    bool MovAbajoIzq(std::vector<int>);

    void VecinoArriba (std::vector<int>& nodoActual, std::vector<std::vector<int>>& cerrada, std::vector<std::vector<int>>& abierta, std::vector<std::vector<Nodo>>& matrizNodos, bool distancia);
    void VecinoDer (std::vector<int>& nodoActual, std::vector<std::vector<int>>& cerrada, std::vector<std::vector<int>>& abierta, std::vector<std::vector<Nodo>>& matrizNodos, bool distancia);
    void VecinoAbajo (std::vector<int>& nodoActual, std::vector<std::vector<int>>& cerrada, std::vector<std::vector<int>>& abierta, std::vector<std::vector<Nodo>>& matrizNodos, bool distancia);
    void VecinoIzq (std::vector<int>& nodoActual, std::vector<std::vector<int>>& cerrada, std::vector<std::vector<int>>& abierta, std::vector<std::vector<Nodo>>& matrizNodos, bool distancia);
    void VecinoArribaDer (std::vector<int>& nodoActual, std::vector<std::vector<int>>& cerrada, std::vector<std::vector<int>>& abierta, std::vector<std::vector<Nodo>>& matrizNodos, bool distancia);
    void VecinoArribaIzq (std::vector<int>& nodoActual, std::vector<std::vector<int>>& cerrada, std::vector<std::vector<int>>& abierta, std::vector<std::vector<Nodo>>& matrizNodos, bool distancia);
    void VecinoAbajoDer (std::vector<int>& nodoActual, std::vector<std::vector<int>>& cerrada, std::vector<std::vector<int>>& abierta, std::vector<std::vector<Nodo>>& matrizNodos, bool distancia);
    void VecinoAbajoIzq (std::vector<int>& nodoActual, std::vector<std::vector<int>>& cerrada, std::vector<std::vector<int>>& abierta, std::vector<std::vector<Nodo>>& matrizNodos, bool distancia);

    float Heuristica(bool distancia, int coordX, int coordY);

    bool MovLegal(int movX, int movY);

    void PrintMundo(void);

    void ActualizarHorVer(std::vector<std::vector<Nodo>>& matrizNodos, std::vector<int> nodoActual, bool distancia, int x, int y);
    void ActualizarDiagonal(std::vector<std::vector<Nodo>>& matrizNodos, std::vector<int> nodoActual, bool distancia, int x, int y);

    std::vector<std::vector<int>> CaminoMinimo4(bool distancia, bool benchmark);
    std::vector<std::vector<int>> CaminoMinimo8(bool distancia, bool benchmark);
    std::vector<std::vector<int>> CaminoMinimo4Traza(bool distancia);
    std::vector<std::vector<int>> CaminoMinimo8Traza(bool distancia);

    int* Representacion(Mundo matriz, int level[]);
    int* Representacion(std::vector<std::vector<int>> camino, int dimensionX, int dimensionY, int levelPath[]);
    std::vector<std::vector<std::vector<int>>>  Representacion(Mundo matriz);

    void Traza (std::vector<int>& nodoActual, std::vector<std::vector<Nodo>>& matrizNodos, int levelPath[], sf::RenderWindow& window, bool& mover, sf::View& vista, sf::Vector2f& oldPos, Mapa bordes[], Mapa& background);
};

int* ConvertToArray (std::vector<std::vector<int>> level, int levelArray[]);

#endif
