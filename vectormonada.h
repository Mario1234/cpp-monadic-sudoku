//vectormonada.h
//
//La vector Monada
//Ofrece la manera de construir listas de acceso aleatorio sobre secuencias de operaciones.

#pragma once

#include <vector>
#include <type_traits>

#include "monada.h"

template<> struct Monada<std::vector>
{
	template<typename TipoGenerico> static const std::vector<TipoGenerico> unidad (TipoGenerico valor)
	{
		return std::vector<TipoGenerico>(1, valor);
	}
};

template<typename TipoGenerico1, typename TipoGenerico2>
auto operator>>=(const std::vector<TipoGenerico1>& entrada, const TipoGenerico2&& valorDeUnTipo)
    -> decltype(valorDeUnTipo(entrada.front()))
{
	typedef typename std::remove_const<decltype(valorDeUnTipo(entrada.front()))>::type tipoAuxiliar;
	tipoAuxiliar salida;
	for(auto i = entrada.begin(); i != entrada.end(); ++i)
	{
		tipoAuxiliar actual = valorDeUnTipo(*i);
		std::copy(actual.begin(), actual.end(), std::back_inserter(salida) );
	}
	return salida;
}
