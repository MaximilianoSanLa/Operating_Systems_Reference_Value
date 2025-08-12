#ifndef MONITOR_H
#define MONITOR_H

#include <chrono>
<<<<<<< HEAD
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// Clase para medir tiempo y memoria en Linux
class Monitor {
public:
    // Inicia la medición de tiempo
    void iniciar_tiempo() {
        inicio = std::chrono::high_resolution_clock::now();
    }
    
    // Detiene la medición de tiempo y devuelve milisegundos
    double detener_tiempo() {
        auto fin = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio).count();
    }
    
    // Obtiene el consumo de memoria actual en KB usando /proc/self/statm
    long obtener_memoria() {
        // Abrir el archivo de estadísticas de memoria
        FILE* file = fopen("/proc/self/statm", "r");
        if (!file) {
            perror("Error al abrir /proc/self/statm");
            return 0;
        }
        
        long size, resident, shared, text, lib, data, dt;
        if (fscanf(file, "%ld %ld %ld %ld %ld %ld %ld", 
                  &size, &resident, &shared, &text, &lib, &data, &dt) != 7) {
            fclose(file);
            return 0;
        }
        
        fclose(file);
        
        // Obtener el tamaño de página del sistema
        long page_size = sysconf(_SC_PAGESIZE) / (1024*1024); // Convertir a KB
        
        // Memoria residente en KB (páginas * tamaño de página en KB)
        return resident * page_size;
    }
    
    // Registra estadísticas para una operación
    void registrar(const std::string& operacion, double tiempo, long memoria) {
        registros.push_back({operacion, tiempo, memoria});
        total_tiempo += tiempo;
        max_memoria = std::max(max_memoria, memoria);
    }
    
    // Muestra estadísticas de una operación
    void mostrar_estadistica(const std::string& operacion, double tiempo, long memoria) {
        std::cout << "\n[ESTADÍSTICAS] " << operacion << " - "
                  << "Tiempo: " << tiempo << " ms, "
                  << "Memoria: " << memoria << " KB\n";
    }
    
    // Muestra todas las estadísticas registradas
    void mostrar_resumen() {
        std::cout << "\n=== RESUMEN DE ESTADÍSTICAS ===";
        for (const auto& reg : registros) {
            std::cout << "\n" << reg.operacion << ": "
                      << reg.tiempo << " ms, " << reg.memoria << " KB";
        }
        std::cout << "\nTotal tiempo: " << total_tiempo << " ms";
        std::cout << "\nMemoria máxima: " << max_memoria << " KB\n";
    }
    
    // Exporta las estadísticas a un archivo CSV
    void exportar_csv(const std::string& nombre_archivo = "estadisticas.csv") {
        std::ofstream archivo(nombre_archivo);
        archivo << "Operacion,Tiempo(ms),Memoria(KB)\n";
        for (const auto& reg : registros) {
            archivo << reg.operacion << "," << reg.tiempo << "," << reg.memoria << "\n";
        }
        archivo.close();
        std::cout << "Estadísticas exportadas a " << nombre_archivo << "\n";
    }

private:
    struct Registro {
        std::string operacion;
        double tiempo;
        long memoria;
    };
    
    std::chrono::high_resolution_clock::time_point inicio;
    std::vector<Registro> registros;
    double total_tiempo = 0;
    long max_memoria = 0;
=======
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

/**
 * Clase para monitorear el rendimiento (tiempo y memoria).
 * 
 * POR QUÉ: Cuantificar el rendimiento de las operaciones.
 * CÓMO: Midiendo tiempo con chrono y memoria con /proc/self/statm (Linux).
 * PARA QUÉ: Optimización y análisis de rendimiento.
 */
class Monitor {
public:
    void iniciar_tiempo();
    double detener_tiempo();
    long obtener_memoria();
    
    void registrar(const std::string& operacion, double tiempo, long memoria);
    void mostrar_estadistica(const std::string& operacion, double tiempo, long memoria);
    void mostrar_resumen();
    void exportar_csv(const std::string& nombre_archivo = "estadisticas.csv");

private:
    // Estructura para almacenar métricas de una operación
    struct Registro {
        std::string operacion; // Nombre de la operación
        double tiempo;         // Tiempo en milisegundos
        long memoria;          // Memoria en KB
    };
    
    std::chrono::high_resolution_clock::time_point inicio; // Punto de inicio del cronómetro
    std::vector<Registro> registros; // Historial de registros
    double total_tiempo = 0;         // Tiempo total acumulado
    long max_memoria = 0;            // Máximo de memoria utilizado
>>>>>>> 7d481a1760ddb5500485fb780ba5c4414a381a01
};

#endif // MONITOR_H