#include "tic_tac_toe.hpp"

// class constructor
tic_tac_toe::tic_tac_toe(){
    int i;
    for(i = 0 ; i < 9 ; i++){
        state[i] = 'Z' ;
        next_state[i] = NULL;
    }
    
    player = 0;
    empty = 0 ;
    won = 0 ;
    score = 0 ;
    minimax_score = 0 ; 

}

tic_tac_toe::tic_tac_toe( tic_tac_toe * parent, int index ){

    int i;
    for(i = 0 ; i < 9 ; i++){
        state[i] = parent[0].state[i] ;
        next_state[i] = NULL;
    }
    empty = 0 ;
    minimax_score = 0 ;

    player0 = parent->player0 ;
    
    if( parent[0].player == 'o' ){
        player = 'x' ;
    }
    else if( parent[0].player == 'x' ){
        player = 'o' ;
    }

    state[index] = parent->player ;

    check_state_completeness() ;

    check_if_won() ;

    if( won == 'o' || won == 'x' ){
        if( won == player0 ){
            score = 1 ;
            minimax_score = 1 ;
        }
        else{
            score = -1 ;
            minimax_score = -1 ;
        }
    }
    else{
        score = 0 ;
        minimax_score = 0 ;
    }
}

char tic_tac_toe::check_if_won(){

    int i;
    won = 0;

    for(i = 0 ; i < 9 ; i++ ){

        switch( i ){

            case (0):
                if( ( state[0] == state[1] && state[0] == state[2] ) ||
                    ( state[0] == state[3] && state[0] == state[6] ) ||
                    ( state[0] == state[4] && state[0] == state[8] ) ){
                    won = state[0] ;
                }
                break;
            
            case(1):
                if( ( state[1] == state[4] && state[1] == state[7] ) ){
                    won = state[1] ;
                }
                break;
            
            case(2):
                if( ( state[2] == state[4] && state[2] == state[6] ) ||
                    ( state[2] == state[5] && state[2] == state[8] ) ){
                    won = state[2] ;
                }
                break;
            
            case(3):
                if( ( state[3] == state[0] && state[3] == state[6] ) ||
                    ( state[3] == state[4] && state[3] == state[5] ) ){
                    won = state[3] ;
                }
                break;
            
            case(6):
                if( ( state[6] == state[7] && state[6] == state[8] ) ){
                    won = state[6] ;
                }
                break;

        }

        if( won == 'o' || won == 'x' ){
                break;
        }
        
    }

    if( won != 'o' && won != 'x' ){
        won = 0;
    }

    return won;
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

    std::cout << input << "\n"; // debug

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
        player0 = player ;
    }
    
    // everything seems fine;
    return 0;

}

