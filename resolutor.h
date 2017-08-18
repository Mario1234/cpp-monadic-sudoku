#ifndef _RESOLUTOR_H_
#define _RESOLUTOR_H_

//#include <stdlib.h>
#include <algorithm>    // std::find
#include "globales.h"
#include "monada.h"
#include "vectormonada.h"

class Resolutor {

    public:
        Resolutor();

        const std::vector<std::vector<int>> recorreArbolIntentos(
                    int x,
                    int y,
                    int casillasVacias,
                    std::vector<std::vector<int>> puzzle,
                    EstructuraResolutora e1);

        EstructuraResolutora reducePosiblesCasilla(EstructuraResolutora e1, int x, int y, const int valor);

        void ponEstructuraListaAux(EstructuraListasAux eLisAux);

    private:
        EstructuraListasAux estructuraListaAux;

        template<typename Tipo1>
        const std::vector<Tipo1> reducePosiblesOtrasCeldas1d(const Tipo1 elemento,
                    const std::vector<Tipo1> posibles1d,
                    const Tipo1 nulo);

        template<typename Tipo1>
        const std::vector<std::vector<Tipo1>> reducePosiblesOtrasCeldas2d(
                    int x,
                    int y,
                    const std::vector<int> listaOtrasY,
                    int indiceX,
                    const Tipo1 elemento,
                    const std::vector<std::vector<Tipo1>> posibles2d,
                    const Tipo1 nulo);

        template<typename Tipo1>
        const std::vector<std::vector<std::vector<Tipo1>>> reducePosiblesOtrasCeldas3d(
                    int x,
                    int y,
                    const std::vector<int> listaOtrasX,
                    const std::vector<int> listaOtrasY,
                    const Tipo1 elemento,
                    const std::vector<std::vector<std::vector<Tipo1>>> posibles3d,
                    const Tipo1 nulo);

        template<typename Tipo1>
        bool todoNulos(const std::vector<Tipo1> listaPosibles,
                    const Tipo1 nulo,
                    int tamanio);

        std::vector<std::pair<int, int>> marcarEnBloqueValorPuesto(std::vector<std::pair<int, int>> &listAux, int x, int y);

        bool esPosibleBloque(EstructuraResolutora e1, int x, int y, int valorIntento);

        int dameNumeroBloquePertenceCelda(std::pair<int, int> celda);
};

#endif
