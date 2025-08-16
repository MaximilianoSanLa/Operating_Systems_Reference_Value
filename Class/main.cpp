#include <iostream>
#include <vector>
#include <limits>
#include <memory>
#include "persona.h"
#include "generador.h"
#include "monitor.h"
#include <map>

/**
 * Muestra el menú principal de la aplicación.
 * 
 * POR QUÉ: Guiar al usuario a través de las funcionalidades disponibles.
 * CÓMO: Imprimiendo las opciones en consola.
 * PARA QUÉ: Interacción amigable con el usuario.
 */
void mostrarMenu() {
    std::cout << "\n\n=== MENÚ PRINCIPAL ===";
    std::cout << "\n0. Crear nuevo conjunto de datos";
    std::cout << "\n1. Mostrar resumen de todas las personas";
    std::cout << "\n2. Mostrar personas mas longevas";
    std::cout << "\n3. Mostrar personas mas longevas por ciudad";
    std::cout << "\n4. Mostrar detalle completo por índice";
    std::cout << "\n5. Buscar persona por ID";
    std::cout << "\n6. Mostrar estadísticas de rendimiento";
    std::cout << "\n7. Exportar estadísticas a CSV";
    std::cout << "\n8. Salir";
    std::cout << "\nSeleccione una opción: ";

}
bool esMasViejoVal(std::string f1, std::string f2) {
    int d1, m1, a1;
    int d2, m2, a2;
    char sep;

    std::stringstream ss1(f1); // f1 y f2 son copias
    std::stringstream ss2(f2);

    ss1 >> d1 >> sep >> m1 >> sep >> a1;
    ss2 >> d2 >> sep >> m2 >> sep >> a2;

    if (a1 != a2) return a1 < a2;
    if (m1 != m2) return m1 < m2;
    return d1 < d2;
}

bool mismaEdadVal(std::string f1, std::string f2) {
    return f1 == f2;  // compara las copias
}

bool esMasViejo(const std::string& f1, const std::string& f2) {
    int d1, m1, a1;
    int d2, m2, a2;
    char sep;

    std::stringstream ss1(f1);
    std::stringstream ss2(f2);

    ss1 >> d1 >> sep >> m1 >> sep >> a1;
    ss2 >> d2 >> sep >> m2 >> sep >> a2;

    if (a1 != a2) return a1 < a2;   // más viejo = año más pequeño
    if (m1 != m2) return m1 < m2;   // mismo año, comparar mes
    return d1 < d2;                 // mismo año y mes, comparar día
}

bool mismaEdad(const std::string& f1, const std::string& f2) {
    return f1 == f2;
}




std::vector<Persona> personasMasLongevasVal(std::vector<Persona> personas) {
    std::vector<Persona> resultado;
    Persona masLongeva = personas[0];  

    for (Persona p : personas) {  
        if (esMasViejoVal(p.getFechaNacimiento(), masLongeva.getFechaNacimiento())) {
            masLongeva = p;  
            resultado.clear();
            resultado.push_back(p);
        } 
        else if (mismaEdadVal(p.getFechaNacimiento(), masLongeva.getFechaNacimiento())) {
            resultado.push_back(p);
        }
    }
    return resultado;  
}

std::map<std::string, std::vector<Persona>> personasMasLongevasPorCiudadVal(std::vector<Persona> personas) {
    std::map<std::string, std::vector<Persona>> resultado;

    for (Persona p : personas) {
        auto& lista = resultado[p.getCiudadNacimiento()];
        if (lista.empty() || esMasViejoVal(p.getFechaNacimiento(), lista[0].getFechaNacimiento())) {
            lista.clear();
            lista.push_back(p);
        } 
        else if (mismaEdadVal(p.getFechaNacimiento(), lista[0].getFechaNacimiento())) {
            lista.push_back(p);
        }
    }
    return resultado;
}

