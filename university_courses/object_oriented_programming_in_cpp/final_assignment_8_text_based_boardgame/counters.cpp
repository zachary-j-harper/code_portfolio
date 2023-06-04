#include <string>
#include <iostream>

#include "board.h"
#include "counters.h"

using namespace counters;


//Most basic move validation funtions
int black_counter::move_ok(std::vector<black_counter> black_pieces, std::vector<white_counter> *white_pieces, int triangle_move){
    double black_on_triangle{0}, white_on_triangle{0};
    if(triangle_move  == 25){ //25 is the off board area for black. Height doesn't matter, so return 1
        return 1;
    }
    if(triangle_move > 25 || triangle_move < 1){
        return 99;
    }
    for(int i{0}; i < (*white_pieces).size(); i++){
        if( (*white_pieces)[i].triangle == triangle_move){
            white_on_triangle++;
        }
    }
    for(int i{0}; i < black_pieces.size(); i++){
        if(black_pieces[i].triangle == triangle_move){
            black_on_triangle++;
        }
    }
    if(white_on_triangle < 2 && black_on_triangle < 5){
        return black_on_triangle + 1; //if move is possible, returns the relevant height
    } 
    else{
        return 99;
    }
    //99 is keyed to an error/impossible move
}

int white_counter::move_ok(std::vector<black_counter> black_pieces, std::vector<white_counter> white_pieces, int triangle_move){
    //Similar in principle to black counterpart
    double white_on_triangle{0}, black_on_triangle{0};
    if(triangle_move == 0){ //0 is the off-board area for white
        return 1;
    }
    if(triangle_move > 25 || triangle_move < 0){
        return 99;
    }
    for(int i{0}; i < white_pieces.size(); i++){
        if(white_pieces[i].triangle == triangle_move){
            white_on_triangle++;
        }
    }
    for(int i{0}; i < black_pieces.size(); i++){
        if(black_pieces[i].triangle == triangle_move){
            black_on_triangle++;
        }
    }
    if(white_on_triangle < 5 && black_on_triangle < 2){
        return white_on_triangle + 1;
    } 
    else{
        return 99;
    }
}

//Larger move validation that returns all possible moves for a specific counter.
//Black version must use pointer thanks to forward loading.
std::vector<backgammon_board::triangle> black_counter::check_moves(std::vector<black_counter> black_pieces, std::vector<white_counter> *white_pieces, int die_1, int die_2){
    std::vector<backgammon_board::triangle> possible_moves;
    int move_1{move_ok(black_pieces, white_pieces, triangle + die_1)}, move_2{move_ok(black_pieces, white_pieces, triangle + die_2)}, move_3{move_ok(black_pieces, white_pieces, triangle + die_1 + die_2)};
    if( move_1 != 99){ //99 keyed to an impossible move/error
        possible_moves.push_back(backgammon_board::triangle{triangle + die_1, move_1});
    }
    if( move_2 != 99){
        possible_moves.push_back(backgammon_board::triangle{triangle + die_2, move_2});
    }
    if( move_3 != 99){
        possible_moves.push_back(backgammon_board::triangle{triangle + die_1 + die_2, move_3});
    }
    return possible_moves;
}

std::vector<backgammon_board::triangle> white_counter::check_moves(std::vector<black_counter> black_pieces, std::vector<white_counter> white_pieces, int die_1, int die_2){
    std::vector<backgammon_board::triangle> possible_moves;
    int move_1{move_ok(black_pieces, white_pieces, triangle - die_1)}, move_2{move_ok(black_pieces, white_pieces, triangle - die_2)}, move_3{move_ok(black_pieces, white_pieces, (triangle - die_1) - die_2)};
    if( move_1 != 99){
        possible_moves.push_back(backgammon_board::triangle{triangle - die_1, move_1});
    }
    if( move_2 != 99){
        possible_moves.push_back(backgammon_board::triangle{triangle - die_2, move_2});
    }
    if( move_3 != 99){
        possible_moves.push_back(backgammon_board::triangle{(triangle - die_1) - die_2, move_3});
    }
    return possible_moves;
}

//Makes moves using board commands. A tidy wrapper.
void black_counter::move_to(int triangle_in, int height_in, backgammon_board::board &board){
    if(triangle == 0 || triangle == 25){
        if(triangle == 0){
            board.remove_black_centre();
        } 
    }   else{
            board.set_empty(triangle, height);

        }
    if(triangle_in == 0 || triangle_in == 25 ){
        if(triangle_in == 0){    
            board.add_black_centre();
        }
    }   else{
            board.set_black(triangle_in, height_in);
        }

    triangle = triangle_in;
    height = height_in;     
}

void white_counter::move_to(int triangle_in, int height_in, backgammon_board::board &board){
    if(triangle == 0 || triangle == 25){
        if(triangle == 25){
            board.remove_white_centre();
        } 
    }   else{
            board.set_empty(triangle, height);

        }
    if(triangle_in == 0 || triangle_in == 25){
        if(triangle_in == 25){    
            board.add_white_centre();
        }
    }   else{
            board.set_white(triangle_in, height_in);
        }

    triangle = triangle_in;
    height = height_in;     
}