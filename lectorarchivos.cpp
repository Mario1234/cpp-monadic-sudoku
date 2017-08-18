#include "lectorarchivos.h"

LectorArchivos::LectorArchivos(){

}

const Lectura LectorArchivos::leeArchivoPuzzle(Resolutor res1, EstructuraResolutora &e1, std::vector<std::vector<int>> &puzzaux, std::string nombreArchivo){
    Lectura lec = Exitosa;
    std::string linea;
    std::ifstream archivo(nombreArchivo);
    if (archivo.is_open())
    {
        int i = 0;
        while ( i<N_FILAS && lec==Exitosa && getline(archivo,linea) )
        {
            lec = aniadeFilaPuzzle(res1, e1, puzzaux, linea, i);
            i++;
        }
        archivo.close();
        return lec;
    }
    else{
        lec = FalloAbrir;
        return lec;
    }
}

const Lectura LectorArchivos::aniadeFilaPuzzle(Resolutor res1, EstructuraResolutora &e1, std::vector<std::vector<int>> &puzzaux, std::string linea, int numeroLinea){
    Lectura lec = Exitosa;
    size_t tamanio = linea.length();
    size_t columnas = (size_t)N_COLUMNAS;
    if(tamanio>columnas){
        tamanio=columnas;
    }
    size_t i=0;
    while(i<tamanio && lec==Exitosa){
        int numero = (int)linea.at(i) - (int)48;
        if(numero<0 || numero>N_VALORES){
            lec=FalloValor;
        }
        //los valores los ponemos del -1 al 8 en vez del 0 al 9
        puzzaux[numeroLinea][i]=numero-1;
        //si el valor es distinto de 0 entonces actualizamos la estructura resolutora
        if((numero-1)>=0){
            e1=res1.reducePosiblesCasilla(e1,numeroLinea,i,numero-1);
        }
        i++;
    }
    return lec;
}
