#include <iostream>
#include <ctime>
#include <vector>
#include <string>
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