// player super-tic-tac-toe ( player1 against player2 )

#include "tic_tac_toe.hpp"
#include "mini_max.hpp"

int main(){

    super_tic_tac_toe game ;

    int resp = 0 ;

    int i = 0 ;

    game.set_state();

    // print current state
    //game.print_current_state() ;

    while( game.won == ' ' ){
        
        if( ( i % 2 ) == 0 ){
            //while( game.get_command( 'x' ) == -1 ) ;

            // computer plays:: 
            // print current state
            std::cout << "get current state : \n" ;
            game.print_current_state() ;

            double current_time = ( clock() / (double)CLOCKS_PER_SEC ) ;
            double delta_time = 0; 

            int k = 3 ;
            
            super_tic_tac_toe game_local = game;

            // 2 * 16 = 32s
            while( delta_time < 2.0 ){
                
                //std::cout << "expand : \n" ;
                game_local.expand( 'x', k ) ;
                
                //std::cout << "mini_max : \n" ;
                game_local.mini_max( 'x', k ) ;       // minimax(&game, 'x', 5); 
                
                delta_time = ( ( clock() / (double)CLOCKS_PER_SEC ) - current_time ) ;

                k++;
            }

            game = game_local;
            
            //std::cout << "expand : \n" ;
            //game.expand( 'x', 6 ) ;
            
            //std::cout << "mini_max : \n" ;
            //game.mini_max( 'x', 6 ) ;       // minimax(&game, 'x', 5); 
            
            int i, j ;
            int first_flag = 0;

            // print best
            std::cout << "BEST : \n" ;
            for( i = 0 ; i < 9 ; i++ ){
                for( j = 0 ; j < 9 ; j++ ){
                    if( game.next_plays[i][j] != NULL){
                        
                        //std::cout << "possible : \n" ;
                        //game.next_plays[i][j]->print_current_state();

                        if( first_flag == 0 ){
                            game.mini_max_eval = game.next_plays[i][j]->mini_max_eval;
                            first_flag = 1 ;
                        }
                        else{
                            if( game.mini_max_eval < game.next_plays[i][j]->mini_max_eval )
                                game.mini_max_eval = game.next_plays[i][j]->mini_max_eval ;
                        }

                    }
                }
            }

            std::cout << "rec_free : \n" ;
            for( i = 0 ; i < 9 ; i++ ){
                for( j = 0 ; j < 9 ; j++ ){
                    if( game.next_plays[i][j] != NULL){

                        if( game.next_plays[i][j]->mini_max_eval != game.mini_max_eval ){
                            
                            game.next_plays[i][j]->rec_free();

                            //delete game.next_plays[i][j] ;     
                            //game.next_plays[i][j] = NULL ;
                        }
                    }
                }
            }
            
            std::cout << "update game : \n" ;
            first_flag = 0;
            for( i = 0 ; i < 9 ; i++ ){
                for( j = 0 ; j < 9 ; j++ ){
                    if( game.next_plays[i][j] != NULL){

                        if( game.next_plays[i][j]->mini_max_eval == game.mini_max_eval && 
                            first_flag == 0 ){

                            std::cout << i << " : " << j << " : " << game.mini_max_eval << " \n";   
                            game.next_plays[i][j]->print_current_state();

                            // game.move( 'x', i, j ) ;
                                                    
                            game = game.next_plays[i][j] ;       

                            std::cout << "hist : " << game.history.back() << " " << 
                                delta_time << " depth : " << k << " \n" ;
                            
                            first_flag = 1;
                        }
                    }
                }
            }
        
        }
        else{
            while( game.get_command( 'o' ) == -1 ) ;
        }
           
        //while( game.get_command( 'o' ) == -1 ) ;


        i++;
    }
    // print current state
    game.print_current_state() ;

    std::cout << "[GAME OVER] : " << game.won << " won the game ! \n ";
        
    return 0;

}