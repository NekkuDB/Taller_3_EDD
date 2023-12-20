#include <iostream>
#include "CSVReader.h"
#include <vector>
#include <string>
#include <unordered_map>
#include <list>
#include <limits>

struct Nodo {
  std::string nombre;
  std::string ip;
  // Otros atributos...
};

struct Arista {
  Nodo* origen;
  Nodo* destino;
  int peso; // Ejemplo: tiempo de envío
};

int main() {
  std::vector<Nodo> nodos;
  std::unordered_map<std::string, Nodo*> nodoMap;
  std::vector<Arista> aristas;

  CSVReader readerServidores("servidores.csv");
  auto datosServidores = readerServidores.readData();

  for (auto& fila : datosServidores) {
    Nodo nodo = {fila[0], fila[1]}; // Asume que fila[0] es el nombre y fila[1] es la IP
    nodos.push_back(nodo);
    nodoMap[nodo.nombre] = &nodos.back(); // Mapeo del nombre al Nodo
  }

  CSVReader readerConexiones("conexiones.csv");
  auto datosConexiones = readerConexiones.readData();

  for (auto& fila : datosConexiones) {
    Nodo* origen = nodoMap[fila[0]]; // Asume que fila[0] es el nombre del nodo de origen
    Nodo* destino = nodoMap[fila[1]]; // Asume que fila[1] es el nombre del nodo de destino
    int peso = std::stoi(fila[2]); // Asume que fila[2] es el peso de la arista

    Arista arista = {origen, destino, peso};
    aristas.push_back(arista);
  }

  // Grafo representado como lista de adyacencia
  std::unordered_map<Nodo*, std::list<Arista>> grafo;

  for (const auto& arista : aristas) {
    Nodo* origen = arista.origen;
    grafo[origen].push_back(arista);
  }

  // Mapeo de Nodo a indices
  std::unordered_map<Nodo*, int> nodoIndices;
  int index = 0;
  for (auto& nodo : nodos) {
    nodoIndices[&nodo] = index++;
  }

  // Inicialización
  std::vector<int> distancias(nodos.size(), std::numeric_limits<int>::max());
  distancias[nodoIndices[&nodos[0]]] = 0; // Inicializa la distancia del primer nodo a 0
  
    int pesoArchivo;
    std::cout << "Ingrese el peso del archivo en MB: ";
    std::cin >> pesoArchivo;

    int numeroParticiones = pesoArchivo / 300; // Asumiendo que 300 MB es el máximo por conexión
    if (pesoArchivo % 300 != 0) {
        numeroParticiones++; // Añadir una partición extra para el residuo
    }

  // Iteración sobre las aristas
  for (int iteracion = 0; iteracion < grafo.size() - 1; iteracion++) {
    for (const auto& arista : aristas) {
      Nodo* u = arista.origen;
      Nodo* v = arista.destino;
      int peso = arista.peso;

      // Relajación
      if (distancias[nodoIndices[u]] != std::numeric_limits<int>::max() && distancias[nodoIndices[u]] + peso < distancias[nodoIndices[v]]) {
        distancias[nodoIndices[v]] = distancias[nodoIndices[u]] + peso;
      }
    }
  }

  // Detección de ciclo negativo
  for (const auto& arista : aristas) {
    Nodo* u = arista.origen;
    Nodo* v = arista.destino;
    int peso = arista.peso;

    if (distancias[nodoIndices[u]] != std::numeric_limits<int>::max() && distancias[nodoIndices[u]] + peso < distancias[nodoIndices[v]]) {
      // Se encontró un ciclo negativo
      std::cout << "El grafo contiene un ciclo de peso negativo." << std::endl;
      return 0;
    }
  }
}

