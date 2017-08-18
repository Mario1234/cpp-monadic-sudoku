#ifndef _INICIALIZACION_H_
#define _INICIALIZACION_H_

#include "globales.h"

//listas de numeros, auxiliares no importantes
static std::vector<int> listaOtrasFilas0(N_FILAS);
static std::vector<int> listaOtrasColumnas0(N_COLUMNAS);
static std::vector<int> listaOtrasBloques0(N_BLOQUES);
static std::vector<int> listaOtrasValores0(N_VALORES);
static std::vector<int> listaOtrasCeldasBloque0(N_CELDAS_BLOQUE);

//listas de inicializacion y reserva de memoria para las estructuras resolutora
static std::vector<std::vector<std::vector<int>>> valoresPosiblesPorCelda(N_FILAS,std::vector<std::vector<int>>( N_COLUMNAS, std::vector<int>(N_VALORES)));
static std::vector<std::vector<std::vector<std::pair<int, int>>>> celdasPosiblesPorBloqueYValor(N_BLOQUES,std::vector<std::vector<std::pair<int, int>>>( N_VALORES, std::vector<std::pair<int, int>>(N_CELDAS_BLOQUE)));

static std::vector<std::vector<std::pair<int, int>>> bloques(N_BLOQUES, std::vector<std::pair<int, int>>(N_CELDAS_BLOQUE));

class Inicializador {
    public:
        Inicializador();
        //en las inicializaciones la estructura pasa por referencia para que se guarden las modificaciones que se hagan sobre ella
        void inicializacion(EstructuraResolutora &e1, std::vector<std::vector<int>> &puzzaux);

        EstructuraListasAux inicializaEstructuraListasAux();

    private:
        const std::vector<int> inicializaListaRangos(std::vector<int> &listaNumeros, int limite);

        void inicializaPuzzle(std::vector<std::vector<int>> &puzzaux);

        void inicializaBloques();

        //constructoras de vectores con resize, modo dinamico
        void creaVectoresEstructura2(EstructuraResolutora &e1);

        //constructoras de vectores por copias de vectores tamanio fijo
        void creaVectoresEstructura(EstructuraResolutora &e1);

        void inicializaEstructura(EstructuraResolutora &e1);
};
#endif
