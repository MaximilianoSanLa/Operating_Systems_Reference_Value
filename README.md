# Operating_Systems_Reference_Value

## Documentación del codigo

Tanto el codigo para Estructuras como para Clases utilizan algoritmos de busquedas lineales en un vector de personas, utilizando paso por valor y por referencia de un unique_ptr y una copia.

## Structs:

## Funciones auxiliares:

cmp y organizar: Ordenan un map por sus valores de mayor a menor patrimonio para despues mostrar el resultado.

obtener_edad: calcula la edad actual de una persona por medeio de su fecha de nacimiento.

obtener_grupo: asigna a cada persona un grupo (A, B o C) según los dos ultimos digitos de su identificación.

## Búsquedas por edad

buscar_edad_valor y buscar_edad_referencia:: busca a las personas mas longevas, de toda la población o por ciudad, recibiendo el vector de personas por valor o por referencia.

## Búsquedas por patrimonio

buscar_patrimonio_valor y buscar_patrimonio_referencia: encuentran a la persona con mayor patrimonio, de toda la población o por ciudad, recibiendo el vector de personas por valor o por referencia.

buscar_patrimonio_grupo_valor y buscar_patrimonio_grupo_referencia: buscan la persona con mayor patrimonio dentro de un grupo (A, B o C), recibiendo el vector de personas por valor o por referencia.

## Listado por grupos

listar_personas_valor y listar_personas_referencia: separan las personas en los grupos A, B y C, mostrando un resumen y el total de personas en cada grupo, recibiendo el vector de personas por valor o por referencia.


## Estadísticas por ciudad

obtener_promedio_ciudades y obtener_promedio_ciudades_referencia: calculan el patrimonio promedio de cada ciudad y los listan de mayor a menor.

## Estadísticas por edad

obtener_personas_mayores y obtener_personas_mayores_referencia: calculan el porcentaje de personas de 60 años o más en un grupo específico.

obtener_personas_menores y obtener_personas_menores_referencia: calculan el porcentaje de personas entre 18 y 25 años en un grupo específico.
