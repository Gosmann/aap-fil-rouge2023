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
        int mandatory_grid ;                  // stores the mandatory subgrid that must be player ( -1 if not mandatory )

        void print_current_state() ;

        int get_command( char player ) ;

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
    mandatory_grid = -1;   
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

                    if( i == (mandatory_grid / 3) && k == (mandatory_grid % 3) ){
                    //if( 0 ){                   // print special chars
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

int super_tic_tac_toe::get_command( char player ){

    std::cout << player << " : " ;
        
    int grid ; 
    std::string sub_grid ; 
    int sub_grid_index[2] ;

    std::cin >> grid >> sub_grid ; 

    int i;
    grid--;
    
    // DEBUG
    //std::cout << "[" << grid << "] \n" ;
    //std::cout << "[" << sub_grid << "] \n" ;

    // check format correctness

    if( grid < 0 || grid > 8 ){     // incorrect grid format
        std::cout << "[ERROR] : incorrect grid format \n" ;
        return -1;
    }
    
    switch ( sub_grid[0] )
    {
    case 'A': case 'a': 
        sub_grid_index[0] = 0 ;
        break ;

    case 'B': case 'b': 
        sub_grid_index[0] = 1 ;
        break ;

    case 'C': case 'c':
        sub_grid_index[0] = 2 ;
        break ;
    
    default:
        std::cout << "[ERROR] : incorrect sub_grid collumn format \n" ;
        return -1;
        break;
    }

    switch ( sub_grid[1] )
    {
    case '1':
        sub_grid_index[1] = 0 ;
        break;

    case '2':
        sub_grid_index[1] = 1 ;
        break;

    case '3': 
        sub_grid_index[1] = 2 ;
        break;
    
    default:
        std::cout << "[ERROR] : incorrect sub_grid row format \n" ;
        return -1;
        break;
    }

    // we assume the input is correct
    

    // update player status
    switch ( player ) {
        case 'x': case 'X':
            plays_x++;
            break;
        
        case 'o': case 'O':
            plays_o++;
            break;
            
        default:
            std::cout << "[ERROR] : incorrect player argument \n" ;
            return -1;
            break;
    }

    if( mandatory_grid != -1 ){             // not any command is valid
        
        if( mandatory_grid != grid ){       // incorrect grid selected

            std::cout << "[ERROR] : incorrect grid selected \n" ;
            return -1;

        }

    }
    
    if (mini_games[ grid / 3 ][ grid % 3 ].state[ sub_grid_index[0] ][ sub_grid_index[1] ] == ' '){
        mini_games[ grid / 3 ][ grid % 3 ].state[ sub_grid_index[0] ][ sub_grid_index[1] ] = player ; 
    }
    else{
        std::cout << "[ERROR] : position already played \n" ;
        return -1;
    };

    // impose mandatory grid
    mandatory_grid = sub_grid_index[0] * 3 + sub_grid_index[1] * 1 ;

    std::cout << "\n";
    return 0;    

}

int main(){

    super_tic_tac_toe game ;

    int resp = 0 ;

    while( 1 ){

        // print current state
        game.print_current_state() ;

        while( game.get_command( 'x' ) == -1 ) ;
        
        game.print_current_state() ;
        
        while( game.get_command( 'o' ) == -1 ) ;

    }

    return 0;

}