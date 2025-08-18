#include <iostream>
#include <vector>
#include <limits>
#include <memory>
#include "persona.h"
#include "generador.h"
#include "monitor.h"
#include <map>
#include <string>

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
    std::cout << "\n4. Mostrar persona con mayor patrimonio";
    std::cout << "\n5. Mostrar persona con mayor patrimonio en una ciudad";
    std::cout << "\n6. Mostrar persona con mayor patrimonio en un grupo";
    std::cout << "\n7. Lista y cuenta de personas por grupo";
    std::cout << "\n8. Mostrar detalle completo por índice";
    std::cout << "\n9. Buscar persona por ID";
    std::cout << "\n10. Mostrar estadísticas de rendimiento";
    std::cout << "\n11. Exportar estadísticas a CSV";
    std::cout << "\n12. Ciudades con patrimonio promedio más alto";
    std::cout << "\n13. Porcentaje de personas mayores a 60 anios";
    std::cout << "\n14. Personas entre 18-25 en las ciudades";
    std::cout << "\n15. Salir";
    std::cout << "\nSeleccione una opción: ";

}

std::map<std::string, double> ciudadesPatrimonioPromRef(const std::vector<Persona>& personas) {
    std::map<std::string, double> suma;
    std::map<std::string, int> conteo;

    for (const auto& p : personas) {
        suma[p.getCiudadNacimiento()] += p.getPatrimonio();
        conteo[p.getCiudadNacimiento()]++;
    }

    std::map<std::string, double> promedio;
    for (auto& [ciudad, total] : suma) {
        promedio[ciudad] = total / conteo[ciudad];
    }
    return promedio;
}

std::map<std::string, double> ciudadesPatrimonioPromVal(std::vector<Persona> personas) {
    return ciudadesPatrimonioPromRef(personas); // reuse logic
}

double porcentajeMayores60Ref(const std::vector<Persona>& personas) {
    if (personas.empty()) return 0.0;
    int mayores = 0;
    for (const auto& p : personas) {
        if (p.getEdad() > 60) mayores++;
    }
    return (100.0 * mayores) / personas.size();
}

double porcentajeMayores60Val(std::vector<Persona> personas) {
    return porcentajeMayores60Ref(personas);
}

std::map<std::string, std::vector<Persona>> personas18a25Ref(const std::vector<Persona>& personas) {
    std::map<std::string, std::vector<Persona>> resultado;
    for (const auto& p : personas) {
        if (p.getEdad() >= 18 && p.getEdad() <= 25) {
            resultado[p.getCiudadNacimiento()].push_back(p);
        }
    }
    return resultado;
}

std::map<std::string, std::vector<Persona>> personas18a25Val(std::vector<Persona> personas) {
    return personas18a25Ref(personas);
}

void listarYContarPorGrupoVal(std::vector<Persona> personas) {
    std::map<char, int> contador;

    std::cout << "\n[Por valor] Listado de personas por grupo:\n";
    for (const auto& p : personas) {
        std::cout << "Nombre: " << p.getNombre() 
                  << " " << p.getApellido()
                  << " | Grupo: " << p.getGrupo() << "\n";
        contador[p.getGrupo()]++;
    }

    std::cout << "\n[Por valor] Conteo por grupo:\n";
    for (const auto& par : contador) {
        std::cout << "Grupo " << par.first << ": " << par.second << " personas\n";
    }
}

// --- Por referencia ---
void listarYContarPorGrupoRef(const std::vector<Persona>& personas) {
    std::map<char, int> contador;

    std::cout << "\n[Por referencia] Listado de personas por grupo:\n";
    for (const auto& p : personas) {
        std::cout << "Nombre: " << p.getNombre() 
                  << " " << p.getApellido()
                  << " | Grupo: " << p.getGrupo() << "\n";
        contador[p.getGrupo()]++;
    }

    std::cout << "\n[Por referencia] Conteo por grupo:\n";
    for (const auto& par : contador) {
        std::cout << "Grupo " << par.first << ": " << par.second << " personas\n";
    }
}


