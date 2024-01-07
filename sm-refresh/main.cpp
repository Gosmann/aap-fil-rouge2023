// player super-tic-tac-toe ( player1 against player2 )

#include <iostream>
#include <string>

class tic_tac_toe{

    public:
        char state[3][3] ;              // hold current state of the board ('o', 'x', ' ', 'Z' )
        char won ;                      // holds if the board was won ( 'o', 'x', 0 ) 

        void print_current_state();

        tic_tac_toe();
        tic_tac_toe(char init);

} ;

tic_tac_toe::tic_tac_toe(){

    int i, j;

    for( i = 0 ; i < 3 ; i++ ){
        for( j = 0 ; j < 3 ; j++ ){
                
            state[i][j] = 'Z' ;                // 'Z' means uninitialized

        }
    }

    won = 0 ;                                  // no one has won yet  

}

tic_tac_toe::tic_tac_toe( char init ){

    int i, j;

    for( i = 0 ; i < 3 ; i++ ){
        for( j = 0 ; j < 3 ; j++ ){
                
            //state[i][j] = 'A' + j + i*3 ;               
            state[i][j] = init ;               

        }
    }

    won = 0 ;                                  // no one has won yet  

}

void tic_tac_toe::print_current_state(){
    
    //std::cout << "print current state ! \n"; 

    // by now, state should be complete
    //int resp = check_state_completeness();
    int resp = 0;

    if( resp == 0){     // if state is complete

        int i;
        for(i = 0 ; i < 9 ; i++ ){

            std::cout << state[i] ;
            
            if( ((i+1) % 3) == 0 ){

                if( i == 2 ){
                    // std::cout << " : " << ( empty ) ;
                }
                else if( i == 5 ){
                    // std::cout << " : " << player << " : " << player0 ;
                }
                else if( i == 8 ){
                    // std::cout << " : " << won << " (" << score << ")" 
                    // << " (" << minimax_score << ")" ;
                }

                std::cout << "\n" ;
            }
            else{
                std::cout << "|" ;
            }
        }
    }

    std::cout << "\n" ;
    //std::cout << "player : " << player << " \n";
    //std::cout << "nº of possible moves : " << empty << " \n";

}

class super_tic_tac_toe{

    public:

        tic_tac_toe mini_games[3][3] ;
        
        int plays_x ;
        int plays_o ;
        int mandatory[2] ;                  // stores the mandatory line and collumn that must be player ( or 0 if not mandatory )

        void print_current_state() ;

        super_tic_tac_toe() ;
} ;

super_tic_tac_toe::super_tic_tac_toe(){
    
    int i, j ;

    for(i = 0 ; i < 3 ; i++ ){
        for(j = 0 ; j < 3 ; j++ ){
            
            //mini_games[i][j] = tic_tac_toe { ( ( j + 3 * i ) + 'A' ) } ;
            mini_games[i][j] = tic_tac_toe { ' ' } ;

        }
    }

    plays_o = 0;
    plays_x = 0;
}

std::string inverse_print( std::string input ){
    return ( "\033[7m" + input + "\033[0m" ) ; 
}


void super_tic_tac_toe::print_current_state(){

    int i, j, k, l ;

    //std::cout << inverse_print( "print_current_state:" ) << " \n\n" ;
    //
    
    for( i = 0 ; i < 3 ; i++ ){                // iterates over the lines in the big board
        
        for( j = 0 ; j < 3 ; j++ ){            // iterates of the lines in the small boards

            for( k = 0 ; k < 3 ; k++){         // iterates over the collumns in the big boards

                for( l = 0 ; l < 3 ; l++){     // iterates over the collumns in the small boards

                    //if( i==1 && k ==1 ){
                    if( 0 ){                   // print special chars
                        std::cout << inverse_print( std::string { mini_games[i][k].state[j][l] } ) ;
                    }
                    else{
                        std::cout << mini_games[i][k].state[j][l] ;
                    }
                    
                    if( l != 2)
                        std::cout << "|" ;
                    else    
                        std::cout << "  " ;
    
                }
            }
            std::cout << "\n" ;
        }
        std::cout << "\n" ;
    }

}



int main(){

    super_tic_tac_toe game ;

    while(1){

        // print current state
        game.print_current_state() ;

        game.get_command( 'x' ) ;

        break;


    }

    return 0;

}