# Operating_Systems_Reference_Value

## Documentación del codigo

Tanto el codigo para Estructuras como para Clases utilizan algoritmos de busquedas lineales en un vector de personas, utilizando paso por valor y por referencia de un unique_ptr y una copia.

## Structs:

## Funciones auxiliares:

cmp y organizar: Ordenan un map por sus valores de mayor a menor patrimonio para despues mostrar el resultado.

obtener_edad: Calcula la edad actual de una persona por medeio de su fecha de nacimiento.

obtener_grupo: Asigna a cada persona un grupo (A, B o C) según los dos ultimos digitos de su identificación.

## Búsquedas por edad

buscar_edad_valor y buscar_edad_referencia:: Busca a las personas mas longevas, de toda la población o por ciudad, recibiendo el vector de personas por valor o por referencia.

## Búsquedas por patrimonio

buscar_patrimonio_valor y buscar_patrimonio_referencia: Encuentran a la persona con mayor patrimonio, de toda la población o por ciudad, recibiendo el vector de personas por valor o por referencia.

buscar_patrimonio_grupo_valor y buscar_patrimonio_grupo_referencia: Buscan la persona con mayor patrimonio dentro de un grupo (A, B o C), recibiendo el vector de personas por valor o por referencia.

## Listado por grupos

listar_personas_valor y listar_personas_referencia: Separan las personas en los grupos A, B y C, mostrando un resumen y el total de personas en cada grupo, recibiendo el vector de personas por valor o por referencia.


## Estadísticas por ciudad

obtener_promedio_ciudades y obtener_promedio_ciudades_referencia: Calculan el patrimonio promedio de cada ciudad y los listan de mayor a menor.

## Estadísticas por edad

obtener_personas_mayores y obtener_personas_mayores_referencia: Calculan el porcentaje de personas de 60 años o más en un grupo específico.

obtener_personas_menores y obtener_personas_menores_referencia: Calculan el porcentaje de personas entre 18 y 25 años en un grupo específico.

## Clases

## Estadísticas de patrimonio por ciudad

ciudadesPatrimonioPromRef y ciudadesPatrimonioPromVal: Calcula el patrimonio promedio de las personas en cada ciudad por referencia y por valor.

porcentajeMayores60Ref y porcentajeMayores60Val: Calcula el porcentaje de personas mayores de 60 años por referencia y por valor.

## Personas de 18 a 25 años

personas18a25Ref y personas18a25Val: Agrupa en un map las personas entre 18 y 25 años según su ciudad por referencia y por valor.

## Listado y conteo por grupo

listarYContarPorGrupoVal y listarYContarPorGrupoRef: Muestra todas las personas con su grupo (A, B, C) y hace muestra la cantidad de personas en cada grupo por referencia y por valor.

## Búsqueda de persona con mayor patrimonio

mayorPatrimonioRef: Engloba las tres funciones por referencia las cuales buscan a la persona con mayor patrimonio por pais, ciudad o grupo.

mayorPatrimonioVal: Engloba las tres funciones por valor las cuales buscan a la persona con mayor patrimonio por pais, ciudad o grupo.

## Personas más longevas

personasMasLongevasVal y personasMasLongevasRef: Obtiene la(s) personas más longevas en el pais por valor o referencia.

personasMasLongevasPorCiudadVal y personasMasLongevasPorCiudadRef: Obtiene las más longevas por ciudad ya sea por valor o referencia.
