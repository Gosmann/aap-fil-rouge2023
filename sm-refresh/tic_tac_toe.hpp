#include <iostream>
#include <vector>
#include <string>

class tic_tac_toe{

    public:
        char state[3][3] ;              // hold current state of the board ('o', 'x', ' ', 'Z' )
        char won ;                      // holds if the board was won ( 'o', 'x', ' ' ) 

        void print_current_state();
        void check_if_won();

        double evaluate( char player ) ;

        tic_tac_toe();
        tic_tac_toe( char init );

} ;


class super_tic_tac_toe{

    public:

        tic_tac_toe mini_games[3][3] ;

        super_tic_tac_toe * next_plays[ 9 ][ 9 ] ;  // ([grid][move]) 

        std::vector< std::string > history ;

        char won ;

        char player_in ;

        int plays_x ;
        int plays_o ;
        int mandatory_grid ;                  // stores the mandatory subgrid that must be player ( -1 if not mandatory )

        double evaluation ;                   // actual evaluation of current state
        double mini_max_eval ;                // evaluation considering minimax

        void print_current_state( void ) ;
        int check_if_won( void ) ;
        void set_state( void ); 
        
        int get_command( char player ) ;
        
        double evaluate_player( char ) ;

        void evaluate( void ) ;

        int expand( char player, int depth ) ;     // 

        //super_tic_tac_toe( char player, int grid, int move ) ;    // creates new game from previous
        int move( char player, int grid, int move ) ; 
        
        int mini_max( char player, int depth ) ;

        super_tic_tac_toe() ;
        
        int rec_free(  ) ;

        super_tic_tac_toe( super_tic_tac_toe * ) ;    // creates new game from previous
} ;

int look_for_seconds( char state[3][3], char player ) ;
