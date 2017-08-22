# cpp-monadic-sudoku

This Application solves the sudoku represented in sudoText2.txt file(0 means empty tile). To try it, download it and install Code::Blocks with TDM compiler, create new project and paste all this project's files. Main code file to execute is pruebas.cpp



# Code Explanation Summary

As show in the application diagram in Diagrama.jpg file, pruebas.cpp has an instance of class Inicializacion which initialitate all data structures necessaries to the sudoku resolving process, and also has an instance of class Resolutor which actually resolves the sudoku using those data structures.

EstructuraResolutora is those data structures, is the struct that represents the sets of possibilities for each square of the sudoku's board in two ways: represents it by row and column (valoresPosiblesPorCelda), and represents it by block (celdasPosiblesPorBloqueYValor) too. 
So, following this concept, valoresPosiblesPorCelda is the 3 dimensional array that represents all value possibilities given a coordinate of the sudoku. And celdasPosiblesPorBloqueYValor is the 3 dimensional array that represents all possible squares given a block and a value.

Resolutor use 4 cases to implemment a recursive tree to execute backtracking over the sudoku:
+first case is no squares empty at all, so the sudoku's board state of values is returned as solution.
+second case is an extra iteration over row index which means that there is not solution in this branch, so returns void.
+thirdone is the iteration over an already filled square, so it does recursion over next square.
+the last case is the most important one, where it tries to fix one of the possible values of a square in that coordinate. Those possible values are saved in EstructuraResolutora. If that process results in an unresolvebal sudoku then it is discarded, else it does recursion over next square.

The way in which Resolutor does the try of fixing a square is implemented in function reducePosiblesCasilla. 
In first step, this function iterate over row in function reducePosiblesOtrasCeldas3d using lambda expressions, then iterate over column in function reducePosiblesOtrasCeldas2d using lambda again and selects all coordinates which are in the same row or column as the fixing square. However, it only removes the fixed value from the list of posible values of each of those selected coordinates in reducePosiblesOtrasCeldas1d using lambda too.
Secondly, it checks every square from the list of posible squares of celdasPosiblesPorBloqueYValor using the fixed square's block and fixed value to index in, and then it removes the square only if is distinct to the fixed one. This is implemmented in the function marcarEnBloqueValorPuesto using a lambda expression.

Lambda expresions above named are >>= operand overloading that implemments a functor template of the monad structure called vectormonada.
vectormonada is an implemmentation of monad template monada which is just the general purpose monad template with its unit method (template bind).
Furtheremore, vectormonada declare its functor method as a >>= operant overloading where it takes a vector and the lambda returned object as parameters of it and executes a iteration over that vector to apply the lambda expression and, also append each lambda result.
i.e.: Thats why function reducePosiblesOtrasCeldas1d in Resolutor can iterate over posibles1d vector parameter applying a check over each element of it and creating unitary vectors from this element using the functor appending.
This complex structure of templates and lambdas also offers the posibility of declaring distinct appending for distint kind of parameters as vectormonada is declared for vector and listmonada is declared for list.
Also, type cases
