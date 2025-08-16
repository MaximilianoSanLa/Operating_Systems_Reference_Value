#include <iostream>
#include <vector>
#include <limits> // Para manejo de límites de entrada
#include <memory> // Para std::unique_ptr y std::make_unique
#include "persona.h"
#include "generador.h"
#include "task.h"
#include "monitor.h" // Nuevo header para monitoreo

void mostrarMenu() {
    std::cout << "\n\n=== MENÚ PRINCIPAL ===";
    std::cout << "\n0. Crear nuevo conjunto de datos";
    std::cout << "\n1. Mostrar resumen de todas las personas";
    std::cout << "\n2. Mostrar detalle completo por índice";
    std::cout << "\n3. Buscar persona por ID";
    std::cout << "\n4. Mostrar estadísticas de rendimiento";
    std::cout << "\n5. Exportar estadísticas a CSV";
    std::cout << "\n6. Obtener persona mas longeva en el pais";
    std::cout << "\n7. Obtener persona mas longeva por ciudad";
    std::cout << "\n8. Obtener persona con mayor patrimonio en el pais";
    std::cout << "\n9. Obtener persona con mayor patrimonio por ciudad";
    std::cout << "\n10. Obtener persona con mayor patrimonio por grupo";
    std::cout << "\n11. Listar por grupo";
    std::cout << "\n12. Salir";
    std::cout << "\nSeleccione una opción: ";
}

void mostrarCiudades() {
    std::cout << "\n\n=== LISTA DE CIUDADES ===";
    std::cout << "\n1. Bogotá";
    std::cout << "\n2. Medellín";
    std::cout << "\n3. Cali";
    std::cout << "\n4. Barranquilla";
    std::cout << "\n5. Cartagena";
    std::cout << "\n6. Bucaramanga";
    std::cout << "\n7. Pereira";
    std::cout << "\n8. Santa Marta";
    std::cout << "\n9. Cúcuta";
    std::cout << "\n10. Ibagué";
    std::cout << "\n11. Manizales";
    std::cout << "\n12. Pasto";
    std::cout << "\n13. Neiva";
    std::cout << "\n14. Villavicencio";
    std::cout << "\n15. Armenia";
    std::cout << "\n16. Sincelejo";
    std::cout << "\n17. Valledupar";
    std::cout << "\n18. Montería";
    std::cout << "\n19. Popayán";
    std::cout << "\n20. Tunja";
    std::cout << "\nSeleccione una ciudad: ";
}

void mostrarGrupos() {
    std::cout << "\n\n=== LISTA DE GRUPOS ===";
    std::cout << "\n1. A";
    std::cout << "\n2. B";
    std::cout << "\n3. C";
    std::cout << "\nSeleccione un grupo: ";
}


