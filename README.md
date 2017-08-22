# cpp-monadic-sudoku

This Application solves the sudoku represented in sudoText2.txt file(0 means empty tile). To try it, download it and install Code::Blocks with TDM compiler, create new project and paste all this project's files. Main code file to execute is pruebas.cpp




# Code Explanation Summary



--Main execution--


As show in the application diagram in Diagrama.jpg file, pruebas.cpp has an instance of class Inicializacion which initialitate all data structures necessaries to the sudoku resolving process, and also has an instance of class Resolutor which actually resolves the sudoku using those data structures.


--Resolver tools--


EstructuraResolutora is those data structures, is the struct that represents the sets of possibilities(of the sudoku's board) for each square and for each pair of block and value, so it use two representations: 

+fristone represents it by row and column (valoresPosiblesPorCelda).

+secondone represents it by block and value (celdasPosiblesPorBloqueYValor). 

So, following this concept, valoresPosiblesPorCelda is the 3 dimensional array that represents all value possibilities given a coordinate of the sudoku. And celdasPosiblesPorBloqueYValor is the 3 dimensional array that represents all possible squares given a block and a value.


--Recursion and Backtracking--


Resolutor uses 4 cases to implement a recursive tree to execute backtracking over the sudoku:

+first case is no squares empty at all, so the sudoku's board state of values is returned as the solution.

+second case is an extra iteration over row index which means that there is no solution in this branch, so returns void.

+thirdone is the iteration over an already filled square, so it does recursion over next square.

+the last case is the most important one, where it tries to fix one of the possible values of a square in that coordinate. Those possible values are saved in EstructuraResolutora. If that process results in an unresolvebal sudoku then it is discarded, else it does recursion over next square.


--Resolver fixing try--


The way in which Resolutor does the try of fixing a square is implemented in function reducePosiblesCasilla. 
In the first step, this function iterate over the row in function reducePosiblesOtrasCeldas3d using lambda expressions, then iterate over the column in function reducePosiblesOtrasCeldas2d using lambda again and selects all coordinates which are in the same row or column as the fixing square. However, it only removes the fixed value from the list of possible values of each of those selected coordinates in reducePosiblesOtrasCeldas1d using lambda too.
Secondly, it checks every square of the list of posible squares of celdasPosiblesPorBloqueYValor using the fixed square's block and fixed value to index in, and then it removes the square only if is distinct to the fixed one. This is implemented in the function marcarEnBloqueValorPuesto using a lambda expression.


--Resolver monadic methods--


Lambda expressions above named are >>= operand overloading that implements a functor template of the monad structure called vectormonada.
vectormonada is an implementation of monad template monada which is just the general purpose monad template with its unit method (template bind).
Furthermore, vectormonada declare its functor method as a >>= operand overloading where it takes a vector and the lambda returned object as parameters of it and executes an iteration over that vector to apply the lambda expression and, also append each lambda result.
i.e.: That's why function reducePosiblesOtrasCeldas1d in Resolutor can iterate over posibles1d vector parameter applying a check over each element of it and creating unitary vectors from this element using the functor appending.


--Monad flexibility--


This complex structure of templates and lambdas also offers the possibility of declaring distinct appending process for distinct kinds of parameters as vectormonada is declared for vector and listamonada is declared for list.
Also, type cases can be implemented too by declaring distinct functor function for each distinct type a vector can hold inside.
So, it is actually able to declare an overloading for those 4 cases i.e.:

+vector<<int>>

+vector<pair<int,int>>

+list<<char>>

+lis<pair<int,float>>