void tic_tac_toe::print_current_state(){
    
    //std::cout << "print current state ! \n"; 

    // by now, state should be complete
    int resp = check_state_completeness();
    
    if( resp == 0){     // if state is complete

        int i;
        for(i = 0 ; i < 9 ; i++ ){

            std::cout << state[i] ;
            
            if( ((i+1) % 3) == 0 ){

                if( i == 2 ){
                    std::cout << " : " << (empty) ;
                }
                else if( i == 5 ){
                    std::cout << " : " << player << " : " << player0 ;
                }
                else if( i == 8 ){
                    std::cout << " : " << won << " (" << score << ")" 
                    << " (" << minimax_score << ")" ;
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

void tic_tac_toe::print_recursive(){

    int i;

    if( 1 ){    // depth can be ajusted here in the future

        for(i = 0 ; i < 9 ; i++ ){

            std::cout << state[i] ;
            
            if( ((i+1) % 3) == 0 ){
                
                
                if( i == 2 ){
                    std::cout << " : " << (9 - empty) ;
                }
                else if( i == 5 ){
                    std::cout << " : " << player ;
                }
                else if( i == 8 ){
                    std::cout << " : " << score << " (" << minimax_score << ")" ;
                }

                std::cout << "\n" ;
            }
            else{
                std::cout << "|" ;
            }

        }
        std::cout << "\n";

        // call next states
        for(i = 0 ; i < 9 ; i++){
            if( next_state[i] != NULL ){
                next_state[i]->print_recursive();
            }
        }
    
    }    

}

void tic_tac_toe::print_recursive(int depth){

    int i;

    if( depth >= 0 ){    // depth can be ajusted here in the future

        for(i = 0 ; i < 9 ; i++ ){

            std::cout << state[i] ;
            
            if( ((i+1) % 3) == 0 ){
                
                
                if( i == 2 ){
                    std::cout << " : " << (empty) ;
                }
                else if( i == 5 ){
                    std::cout << " : " << player ;
                }
                else if( i == 8 ){
                    std::cout << " : " << score << " (" << minimax_score << ")" ;
                }

                std::cout << "\n" ;
            }
            else{
                std::cout << "|" ;
            }

        }
        std::cout << "\n";

        // call next states
        for(i = 0 ; i < 9 ; i++){
            if( next_state[i] != NULL ){
                next_state[i]->print_recursive( depth - 1 );
            }
        }
    
    }    

}

void tic_tac_toe::expand( void ){

    // check_state_completeness()
    int i;

    // check all possible expansions
    for(i = 0 ; i < 9 ; i++){

        if( state[i] == ' ' ){      // there is room for expansion

            next_state[i] = new tic_tac_toe( this, i ) ;

            //std::cout << "EXPAND! \n" ;
            //next_state[i]->print_current_state(  ) ;
            
            // print new state for debugging
            //next_state[i]->print_current_state();

            if( next_state[i]->won == 0 )
                next_state[i]->expand() ;
            else{
                //std::cout << "WON! \n" ;
                //next_state[i]->print_current_state(  ) ;
            }

        }

    }

}

void tic_tac_toe::minimax( void ){

    int i;

    for( i = 0 ; i < 9 ; i++ ){

        if( next_state[i] != NULL ){

            next_state[i]->minimax();

        }
    
    }

    //std::cout << "minimax : \n" ;
    //print_current_state();
    //std::cout << "\n" ;
    
    // is it a leaf node?
    int flag_leaf = 1 ;
    for( i = 0 ; i < 9 ; i++ ){
        if( next_state[i] != NULL )
            flag_leaf = 0;
    }

    if( flag_leaf ){    // it is a leaf node
        
        minimax_score = score ;

    }
    else{               // it is not a leaf node

        if( player == player0 ){
            //max();  
            int flag_best_score = 0;
                        
            for(i = 0 ; i < 9 ; i++){   // looks for the best score
                
                if( next_state[i] != NULL ){
                    if( flag_best_score == 0 ){
                        flag_best_score = 1;
                        minimax_score = next_state[i]->minimax_score ;
                        minimax_max = i ;
                    }
                    if( minimax_score < next_state[i]->minimax_score ){
                        minimax_score = next_state[i]->minimax_score ;
                        minimax_max = i ;
                    }
                }
            }
        }
        else{
            //min();
            int flag_best_score = 0;
                        
            for(i = 0 ; i < 9 ; i++){   // looks for the best score
                
                if( next_state[i] != NULL ){
                    if( flag_best_score == 0 ){
                        flag_best_score = 1;
                        minimax_score = next_state[i]->minimax_score ;
                        minimax_max = i ;
                    }
                    if( minimax_score > next_state[i]->minimax_score ){
                        minimax_score = next_state[i]->minimax_score ;
                        minimax_max = i ;
                    }
                }
            }
            
        }
            
    }

    // for debugging
    //std::cout << "minimax : \n" ;
    //print_current_state();
    //std::cout << "\n" ;
    
    
}

tic_tac_toe tic_tac_toe::pick_max( void ){

    return next_state[ minimax_max ][0] ;
    
}