const Persona& mayorPatrimonioPaisRef(const std::vector<Persona>& personas){
    const Persona* max = &personas[0];
    for (const auto& p : personas) {
        if (p.getPatrimonio() > max->getPatrimonio()) {
            max = &p;
        }
    }
    return *max;
}

// Ciudad
const Persona& mayorPatrimonioCiudadRef(const std::vector<Persona>& personas, const std::string& ciudad){
    const Persona* max = nullptr;
    for (const auto& p : personas) {
        if (p.getCiudadNacimiento() == ciudad) {
            if (!max || p.getPatrimonio() > max->getPatrimonio()) {
                max = &p;
            }
        }
    }
    return *max;
}


// Grupo
const Persona& mayorPatrimonioGrupoRef(const std::vector<Persona>& personas, char grupo){
    const Persona* max = nullptr;
    for (const auto& p : personas) {
        if (p.getGrupo() == grupo) {
            if (!max || p.getPatrimonio() > max->getPatrimonio()) {
                max = &p;
            }
        }
    }
    return *max;
}

// ===============================
// MÉTODOS POR VALOR
// ===============================

// País
Persona mayorPatrimonioPaisVal(std::vector<Persona> personas){
    Persona max = personas[0];
    for (auto p : personas) {
        if (p.getPatrimonio() > max.getPatrimonio()) {
            max = p;
        }
    }
    return max;
}

// Ciudad
Persona mayorPatrimonioCiudadVal(std::vector<Persona> personas, std::string ciudad){
    Persona max=personas[0];
    bool found = false;
    for (auto p : personas) {
        if (p.getCiudadNacimiento() == ciudad) {
            if (!found || p.getPatrimonio() > max.getPatrimonio()) {
                max = p;
                found = true;
            }
        }
    }
    return max;
}

