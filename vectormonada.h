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

template<typename TipoGenerico1, typename TipoLambda>
auto operator>>=(const std::vector<TipoGenerico1>& entrada, const TipoLambda&& funcionLambda)
    -> decltype(funcionLambda(entrada.front()))
{
	typedef typename std::remove_const<decltype(funcionLambda(entrada.front()))>::type tipoRetornoFuncionLambda;
	tipoRetornoFuncionLambda retornoFuncionLambda;
	for(auto i = entrada.begin(); i != entrada.end(); ++i)
	{
		tipoRetornoFuncionLambda actual = funcionLambda(*i);//actual es un vector de tamanio 1, resultado de el metodo unidad
		retornoFuncionLambda.push_back(actual[0]);
		//std::copy(actual.begin(), actual.end(), std::back_inserter(retornoFuncionLambda) );
	}
	return retornoFuncionLambda;
}