int main() {
    srand(time(nullptr));
    
    // Usar unique_ptr para manejar la colección de personas
    std::unique_ptr<std::vector<Persona>> personas = nullptr;
    std::unique_ptr<std::vector<Persona>> personas_aux = nullptr;
    Monitor monitor;
    Task task;
    
    int opcion;
    int aux;
    do {
        mostrarMenu();
        std::cin >> opcion;
        
        size_t tam = 0;
        int indice;
        std::string idBusqueda;
        
        // Iniciar medición de tiempo y memoria para esta operación
        long memoria_inicio = monitor.obtener_memoria();;
        
        if (opcion >= 6 && opcion <= 11) {
            std::cout << "\n1. Pasar por valor";
            std::cout << "\n2. Pasar por referencia";
            std::cout << "\nSeleccione una opción: ";
            std::cin >> aux;
        }

        switch(opcion) {

            case 0: {
                int n;
                std::cout << "\nIngrese el número de personas a generar: ";
                std::cin >> n;

                monitor.iniciar_tiempo();
                
                if (n <= 0) {
                    std::cout << "Error: Debe generar al menos 1 persona\n";
                    break;
                }
                
                // Generar el nuevo conjunto de datos
                personas = std::make_unique<std::vector<Persona>>(generarColeccion(n));
                tam = personas->size();
                
                double tiempo_gen = monitor.detener_tiempo();
                long memoria_gen = monitor.obtener_memoria() - memoria_inicio;
                
                std::cout << "Generadas " << tam << " personas en " 
                          << tiempo_gen << " ms, Memoria: " << memoria_gen << " KB\n";
                
                monitor.registrar("Crear datos", tiempo_gen, memoria_gen);
                break;
            }
                
            case 1: {
                if (!personas || personas->empty()) {
                    std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                    break;
                }
                
                monitor.iniciar_tiempo();
                
                tam = personas->size();
                std::cout << "\n=== RESUMEN DE PERSONAS (" << tam << ") ===\n";
                for(size_t i = 0; i < tam; ++i) {
                    std::cout << i << ". ";
                    (*personas)[i].mostrarResumen();
                }
                
                double tiempo_mostrar = monitor.detener_tiempo();
                long memoria_mostrar = monitor.obtener_memoria() - memoria_inicio;
                monitor.registrar("Mostrar resumen", tiempo_mostrar, memoria_mostrar);
                break;
            }
                
            case 2: {
                if (!personas || personas->empty()) {
                    std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                    break;
                }
                
                monitor.iniciar_tiempo();

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
                
            case 3: {
                if (!personas || personas->empty()) {
                    std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                    break;
                }
                
                std::cout << "\nIngrese el ID a buscar: ";
                std::cin >> idBusqueda;

                monitor.iniciar_tiempo();
                
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
                
            case 4:
                monitor.mostrar_resumen();
                break;
                
            case 5:
                monitor.exportar_csv();
                break;
                
            case 6: {

                if (!personas || personas->empty()) {
                    std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                    break;
                }

                monitor.iniciar_tiempo();

                if(aux == 1){
                    personas = task.buscar_edad_valor(std::move(personas), 0);
                } else if(aux == 2){
                    task.buscar_edad_referencia(personas, 0);
                }
                else {
                    std::cout<< "Opción invalidad \n";
                }
                

                double tiempo_longevo = monitor.detener_tiempo();
                long memoria_longevo = monitor.obtener_memoria() - memoria_inicio;
                monitor.registrar("Persona mas longeva", tiempo_longevo, memoria_longevo);

                monitor.mostrar_estadistica("Opción " + std::to_string(opcion), tiempo_longevo, memoria_longevo);

                break;
            }

            case 7: {
                if (!personas || personas->empty()) {
                    std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                    break;
                }

                int ciudad;

                mostrarCiudades();
                std::cin >> ciudad;

                monitor.iniciar_tiempo();

                if(aux == 1){
                    personas = task.buscar_edad_valor(std::move(personas), ciudad);
                } else if(aux == 2){
                    task.buscar_edad_referencia(personas, ciudad);
                }
                else {
                    std::cout<< "Opción invalidad \n";
                }

                double tiempo_longevo_ciudad = monitor.detener_tiempo();
                long memoria_longevo_ciudad = monitor.obtener_memoria() - memoria_inicio;
                monitor.registrar("Persona mas longeva ciudad", tiempo_longevo_ciudad, memoria_longevo_ciudad);

                monitor.mostrar_estadistica("Opción " + std::to_string(opcion), tiempo_longevo_ciudad, memoria_longevo_ciudad);

                break;

            }

            case 8: {
                if (!personas || personas->empty()) {
                    std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                    break;
                }

                monitor.iniciar_tiempo();

                if(aux == 1){
                    personas = task.buscar_patrimonio_valor(std::move(personas), 0);
                } else if(aux == 2){
                    task.buscar_patrimonio_referencia(personas, 0);
                }
                else {
                    std::cout<< "Opción invalidad \n";
                }

                double tiempo_patrimonio = monitor.detener_tiempo();
                long memoria_patrimonio = monitor.obtener_memoria() - memoria_inicio;
                monitor.registrar("Patrimonio", tiempo_patrimonio, memoria_patrimonio);

                monitor.mostrar_estadistica("Opción " + std::to_string(opcion), tiempo_patrimonio, memoria_patrimonio);

                break;
            }

            case 9: {
                if (!personas || personas->empty()) {
                    std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                    break;
                }

                int ciudad;

                mostrarCiudades();
                std::cin >> ciudad;

                monitor.iniciar_tiempo();

                if(aux == 1){
                    personas = task.buscar_patrimonio_valor(std::move(personas), ciudad);
                } else if(aux == 2){
                    task.buscar_patrimonio_referencia(personas, ciudad);
                }
                else {
                    std::cout<< "Opción invalidad \n";
                }

                double tiempo_longevo_ciudad = monitor.detener_tiempo();
                long memoria_longevo_ciudad = monitor.obtener_memoria() - memoria_inicio;
                monitor.registrar("Patrimonio ciudad", tiempo_longevo_ciudad, memoria_longevo_ciudad);

                monitor.mostrar_estadistica("Opción " + std::to_string(opcion), tiempo_longevo_ciudad, memoria_longevo_ciudad);

                break;
            }

            case 10: {
                if (!personas || personas->empty()) {
                    std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                    break;
                }

                int grupo;

                mostrarGrupos();
                std::cin >> grupo;

                monitor.iniciar_tiempo();

                if(aux == 1){
                    personas = task.buscar_patrimonio_grupo_valor(std::move(personas), grupo);
                } else if(aux == 2){
                    task.buscar_patrimonio_grupo_referencia(personas, grupo);
                }
                else {
                    std::cout<< "Opción invalidad \n";
                }

                double tiempo_longevo_grupo = monitor.detener_tiempo();
                long memoria_longevo_grupo = monitor.obtener_memoria() - memoria_inicio;
                monitor.registrar("Patrimonio grupo", tiempo_longevo_grupo, memoria_longevo_grupo);

                monitor.mostrar_estadistica("Opción " + std::to_string(opcion), tiempo_longevo_grupo, memoria_longevo_grupo);

                break;
            }

            case 11: {
                if (!personas || personas->empty()) {
                    std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                    break;
                }

                monitor.iniciar_tiempo();

                if(aux == 1){
                    personas = task.listar_personas_valor(std::move(personas));
                } else if(aux == 2){
                    task.listar_personas_referencia(personas);
                }
                else {
                    std::cout<< "Opción invalidad \n";
                }

                double tiempo_grupo = monitor.detener_tiempo();
                long memoria_grupo = monitor.obtener_memoria() - memoria_inicio;
                monitor.registrar("Listar grupos", tiempo_grupo, memoria_grupo);

                monitor.mostrar_estadistica("Opción " + std::to_string(opcion), tiempo_grupo, memoria_grupo);

                break;
            }

            case 12: {
                std::cout << "Saliendo...\n";
                break;
            }
                
                
            default:
                std::cout << "Opción inválida!\n";
        }
        
        // Mostrar estadísticas para las operaciones principales
        if (opcion >= 0 && opcion <= 3) {
            double tiempo = monitor.detener_tiempo();
            long memoria = monitor.obtener_memoria() - memoria_inicio;
            monitor.mostrar_estadistica("Opción " + std::to_string(opcion), tiempo, memoria);
        }
        
    } while(opcion != 12);
    
    return 0;
}