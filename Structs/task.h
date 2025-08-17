

#include <iostream>
#include <ctime>
#include <vector>
#include <string>
#include <memory> 
//#include "task.h"
#include "persona.h"

inline int obtener_edad(std::string fecha_nacimiento) {
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

inline char obtener_grupo(std::string id){

    std::string sub = id.substr(id.size() - 2);

    int aux = stoi(sub);

    if(aux <= 39){
        return 'A';
    }else if(aux >= 40  && aux <= 79){
        return 'B';
    }else{
        return 'C';
    }

    
}

inline void buscar_edad_valor(std::vector<Persona> personas, int opcion){
    std::vector<Persona> personas_edad;

    std::cout << "Dirección del vector dentro de la función: " << personas.data() << std::endl;


    size_t tam = personas.size();
    int max_edad = personas[0].edad;
    std::string ciudad;

    std::string ciudades[21]={"todos", "Bogotá","Medellín","Cali","Barranquilla","Cartagena","Bucaramanga","Pereira",
        "Santa Marta","Cúcuta","Ibagué","Manizales","Pasto","Neiva","Villavicencio","Armenia","Sincelejo","Valledupar",
        "Montería", "Popayán", "Tunja"
    };

    ciudad = ciudades[opcion];

    
    if (!opcion){ //ciudad=="todos"
        for(size_t i = 0; i < tam; ++i){
            if(max_edad == personas[i].edad){
                personas_edad.push_back(personas[i]);
            }

            if(max_edad < personas[i].edad){
                personas_edad.clear();
                personas_edad.push_back(personas[i]);
                max_edad = personas[i].edad;
            }
        }
    }
    else {
        for(size_t i = 0; i < tam; ++i){

            if(ciudad == personas[i].ciudadNacimiento){
                if(max_edad == personas[i].edad){
                    personas_edad.push_back(personas[i]);
                }

                if(max_edad < personas[i].edad){
                    personas_edad.clear();
                    personas_edad.push_back(personas[i]);
                    max_edad = personas[i].edad;
                }
            }
            
        }
    }

    size_t tam_edad = personas_edad.size();

    for(size_t i = 0; i < tam_edad; ++i){
        personas_edad[i].mostrar();
    }

}

inline void buscar_edad_referencia(std::unique_ptr<std::vector<Persona>> &personas, int opcion){
    std::vector<Persona> personas_edad;

    size_t tam = personas->size();
    int max_edad = (*personas)[0].edad;
    std::string ciudad;

    std::string ciudades[21]={"todos", "Bogotá","Medellín","Cali","Barranquilla","Cartagena","Bucaramanga","Pereira",
        "Santa Marta","Cúcuta","Ibagué","Manizales","Pasto","Neiva","Villavicencio","Armenia","Sincelejo","Valledupar",
        "Montería", "Popayán", "Tunja"
    };

    ciudad = ciudades[opcion];
    


    
    if (!opcion){
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

inline void buscar_patrimonio_valor(std::vector<Persona> personas, int opcion){
    std::vector<Persona> personas_patrimonio;

    size_t tam = personas.size();
    int max_patrimonio = personas[0].patrimonio;
    std::string ciudad;


    std::string ciudades[21]={"todos", "Bogotá","Medellín","Cali","Barranquilla","Cartagena","Bucaramanga","Pereira",
        "Santa Marta","Cúcuta","Ibagué","Manizales","Pasto","Neiva","Villavicencio","Armenia","Sincelejo","Valledupar",
        "Montería", "Popayán", "Tunja"
    };

    ciudad = ciudades[opcion];


    if (!opcion){
        for(size_t i = 0; i < tam; ++i){
            if(max_patrimonio == personas[i].patrimonio){
                personas_patrimonio.push_back(personas[i]);
            }

            if(max_patrimonio < personas[i].patrimonio){
                personas_patrimonio.clear();
                personas_patrimonio.push_back(personas[i]);
                max_patrimonio = personas[i].patrimonio;
            }
        }
    }
    else {
        for(size_t i = 0; i < tam; ++i){

            if(ciudad == personas[i].ciudadNacimiento){
                if(max_patrimonio == personas[i].patrimonio){
                    personas_patrimonio.push_back(personas[i]);
                }

                if(max_patrimonio < personas[i].patrimonio){
                    personas_patrimonio.clear();
                    personas_patrimonio.push_back(personas[i]);
                    max_patrimonio = personas[i].patrimonio;
                }
            }
            
        }
    }

    size_t tam_patrimonio = personas_patrimonio.size();

    for(size_t i = 0; i < tam_patrimonio; ++i){
        personas_patrimonio[i].mostrar();
    }

}

inline void buscar_patrimonio_referencia(std::unique_ptr<std::vector<Persona>> &personas, int opcion){
    std::vector<Persona> personas_patrimonio;

    size_t tam = personas->size();
    int max_patrimonio = (*personas)[0].patrimonio;
    std::string ciudad;

    std::string ciudades[21]={"todos", "Bogotá","Medellín","Cali","Barranquilla","Cartagena","Bucaramanga","Pereira",
        "Santa Marta","Cúcuta","Ibagué","Manizales","Pasto","Neiva","Villavicencio","Armenia","Sincelejo","Valledupar",
        "Montería", "Popayán", "Tunja"
    };

    ciudad = ciudades[opcion];


    if (!opcion){
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

inline void buscar_patrimonio_grupo_valor(std::vector<Persona> personas, int opcion){
    std::vector<Persona> personas_patrimonio;

    size_t tam = personas.size();
    int max_patrimonio = personas[0].patrimonio;
    char grupo;

    switch (opcion) {
        case 1:  grupo = 'A'; break;
        case 2:  grupo = 'B'; break;
        case 3:  grupo = 'C'; break;
        default: 
            std::cout<<"numero invalido"<<"\n";
            return;
    }
    
    for(size_t i = 0; i < tam; ++i){
        if(grupo == personas[i].grupo){
            if(max_patrimonio == personas[i].patrimonio){
                personas_patrimonio.push_back(personas[i]);
            }

            if(max_patrimonio < personas[i].patrimonio){
                personas_patrimonio.clear();
                personas_patrimonio.push_back(personas[i]);
                max_patrimonio = personas[i].patrimonio;
            }
        }
    }

    size_t tam_patrimonio = personas_patrimonio.size();

    for(size_t i = 0; i < tam_patrimonio; ++i){
        personas_patrimonio[i].mostrar();
    }

}

inline void buscar_patrimonio_grupo_referencia(std::unique_ptr<std::vector<Persona>> &personas, int opcion){
    std::vector<Persona> personas_patrimonio;

    size_t tam = personas->size();
    int max_patrimonio = (*personas)[0].patrimonio;
    char grupo;

    switch (opcion) {
        case 1:  grupo = 'A'; break;
        case 2:  grupo = 'B'; break;
        case 3:  grupo = 'C'; break;
        default: 
            std::cout<<"numero invalido"<<"\n";
            return;
    }
    
    for(size_t i = 0; i < tam; ++i){
        if(grupo == (*personas)[i].grupo){
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

    size_t tam_patrimonio = personas_patrimonio.size();

    for(size_t i = 0; i < tam_patrimonio; ++i){
        personas_patrimonio[i].mostrar();
    }
}

inline void listar_personas_valor(std::vector<Persona> personas){
    std::vector<Persona> personas_A;
    std::vector<Persona> personas_B;
    std::vector<Persona> personas_C;

    size_t tam = personas.size();
    
    for(size_t i = 0; i < tam; ++i){
        if(personas[i].grupo == 'A'){
            personas_A.push_back(personas[i]);
        }

        if(personas[i].grupo == 'B'){
            personas_B.push_back(personas[i]);
        }

        if(personas[i].grupo == 'C'){
            personas_C.push_back(personas[i]);
        }

        
    }

    size_t tam_A = personas_A.size();
    size_t tam_B = personas_B.size();
    size_t tam_C = personas_C.size();

    std::cout<<"\n\n=====================GRUPO A=====================\n\n";

    for(size_t i = 0; i < tam_A; ++i){
        personas_A[i].mostrar();
    }

    std::cout<<"\n\n=====================GRUPO B=====================\n\n";

    for(size_t i = 0; i < tam_B; ++i){
        personas_B[i].mostrar();
    }

    std::cout<<"\n\n=====================GRUPO C=====================\n\n";

    for(size_t i = 0; i < tam_C; ++i){
        personas_C[i].mostrar();
    }

    std::cout<<"GRUPO A: " <<tam_A <<"\n";
    std::cout<<"GRUPO B: " <<tam_B <<"\n";
    std::cout<<"GRUPO C: " <<tam_C <<"\n";
}

inline void listar_personas_referencia(std::unique_ptr<std::vector<Persona>> &personas){
    std::vector<Persona> personas_A;
    std::vector<Persona> personas_B;
    std::vector<Persona> personas_C;

    size_t tam = personas->size();
    
    for(size_t i = 0; i < tam; ++i){
        if((*personas)[i].grupo == 'A'){
            personas_A.push_back((*personas)[i]);
        }

        if((*personas)[i].grupo == 'B'){
            personas_B.push_back((*personas)[i]);
        }

        if((*personas)[i].grupo == 'C'){
            personas_C.push_back((*personas)[i]);
        }

        
    }

    size_t tam_A = personas_A.size();
    size_t tam_B = personas_B.size();
    size_t tam_C = personas_C.size();

    std::cout<<"\n\n=====================GRUPO A=====================\n\n";

    for(size_t i = 0; i < tam_A; ++i){
        personas_A[i].mostrar();
    }

    std::cout<<"\n\n=====================GRUPO B=====================\n\n";

    for(size_t i = 0; i < tam_B; ++i){
        personas_B[i].mostrar();
    }

    std::cout<<"\n\n=====================GRUPO C=====================\n\n";

    for(size_t i = 0; i < tam_C; ++i){
        personas_C[i].mostrar();
    }

    std::cout<<"GRUPO A: " <<tam_A <<"\n";
    std::cout<<"GRUPO B: " <<tam_B <<"\n";
    std::cout<<"GRUPO C: " <<tam_C <<"\n";
}