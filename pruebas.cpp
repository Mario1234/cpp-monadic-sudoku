#include <iostream> //salida por consola
#include <windows.h> //dormir hilo

#include "muestra.h"
#include "inicializacion.h"
#include "lectorarchivos.h"

std::vector<std::vector<int>> puzzle(N_FILAS, std::vector<int>(N_COLUMNAS));

Inicializador inicializador;
LectorArchivos lecArch;
Resolutor resolutor;


void muestraArrays(EstructuraResolutora e1){
    std::cout << muestra(e1.valoresPosiblesPorCelda) << std::endl;
    std::cout << muestra(e1.celdasPosiblesPorBloqueYValor) << std::endl;
}

int dameNumeroVaciasPuzz(){
    int nvacias=0;
    for(int i=0;i<N_FILAS;i++){
        for(int j=0;j<N_COLUMNAS;j++){
            if(puzzle[i][j]<0){
                nvacias++;
            }
        }
    }
    return nvacias;
}

int main(int argc, char** argv)
{
    EstructuraResolutora e1;
    inicializador.inicializacion(e1,puzzle);
    resolutor.ponEstructuraListaAux(inicializador.inicializaEstructuraListasAux());
//    EstructuraResolutora e2 = resolutor.reducePosiblesCasilla(e1,0,0,1);
//    muestraArrays(e2);
    Lectura lec = lecArch.leeArchivoPuzzle(resolutor, e1, puzzle, "sudoTest2.txt");
    switch(lec){
        case Fallida:
            std::cout << "Fallo de lectura";
            break;
        case FalloAbrir:
            std::cout << "Fallo al abrir el archivo";
            break;
        case FalloValor:
            std::cout << "Fallo: un valor no valido";
            break;
        default:
            std::cout << "Archivo leido";
            break;
    }
//    muestraArrays(e1);
//    std::pair<int, int> celda(6,3);
//    std::cout << dameNumeroBloquePertenceCelda(celda) << std::endl;
    int cantidadCasillasVacias = dameNumeroVaciasPuzz();
    std::cout << cantidadCasillasVacias << std::endl;
    std::cout << muestra(puzzle) << std::endl;
    std::vector<std::vector<int>> solucion = resolutor.recorreArbolIntentos(0,0,cantidadCasillasVacias,puzzle,e1);
    std::cout << muestra(solucion) << std::endl;
    Sleep(2000);
	return 0;
}
