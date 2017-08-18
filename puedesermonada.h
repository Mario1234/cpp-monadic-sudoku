//maybem.h
//
//PuedeSer Monada
//Añade un comportamiento monadico al tipo PuedeSer. Permite realizar una secuencia
//de operaciones del tipo PuedeSer<TipoGenerico>, y parar la secuencia y salir en cuanto haya un fallo.

#pragma once

#include "monada.h"
#include "puedeser.h"

//esta monada tiene por ClaseGenerica = PuedeSer
//template<>: es un switch case de tipos, se llama plantilla de especializacion
//aqui se define el PuedeSer Monada generico, se pueden definir especializaciones especificas
//por ejemplo un template<int> struct Monada<PuedeSer> es la especializacion de la Monada PuedeSer para enteros
template<> struct Monada<PuedeSer>
{
	template<typename TipoGenerico> static const PuedeSer<TipoGenerico> unidad (TipoGenerico valor)
	{
		return ConstructorPublico(valor);
	}
};

//functor que define el comportamiento de binding de esta monada
template<typename TipoGenerico1, typename TipoGenerico2>
//auto operator>>=: se usa funcion lambda para definir functor
//valorDeUnTipo(...) es inicializacion directa, constructor, por ejemplo int()
auto operator>>=(const PuedeSer<TipoGenerico1>&& entrada, const TipoGenerico2&& valorDeUnTipo)
    -> decltype(valorDeUnTipo(entrada.dameValor()))
{
    //define tipoAuxiliar como PuedeSer<TipoGenerico1>, valorDeUnTipo(entrada.dameValor()) es de este tipo
	typedef decltype(valorDeUnTipo(entrada.dameValor())) tipoAuxiliar;
	return entrada.tieneValor() ? valorDeUnTipo(entrada.dameValor()) : tipoAuxiliar::Nada();
}
