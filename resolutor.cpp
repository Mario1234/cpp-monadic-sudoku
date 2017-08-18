#include "resolutor.h"

template<typename Tipo1>
const std::vector<Tipo1> Resolutor::reducePosiblesOtrasCeldas1d(
                   const Tipo1 elemento,
                   const std::vector<Tipo1> posibles1d,
                   const Tipo1 nulo)
{
    //elemento es la posibilidad a eliminar
    //elemAux es la posibilidad de esta iteraccion
    return posibles1d  >>= [&] (const Tipo1 elemAux) {
        if(elemAux==elemento){
                return Monada<std::vector>::unidad(nulo);
        }
        else{
            return Monada<std::vector>::unidad(elemAux);
        }
    };
}

//itera por segundo indice
template<typename Tipo1>
const std::vector<std::vector<Tipo1>> Resolutor::reducePosiblesOtrasCeldas2d(
                   int x,
                   int y,
                   const std::vector<int> listaOtrasY,
                   int indiceX,
                   const Tipo1 elemento,
                   const std::vector<std::vector<Tipo1>> posibles2d,
                   const Tipo1 nulo)
{
    //conceptos
    //celdaAreducirPosibilidades con indices indiceX, indiceY
    //celdaRellena con indices x, y
    return listaOtrasY >>= [&] (const int indiceY) {
        //mientras sea otra celda que comparta solo un indice
        //eliminar la posibilidad, recien puesta en la celdaRellena, de la lista
        if((x==indiceX && y!=indiceY) || (x!=indiceX && y==indiceY)){
            //como esta celda(celdaAreducirPosibilidades) comparte solo un indice con la celdaRellena
            //entonces elimina la posibilidad en esta celda(celdaAreducirPosibilidades).
            //la posibilidad eliminada es la del elemento puesto en la posicion x y (celda rellenada),
            //Por ejemplo:
            //posibles = celdasPosiblesPorBloqueYValor
            //-------Leyenda: celda = (bloque, valor)--------
            //celdaRellena = (0,0)
            //celdaAreducirPosibilidades = (0,1)
            return Monada<std::vector>::unidad(reducePosiblesOtrasCeldas1d(elemento,posibles2d[indiceY],nulo));
        }
        //si es la casilla rellena o cualquier otra casilla que no comparte
        //ninguna coordenada con la rellana, entonces dejar las posibilidades como estan
        else{
            return Monada<std::vector>::unidad(posibles2d[indiceY]);
        }
    };
}

//esta funcion elimina de la lista "posibles" de esta llamada de la estructura resolutora
//todas aquellas apariciones del valor que se acaba de fijar en la celda x y(celdaRellana)
//excepto en ella misma
//itera por primer indice
template<typename Tipo1>
const std::vector<std::vector<std::vector<Tipo1>>> Resolutor::reducePosiblesOtrasCeldas3d(
                   int x,
                   int y,
                   const std::vector<int> listaOtrasX,
                   const std::vector<int> listaOtrasY,
                   const Tipo1 elemento,
                   const std::vector<std::vector<std::vector<Tipo1>>> posibles3d,
                   const Tipo1 nulo)
{
    return listaOtrasX >>= [&] (const int indiceX) {
        return Monada<std::vector>::unidad(reducePosiblesOtrasCeldas2d(x,y,listaOtrasY,indiceX,elemento,posibles3d[indiceX],nulo));
    };
}

template<typename Tipo1>
bool Resolutor::todoNulos(const std::vector<Tipo1> listaPosibles,
               const Tipo1 nulo,
               int tamanio){
    int i=0;
    while(listaPosibles[i]==nulo){
        i++;
    }
    if(i==tamanio){
        return true;
    }
    else{
        return false;
    }
}

//quita todas las casillas del bloque que no sean la (x,y) de la estructura como posibles para ese valor
//listAux es lista de posibles para ese bloque y ese valor
std::vector<std::pair<int, int>> Resolutor::marcarEnBloqueValorPuesto(std::vector<std::pair<int, int>> &listAux, int x, int y){
    std::pair<int, int> celdaux(x,y);
    return listAux >>= [&] (const std::pair<int, int> celdaI) {
        if(celdaI!=celdaux){
            return Monada<std::vector>::unidad(CELDA_NULA);
        }
        else{
            return Monada<std::vector>::unidad(celdaI);
        }
    };
}

bool Resolutor::esPosibleBloque(EstructuraResolutora e1, int x, int y, int valorIntento){
    std::pair<int, int> celdaux(x,y);
    int numBloq = dameNumeroBloquePertenceCelda(celdaux);
    std::vector<std::pair<int, int>> vaux = e1.celdasPosiblesPorBloqueYValor[numBloq][valorIntento];
    return (std::find(vaux.begin(), vaux.end(), celdaux) != vaux.end());
}

