#include <iostream>
#include "tic_tac_toe.hpp"

int main(int argc, char * argv[] ){

    tic_tac_toe game ; 

    switch( argc ){

        case (2) :
            game.read_current_state( argv[1] );
            //game.print_current_state();
            break;

        default :
            std::cout << "incorrect number of arguments \n";
            return -1;
    }

    //game.print_current_state();

    game.expand() ;

    //game.print_recursive(1) ;

    game.minimax() ;

    game.print_recursive(1) ;

    //game.print_current_state();

    return 0;
}