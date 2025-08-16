#ifndef TASK_H
#define TASK_H

#include "persona.h"
#include <memory> 

class Task{
    public:
        int obtener_edad(std::string fecha_nacimiento);
        char obtener_grupo(std::string ID);
        std::unique_ptr<std::vector<Persona>> buscar_edad_valor(std::unique_ptr<std::vector<Persona>> personas, int opcion);
        std::unique_ptr<std::vector<Persona>> buscar_patrimonio_valor(std::unique_ptr<std::vector<Persona>> personas, int opcion);
        void buscar_edad_referencia(std::unique_ptr<std::vector<Persona>> &personas, int opcion);
        void buscar_patrimonio_referencia(std::unique_ptr<std::vector<Persona>> &personas, int opcion);
        std::unique_ptr<std::vector<Persona>> buscar_patrimonio_grupo_valor(std::unique_ptr<std::vector<Persona>> personas, int opcion);
        void buscar_patrimonio_grupo_referencia(std::unique_ptr<std::vector<Persona>> &personas, int opcion);

};

#endif