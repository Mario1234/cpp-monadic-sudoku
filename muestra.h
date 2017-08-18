//muestra.h
//
//Define la operación mostrar. El valor predeterminado es utilizar el operador de flujo.

#pragma once
#include <utility> //funcion get para clase pair
#include <vector> //para vectores
#include <list>
#include <sstream>
#include "puedesermonada.h"

#define ARRAY_SIZE(array) (sizeof((array))/sizeof((array[0])))

template<typename T, size_t N> constexpr size_t arraysize(T(&arr)[N])
{
    return sizeof(arr) / sizeof(*arr);
}

template<typename Tipo1> std::string muestra(Tipo1 x)
{
	std::stringstream salida;
	salida << x;
	return salida.str();
}

template<typename Tipo1> std::string muestra(PuedeSer<Tipo1> x)
{
	if(x.tieneValor()) {
		std::stringstream salida;
		salida << "DameValor " << x.dameValor();
		return salida.str();
	} else return "Nada";
}

template<typename Tipo1, typename Tipo2> std::string muestra(std::pair<Tipo1, Tipo2> par)
{
	std::stringstream salida;
	salida << "(" << par.first << "," << par.second << ")";
	return salida.str();
}

template<typename Tipo1> std::string muestra(std::list<Tipo1> lista)
{
	std::stringstream salida;
	salida << "[";
	for(auto i = lista.begin(); i != lista.end(); ++i)
	{
		salida << muestra(*i);
		if(i != --lista.end())
			salida << ",";
	}
	salida << "]";
	return salida.str();
}

template<typename Tipo1> std::string muestra(std::vector<Tipo1> lista)
{
	std::stringstream salida;
	salida << "[";
	for(auto i = lista.begin(); i != lista.end(); ++i)
	{
		salida << muestra(*i);
		if(i != --lista.end())
			salida << ",";
	}
	salida << "]";
	return salida.str();
}

//template<typename Tipo1, std::size_t TAMANIO> std::string muestra(std::array<Tipo1, TAMANIO> lista)
//{
//	std::stringstream salida;
//	salida << "[";
//	size_t longitudLista = lista.size();
//	for(unsigned int i = 0; i < longitudLista; i++)
//	{
//		salida << muestra(lista[i]);
//		if((i+1) < longitudLista)
//			salida << ",";
//	}
//	salida << "]";
//	return salida.str();
//}
