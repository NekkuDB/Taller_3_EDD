#include <iostream>
#include "CSVReader.h"
#include <vector>
#include <string>
#include <unordered_map>
#include <list>
#include <limits>
#include <cctype>
#include <fstream>

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



  std::string nombreOrigen;
  std::cout << "Ingrese el nombre del nodo origen: ";
  std::cin >> nombreOrigen;

  

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
      aristas.push_back(arista);
  }

  // Verificar existencia del nodo destino
  if (nodoMap.find(nombreDestino) == nodoMap.end()) {
      std::cerr << "Nodo destino no encontrado." << std::endl;
      return 1; // o manejar de otra manera
  }


  // Grafo representado como lista de adyacencia
  std::unordered_map<Nodo*, std::list<Arista>> grafo;
  for (const auto& arista : aristas) {
    Nodo* origen = arista.origen;
    int tiempoConexion = arista.distancia * numeroParticiones;
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
  std::vector<Nodo*> ruta;
  Nodo* actual = nodoDestino;
  while (actual != nullptr) {
      ruta.insert(ruta.begin(), actual); // Inserta al inicio para revertir la ruta
      actual = predecesores[actual]; // Sigue al predecesor
  }

 std::ofstream salida("ruta.csv");
  salida << "Nodo, Tiempo Acumulado\n";

  for (auto nodo : ruta) {
      std::cout << "Nodo: " << nodo->nombre << " - Tiempo acumulado: " << distancias[nodoIndices[nodo]] << " segundos" << std::endl;
      salida << nodo->nombre << ", " << distancias[nodoIndices[nodo]] << "\n";
  }

  salida.close();
  std::cout << "La ruta ha sido exportada a 'ruta.csv'." << std::endl;

  // Verificar existencia del nodo origen
  if (nodoMap.find(nombreOrigen) == nodoMap.end()) {
      std::cerr << "Nodo origen no encontrado." << std::endl;
      return 1;
  }
  Nodo* nodoOrigen = nodoMap[nombreOrigen];

  // Inicialización de distancias
  for (auto& nodo : nodos) {
      distancias[nodoIndices[&nodo]] = std::numeric_limits<int>::max();
  }
  distancias[nodoIndices[nodoOrigen]] = 0;

}
  


