std::vector<const Persona*> personasMasLongevasRef(const std::vector<Persona>& personas) {
    std::vector<const Persona*> resultado;
    const Persona* masLongeva = &personas[0];  

    for (const Persona& p : personas) {
        if (esMasViejo(p.getFechaNacimiento(), masLongeva->getFechaNacimiento())) {
            masLongeva = &p;
            resultado.clear();
            resultado.push_back(&p);
        } 
        else if (mismaEdad(p.getFechaNacimiento(), masLongeva->getFechaNacimiento())) {
            resultado.push_back(&p);
        }
    }
    return resultado;  
}

std::map<std::string, std::vector<const Persona*>> personasMasLongevasPorCiudadRef(const std::vector<Persona>& personas) {
    std::map<std::string, std::vector<const Persona*>> resultado;

    for (const Persona& p : personas) {
        auto& lista = resultado[p.getCiudadNacimiento()];
        if (lista.empty() || esMasViejo(p.getFechaNacimiento(), lista[0]->getFechaNacimiento())) {
            lista.clear();
            lista.push_back(&p);
        } 
        else if (mismaEdad(p.getFechaNacimiento(), lista[0]->getFechaNacimiento())) {
            lista.push_back(&p);
        }
    }
    return resultado;
}

/**
 * Punto de entrada principal del programa.
 * 
 * POR QUÉ: Iniciar la aplicación y manejar el flujo principal.
 * CÓMO: Mediante un bucle que muestra el menú y procesa la opción seleccionada.
 * PARA QUÉ: Ejecutar las funcionalidades del sistema.
 */
