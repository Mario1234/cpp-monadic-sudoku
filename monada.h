//monada.h
//
//Define las dos operaciones de la monada. Toda clase que quiera ser tratada como monada
//debe proveer un constructor (unidad) de la Monada que tome un unico parametro del tipo
//que esta envolviendo(wrap). Tambien debe sobrecargar el operador >>= para definir el
//comportamiento de binding

#pragma once
//template < ... class ClaseGenerica>: se va a usar una clase generica con varios tipos genericos de datos
//template <typename TipoGenerico, typename...>: se van a usar varios tipos genericos de datos, de 1 a N
template <template <typename TipoGenerico, typename...> class ClaseGenerica>
struct Monada
{
    //template <typename TipoGenerico>: declara tipogenerico para usar en definicion de funcion
    //static ClaseGenerica<TipoGenerico>: tipo devuelto por la funcion
    //unidad nombre de la funcion
    //TipoGenerico valor: tipo y nombre de parametro de la funcion
    //return ClaseGenerica<TipoGenerico>(valor): devuelve la instancia de la ClaseGenerica construida
    //con el constructor de parametro del tipo TipoGenerico
	template <typename TipoGenerico> static ClaseGenerica<TipoGenerico> unidad(TipoGenerico valor)
	{ return ClaseGenerica<TipoGenerico>(valor); }
};
