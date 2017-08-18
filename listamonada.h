//listamonada.h
//
//La lista Monada
//Ofrece la manera de construir listas sobre secuencias de operaciones.

#pragma once

#include <list>
#include <type_traits>

#include "monada.h"

template<> struct Monada<std::list>
{
	template<typename TipoGenerico> static const std::list<TipoGenerico> unidad (TipoGenerico valor)
	{
		return std::list<TipoGenerico>(1, valor);
	}
};

template<typename TipoGenerico1, typename TipoGenerico2>
auto operator>>=(const std::list<TipoGenerico1>& entrada, const TipoGenerico2&& valorDeUnTipo)
    -> decltype(valorDeUnTipo(entrada.front()))
{
	typedef typename std::remove_const<decltype(valorDeUnTipo(entrada.front()))>::type tipoAuxiliar;
	tipoAuxiliar salida;
	for(auto i = entrada.begin(); i != entrada.end(); ++i)
	{
		tipoAuxiliar actual = valorDeUnTipo(*i);
		salida.splice(salida.end(), actual);
	}
	return salida;
}