int main() {
    srand(time(nullptr)); // Semilla para generación aleatoria
    
    // Puntero inteligente para gestionar la colección de personas
    // POR QUÉ: Evitar fugas de memoria y garantizar liberación automática.
    std::unique_ptr<std::vector<Persona>> personas = nullptr;
    
    Monitor monitor; // Monitor para medir rendimiento
    
    int opcion;
    do {
        mostrarMenu();
        std::cin >> opcion;
        
        // Variables locales para uso en los casos
        size_t tam = 0;
        int indice;
        std::string idBusqueda;

        long memoria_inicio = monitor.obtener_memoria();
        
        switch(opcion) {
            case 0: { // Crear nuevo conjunto de datos
                int n;
                std::cout << "\nIngrese el número de personas a generar: ";
                std::cin >> n;
                
                // Iniciar medición de tiempo y memoria para la operación actual
                monitor.iniciar_tiempo();

                if (n <= 0) {
                    std::cout << "Error: Debe generar al menos 1 persona\n";
                    break;
                }
                
                // Generar el nuevo conjunto de personas
                auto nuevasPersonas = generarColeccion(n);
                tam = nuevasPersonas.size();
                
                // Mover el conjunto al puntero inteligente (propiedad única)
                personas = std::make_unique<std::vector<Persona>>(std::move(nuevasPersonas));
                
                // Medir tiempo y memoria usada
                double tiempo_gen = monitor.detener_tiempo();
                long memoria_gen = monitor.obtener_memoria() - memoria_inicio;
                
                std::cout << "Generadas " << tam << " personas en " 
                          << tiempo_gen << " ms, Memoria: " << memoria_gen << " KB\n";
                
                // Registrar la operación
                monitor.registrar("Crear datos", tiempo_gen, memoria_gen);
                break;
            }
            case 1:{
                if (!personas || personas->empty()) {
                    std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                    break;
                }
                memoria_inicio = monitor.obtener_memoria();
                monitor.iniciar_tiempo();
                auto longevos=personasMasLongevasRef(*personas);
                std::cout << "\nPersonas más longevas por ref:\n";
                for (const auto& p : longevos) {
                    std::cout << "Nombre: " << p->getNombre() << " "
                  << p->getApellido() << " | "
                  << "Ciudad: " << p->getCiudadNacimiento() << " | "
                  << "Fecha de nacimiento: " << p->getFechaNacimiento() << "\n";
                }
                double tiempo_mostrar = monitor.detener_tiempo();
                long memoria_mostrar = monitor.obtener_memoria() - memoria_inicio;
                monitor.registrar("Mostrar resumen", tiempo_mostrar, memoria_mostrar);
                
                


                break;
            }


            case 2:{
                if (!personas || personas->empty()) {
                    std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                    break;
                }
                memoria_inicio = monitor.obtener_memoria();
                monitor.iniciar_tiempo();
                auto longevos = personasMasLongevasVal(*personas);
                std::cout << "\nPersonas más longevas por ciudad (by value):\n";
                for (const auto& p : longevos) {
                    std::cout << "Nombre: " << p.getNombre() << " "
                  << p.getApellido() << " | "
                  << "Ciudad: " << p.getCiudadNacimiento() << " | "
                  << "Fecha de nacimiento: " << p.getFechaNacimiento() << "\n";
                }
                double tiempo_mostrar = monitor.detener_tiempo();
                long memoria_mostrar = monitor.obtener_memoria() - memoria_inicio;
                monitor.registrar("Mostrar resumen", tiempo_mostrar, memoria_mostrar);
                break;
            }


            case 3: { // Mostrar resumen de todas las personas
                if (!personas || personas->empty()) {
                    std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                    break;
                }
                
                tam = personas->size();
                std::cout << "\n=== RESUMEN DE PERSONAS (" << tam << ") ===\n";
                for(size_t i = 0; i < tam; ++i) {
                    std::cout << i << ". ";
                    (*personas)[i].mostrarResumen();
                    std::cout << "\n";
                }
                
                double tiempo_mostrar = monitor.detener_tiempo();
                long memoria_mostrar = monitor.obtener_memoria() - memoria_inicio;
                monitor.registrar("Mostrar resumen", tiempo_mostrar, memoria_mostrar);
                break;
            }
                
            case 4: { // Mostrar detalle por índice
                if (!personas || personas->empty()) {
                    std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                    break;
                }
                
                tam = personas->size();
                std::cout << "\nIngrese el índice (0-" << tam-1 << "): ";
                if(std::cin >> indice) {
                    if(indice >= 0 && static_cast<size_t>(indice) < tam) {
                        (*personas)[indice].mostrar();
                    } else {
                        std::cout << "Índice fuera de rango!\n";
                    }
                } else {
                    std::cout << "Entrada inválida!\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                
                double tiempo_detalle = monitor.detener_tiempo();
                long memoria_detalle = monitor.obtener_memoria() - memoria_inicio;
                monitor.registrar("Mostrar detalle", tiempo_detalle, memoria_detalle);
                break;
            }
                
            case 5: { // Buscar por ID
                if (!personas || personas->empty()) {
                    std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                    break;
                }
                
                std::cout << "\nIngrese el ID a buscar: ";
                std::cin >> idBusqueda;
                
                if(const Persona* encontrada = buscarPorID(*personas, idBusqueda)) {
                    encontrada->mostrar();
                } else {
                    std::cout << "No se encontró persona con ID " << idBusqueda << "\n";
                }
                
                double tiempo_busqueda = monitor.detener_tiempo();
                long memoria_busqueda = monitor.obtener_memoria() - memoria_inicio;
                monitor.registrar("Buscar por ID", tiempo_busqueda, memoria_busqueda);
                break;
            }
                
            case 6: // Mostrar estadísticas de rendimiento
                monitor.mostrar_resumen();
                break;
                
            case 7: // Exportar estadísticas a CSV
                monitor.exportar_csv();
                break;
                
            case 8: // Salir
                std::cout << "Saliendo...\n";
                break;
                
            default:
                std::cout << "Opción inválida!\n";
        }
        
        // Mostrar estadísticas de la operación (excepto para opciones 4,5,6)
        if (opcion >= 0 && opcion <= 3) {
            double tiempo = monitor.detener_tiempo();
            long memoria = monitor.obtener_memoria() - memoria_inicio;
            monitor.mostrar_estadistica("Opción " + std::to_string(opcion), tiempo, memoria);
        }
        
    } while(opcion != 8);
    
    return 0;
}