#include <iostream>

class tic_tac_toe{
    
    public:
        char state[9] ;     // state of the board
        char player ;       // either 'x' or 'o'
        int empty ;         // number of empty squares

        tic_tac_toe();
        int check_state_completeness( void ) ;
        int read_current_state( char * input ) ;   
        void print_current_state( void ) ;
        
};

// class constructor
tic_tac_toe::tic_tac_toe(){
    int i;
    for(i = 0 ; i < 9 ; i++){
        state[i] = 'Z' ;
    }
    empty = 0;

}

// check state completeness
int tic_tac_toe::check_state_completeness(){
    int i;
    empty = 0;
    
    for( i = 0 ; i < 9 ; i++ ){
        
        //std::cout << "[" << state[i] << "]"; 
        
        if( state[i] != 'x' && state[i] != 'o' && state[i] != ' ' ){
            std::cout << "[ERROR] : state is not complete \n";
            return -1 ;
        }

        if( state[i] == ' ' ){
            empty++;
        } 

    }

    return 0;
}

// read current state from command line 
int tic_tac_toe::read_current_state( char * input ){

    int i, j = 0;

    //std::cout << input << "\n"; // debug

    for(i = 0 ; i < 9 ; i++){
        
        // debug start
        //std::cout << "i : " << i << " [" << state << "] \n";

        char elt = input[j] ;

        if( elt == 'o' || elt == 'O' || elt == 'x' || elt == 'X' ){
                // elt is a play
            if( elt == 'o' || elt == 'O' )
                state[i] = 'o' ;

            else if( elt == 'x' || elt == 'X'  ) 
                state[i] = 'x' ;

            j++;
        }

        else if( elt >= '1' && elt <= '9' ){   // elt is blank
            int k;
            for( k = 0 ; k < (elt - '0') ; k++ ){
                state[i] = ' ' ;
                i++;
            }
            i--;
            j++;
        }

        //debug end
        //std::cout << "i : " << i << " [" << state << "] \n";
    }

    // by now, state should be complete
    // verify if
    int resp = check_state_completeness();
    if( resp == -1){
        return -1 ;
    }

    // by here it is complete
    if( input[j] != ' ' ){
        std::cout << "[ERROR] : space not correctly positioned \n";
        return -1 ;
    }

    // check player
    j++;
    if( input[j] != 'x' && input[j] != 'o' ){
        std::cout << "[ERROR] : unrecognized player \n ";
        return -1 ;
    }
    else{
        player = input[j] ;
    }
    
    // everything seems fine;
    return 0;

}

void tic_tac_toe::print_current_state(){
    
    // by now, state should be complete
    int resp = check_state_completeness();
    
    if( resp == 0){     // if state is complete

        int i;
        for(i = 0 ; i < 9 ; i++ ){

            std::cout << state[i] ;
            
            if( ((i+1) % 3) == 0 ){
                std::cout << "\n" ;
            }
            else{
                std::cout << "|" ;
            }
        }
    }

    std::cout << "player : " << player << " \n";
    std::cout << "nº of possible moves : " << empty << " \n";

}

int main(int argc, char * argv[] ){

    tic_tac_toe game ; 

    switch( argc ){

        case (2) :
            game.read_current_state( argv[1] );
            game.print_current_state();
            break;

        default :
            std::cout << "incorrect number of arguments \n";

    }

    return 0;
}