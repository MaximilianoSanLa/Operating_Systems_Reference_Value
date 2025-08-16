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
    
    if (1 + ltm->tm_mon == fecha_aux[1] && ltm->tm_mday >= fecha_aux[0]) { // Si el mes actual es igual al mes de nacimiento comparo si ya paso o esta pasado el dia del cumpleaños
        return (1900 + ltm->tm_year)-fecha_aux[2];
    }

    return ((1900 + ltm->tm_year)-fecha_aux[2]) - 1;
    
    
}

char Task::obtener_grupo(std::string id){

    std::string sub = id.substr(8, 2);

    int aux = stoi(sub);

    if(aux <= 39){
        return 'A';
    }else if(aux >= 40  && aux <= 79){
        return 'B';
    }else{
        return 'C';
    }

    
}

std::unique_ptr<std::vector<Persona>> Task::buscar_edad_valor(std::unique_ptr<std::vector<Persona>> personas, int opcion){
    std::vector<Persona> personas_edad;

    size_t tam = personas->size();
    int max_edad = (*personas)[0].edad;
    std::string ciudad;


    switch (opcion) {
        case 0: ciudad = "todos"; break; 
        case 1:  ciudad = "Bogotá"; break;
        case 2:  ciudad = "Medellín"; break;
        case 3:  ciudad = "Cali"; break;
        case 4:  ciudad = "Barranquilla"; break;
        case 5:  ciudad = "Cartagena"; break;
        case 6:  ciudad = "Bucaramanga"; break;
        case 7:  ciudad = "Pereira"; break;
        case 8:  ciudad = "Santa Marta"; break;
        case 9:  ciudad = "Cúcuta"; break;
        case 10: ciudad = "Ibagué"; break;
        case 11: ciudad = "Manizales"; break;
        case 12: ciudad = "Pasto"; break;
        case 13: ciudad = "Neiva"; break;
        case 14: ciudad = "Villavicencio"; break;
        case 15: ciudad = "Armenia"; break;
        case 16: ciudad = "Sincelejo"; break;
        case 17: ciudad = "Valledupar"; break;
        case 18: ciudad = "Montería"; break;
        case 19: ciudad = "Popayán"; break;
        case 20: ciudad = "Tunja"; break;
        default: 
            std::cout<<"numero invalido"<<"\n";
            return personas;
    }

    
    if (ciudad == "todos"){
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
    }
    else {
        for(size_t i = 0; i < tam; ++i){

            if(ciudad == (*personas)[i].ciudadNacimiento){
                if(max_edad == (*personas)[i].edad){
                    personas_edad.push_back((*personas)[i]);
                }

                if(max_edad < (*personas)[i].edad){
                    personas_edad.clear();
                    personas_edad.push_back((*personas)[i]);
                    max_edad = (*personas)[i].edad;
                }
            }
            
        }
    }

    size_t tam_edad = personas_edad.size();

    for(size_t i = 0; i < tam_edad; ++i){
        personas_edad[i].mostrar();
    }

    return personas;
}

void Task::buscar_edad_referencia(std::unique_ptr<std::vector<Persona>> &personas, int opcion){
    std::vector<Persona> personas_edad;

    size_t tam = personas->size();
    int max_edad = (*personas)[0].edad;
    std::string ciudad;


    switch (opcion) {
        case 0: ciudad = "todos"; break; 
        case 1:  ciudad = "Bogotá"; break;
        case 2:  ciudad = "Medellín"; break;
        case 3:  ciudad = "Cali"; break;
        case 4:  ciudad = "Barranquilla"; break;
        case 5:  ciudad = "Cartagena"; break;
        case 6:  ciudad = "Bucaramanga"; break;
        case 7:  ciudad = "Pereira"; break;
        case 8:  ciudad = "Santa Marta"; break;
        case 9:  ciudad = "Cúcuta"; break;
        case 10: ciudad = "Ibagué"; break;
        case 11: ciudad = "Manizales"; break;
        case 12: ciudad = "Pasto"; break;
        case 13: ciudad = "Neiva"; break;
        case 14: ciudad = "Villavicencio"; break;
        case 15: ciudad = "Armenia"; break;
        case 16: ciudad = "Sincelejo"; break;
        case 17: ciudad = "Valledupar"; break;
        case 18: ciudad = "Montería"; break;
        case 19: ciudad = "Popayán"; break;
        case 20: ciudad = "Tunja"; break;
        default: 
            std::cout<<"numero invalido"<<"\n";
            return;
    }

    
    if (ciudad == "todos"){
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
    }
    else {
        for(size_t i = 0; i < tam; ++i){

            if(ciudad == (*personas)[i].ciudadNacimiento){
                if(max_edad == (*personas)[i].edad){
                    personas_edad.push_back((*personas)[i]);
                }

                if(max_edad < (*personas)[i].edad){
                    personas_edad.clear();
                    personas_edad.push_back((*personas)[i]);
                    max_edad = (*personas)[i].edad;
                }
            }
            
        }
    }

    size_t tam_edad = personas_edad.size();

    for(size_t i = 0; i < tam_edad; ++i){
        personas_edad[i].mostrar();
    }

}

