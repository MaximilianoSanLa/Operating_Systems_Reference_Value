#ifndef TASK_H
#define TASK_H

#include "persona.h"
#include <memory> 

class Task{
    public:
        int obtener_edad(std::string fecha_nacimiento);
        std::unique_ptr<std::vector<Persona>> buscar_edad_valor(std::unique_ptr<std::vector<Persona>> personas);

};

#endif