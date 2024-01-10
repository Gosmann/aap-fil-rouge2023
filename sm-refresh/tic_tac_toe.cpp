#include "tic_tac_toe.hpp"

tic_tac_toe::tic_tac_toe(){

    int i, j;

    for( i = 0 ; i < 3 ; i++ ){
        for( j = 0 ; j < 3 ; j++ ){
                
            state[i][j] = 'Z' ;                // 'Z' means uninitialized

        }
    }

    won = ' ' ;                                  // no one has won yet  

}

tic_tac_toe::tic_tac_toe( char init ){

    int i, j;

    for( i = 0 ; i < 3 ; i++ ){
        for( j = 0 ; j < 3 ; j++ ){
                
            //state[i][j] = 'A' + j + i*3 ;               
            state[i][j] = init ;               

        }
    }

    won = ' ' ;                                  // no one has won yet  

}

void tic_tac_toe::check_if_won(){
    
    int i;
    int l_state[9] ;    // local state variable

    for(i = 0 ; i < 9 ; i++ )
        l_state[i] = state[ i / 3 ][ i % 3 ] ;

    won = ' ';

    for(i = 0 ; i < 9 ; i++ ){

        if( l_state[i] == 'o' || l_state[i] == 'x' ){

            switch( i ){

                case (0):
                    if( ( l_state[0] == l_state[1] && l_state[0] == l_state[2] ) ||
                        ( l_state[0] == l_state[3] && l_state[0] == l_state[6] ) ||
                        ( l_state[0] == l_state[4] && l_state[0] == l_state[8] ) ){
                        won = l_state[0] ;
                    }
                    break;
                
                case(1):
                    if( ( l_state[1] == l_state[4] && l_state[1] == l_state[7] ) ){
                        won = l_state[1] ;
                    }
                    break;
                
                case(2):
                    if( ( l_state[2] == l_state[4] && l_state[2] == l_state[6] ) ||
                        ( l_state[2] == l_state[5] && l_state[2] == l_state[8] ) ){
                        won = l_state[2] ;
                    }
                    break;
                
                case(3):
                    if( ( l_state[3] == l_state[0] && l_state[3] == l_state[6] ) ||
                        ( l_state[3] == l_state[4] && l_state[3] == l_state[5] ) ){
                        won = l_state[3] ;
                    }
                    break;
                
                case(6):
                    if( ( l_state[6] == l_state[7] && l_state[6] == l_state[8] ) ){
                        won = l_state[6] ;
                    }
                    break;

            }
        }        
    }


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

double tic_tac_toe::evaluate( char player ){

    double evaluation = 0;
    
    if( state[1][1] == player )
        evaluation += 1 ;
    
    return evaluation ; 
}

super_tic_tac_toe::super_tic_tac_toe(){
    
    int i, j ;

    for(i = 0 ; i < 3 ; i++ ){
        for(j = 0 ; j < 3 ; j++ ){
            
            //mini_games[i][j] = tic_tac_toe { ( ( j + 3 * i ) + 'A' ) } ;
            mini_games[i][j] = tic_tac_toe { ' ' } ;

        }
    }

    for( i = 0 ; i < 9 ; i++ ){
        for( j = 0 ; j < 9 ; j++ ){
            next_plays[i][j] = NULL;
        }
    }

    player_in = ' ' ;
    plays_o = 0 ;
    plays_x = 0 ;
    won = ' ' ;
    mandatory_grid = -1 ;    
}

int super_tic_tac_toe::check_if_won(){
    
    int i;
    int l_state[9] ;    // local state variable

    for(i = 0 ; i < 9 ; i++ )
        //l_state[i] = state[ i / 3 ][ i % 3 ] ;
        l_state[i] = mini_games[ i / 3 ][ i % 3 ].won ;

    won = ' ';

    for(i = 0 ; i < 9 ; i++ ){

        if( l_state[i] == 'o' || l_state[i] == 'x' ){

            switch( i ){

                case (0):
                    if( ( l_state[0] == l_state[1] && l_state[0] == l_state[2] ) ||
                        ( l_state[0] == l_state[3] && l_state[0] == l_state[6] ) ||
                        ( l_state[0] == l_state[4] && l_state[0] == l_state[8] ) ){
                        won = l_state[0] ;
                    }
                    break;
                
                case(1):
                    if( ( l_state[1] == l_state[4] && l_state[1] == l_state[7] ) ){
                        won = l_state[1] ;
                    }
                    break;
                
                case(2):
                    if( ( l_state[2] == l_state[4] && l_state[2] == l_state[6] ) ||
                        ( l_state[2] == l_state[5] && l_state[2] == l_state[8] ) ){
                        won = l_state[2] ;
                    }
                    break;
                
                case(3):
                    if( ( l_state[3] == l_state[0] && l_state[3] == l_state[6] ) ||
                        ( l_state[3] == l_state[4] && l_state[3] == l_state[5] ) ){
                        won = l_state[3] ;
                    }
                    break;
                
                case(6):
                    if( ( l_state[6] == l_state[7] && l_state[6] == l_state[8] ) ){
                        won = l_state[6] ;
                    }
                    break;

            }
        }        
    }

    // displays information if won
    if( won != ' ' ){
        switch(won){
            case 'x' :
                //std::cout << "[END] : player 'x' won !!! \n\n" ;
                return 1;
                break; 
            case 'o' :
                //std::cout << "[END] : player 'o' won !!! \n\n" ;
                return 1;
                break; 
            default : 
                break;
        }

        std::cout << "GAME : " ;
        for( i = 0 ; i < history.size() ; i++ ){
            std::cout << "[" << history[i] << "]" ;
        }
        std::cout << "\n";

    }


    return 0;

}

std::string inverse_print( std::string input ){
    return ( "\033[7m" + input + "\033[0m" ) ; 
}

std::string dashed_print( std::string input ){
    return ( "\033[9m" + input + "\033[0m" ) ; 
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
                    else if( mini_games[i][k].won != ' ' ){
                        if( mini_games[i][k].state[j][l] == mini_games[i][k].won )
                            std::cout << dashed_print( std::string { mini_games[i][k].state[j][l] } ) ;
                        else
                            std::cout << mini_games[i][k].state[j][l] ;
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

    // print mini game 
    // std::cout << "won : " ;
    for( i = 0 ; i < 3 ; i++ ){

        std::cout << "       " ;
        for( j = 0 ; j < 3 ; j++ ){
            std::cout << mini_games[i][j].won ;
            
            if( j != 2)
                std::cout << "|" ;
            else    
                std::cout << "\n" ;
        }
    }

    // print history
    /*
    for( i = 0 ; i < history.size() ; i++ ){
        std::cout << "[" <<  history[i] << "]" ;
    } */
    
    // print evaluation
    std::cout << "\n" ;
    std::cout << "evaluation : [" <<  evaluation << "] \n" ;


    std::cout << "\n" ;

}

int super_tic_tac_toe::get_command( char player ){

    std::cout << player << " : " ;
        
    int grid ;                     // 1, 2, 3, 4, 5, 6, 7, 8, 9
    std::string sub_grid ; 
    int sub_grid_index[2] ;

    std::cin >> grid >> sub_grid ; 

    int i;
    grid--;                         // 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
    
    // DEBUG
    //std::cout << "[" << grid << "] \n" ;
    //std::cout << "[" << sub_grid << "] \n" ;

    // check format correctness
    if( grid < 0 || grid > 8 ){     // incorrect grid format
        std::cout << "[ERROR] : incorrect grid format \n" ;
        std::cin.clear();
        std::cin.ignore(1024, '\n');
    
        return -1;
    }
    
    switch ( sub_grid[0] )
    {
    case 'A': case 'a': 
        sub_grid_index[1] = 0 ;
        break ;

    case 'B': case 'b': 
        sub_grid_index[1] = 1 ;
        break ;

    case 'C': case 'c':
        sub_grid_index[1] = 2 ;
        break ;
    
    default:
        std::cout << "[ERROR] : incorrect sub_grid collumn format \n" ;
        return -1;
        break;
    }

    switch ( sub_grid[1] )
    {
    case '1':
        sub_grid_index[0] = 2 ;
        break;

    case '2':
        sub_grid_index[0] = 1 ;
        break;

    case '3': 
        sub_grid_index[0] = 0 ;
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
    
    // check if the game was already won
    if( mini_games[ grid / 3 ][ grid % 3 ].won != ' ' ){
        std::cout << "[ERROR] : game already won \n" ;
        return -1;
    }

    if (mini_games[ grid / 3 ][ grid % 3 ].state[ sub_grid_index[0] ][ sub_grid_index[1] ] == ' '){
        
        // mini_games[ grid / 3 ][ grid % 3 ].state[ sub_grid_index[0] ][ sub_grid_index[1] ] = player ; 
        
        move( player, grid, sub_grid_index[0] * 3 + sub_grid_index[1] ) ;

    }
    else{
        std::cout << "[ERROR] : position already played \n" ;
        return -1;
    };

    // update history status
    history.push_back(  std::string { grid + 1 + '0' } + " " + sub_grid ) ;

    // update winning state
    mini_games[ grid / 3 ][ grid % 3 ].check_if_won();        

    // update winning state of big game
    check_if_won();        
        
    // check if next was won
    if( mini_games[ sub_grid_index[0] ][ sub_grid_index[1] ].won == ' ' ){
        mandatory_grid = sub_grid_index[0] * 3 + sub_grid_index[1] * 1 ;
    }
    else{
        mandatory_grid = -1 ;
    }

    // evaluate
    evaluate() ; 
    
    std::cout << "\n";
    return 0;    

}

int look_for_seconds( char state[3][3], char player ){
    
    //std::cout << "look for seconds! \n" ;

    int i;
    int seconds_count = 0;

    // check "almost" hits in big square
    int l_state[9] ;

    for( i = 0 ; i < 9 ; i++ )
        l_state[i] = state[ i / 3 ][ i % 3 ] ;

    for( i = 0 ; i < 9 ; i++ ){     // goes over big board in linear mode
        switch( i ){

            case 0:                 // upper left cornet
                if( l_state[0] == player && l_state[1] == player && l_state[2] == ' ' )
                    seconds_count++ ;
                if( l_state[0] == player && l_state[4] == player && l_state[8] == ' ' )
                    seconds_count++ ;
                if( l_state[0] == player && l_state[3] == player && l_state[6] == ' ' )
                    seconds_count++ ;
                if( l_state[0] == player && l_state[2] == player && l_state[1] == ' ' )
                    seconds_count++ ;
                if( l_state[0] == player && l_state[6] == player && l_state[3] == ' ' )
                    seconds_count++ ;
                if( l_state[0] == player && l_state[8] == player && l_state[4] == ' ' )
                    seconds_count++ ;
                    
                break;
            
            case 1:
                if( l_state[1] == player && l_state[2] == player && l_state[0] == ' ' )
                    seconds_count++ ;
                if( l_state[1] == player && l_state[4] == player && l_state[7] == ' ' )
                    seconds_count++ ;
                if( l_state[1] == player && l_state[7] == player && l_state[4] == ' ' )
                    seconds_count++ ;
                break;

            case 2:
                if( l_state[2] == player && l_state[5] == player && l_state[8] == ' ' )
                    seconds_count++ ;
                if( l_state[2] == player && l_state[4] == player && l_state[6] == ' ' )
                    seconds_count++ ;
                if( l_state[2] == player && l_state[6] == player && l_state[4] == ' ' )
                    seconds_count++ ;
                if( l_state[2] == player && l_state[8] == player && l_state[5] == ' ' )
                    seconds_count++ ;
                break;

            case 3:
                if( l_state[3] == player && l_state[4] == player && l_state[5] == ' ' )
                    seconds_count++ ;
                if( l_state[3] == player && l_state[6] == player && l_state[0] == ' ' )
                    seconds_count++ ;
                if( l_state[3] == player && l_state[5] == player && l_state[4] == ' ' )
                    seconds_count++ ;
                break;

            case 4:
                if( l_state[4] == player && l_state[5] == player && l_state[3] == ' ' )
                    seconds_count++ ;
                if( l_state[4] == player && l_state[7] == player && l_state[1] == ' ' )
                    seconds_count++ ;
                if( l_state[4] == player && l_state[6] == player && l_state[2] == ' ' )
                    seconds_count++ ;
                if( l_state[4] == player && l_state[8] == player && l_state[0] == ' ' )
                    seconds_count++ ;
                break;
            
            case 5:
                if( l_state[5] == player && l_state[8] == player && l_state[2] == ' ' )
                    seconds_count++ ;
                break;
            
            case 6:
                if( l_state[6] == player && l_state[7] == player && l_state[8] == ' ' )
                    seconds_count++ ;
                if( l_state[6] == player && l_state[8] == player && l_state[7] == ' ' )
                    seconds_count++ ;
                break;
            
            case 7:
                if( l_state[7] == player && l_state[8] == player && l_state[6] == ' ' )
                    seconds_count++ ;
                break;

            default :
                break;
        }
    }

    return seconds_count ;
}

double super_tic_tac_toe::evaluate_player( char player ){
    
    int i, j, k, l;

    double evaluation = 0 ;

    // check ultimate win
    if( won == player )
        evaluation += 10000.0 ;

    // check if won any small board
    for( i = 0 ; i < 3 ; i++ ){
        for( j  = 0 ; j < 3 ; j++ ){
            if( mini_games[i][j].won == player )
                evaluation += 20.0 ;
        }
    }

    // check big board wins
    if( mini_games[1][1].won == player )
        evaluation += 2.0 ;
    
    // check if won a corner board
    if( mini_games[0][0].won == player )
        evaluation += 1.0 ;
    
    if( mini_games[0][2].won == player )
        evaluation += 1.0 ;

    if( mini_games[2][0].won == player )
        evaluation += 1.0 ;

    if( mini_games[2][2].won == player )
        evaluation += 1.0 ;

    // check small board wins
    for( i = 0 ; i < 3 ; i++ ){
        for( j = 0 ; j < 3 ; j++ ){
            
            // get number of center squares
            evaluation += mini_games[i][j].evaluate( player ) * 1.0 ; 
            
            // evaluate center game
            if( j == 1 && i == 1 ){
                // count number of plays in the center square
                for( k = 0 ; k < 3 ; k++ ){
                    for( l = 0 ; l < 3 ; l++ ){
                        if( mini_games[i][j].state[k][l] == player )
                            evaluation += 0.5 ;
                    }
                }   
            }
            
            // look for seconds in the small games
            evaluation += ( look_for_seconds( mini_games[i][j].state ,  player ) * 5.0 ) ;
        }
    }

    // look_fot_seconds in the big game
    char temp_state[3][3] ;
    
    for( i = 0 ; i < 3 ; i++){
        for( j = 0 ; j < 3 ; j++){
            temp_state[i][j] = mini_games[i][j].won ;
        }
    }
    evaluation += ( look_for_seconds( temp_state ,  player ) * 50.0 ) ;

    return evaluation ; 
}

void super_tic_tac_toe::evaluate( void ){
    evaluation = evaluate_player('x') - evaluate_player('o') ;
}

void super_tic_tac_toe::set_state( void ){

    int i;
    
    //mini_games[0][2].state[1][0] = 'x' ;
    //mini_games[0][2].state[1][1] = 'x' ;
    //mini_games[0][2].state[2][2] = 'x' ;


    // update winning state
    for(i = 0 ; i < 9 ; i++ ){
        // update winning state
        mini_games[ i / 3 ][ i % 3 ].check_if_won();  
    }
    
    check_if_won(); 
    
    evaluate();
    
}

int super_tic_tac_toe::expand( char player , int depth ){
    int i, j;
    // consider all moves 'player' has for 1 depth

    // checks if a there is a mandatory square : 

    if( mandatory_grid == -1 ){     // no grid is mandatory : 81 possibilities
        // no grid is mandatory
        // a grid is mandatory : 9 possibilities
        
        for( i = 0 ; i < 9 ; i++ ){
            for( j = 0 ; j < 9 ; j++ ){
                
                // if move is available
                if( mini_games[ i / 3 ][ i % 3 ].state[ j / 3 ][ j % 3 ] == ' ' &&
                    mini_games[ i / 3 ][ i % 3 ].won == ' ' ){
                    
                    // update pointer
                    next_plays[ i ][ j ] = new super_tic_tac_toe( this ) ;
                    
                    next_plays[ i ][ j ]->move( player, i , j ) ;

                    //next_plays[ i ][ j ]->print_current_state() ;

                    //std::cout << "[" << i << " : " << j << "]" <<  
                    //    next_plays[ i ][ j ]->evaluation << "\n";

                    if( depth > 1 ){

                        switch ( player ) {
                            case 'x':
                                next_plays[ i ][ j ]->expand( 'o' , depth -1 ) ;    
                                break;
                            case 'o':
                                next_plays[ i ][ j ]->expand( 'x' , depth -1 ) ;    
                                break;
                            default:
                                std::cout << "[ERROR] in player \n" ;
                                break;
                        }
                    
                    }

                }
            }
        }

    }
    
    else if( mandatory_grid >= 0 && mandatory_grid <= 8 ){
        // a grid is mandatory : 9 possibilities
        for( i = 0 ; i < 9 ; i++ ){
            
            // if move is available
            if( mini_games[ mandatory_grid / 3 ][ mandatory_grid % 3 ].state[ i / 3 ][ i % 3 ] == ' '  &&
                mini_games[ mandatory_grid / 3 ][ mandatory_grid % 3 ].won == ' ' ){
                // update pointer
                next_plays[ mandatory_grid ][ i ] = new super_tic_tac_toe( this ) ;
                
                next_plays[ mandatory_grid ][ i ]->move( player, mandatory_grid, i ) ;

                //next_plays[ mandatory_grid ][ i ]->print_current_state(  ) ;

                //std::cout << "[" << mandatory_grid << " : " << i << "]" <<  
                //    next_plays[ mandatory_grid ][ i ]->evaluation << "\n";
                
                if( depth > 1 ){

                    switch ( player ) {
                        case 'x':
                            next_plays[ mandatory_grid ][ i ]->expand( 'o' , depth -1 ) ;    
                            break;
                        case 'o':
                            next_plays[ mandatory_grid ][ i ]->expand( 'x' , depth -1 ) ;    
                            break;
                        default:
                            std::cout << "[ERROR] in player \n" ;
                            break;
                    }
                
                }

            }
        }
    }   
    else{
        return -1 ;
        std::cout << "[ERROR] : mandatory grid format \n" ;
    }
    


    return 0;
}

super_tic_tac_toe::super_tic_tac_toe( super_tic_tac_toe * parent ){

    int i, j;

    // copy all 9 minigames    
    for( i = 0 ; i < 3 ; i++ ){
        for( j = 0 ; j < 3 ; j++ ){
            mini_games[i][j] = parent->mini_games[i][j] ;
        }
    }

    // next plays are equal to NULL
    for( i = 0 ; i < 9 ; i++ ){
        for( j = 0 ; j < 9 ; j++ ){
            next_plays[i][j] = NULL ;
        }
    }

    history = parent->history ;
    
    won = parent->won ;
    
    player_in = parent->player_in ;
    plays_x = parent->plays_x ;
    plays_o = parent->plays_o ;
    mandatory_grid = parent->mandatory_grid ;

    evaluation = parent->evaluation ;
    double mini_max_eval = parent->mini_max_eval ;    

}

int super_tic_tac_toe::move( char player, int grid, int move ){

    // test if move is availavle
    if( mini_games[ grid / 3 ][ grid % 3 ].state[ move / 3 ][ move % 3 ] == ' ' ){
        // make the move
        switch( player ){
            case 'o':
                plays_o++;
                break;
            case 'x':
                plays_x++;
                break;
            default:
                return -1;
                std::cout << "[ERROR] : incorrect player \n" ;
                break; 
        }

        mini_games[ grid / 3 ][ grid % 3 ].state[ move / 3 ][ move % 3 ] = player ;

        // check if won sub_game
        mini_games[ grid / 3 ][ grid % 3 ].check_if_won();

        // check if won game
        check_if_won() ;

        // check if next will be mandatory or not
        if( mini_games[ move / 3 ][ move % 3 ].won == ' ' ){
            // if some one has won
            mandatory_grid = move ;
        }
        else{
            mandatory_grid = -1 ;
        }
        

        // evaluate
        evaluate();
        
        
        // prev

        std::string move_str ;

        switch( move ){
            case 0:
                move_str = "a3";
                break;
            case 1:
                move_str = "b3";
                break;
            case 2:
                move_str = "c3";
                break;
            case 3:
                move_str = "a2";
                break;
            case 4:
                move_str = "b2";
                break;
            case 5:
                move_str = "c2";
                break;
            case 6:
                move_str = "a1";
                break;
            case 7:
                move_str = "b1";
                break;
            case 8:
                move_str = "c1";
                break;
            default:
                break;

        }

        //update history status
        history.push_back(  std::string { grid + 1 + '0' } + " " + move_str ) ;

        // evaluate
        //evaluate() ; 


    }
    else{
        return -1;
        std::cout << "[ERROR] : mandatory grid format \n" ;
    }

    return 0;

}

// int minimax( super_tic_tac_toe * game, char player, int depth ) 
int super_tic_tac_toe::mini_max( char player, int depth ){

    
    player_in = player ;
    int i, j;
    int flag_first = 0;
    // evaluate depth of 1
    
    if( depth > 1 ){

        for( i = 0 ; i < 9 ; i++ ){
            for( j = 0 ; j < 9 ; j++ ){
                
                //std::cout << "next_plays[" << i << "]" << "[" << j << "] : "
                //    << next_plays[i][j] << " \n" ;

                if( next_plays[i][j] != NULL ){     // next move is possible
                    
                    switch ( player )   {
                        case 'x':
                            // maximize
                            next_plays[i][j]->mini_max( 'o', depth - 1 );
                            break;

                        case 'o':
                            // minimize
                            next_plays[i][j]->mini_max( 'x', depth - 1 );
                            break;

                        default:
                            std::cout << "[ERROR] : incorrect player \n";
                            return -1;
                            break;
                    }
                    
                    if( flag_first == 0 ){
                        flag_first = 1;
                        mini_max_eval = next_plays[i][j]->mini_max_eval ;
                    }
                    else{
                        switch ( player )   {
                            case 'x':
                                // maximize
                                if( next_plays[i][j]->mini_max_eval > mini_max_eval )
                                    mini_max_eval = next_plays[i][j]->mini_max_eval ;
                                break;

                            case 'o':
                                // minimize
                                if( next_plays[i][j]->mini_max_eval < mini_max_eval )
                                    mini_max_eval = next_plays[i][j]->mini_max_eval ;
                                break;

                            default:
                                std::cout << "[ERROR] : incorrect player \n";
                                return -1;
                                break;
                        }
                    }
                    
                } 
            
            }
        }

    }

    else{   // depth == 1

        for( i = 0 ; i < 9 ; i++ ){
            for( j = 0 ; j < 9 ; j++ ){
            
                if( next_plays[i][j] != NULL ){     // next move is possible
                    if( flag_first == 0 ){
                        flag_first = 1;
                        mini_max_eval = next_plays[i][j]->evaluation ;
                    }
                    else{
                        
                        switch ( player )   {

                            case 'x':
                                // maximize
                                if( next_plays[i][j]->evaluation > mini_max_eval )
                                    mini_max_eval = next_plays[i][j]->evaluation ;
                                break;

                            case 'o':
                                // minimize
                                if( next_plays[i][j]->evaluation < mini_max_eval )
                                    mini_max_eval = next_plays[i][j]->evaluation ;

                                break;

                            default:
                                std::cout << "[ERROR] : incorrect player \n";
                                return -1;
                                break;
                        }
                    }
                    
                } 
            
            }
        }

    }

    
    // print best move
    /*
    for( i = 0 ; i < 9 ; i++ ){
        for( j = 0 ; j < 9 ; j++ ){
            if( next_plays[i][j] != NULL){
                
                std::cout << "mini_max : " << depth << " | eval : " << mini_max_eval <<" \n" ;
                next_plays[i][j]->print_current_state();


                if( next_plays[i][j]->evaluation == mini_max_eval ){
                    std::cout << i << " : " << j << " : " << mini_max_eval << " \n";   
                }

            }
        }
    }
    */

    return 0;

}

int super_tic_tac_toe::rec_free( void ){

    int i, j;

    for( i = 0 ; i < 9 ; i++ ){
        for( j = 0 ; j < 9 ; j++ ){
            if( next_plays[i][j] != NULL ){

                next_plays[i][j]->rec_free();
                
                delete next_plays[i][j] ;
            }
        }
    }

}