std::unique_ptr<std::vector<Persona>> Task::buscar_patrimonio_valor(std::unique_ptr<std::vector<Persona>> personas, int opcion){
    std::vector<Persona> personas_patrimonio;

    size_t tam = personas->size();
    int max_patrimonio = (*personas)[0].patrimonio;
    std::string ciudad;


    switch (opcion) {
        case 0: ciudad = "todos"; break; 
        case 1:  ciudad = "Bogotá"; break;
        case 2:  ciudad = "Medellín"; break;
        case 3:  ciudad = "Cali"; break;
        case 4:  ciudad = "Barranquilla"; break;
        case 5:  ciudad = "Cartagena"; break;
        case 6:  ciudad = "Bucaramanga"; break;
        case 7:  ciudad = "Pereira"; break;
        case 8:  ciudad = "Santa Marta"; break;
        case 9:  ciudad = "Cúcuta"; break;
        case 10: ciudad = "Ibagué"; break;
        case 11: ciudad = "Manizales"; break;
        case 12: ciudad = "Pasto"; break;
        case 13: ciudad = "Neiva"; break;
        case 14: ciudad = "Villavicencio"; break;
        case 15: ciudad = "Armenia"; break;
        case 16: ciudad = "Sincelejo"; break;
        case 17: ciudad = "Valledupar"; break;
        case 18: ciudad = "Montería"; break;
        case 19: ciudad = "Popayán"; break;
        case 20: ciudad = "Tunja"; break;
        default: 
            std::cout<<"numero invalido"<<"\n";
            return personas;
    }


    if (ciudad == "todos"){
        for(size_t i = 0; i < tam; ++i){
            if(max_patrimonio == (*personas)[i].patrimonio){
                personas_patrimonio.push_back((*personas)[i]);
            }

            if(max_patrimonio < (*personas)[i].patrimonio){
                personas_patrimonio.clear();
                personas_patrimonio.push_back((*personas)[i]);
                max_patrimonio = (*personas)[i].patrimonio;
            }
        }
    }
    else {
        for(size_t i = 0; i < tam; ++i){

            if(ciudad == (*personas)[i].ciudadNacimiento){
                if(max_patrimonio == (*personas)[i].patrimonio){
                    personas_patrimonio.push_back((*personas)[i]);
                }

                if(max_patrimonio < (*personas)[i].patrimonio){
                    personas_patrimonio.clear();
                    personas_patrimonio.push_back((*personas)[i]);
                    max_patrimonio = (*personas)[i].patrimonio;
                }
            }
            
        }
    }

    size_t tam_patrimonio = personas_patrimonio.size();

    for(size_t i = 0; i < tam_patrimonio; ++i){
        personas_patrimonio[i].mostrar();
    }

    return personas;
}

void Task::buscar_patrimonio_referencia(std::unique_ptr<std::vector<Persona>> &personas, int opcion){
    std::vector<Persona> personas_patrimonio;

    size_t tam = personas->size();
    int max_patrimonio = (*personas)[0].patrimonio;
    std::string ciudad;


    switch (opcion) {
        case 0: ciudad = "todos"; break; 
        case 1:  ciudad = "Bogotá"; break;
        case 2:  ciudad = "Medellín"; break;
        case 3:  ciudad = "Cali"; break;
        case 4:  ciudad = "Barranquilla"; break;
        case 5:  ciudad = "Cartagena"; break;
        case 6:  ciudad = "Bucaramanga"; break;
        case 7:  ciudad = "Pereira"; break;
        case 8:  ciudad = "Santa Marta"; break;
        case 9:  ciudad = "Cúcuta"; break;
        case 10: ciudad = "Ibagué"; break;
        case 11: ciudad = "Manizales"; break;
        case 12: ciudad = "Pasto"; break;
        case 13: ciudad = "Neiva"; break;
        case 14: ciudad = "Villavicencio"; break;
        case 15: ciudad = "Armenia"; break;
        case 16: ciudad = "Sincelejo"; break;
        case 17: ciudad = "Valledupar"; break;
        case 18: ciudad = "Montería"; break;
        case 19: ciudad = "Popayán"; break;
        case 20: ciudad = "Tunja"; break;
        default: 
            std::cout<<"numero invalido"<<"\n";
            return;
    }


    if (ciudad == "todos"){
        for(size_t i = 0; i < tam; ++i){
            if(max_patrimonio == (*personas)[i].patrimonio){
                personas_patrimonio.push_back((*personas)[i]);
            }

            if(max_patrimonio < (*personas)[i].patrimonio){
                personas_patrimonio.clear();
                personas_patrimonio.push_back((*personas)[i]);
                max_patrimonio = (*personas)[i].patrimonio;
            }
        }
    }
    else {
        for(size_t i = 0; i < tam; ++i){

            if(ciudad == (*personas)[i].ciudadNacimiento){
                if(max_patrimonio == (*personas)[i].patrimonio){
                    personas_patrimonio.push_back((*personas)[i]);
                }

                if(max_patrimonio < (*personas)[i].patrimonio){
                    personas_patrimonio.clear();
                    personas_patrimonio.push_back((*personas)[i]);
                    max_patrimonio = (*personas)[i].patrimonio;
                }
            }
            
        }
    }

    size_t tam_patrimonio = personas_patrimonio.size();

    for(size_t i = 0; i < tam_patrimonio; ++i){
        personas_patrimonio[i].mostrar();
    }

}