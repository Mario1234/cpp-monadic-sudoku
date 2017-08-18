#ifndef _GLOBALES_H_
#define _GLOBALES_H_

#include <utility> //funcion get para clase pair
#include <vector> //para vectores

const int N_FILAS = 9;
const int N_COLUMNAS = 9;
const int N_BLOQUES = 9;
const int N_VALORES = 9;
const int N_CELDAS_BLOQUE = 9;

struct EstructuraListasAux{
    std::vector<int> listaOtrasFilas;
    std::vector<int> listaOtrasColumnas;
    std::vector<int> listaOtrasBloques;
    std::vector<int> listaOtrasValores;
};

//las celdas son del tipo pair<int, int>
//int valoresPosiblesPorCelda[N_FILAS][N_COLUMNAS][N_VALORES];
//pair<int, int> celdasPosiblesPorFilaYValor[N_FILAS][N_VALORES][N_COLUMNAS];//N_CELDAS_FILA
//pair<int, int> celdasPosiblesPorColumnaYValor[N_COLUMNAS][N_VALORES][N_FILAS];//N_CELDAS_COLUMNA
//pair<int, int> celdasPosiblesPorBloqueYValor[N_BLOQUES][N_VALORES][N_CELDAS_BLOQUE];
//pair<int, int> bloques[N_BLOQUES][N_CELDAS_BLOQUE];
struct EstructuraResolutora{
    std::vector<std::vector<std::vector<int>>> valoresPosiblesPorCelda;
    std::vector<std::vector<std::vector<std::pair<int, int>>>> celdasPosiblesPorBloqueYValor;
    bool sePuedeResolver;
};

const int NULO = -1;
const std::pair<int, int> CELDA_NULA(-1,-1);

#endif