int Resolutor::dameNumeroBloquePertenceCelda(std::pair<int, int> celda){
    int x = std::get<0>(celda);
    int y = std::get<1>(celda);
    return x - (x%3) + (y/3);
}

//-------------------PUBLICAS-------------------

void Resolutor::ponEstructuraListaAux(EstructuraListasAux eLisAux){
    estructuraListaAux = eLisAux;
}

//restringe las opciones en cada estructura al poner un valor en una casilla y mira si se sigue pudiendo
//resolver el puzzle
//devuelve si el puzzle sigue teniendo solucion, si una estructura tiene una fila de nulos ya no tiene solucion
EstructuraResolutora Resolutor::reducePosiblesCasilla(EstructuraResolutora e1, int x, int y, const int valor)
{
    std::pair<int, int> celdaux(x,y);
    int numBloque=dameNumeroBloquePertenceCelda(celdaux);
    e1.valoresPosiblesPorCelda = reducePosiblesOtrasCeldas3d(
                                                             x,y,estructuraListaAux.listaOtrasFilas,
                                                             estructuraListaAux.listaOtrasColumnas,valor,
                                                             e1.valoresPosiblesPorCelda,NULO
                                                             );
    e1.celdasPosiblesPorBloqueYValor = reducePosiblesOtrasCeldas3d(
                                                                   numBloque,valor,estructuraListaAux.listaOtrasBloques,
                                                                   estructuraListaAux.listaOtrasValores,celdaux,
                                                                   e1.celdasPosiblesPorBloqueYValor,CELDA_NULA
                                                                   );

    e1.celdasPosiblesPorBloqueYValor[numBloque][valor] = marcarEnBloqueValorPuesto(e1.celdasPosiblesPorBloqueYValor[numBloque][valor],x,y);

    //mira si tiene todo nulos en la fila cambiada de esta estructura
    if(todoNulos(e1.valoresPosiblesPorCelda[x][y], NULO, N_VALORES)){
        e1.sePuedeResolver=false;
        return e1;
    }
    if(todoNulos(e1.celdasPosiblesPorBloqueYValor[numBloque][valor], CELDA_NULA, N_CELDAS_BLOQUE)){
        e1.sePuedeResolver=false;
        return e1;
    }
    e1.sePuedeResolver=true;
    return e1;
}

Resolutor::Resolutor(){

}

const std::vector<std::vector<int>> Resolutor::recorreArbolIntentos(
                    int x,
                    int y,
                    int casillasVacias,
                    std::vector<std::vector<int>> puzzaux,
                    EstructuraResolutora e1)
{
    std::vector<std::vector<int>> solucion;
    //hasta que no queden casillas por rellenar o hasta la casilla siguiente a [8][8] que es [9][0]
    if(casillasVacias==0){
        return puzzaux;//devuelve la solucion
    }
    else if(x==N_FILAS){
//        muestraArrays(e1);
        return solucion;//devuelve vacio
    }
    else{
        int sigFil = x; int sigCol = y;
        //calcula siguientes corrdenadas de casilla a rellenar
        if(y==(N_COLUMNAS-1)){
            sigFil = x+1;
            sigCol=0;
        }
        else{
            sigCol++;
        }
        //si ya tiene un valor la casilla iteramos a la siguiente
        if(puzzaux[x][y]!=-1){
            solucion = recorreArbolIntentos(sigFil, sigCol, casillasVacias, puzzaux, e1);
        }
        else{
            //genera un intento por cada valor posible para la casilla (x,y)
            for(size_t i=0;i<e1.valoresPosiblesPorCelda[x][y].size();i++){
                int valorIntento = e1.valoresPosiblesPorCelda[x][y][i];
                //los valores posibles -1 significa que no son posibles
                //se descartan
                //y los posibles que no esten en la lista de posibles del bloque
                //tambien se descartan
                if(valorIntento>-1 && esPosibleBloque(e1,x,y,valorIntento)){
                   //establece el valor posible de la casilla (x,y) valorIntento en la casilla (x,y)
                    //y comprueba si se puede resolver
                    EstructuraResolutora e2 = reducePosiblesCasilla(e1,x,y,valorIntento);
                    //si las estructuras resolutoras siguen teniendo valores no nulos en las filas cambiadas
                    //se puede resolver, asi que hacemos recursion
                    if(e2.sePuedeResolver){
                        puzzaux[x][y]=valorIntento;
                        //recursion sig casilla
                        solucion = recorreArbolIntentos(sigFil, sigCol, casillasVacias-1, puzzaux, e2);
                        //si no es vacio lo devuelve como solucion
                        if(!solucion.empty()){
                            return solucion;
                        }
                    }
                }
            }
        }
        return solucion;//devuelve vacio
    }

}
