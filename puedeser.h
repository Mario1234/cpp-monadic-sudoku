//maybe.h
//
//Tipo PuedeSer
//Provee una manera mas segura de devolver posibles errores que valores NULL.
//C++ no tiene "clasificador"(matching) de patrones, asi que tengo que llamar siempre
//a la funcion tieneValor() antes de recoger el valor con dameValor()

#pragma once

#include <cassert>

template<typename TipoGenerico> class PuedeSer
{
	public:
		static const PuedeSer<TipoGenerico> ConstructorPublico(const TipoGenerico valorIni) { return PuedeSer(valorIni); }
		static const PuedeSer<TipoGenerico> Nada()           { return PuedeSer(); }

		const bool tieneValor() const                 { return valido; }
		const TipoGenerico dameValor() const       { assert(tieneValor());
		                                            return valor; }

	private:
		PuedeSer() : valido(false) {}
		//direct-initialized valor(valorIni), es como hacer int(3), inicializa a 3 la variable valor
		//constructor privado, valor(valorIni) es
		PuedeSer(const TipoGenerico valorIni) : valor(valorIni), valido(true) {}
		PuedeSer(const TipoGenerico valorIni, const bool validoIni) : valor(valorIni), valido(validoIni) {}
		TipoGenerico valor;
		const bool valido;
};

template<typename TipoGenerico> const PuedeSer<TipoGenerico> ConstructorPublico(const TipoGenerico valorIni)
{
	return PuedeSer<TipoGenerico>::ConstructorPublico(valorIni);
}

template<typename TipoGenerico> const PuedeSer<TipoGenerico> Nada()
{
	return PuedeSer<TipoGenerico>::Nada();
}
