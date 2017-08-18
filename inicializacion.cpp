#include "inicializacion.h"

EstructuraListasAux Inicializador::inicializaEstructuraListasAux(){
    EstructuraListasAux eLisAux;
    eLisAux.listaOtrasFilas = inicializaListaRangos(listaOtrasFilas0,N_FILAS);
    eLisAux.listaOtrasColumnas = inicializaListaRangos(listaOtrasColumnas0,N_COLUMNAS);
    eLisAux.listaOtrasBloques = inicializaListaRangos(listaOtrasBloques0,N_BLOQUES);
    eLisAux.listaOtrasValores = inicializaListaRangos(listaOtrasValores0,N_VALORES);
    return eLisAux;
};

const std::vector<int> Inicializador::inicializaListaRangos(std::vector<int> &listaNumeros, int limite){
    for (int i = 0; i < limite; i++)
    {
        listaNumeros[i] = i;
    }
    return listaNumeros;
}

void Inicializador::inicializaBloques(){
    for(int i=0;i<N_BLOQUES;i++){
        int i_celdaBloque = 0;
        int xIni = (i/3)*3;
        int yIni = (i%3)*3;
        int altoBloque = (N_FILAS/3);
        for(int j=0;j<altoBloque;j++){//0..2
            int anchoBloque = (N_COLUMNAS/3);
            for(int k=0;k<anchoBloque;k++){//0..2
                std::pair<int, int> celda(xIni + j, yIni + k);
                bloques[i][i_celdaBloque]=celda;
                i_celdaBloque++;
            }
        }
    }
}

void Inicializador::inicializaPuzzle(std::vector<std::vector<int>> &puzzaux){
    for(int i=0;i<N_FILAS;i++){
        for(int j=0;j<N_COLUMNAS;j++){
            puzzaux[i][j]=NULO;
        }
    }
}

//constructoras de vectores con resize, modo dinamico
void Inicializador::creaVectoresEstructura2(EstructuraResolutora &e1){
    e1.valoresPosiblesPorCelda.resize(N_FILAS);
    for(auto &i : e1.valoresPosiblesPorCelda){
        i.resize(N_COLUMNAS);
        for(auto &j : i){
            j.resize(N_VALORES);
        }
    }
    e1.celdasPosiblesPorBloqueYValor.resize(N_BLOQUES);
    for(auto &i : e1.celdasPosiblesPorBloqueYValor){
        i.resize(N_VALORES);
        for(auto &j : i){
            j.resize(N_CELDAS_BLOQUE);
        }
    }
    e1.sePuedeResolver=true;
}

//constructoras de vectores por copias de vectores tamanio fijo
void Inicializador::creaVectoresEstructura(EstructuraResolutora &e1){
    e1.valoresPosiblesPorCelda=valoresPosiblesPorCelda;
    e1.celdasPosiblesPorBloqueYValor=celdasPosiblesPorBloqueYValor;
    e1.sePuedeResolver=true;
}

void Inicializador::inicializaEstructura(EstructuraResolutora &e1){
    creaVectoresEstructura(e1);
//    (,vector<vector<int>>( N_COLUMNAS, vector<int>(N_VALORES)));
//    e1.celdasPosiblesPorFilaYValor(new (N_FILAS,vector<vector<pair<int, int>>>( N_VALORES, vector<pair<int, int>>(N_COLUMNAS))));
//    e1.celdasPosiblesPorColumnaYValor(new (N_COLUMNAS,vector<vector<pair<int, int>>>( N_VALORES, vector<pair<int, int>>(N_FILAS))));
//    e1.celdasPosiblesPorBloqueYValor(new (N_BLOQUES,vector<vector<pair<int, int>>>( N_VALORES, vector<pair<int, int>>(N_CELDAS_BLOQUE))));
    //inicializa valoresPosiblesPorCelda
    for(int i=0;i<N_FILAS;i++){
        for(int j=0;j<N_COLUMNAS;j++){
            for(int k=0;k<N_VALORES;k++){
                e1.valoresPosiblesPorCelda[i][j][k]=k;
            }
        }
    }
    //inicializa celdasPosiblesPorBloqueYValor
    for(int i=0;i<N_BLOQUES;i++){
        for(int j=0;j<N_VALORES;j++){
            //std::copy(std::begin(bloques[i]), std::end(bloques[i]), std::begin(celdasPosiblesPorBloqueYValor[i][j]));
            e1.celdasPosiblesPorBloqueYValor[i][j]=bloques[i];
        }
    }
}

//---------------------------PUBLICAS---------------------

Inicializador::Inicializador(){

}

//en las inicializaciones la estructura pasa por referencia para que se guarden las modificaciones que se hagan sobre ella
void Inicializador::inicializacion(EstructuraResolutora &e1, std::vector<std::vector<int>> &puzzaux){
    inicializaPuzzle(puzzaux);
    inicializaBloques();
    inicializaEstructura(e1);
}
