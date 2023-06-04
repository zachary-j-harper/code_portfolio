#ifndef COUNTERS_H
#define COUNTERS_H

#include <string>

#include "board.h"

namespace counters{
    
//Abstract base class
//Unfortuately, serious issues with forward loading prevent this class from being more useful, see report for the detailed discussion required.
class counter{
    public:
        int triangle, height;
        
        counter(int triangle_in, int height_in):
            triangle{triangle_in}, height{height_in} {}

        virtual ~counter(){}

        //virtual int move_ok(std::vector<black_counter> black_pieces, std::vector<white_counter> *white_pieces, int triangle_move) = 0;
        //virtual std::vector<backgammon_board::triangle> check_moves(std::vector<black_counter> black_pieces, std::vector<white_counter> white_pieces, int die_1, int die_2) = 0;
        //Pure Virtual functions still need parameters definited. Can't use derived classes as parameters. Unfortunate.

        virtual void move_to(int triangle_in, int height_in, backgammon_board::board &board) = 0;

};

//Forward load
class white_counter;

//Classes need to be aware of each others' existiances, requiring forward loading.
class black_counter: public counter {
    public:

        black_counter(int triangle_in, int height_in):
            counter{triangle_in, height_in} {}

        ~black_counter(){}

        //Pointers are necessary due to forward loading.
        int move_ok(std::vector<black_counter> black_pieces, std::vector<white_counter> *white_pieces, int triangle_move);

        std::vector<backgammon_board::triangle> check_moves(std::vector<black_counter> black_pieces, std::vector<white_counter> *white_pieces, int die_1, int die_2);

        void move_to(int triangle_in, int height_in, backgammon_board::board &board);
};
//Practically Identical to black_counter, but doesn't need pointers!
class white_counter: public counter {
    public:
        white_counter(int triangle_in, int height_in):
            counter{triangle_in, height_in} {}

        ~white_counter(){}

        int move_ok(std::vector<black_counter> black_pieces, std::vector<white_counter> white_pieces, int triangle_move);

        std::vector<backgammon_board::triangle> check_moves(std::vector<black_counter> black_pieces, std::vector<white_counter> white_pieces, int die_1, int die_2);

        void move_to(int triangle_in, int height_in, backgammon_board::board &board);
};

}

#endif