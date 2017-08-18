#ifndef _LECTORARCHIVOS_H_
#define _LECTORARCHIVOS_H_

#include <iostream>
#include <fstream>
#include <string>
#include "resolutor.h"

enum Lectura{Exitosa, Fallida, FalloAbrir, FalloValor};

class LectorArchivos {
    public:
        LectorArchivos();
        const Lectura leeArchivoPuzzle(Resolutor res1, EstructuraResolutora &e1, std::vector<std::vector<int>> &puzzaux, std::string nombreArchivo);
    private:
        const Lectura aniadeFilaPuzzle(Resolutor res1, EstructuraResolutora &e1, std::vector<std::vector<int>> &puzzaux, std::string linea, int numeroLinea);
};

#endif
