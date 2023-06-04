#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

//This is the most fundamental class of the program, it loads in without any other files.
//The board class is purely UI based, allowing the other classes to manipulate it to alter the apperance of the game.

namespace backgammon_board{

//A basic struct used by most other classes
struct triangle{
    int triangle, height;
};

class board{
    private:
        //A struct specific to this class to better encapsulate the position data
        struct board_data{
            std::vector<std::vector<std::string>> triangles;
            std::vector<std::string> black_taken, white_taken;
            int black_taken_number, white_taken_number;
        };
        //Some easily modifiable symbols to alter appearence quickly.
        const std::string black_piece{'x'}, white_piece{'o'}, backslash{'\\'}, forwardslash{'/'}, space{' '}, line{'|'}, dash{'-'};
        std::vector<std::string> board_instance;
        board_data data_store;

        std::string add_spaces(int spaces);

        std::string build_line(int row_num);
              
    public:

        board(){
            data_store.black_taken_number = 15;
            data_store.white_taken_number = 0;
            std::string row;
            std::vector<std::string> empty_states;
            for(int i{0}; i < 6; i++){
                empty_states.push_back(space);
            }
            for( int i{0}; i<24; i++){
                data_store.triangles.push_back(empty_states);
            }
            for(int i{6}; i<15; i++){
                empty_states.push_back(space);
            }
            data_store.black_taken = empty_states;
            data_store.white_taken = empty_states;
        }

        ~board(){}

        //Board edit commands for use by other funtions.
        void set_black(int triangle, int height);

        void set_white(int triangle, int height);

        void set_empty(int triangle, int height);

        void add_black_centre();

        void add_white_centre();

        void remove_black_centre();

        void remove_white_centre();

        void print();
};
}
#endif