#include "board.h"

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace backgammon_board;

//Most of these do what they say on the tin
void board::set_black(int triangle, int height){
    (data_store.triangles[triangle-1])[height-1] = black_piece;
}

void board::set_white(int triangle, int height){
    (data_store.triangles[triangle-1])[height-1] = white_piece;
}

void board::set_empty(int triangle, int height){
    (data_store.triangles[triangle-1])[height-1] = space;
}

void board::print(){
    for(int i{1}; i <= 17; i++){
        std::cout << build_line(i) << std::endl;
    }
}

void board::add_black_centre(){
    data_store.black_taken[data_store.black_taken_number] = black_piece;
    data_store.black_taken_number++;
}

void board::add_white_centre(){
    data_store.white_taken[data_store.white_taken_number] = white_piece;
    data_store.white_taken_number++;
}

void board::remove_black_centre(){
    data_store.black_taken_number--;
    data_store.black_taken[data_store.black_taken_number] = space;
}

void board::remove_white_centre(){
    data_store.white_taken_number--;
    data_store.white_taken[data_store.white_taken_number] = space;
}

//Creates a string of spaces of specified length, usign in build line
std::string board::add_spaces(int spaces){
    std::stringstream buffer;
    std::string gap;
    for(int i{0}; i < spaces; i++){
        buffer << space;
    }
    std::getline(buffer, gap);
    return gap;
}

//Creates the UI for the board for print out.
//Can work out result for each line based only on row number.
std::string board::build_line(int row_num){
    std::stringstream row;
    std::string base, row_out;
    row << line;

    //Top/bottom
    if( row_num == 1){
        row << "-----13-----------14-----------15-----------16-----------17-----------18--------W25-------19-----------20-----------21-----------22-----------23-----------24------|B25--";
    }
    if( row_num == 17){
        row << "-----12-----------11-----------10------------9------------8------------7---------B0--------6------------5------------4------------3------------2------------1------|-W0--";
    } 
    //Top half
    if(row_num > 1 && row_num < 8){
        for(int i{0}; i < 6; i++ ){
            row << add_spaces(row_num-2) << backslash << add_spaces(7-row_num) << data_store.triangles[i+12][row_num-2] << add_spaces(7-row_num) << forwardslash << add_spaces(row_num-2);
        }
        row << line << data_store.black_taken[row_num-2] << add_spaces(3) << data_store.white_taken[row_num-2] << line;

        for(int i{6}; i < 12; i++){
            row << add_spaces(row_num-2) << backslash << add_spaces(7-row_num) << data_store.triangles[i+12][row_num-2] << add_spaces(7-row_num) << forwardslash << add_spaces(row_num-2);
        }

    }
    //Middle
    if(row_num >= 8 && row_num <= 10){
        row << add_spaces(78) << line << data_store.black_taken[row_num-2] << add_spaces(3) << data_store.white_taken[row_num-2] << line << add_spaces(78); 
    }
    //Bottom half
    if(row_num > 10 && row_num < 17){
        for(int i{0}; i < 6; i++ ){
            row << add_spaces(16-row_num) << forwardslash << add_spaces(row_num-11) << data_store.triangles[11-i][16-row_num] << add_spaces(row_num-11) << backslash << add_spaces(16-row_num);
        }
        row << line << data_store.black_taken[row_num-2] << add_spaces(3) << data_store.white_taken[row_num-2] << line;

        for(int i{6}; i < 12; i++){
            row << add_spaces(16-row_num) << forwardslash << add_spaces(row_num-11) << data_store.triangles[11-i][16-row_num] << add_spaces(row_num-11) << backslash << add_spaces(16-row_num);
        }
    }
    row << line << '\n';
    std::getline(row, row_out); //Needs to be used to capture spacing properly.
    return row_out;
}