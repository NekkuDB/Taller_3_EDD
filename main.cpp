#include <iostream>
#include "CSVReader.h"
#include <vector>
#include <string>
#include <unordered_map>
#include <list>
#include <limits>
#include <cctype>

struct Nodo {
  int id;
  std::string nombre;
  std::string tipo;
};

struct Arista {
  Nodo* origen;
  Nodo* destino;
  int velocidad;
  int distancia;
};

int main() {
  std::vector<Nodo> nodos;
  std::unordered_map<std::string, Nodo*> nodoMap;
  std::vector<Arista> aristas;

    // ... [resto del código inicial]

    int pesoArchivo, numeroParticiones;
    std::cout << "Ingrese el peso del archivo en MB: ";
    std::cin >> pesoArchivo;

    numeroParticiones = (pesoArchivo + 299) / 300; // Asume que la capacidad máxima por conexión es de 300 MB
    std::cout << "Número de particiones necesarias: " << numeroParticiones << std::endl;

    std::string nombreDestino;
    std::cout << "Ingrese el nombre del nodo destino: ";
    std::cin >> nombreDestino;
    Nodo* nodoDestino = nodoMap[nombreDestino]; // Asegúrate de que este nodo existe en tu mapa




  CSVReader readerServidores("servidores.csv");
  auto datosServidores = readerServidores.readData();

  for (auto& fila : datosServidores) {
  Nodo nodo = {std::stoi(fila[0]), fila[1], fila[2]};
    nodos.push_back(nodo);
    nodoMap[nodo.nombre] = &nodos.back(); // Mapeo del nombre al Nodo
  }

  CSVReader readerConexiones("conexiones.csv");
  auto datosConexiones = readerConexiones.readData();

  for (auto& fila : datosConexiones) {
      Nodo* origen = nodoMap[fila[0]];
      Nodo* destino = nodoMap[fila[1]];
      int velocidad = std::stoi(fila[2]);
      int distancia = std::stoi(fila[3]);
    
      Arista arista = {origen, destino, velocidad, distancia};
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

  std::unordered_map<Nodo*, Nodo*> predecesores;
  
  // Inicialización
  std::vector<int> distancias(nodos.size(), std::numeric_limits<int>::max());
  distancias[nodoIndices[&nodos[0]]] = 0; // Inicializa la distancia del primer nodo a 0
 

  // Iteración sobre las aristas
  for (int iteracion = 0; iteracion < grafo.size() - 1; iteracion++) {
    for (const auto& arista : aristas) {
        Nodo* u = arista.origen;
        Nodo* v = arista.destino;
        int tiempoConexion = arista.distancia * numeroParticiones; // Tiempo total considerando las particiones

        if (distancias[nodoIndices[u]] + tiempoConexion < distancias[nodoIndices[v]]) {
            distancias[nodoIndices[v]] = distancias[nodoIndices[u]] + tiempoConexion;
            predecesores[v] = u;
        }
    }
  }

  // Detección de ciclo negativo
  for (const auto& arista : aristas) {
    Nodo* u = arista.origen;
    Nodo* v = arista.destino;
    int peso = arista.velocidad;

    if (distancias[nodoIndices[u]] != std::numeric_limits<int>::max() && distancias[nodoIndices[u]] + peso < distancias[nodoIndices[v]]) {
      // Se encontró un ciclo negativo
      std::cout << "El grafo contiene un ciclo de peso negativo." << std::endl;
      return 0;
    }
  }
  Nodo* actual = nodoDestino; // Asumiendo que tienes un nodoDestino
  while (actual != nullptr) {
      std::cout << "Nodo: " << actual->nombre << " - Tiempo hasta ahora: " << distancias[nodoIndices[actual]] << " segundos" << std::endl;
      actual = predecesores[actual];
  }
}

















