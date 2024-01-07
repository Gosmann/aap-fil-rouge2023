#include <iostream>

class tic_tac_toe{
    
    public:
        char state[9] ;     // state of the board
        char player ;       // either 'x' or 'o'
        char player0 ;      // either 'x' or 'o' on the first move

        int empty ;         // number of empty squares
        char won ;          // either 'x' or 'o' or 0 (who won?) 
        int score ;         // -1, 0, 1 (depending on player and won)
        
        int minimax_score ;    
        int minimax_max ;

        tic_tac_toe * next_state[9] ;

        // constructors
        tic_tac_toe();
        tic_tac_toe( tic_tac_toe *, int index);
        
        int check_state_completeness( void ) ;
        char check_if_won( void ) ;

        int read_current_state( char * input ) ;   
        
        void print_current_state( void ) ;
        void print_recursive( void ) ;
        void print_recursive( int ) ;
        
        void expand( void ) ;

        void minimax( void ) ;

        tic_tac_toe pick_max(void) ;
};