// Grupo
Persona mayorPatrimonioGrupoVal(std::vector<Persona> personas, char grupo){
    Persona max=personas[0];
    bool found = false;
    for (auto p : personas) {
        if (p.getGrupo() == grupo) {
            if (!found || p.getPatrimonio() > max.getPatrimonio()) {
                max = p;
                found = true;
            }
        }
    }
    return max;
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
        long memoria_val;
        double tiempo_val;
        std::map<std::string, double> val;
        long memoria_ref;
        double tiempo_ref;
        std::map<std::string, double>  ref;
        std::map<std::string, std::vector<Persona>> val1;
        std::map<std::string, std::vector<Persona>> ref1;

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
            case 2:{//personas mas longevas
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


            case 3:{ //personas mas longevas por ciudad
                if (!personas || personas->empty()) {
                    std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                    break;
                }
                memoria_inicio = monitor.obtener_memoria();
                monitor.iniciar_tiempo();
                auto longevos = personasMasLongevasVal(*personas);
                double tiempo_mostrar = monitor.detener_tiempo();
                std::cout << "\nPersonas más longevas por ciudad (by value):\n";
                for (const auto& p : longevos) {
                    std::cout << "Nombre: " << p.getNombre() << " "
                  << p.getApellido() << " | "
                  << "Ciudad: " << p.getCiudadNacimiento() << " | "
                  << "Fecha de nacimiento: " << p.getFechaNacimiento() << "\n";
                }
                long memoria_mostrar = monitor.obtener_memoria() - memoria_inicio;
                monitor.registrar("Mostrar resumen", tiempo_mostrar, memoria_mostrar);
                break;
            }
            case 4: { // Mostrar Persona con mayor patrimonio en el pais
                monitor.iniciar_tiempo();
                Persona maxRef = mayorPatrimonioPaisRef(*personas);
                double tiempo_ref = monitor.detener_tiempo();
                long memoria_ref = monitor.obtener_memoria() - memoria_inicio;
                std::cout << "Mayor patrimonio en el país (REF): " << maxRef.getNombre()
                << " " << maxRef.getApellido()
                << " con patrimonio: " << maxRef.getPatrimonio() << "\n";
                monitor.registrar("Mayor patrimonio país (Ref)", tiempo_ref, memoria_ref);

                monitor.iniciar_tiempo();
                Persona maxVal = mayorPatrimonioPaisVal(*personas);
                double tiempo_val = monitor.detener_tiempo();
                long memoria_val = monitor.obtener_memoria() - memoria_inicio;
                std::cout << "Mayor patrimonio en el país (VAL): " << maxVal.getNombre()
                << " " << maxVal.getApellido()
                << " con patrimonio: " << maxVal.getPatrimonio() << "\n";
                monitor.registrar("Mayor patrimonio país (Val)", tiempo_val, memoria_val);
                break;
            }
        case 5: { // Mostrar Persona con mayor patrimonio en una ciudad
            //std::string ciudad;
            short ciudad_id;
            std::cout << "Ingrese ID ciudad: ";
            std::cin >> ciudad_id;
            std::string ciudades[21]={"todos", "Bogotá","Medellín","Cali","Barranquilla","Cartagena","Bucaramanga","Pereira",
                "Santa Marta","Cúcuta","Ibagué","Manizales","Pasto","Neiva","Villavicencio","Armenia","Sincelejo","Valledupar",
                "Montería", "Popayán", "Tunja"
            };
            std::string ciudad = (ciudad_id < 22)?ciudades[ciudad_id]:"todos";

            monitor.iniciar_tiempo();
            Persona maxRef = mayorPatrimonioCiudadRef(*personas, ciudad);
            double tiempo_ref = monitor.detener_tiempo();
            long memoria_ref = monitor.obtener_memoria() - memoria_inicio;
            std::cout << "Mayor patrimonio en " << ciudad << " (REF): " 
              << maxRef.getNombre() << " " << maxRef.getApellido()
              << " con patrimonio: " << maxRef.getPatrimonio() << "\n";
            monitor.registrar("Mayor patrimonio ciudad (Ref)", tiempo_ref, memoria_ref);

            monitor.iniciar_tiempo();
            Persona maxVal = mayorPatrimonioCiudadVal(*personas, ciudad);
            double tiempo_val = monitor.detener_tiempo();
            long memoria_val = monitor.obtener_memoria() - memoria_inicio;
            std::cout << "Mayor patrimonio en " << ciudad << " (VAL): " 
              << maxVal.getNombre() << " " << maxVal.getApellido()
              << " con patrimonio: " << maxVal.getPatrimonio() << "\n";
            monitor.registrar("Mayor patrimonio ciudad (Val)", tiempo_val, memoria_val);
        break;
        }
        case 6: { // Mostrar Persona con mayor patrimonio en un grupo
            char grupo;
            std::cout << "Ingrese grupo (A/B/C): ";
            std::cin >> grupo;

            monitor.iniciar_tiempo();
            Persona maxRef = mayorPatrimonioGrupoRef(*personas, grupo);
            double tiempo_ref = monitor.detener_tiempo();
            long memoria_ref = monitor.obtener_memoria() - memoria_inicio;
            std::cout << "Mayor patrimonio en grupo " << grupo << " (REF): " 
              << maxRef.getNombre() << " " << maxRef.getApellido()
              << " con patrimonio: " << maxRef.getPatrimonio() << "\n";
            monitor.registrar("Mayor patrimonio grupo (Ref)", tiempo_ref, memoria_ref);

            monitor.iniciar_tiempo();
            Persona maxVal = mayorPatrimonioGrupoVal(*personas, grupo);
            double tiempo_val = monitor.detener_tiempo();
            long memoria_val = monitor.obtener_memoria() - memoria_inicio;
            std::cout << "Mayor patrimonio en grupo " << grupo << " (VAL): " 
              << maxVal.getNombre() << " " << maxVal.getApellido()
              << " con patrimonio: " << maxVal.getPatrimonio() << "\n";
            monitor.registrar("Mayor patrimonio grupo (Val)", tiempo_val, memoria_val);
        break;
    }
        case 7: { // Lista y cuenta de personas por grupo
            monitor.iniciar_tiempo();
            listarYContarPorGrupoRef(*personas);
            double tiempo_ref = monitor.detener_tiempo();
            long memoria_ref = monitor.obtener_memoria() - memoria_inicio;
            monitor.registrar("Listar y contar por grupo (Ref)", tiempo_ref, memoria_ref);

            monitor.iniciar_tiempo();
            listarYContarPorGrupoVal(*personas);
            double tiempo_val = monitor.detener_tiempo();
            long memoria_val = monitor.obtener_memoria() - memoria_inicio;
            monitor.registrar("Listar y contar por grupo (Val)", tiempo_val, memoria_val);
            break;
        }


            case 1: { // Mostrar resumen de todas las personas
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
                
            case 8: { // Mostrar detalle por índice
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
                
            case 9: { // Buscar por ID
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
                
            case 10: // Mostrar estadísticas de rendimiento
                monitor.mostrar_resumen();
                break;
                
            case 11: // Exportar estadísticas a CSV
                monitor.exportar_csv();
                break;
            case 12: //Ciudades con patrimonio mas alto
                monitor.iniciar_tiempo();
                ref = ciudadesPatrimonioPromRef(*personas);
                tiempo_ref = monitor.detener_tiempo();
                memoria_ref = monitor.obtener_memoria() - memoria_inicio;
                std::cout << "Patrimonio promedio por ciudad (REF):\n";
                for (auto& [ciudad, prom] : ref) {
                    std::cout << ciudad << ": " << prom << "\n";
                }
                monitor.registrar("Patrimonio promedio ciudades (Ref)", tiempo_ref, memoria_ref);
            
                monitor.iniciar_tiempo();
                val = ciudadesPatrimonioPromVal(*personas);
                tiempo_val = monitor.detener_tiempo();
                memoria_val = monitor.obtener_memoria() - memoria_inicio;
                std::cout << "Patrimonio promedio por ciudad (VAL):\n";
                for (auto& [ciudad, prom] : val) {
                    std::cout << ciudad << ": " << prom << "\n";
                }
                monitor.registrar("Patrimonio promedio ciudades (Val)", tiempo_val, memoria_val);
                break;
            case 13: //Porcentaje de personas mayores a 60 anios
                monitor.iniciar_tiempo();

                ref = ciudadesPatrimonioPromRef(*personas);
                tiempo_ref = monitor.detener_tiempo();
                memoria_ref = monitor.obtener_memoria() - memoria_inicio;
                std::cout << "[REF] Ciudades con patrimonio promedio más alto:\n";
                for (auto &p : ref) {
                std::cout << "  " << p.first << ": " << p.second << "\n";
                }
                monitor.registrar("Patrimonio promedio REF", tiempo_ref, memoria_ref);

                monitor.iniciar_tiempo();
                val = ciudadesPatrimonioPromVal(*personas);
                tiempo_val = monitor.detener_tiempo();
                memoria_val = monitor.obtener_memoria() - memoria_inicio;
                std::cout << "[VAL] Ciudades con patrimonio promedio más alto:\n";
                for (auto &p : val) {
                    std::cout << "  " << p.first << ": " << p.second << "\n";
                }
                monitor.registrar("Patrimonio promedio VAL", tiempo_val, memoria_val);
                break;
            case 14: //Personas entre 18-25 anios en las ciudades
                monitor.iniciar_tiempo();
                ref1 = personas18a25Ref(*personas);
                tiempo_ref = monitor.detener_tiempo();
                memoria_ref = monitor.obtener_memoria() - memoria_inicio;
                std::cout << "[REF] Personas 18-25 por ciudad:\n";
                for (auto &p : ref1) {
                    std::cout << "  " << p.first << ": ";
                    for (const auto& persona : p.second) {
                         std::cout << persona.getNombre() << " "; // or getID()
                    }
                    std::cout << "\n";
                }

                monitor.registrar("Personas 18-25 REF", tiempo_ref, memoria_ref);

                monitor.iniciar_tiempo();
                
                val1 = personas18a25Val(*personas);
                tiempo_val = monitor.detener_tiempo();
                memoria_val = monitor.obtener_memoria() - memoria_inicio;
                std::cout << "[VAL] Personas 18-25 por ciudad:\n";
                for (auto &p : val1) {
                    std::cout << "  " << p.first << ": ";
                    for (const auto& persona : p.second) {
                    std::cout << persona.getNombre() << " "; // or getID()
                    }
                std::cout << "\n";
                }
                monitor.registrar("Personas 18-25 VAL", tiempo_val, memoria_val);
                break;
            case 15: // Salir
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
        
    } while(opcion !=15);
    
    return 0;
}