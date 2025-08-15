#include <iostream>
#include <ctime>
#include <vector>
#include <string>
#include <memory> 
#include "task.h"
#include "persona.h"

int Task::obtener_edad(std::string fecha_nacimiento){
    std::stringstream fechaNacimiento(fecha_nacimiento);

    std::string t;

    char del = '/';

    std::vector<int> fecha_aux;

    while (getline(fechaNacimiento, t, del)){
        fecha_aux.push_back(stoi(t));
    }

    time_t now = time(0);

    tm *ltm = localtime(&now); // Obtengo la hora actual

    if (1 + ltm->tm_mon > fecha_aux[1]){ // Comparo si el mes actual es mayor al mes de nacimiento
        return (1900 + ltm->tm_year)-fecha_aux[2];
    }
    
    if (1 + ltm->tm_mon == fecha_aux[1] && ltm->tm_mday >= fecha_aux[0]) { // Si el mes actual es igual al mes de nacimiento comparo si ya paso o esta pasadno el dia del cumpleaños
        return (1900 + ltm->tm_year)-fecha_aux[2];
    }

    return ((1900 + ltm->tm_year)-fecha_aux[2]) - 1;
    
    
}

std::unique_ptr<std::vector<Persona>> Task::buscar_edad_valor(std::unique_ptr<std::vector<Persona>> personas){
    std::vector<Persona> personas_edad;

    size_t tam = personas->size();
    int max_edad = (*personas)[0].edad;
    

    for(size_t i = 0; i < tam; ++i){
        if(max_edad == (*personas)[i].edad){
            personas_edad.push_back((*personas)[i]);
        }

        if(max_edad < (*personas)[i].edad){
            personas_edad.clear();
            personas_edad.push_back((*personas)[i]);
            max_edad = (*personas)[i].edad;
        }
    }

    size_t tam_edad = personas_edad.size();

    for(size_t i = 0; i < tam_edad; ++i){
        personas_edad[i].mostrar();
    }

    return personas;
}




