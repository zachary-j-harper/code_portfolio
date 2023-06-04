#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

#include "board.h"
#include "counters.h"
#include "dice.h"

#include "test.h"

struct move{ //A structure to store moves, only really used here.
    backgammon_board::triangle triangle_to;
    int counter;
};
//Static variables allow for use in all functions, meaning less information to pass into them.
static backgammon_board::board board;
static dice::die d6{6};
static std::vector<counters::black_counter> black_pieces;
static std::vector<counters::white_counter> white_pieces;
static std::vector<counters::white_counter> *white_pieces_ptr = &white_pieces; //Necessary thanks to forward declaration

//Functions that were difficult to fit into any particular class. Most are simply components of the final turn functions set apart for ease of readability and debugging.
//Most have two colour variants due to using two seperate classes for counters, with minor enough differences between then to render using the same functions impossible.


//Puts counters in the correct places.
void setup( std::vector<counters::black_counter> &black_pieces, std::vector<counters::white_counter> &white_pieces, backgammon_board::board &board){
    black_pieces[0].move_to(1, 1, board);
    black_pieces[1].move_to(1, 2, board);
    black_pieces[2].move_to(12, 1, board);
    black_pieces[3].move_to(12, 2, board);
    black_pieces[4].move_to(12, 3, board);
    black_pieces[5].move_to(12, 4, board);
    black_pieces[6].move_to(12, 5, board);
    black_pieces[7].move_to(17, 1, board);
    black_pieces[8].move_to(17, 2, board);
    black_pieces[9].move_to(17, 3, board);
    black_pieces[10].move_to(19, 1, board);
    black_pieces[11].move_to(19, 2, board);
    black_pieces[12].move_to(19, 3, board);
    black_pieces[13].move_to(19, 4, board);
    black_pieces[14].move_to(19, 5, board);
    
    white_pieces[0].move_to(6, 1, board);
    white_pieces[1].move_to(6, 2, board);
    white_pieces[2].move_to(6, 3, board);
    white_pieces[3].move_to(6, 4, board);
    white_pieces[4].move_to(6, 5, board);
    white_pieces[5].move_to(8, 1, board);
    white_pieces[6].move_to(8, 2, board);
    white_pieces[7].move_to(8, 3, board);
    white_pieces[8].move_to(13, 1, board);
    white_pieces[9].move_to(13, 2, board);
    white_pieces[10].move_to(13, 3, board);
    white_pieces[11].move_to(13, 4, board);
    white_pieces[12].move_to(13, 5, board);
    white_pieces[13].move_to(24, 1, board);
    white_pieces[14].move_to(24, 2, board);
}

//Test setup function to fiddle with for debugging
void setup_test( std::vector<counters::black_counter> &black_pieces, std::vector<counters::white_counter> &white_pieces, backgammon_board::board &board){
    black_pieces[0].move_to(24, 1, board);
    black_pieces[1].move_to(24, 2, board);
    black_pieces[2].move_to(25, 3, board);
    black_pieces[3].move_to(25, 4, board);
    black_pieces[4].move_to(25, 5, board);
    black_pieces[5].move_to(25, 1, board);
    black_pieces[6].move_to(25, 1, board);
    black_pieces[7].move_to(25, 2, board);
    black_pieces[8].move_to(25, 3, board);
    black_pieces[9].move_to(25, 4, board);
    black_pieces[10].move_to(25, 1, board);
    black_pieces[11].move_to(25, 2, board);
    black_pieces[12].move_to(25, 3, board);
    black_pieces[13].move_to(25, 4, board);
    black_pieces[14].move_to(25, 5, board);
    
    white_pieces[0].move_to(1, 1, board);
    white_pieces[1].move_to(1, 2, board);
    white_pieces[2].move_to(25, 1, board);
    white_pieces[3].move_to(25, 2, board);
    white_pieces[4].move_to(25, 1, board);
    white_pieces[5].move_to(25, 1, board);
    white_pieces[6].move_to(25, 2, board);
    white_pieces[7].move_to(25, 2, board);
    white_pieces[8].move_to(25, 1, board);
    white_pieces[9].move_to(25, 2, board);
    white_pieces[10].move_to(25, 3, board);
    white_pieces[11].move_to(25, 4, board);
    white_pieces[12].move_to(25, 5, board);
    white_pieces[13].move_to(25, 1, board);
    white_pieces[14].move_to(25, 1, board);
}

//Adds UI to rolling the dice.
std::vector<int> roll_the_dice(){
    std::string response;
    std::vector<int> rolls{0, 0};
    std::cout << "Roll the dice! [Type 'roll']" << std::endl;
    while(true){
        std::cin >> response;
        if(response == "roll"){
            rolls[0] = d6.roll();
            rolls[1] = d6.roll();
            std::cout << "You rolled a " << rolls[0] << " and a " << rolls[1] << ".\nThat makes " << rolls[0] + rolls[1] << " in total." << std::endl;
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
            break;
        }
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
        std::cout << "That wasn't the word roll, was it?" << std::endl;
    }
    return rolls;
}

//Collects all triangles that have the relevant colour pieces on
std::vector<int> get_black_triangles(std::vector<counters::black_counter> black_pieces){
    std::vector<int> occupied_triangles;
    for(int i{0}; i < black_pieces.size(); i++){
        if( std::find(occupied_triangles.begin(), occupied_triangles.end(), black_pieces[i].triangle) == occupied_triangles.end()){
            occupied_triangles.push_back(black_pieces[i].triangle);
        }
    }
    return occupied_triangles;
}

std::vector<int> get_white_triangles(std::vector<counters::white_counter> white_pieces){
    std::vector<int> occupied_triangles;
    for(int i{0}; i < white_pieces.size(); i++){
        if( std::find(occupied_triangles.begin(), occupied_triangles.end(), white_pieces[i].triangle) == occupied_triangles.end()){
            occupied_triangles.push_back(white_pieces[i].triangle);
        }
    }
    return occupied_triangles;
}

//Finds the top counter of relevant colour on a specific triangle
int get_top_black_counter(int triangle, std::vector<counters::black_counter> black_pieces){
    int highest_height{0}, best_counter{0};
    for(int i{0}; i < black_pieces.size(); i++){
        if(black_pieces[i].triangle == triangle && black_pieces[i].height > highest_height){
            highest_height = black_pieces[i].height;
            best_counter = i;
        }
    }
    return best_counter;
}

int get_top_white_counter(int triangle, std::vector<counters::white_counter> white_pieces){
    int highest_height{0}, best_counter{0};
    for(int i{0}; i < white_pieces.size(); i++){
        if(white_pieces[i].triangle == triangle && white_pieces[i].height > highest_height){
            highest_height = white_pieces[i].height;
            best_counter = i;
        }
    }
    return best_counter;
}

//Some niche situational checkers. 
//Looks one move into the future to make sure that making a move won't prevent the user from being able to make another move
// as this is illegal in backgammon.
//Returns true moves can still be made, false if they cannot.
bool black_prescience(int counter, backgammon_board::triangle move_to, int roll){
    std::vector<counters::black_counter> virtual_black_pieces = black_pieces;
    virtual_black_pieces[counter].height = move_to.height;
    virtual_black_pieces[counter].triangle = move_to.triangle;


    std::vector<backgammon_board::triangle> possible_moves;
    int top_counter, roll_uses{0};
    std::vector<int> black_triangles{get_black_triangles(virtual_black_pieces)}, valid_triangles;
    for(int i{0}; i < black_triangles.size(); i++){
        top_counter = get_top_black_counter(black_triangles[i], virtual_black_pieces);
        possible_moves = black_pieces[top_counter].check_moves(black_pieces, white_pieces_ptr, roll, 99); //Can never make move triangle + 99, need to make triangle + roll 
        if(possible_moves.size() > 0){
            return true; //If any move can be made after making move 'move', return true
        }
    }
    return false; //else if no moves can be made after making move 'move', return false.

}

bool white_prescience(int counter, backgammon_board::triangle move_to, int roll){
    std::vector<counters::white_counter> virtual_white_pieces = white_pieces;
    virtual_white_pieces[counter].height = move_to.height;
    virtual_white_pieces[counter].triangle = move_to.triangle;


    std::vector<backgammon_board::triangle> possible_moves;
    int top_counter, roll_uses{0};
    std::vector<int> white_triangles{get_white_triangles(virtual_white_pieces)}, valid_triangles;
    for(int i{0}; i < white_triangles.size(); i++){
        top_counter = get_top_white_counter(white_triangles[i], virtual_white_pieces);
        possible_moves = white_pieces[top_counter].check_moves(black_pieces, white_pieces, roll, 99); //Can never make move triangle + 99, need to make triangle + roll 
        if(possible_moves.size() > 0){
            return true; //If any move can be made after making move 'move', return true
        }
    }
    return false; //else if no moves can be made after making move 'move', return false.

}

//Collects all possible moves, and then checks if they're valid or make, only returning those that are valid.
std::vector<move> get_all_valid_black_moves(int roll_1, int roll_2){
    std::vector<backgammon_board::triangle> possible_moves;
    std::vector<move> all_possible_moves, all_valid_moves;
    int selected_triangle, top_counter, selected_move, decided_move, roll_1_uses{0}, roll_2_uses{0}, used_roll;

    std::vector<int> black_triangles{get_black_triangles(black_pieces)}, valid_triangles;
    for(int i{0}; i < black_triangles.size(); i++){
        top_counter = (get_top_black_counter(black_triangles[i], black_pieces));
        possible_moves = black_pieces[top_counter].check_moves(black_pieces, white_pieces_ptr, roll_1, roll_2);
        for(int j{0}; j < possible_moves.size(); j++){
            if( possible_moves[j].triangle == black_pieces[top_counter].triangle + roll_1){
                roll_1_uses++;
            }   else{   if(possible_moves[j].triangle == black_pieces[top_counter].triangle + roll_2){
                            roll_2_uses++;
                        }   else{   if(possible_moves[j].triangle == black_pieces[top_counter].triangle + roll_1 + roll_2){
                                        roll_1_uses++;
                                        roll_2_uses++;
                                    }
                            }
                }
            all_possible_moves.push_back(move{possible_moves[j], top_counter});
        }
    }
    if(black_pieces.size() > 1 && roll_2 < 99 && roll_1 < 99){
        //Checks to ensure that both dice can still be used.
        if(roll_1_uses < 1 && roll_2_uses < 1){
            return all_valid_moves;
        }
        bool move_added = false;
        if(roll_1_uses < 1){
            
            for(int i{0}; i < all_possible_moves.size(); i++){
                if(black_prescience(all_possible_moves[i].counter, all_possible_moves[i].triangle_to, roll_1)){
                    all_valid_moves.push_back(all_possible_moves[i]);
                    move_added = true;
                }
            }
            if(move_added == true){
                return all_valid_moves;
            } else{return all_possible_moves;}
        }
        if(roll_2_uses < 1){
            for(int i{0}; i < all_possible_moves.size(); i++){
                if(black_prescience(all_possible_moves[i].counter, all_possible_moves[i].triangle_to, roll_2)){
                    all_valid_moves.push_back(all_possible_moves[i]);
                    move_added = true;
                }
            }
            if(move_added == true){
                return all_valid_moves;
            } else{return all_possible_moves;}
        }
        for(int i{0}; i < all_possible_moves.size(); i++){
            used_roll = all_possible_moves[i].triangle_to.triangle - black_pieces[all_possible_moves[i].counter].triangle;
            if(used_roll == roll_1){
                if(black_prescience(all_possible_moves[i].counter, all_possible_moves[i].triangle_to, roll_2)){
                        all_valid_moves.push_back(all_possible_moves[i]);
                }
            }
               else{   if(used_roll == roll_2){
                            if(black_prescience(all_possible_moves[i].counter, all_possible_moves[i].triangle_to, roll_2)){
                                all_valid_moves.push_back(all_possible_moves[i]);
                            }
                        } else{all_valid_moves.push_back(all_possible_moves[i]);}
                }
            
        }
        return all_valid_moves;
    }
    //If there's one piece left, or only one dice to use, two moves don't need to be made.
    return all_possible_moves;
}

std::vector<move> get_all_valid_white_moves(int roll_1, int roll_2){
    std::vector<backgammon_board::triangle> possible_moves;
    std::vector<move> all_possible_moves, all_valid_moves;
    int selected_triangle, top_counter, selected_move, decided_move, roll_1_uses{0}, roll_2_uses{0}, used_roll;

    std::vector<int> white_triangles{get_white_triangles(white_pieces)}, valid_triangles;
    for(int i{0}; i < white_triangles.size(); i++){
        top_counter = (get_top_white_counter(white_triangles[i], white_pieces));
        possible_moves = white_pieces[top_counter].check_moves(black_pieces, white_pieces, roll_1, roll_2);
        for(int j{0}; j < possible_moves.size(); j++){
            if( possible_moves[j].triangle == white_pieces[top_counter].triangle - roll_1){
                roll_1_uses++;
            }   else{   if(possible_moves[j].triangle == white_pieces[top_counter].triangle - roll_2){
                            roll_2_uses++;
                        }   else{   if(possible_moves[j].triangle == white_pieces[top_counter].triangle + roll_1 - roll_2){
                                        roll_1_uses++;
                                        roll_2_uses++;
                                    }
                            }
                }
            all_possible_moves.push_back(move{possible_moves[j], top_counter});
        }
    }
    if(white_pieces.size() > 1 && roll_2 < 99 && roll_1 < 99){
        if(roll_1_uses < 1 && roll_2_uses < 1){
            return all_valid_moves;
        }
        bool move_added = false; //Makes sure that a move isn't thrown out if no moves would have been possible anyway. Not necessary for rest of code
        if(roll_1_uses < 1){
            for(int i{0}; i < all_possible_moves.size(); i++){
                if(white_prescience(all_possible_moves[i].counter, all_possible_moves[i].triangle_to, roll_1)){
                    all_valid_moves.push_back(all_possible_moves[i]);
                    move_added = true;
                }
            }
            if(move_added == true){
                return all_valid_moves;
            } else{return all_possible_moves;}
        }
        if(roll_2_uses < 1){
            for(int i{0}; i < all_possible_moves.size(); i++){
                if(white_prescience(all_possible_moves[i].counter, all_possible_moves[i].triangle_to, roll_2)){
                    all_valid_moves.push_back(all_possible_moves[i]);
                    move_added = true;
                }
            }
            if(move_added == true){
                return all_valid_moves;
            } else{return all_possible_moves;}

        }

        for(int i{0}; i < all_possible_moves.size(); i++){
            used_roll = all_possible_moves[i].triangle_to.triangle - black_pieces[all_possible_moves[i].counter].triangle;
            if(used_roll == roll_1){
                if(white_prescience(all_possible_moves[i].counter, all_possible_moves[i].triangle_to, roll_2)){
                        all_valid_moves.push_back(all_possible_moves[i]);
                }
            }
               else{   if(used_roll == roll_2){
                            if(white_prescience(all_possible_moves[i].counter, all_possible_moves[i].triangle_to, roll_2)){
                                all_valid_moves.push_back(all_possible_moves[i]);
                            }
                        } else{all_valid_moves.push_back(all_possible_moves[i]);}
                }
            
        }
        return all_valid_moves;
    }
    return all_possible_moves;
}

//Hopefully self-explanatory
std::string check_win(){
    int black_pieces_off{0}, white_pieces_off{0};
    for(int i{0}; i < black_pieces.size(); i++){
        if(black_pieces[i].triangle == 25){
            black_pieces_off++;
        }
    }
    for(int i{0}; i < white_pieces.size(); i++){
        if(white_pieces[i].triangle == 0){
            white_pieces_off++;
        }
    }
    if(black_pieces_off == 15){
        return "black";
    }
    if(white_pieces_off == 15){
        return "white";
    }
    return "none";
}

//UI and sanitisation wrapper for above functions.
void black_turn(int roll_1, int roll_2){
    std::vector<int> valid_triangles, printed_triangles;
    int selected_triangle, selected_counter, selected_triangle_to, selected_move, distance_moved;
    bool move_undecided = true, roll_1_used = false, roll_2_used = false;
    std::vector<move> allowed_moves = get_all_valid_black_moves(roll_1, roll_2), potential_moves;

    if(allowed_moves.size() == 0){
        std::cout << "Ah, tough luck, there's no more moves you can make!" << std::endl;
        return;
    }
    //Flags for a second run through
    if(roll_1 == 99){
        roll_1_used = true;
    }
    if(roll_2 == 99){
        roll_2_used = true;
    }
    //Gets triangle printout
    for(int i{0}; i < allowed_moves.size(); i++){
        if(std::find(valid_triangles.begin(), valid_triangles.end(), black_pieces[allowed_moves[i].counter].triangle ) == valid_triangles.end()){
            valid_triangles.push_back(black_pieces[allowed_moves[i].counter].triangle);
        }
    }
    while(move_undecided){
        potential_moves.clear();
        std::cout << "Please select the rank whose top piece you'd like to move: ";
        for(int i{0}; i < valid_triangles.size(); i++){
            std::cout << valid_triangles[i] << ", ";
        }
        std::cout << std::endl;
        //Validation loop
        while(true){
            std::cin >> selected_triangle;
            if(std::cin.fail() == false && std::cin.peek() == '\n'){
                if(std::find(valid_triangles.begin(), valid_triangles.end(), selected_triangle) != valid_triangles.end()){
                    std::cin.clear();
                    std::cin.ignore(INT_MAX, '\n');
                    break;
                }              
            }
            std::cout << "Sorry, that's not a valid rank." << std::endl;
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
        }
        selected_counter = get_top_black_counter(selected_triangle, black_pieces);
        for(int i{0}; i < allowed_moves.size(); i++){
            if(allowed_moves[i].counter == selected_counter){
                potential_moves.push_back(allowed_moves[i]);
            }
        }
        //Gets rank to move to
        std::cout << "Type 99 to go back, or select a rank you'd like to move this piece to: ";
        for(int i{0}; i < potential_moves.size(); i++){
            if(std::find(printed_triangles.begin(), printed_triangles.end(), potential_moves[i].triangle_to.triangle) == printed_triangles.end()){
                std::cout << potential_moves[i].triangle_to.triangle;
                printed_triangles.push_back(potential_moves[i].triangle_to.triangle);
                if(i < potential_moves.size() - 1){
                    std::cout << ", ";
                }
            }
        }
        std::cout << std::endl;
        //Another validation loop
        while(move_undecided){
            std::cin >> selected_triangle_to;
            if(std::cin.fail() == false && std::cin.peek() == '\n'){
                for(int i{0}; i < potential_moves.size(); i++){
                    if(potential_moves[i].triangle_to.triangle == selected_triangle_to){
                        selected_move = i;
                        move_undecided = false;
                        break;
                    }
                }
                if(selected_triangle_to == 99)
                    std::cin.clear();
                    std::cin.ignore(INT_MAX, '\n');
                    break;                
            }
            std::cout << "Sorry, that's not a valid rank." << std::endl;
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
        }
    }
    //A few case checkers
    distance_moved = potential_moves[selected_move].triangle_to.triangle - black_pieces[potential_moves[selected_move].counter].triangle;
    if(distance_moved == roll_1){
        roll_1_used = true; 
    }   else{   if(distance_moved == roll_2){
                    roll_2_used = true;
                }   else{   if(distance_moved == roll_1 + roll_2){
                                roll_1_used = true;
                                roll_2_used = true;
                            }
                    }
        }
    for(int i{0}; i < white_pieces.size(); i++){
        if(white_pieces[i].triangle == potential_moves[selected_move].triangle_to.triangle){
            white_pieces[i].move_to(25, 1, board);
        }
    }
    //Makes the move. could make this shorter but would just require more variable definitions, which feels messier overall.
    black_pieces[potential_moves[selected_move].counter].move_to(potential_moves[selected_move].triangle_to.triangle, potential_moves[selected_move].triangle_to.height, board);

    board.print();
    //runs another move if required.
    if(check_win() == "none"){
        if(roll_1_used == false){
            black_turn(roll_1, 99);
        }   else{   if(roll_2_used == false){
                        black_turn(99, roll_2);
                    }
            }
    }
}

void white_turn(int roll_1, int roll_2){
    //This functions is nigh-on identical to the one above, but with the counter types and a few signs flipped.
    std::vector<int> valid_triangles, printed_triangles;
    int selected_triangle, selected_counter, selected_triangle_to, selected_move, distance_moved;
    bool move_undecided = true, roll_1_used = false, roll_2_used = false;
    std::vector<move> allowed_moves = get_all_valid_white_moves(roll_1, roll_2), potential_moves;
    if(allowed_moves.size() == 0){
        std::cout << "Ah, tough luck, there's no more moves you can make!" << std::endl;
        return;
    }
    if(roll_1 == 99){
        roll_1_used = true;
    }
    if(roll_2 == 99){
        roll_2_used = true;
    }
    for(int i{0}; i < allowed_moves.size(); i++){
        if(std::find(valid_triangles.begin(), valid_triangles.end(), white_pieces[allowed_moves[i].counter].triangle ) == valid_triangles.end()){
            valid_triangles.push_back(white_pieces[allowed_moves[i].counter].triangle);
        }
    }
    while(move_undecided){
        potential_moves.clear();
        printed_triangles.clear();
        std::cout << "Please select the rank whose top piece you'd like to move: ";
        for(int i{0}; i < valid_triangles.size(); i++){
            std::cout << valid_triangles[i] << ", ";
        }
        std::cout << std::endl;
        while(true){
            std::cin >> selected_triangle;
            if(std::cin.fail() == false && std::cin.peek() == '\n'){
                if(std::find(valid_triangles.begin(), valid_triangles.end(), selected_triangle) != valid_triangles.end()){
                    std::cin.clear();
                    std::cin.ignore(INT_MAX, '\n');
                    break;
                }
                
            }
            std::cout << "Sorry, that's not a valid rank." << std::endl;
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
        }
        selected_counter = get_top_white_counter(selected_triangle, white_pieces);
        for(int i{0}; i < allowed_moves.size(); i++){
            if(allowed_moves[i].counter == selected_counter){
                potential_moves.push_back(allowed_moves[i]);
            }
        }
        std::cout << "Type 99 to go back, or select a rank you'd like to move this piece to: ";
        for(int i{0}; i < potential_moves.size(); i++){
            if(std::find(printed_triangles.begin(), printed_triangles.end(), potential_moves[i].triangle_to.triangle) == printed_triangles.end()){
                std::cout << potential_moves[i].triangle_to.triangle;
                printed_triangles.push_back(potential_moves[i].triangle_to.triangle);
                if(i < potential_moves.size() - 1){
                    std::cout << ", ";
                }
            }
        }
        std::cout << std::endl;
        while(move_undecided){
            std::cin >> selected_triangle_to;
            if(std::cin.fail() == false && std::cin.peek() == '\n'){
                for(int i{0}; i < potential_moves.size(); i++){
                    if(potential_moves[i].triangle_to.triangle == selected_triangle_to){
                        selected_move = i;
                        move_undecided = false;
                        break;
                    }
                }
                if(selected_triangle_to == 99)
                    std::cin.clear();
                    std::cin.ignore(INT_MAX, '\n');
                    break;
                
            }
            std::cout << "Sorry, that's not a valid rank." << std::endl;
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
        }

    }
    distance_moved = abs(potential_moves[selected_move].triangle_to.triangle - white_pieces[potential_moves[selected_move].counter].triangle);
    if(distance_moved == roll_1){
        roll_1_used = true; 
    }   else{   if(distance_moved == roll_2){
                    roll_2_used = true;
                }   else{   if(distance_moved == roll_1 + roll_2){
                                roll_1_used = true;
                                roll_2_used = true;
                            } else{std::cout << "oops" << std::endl;}
                    }
        }
    for(int i{0}; i < black_pieces.size(); i++){
        if(black_pieces[i].triangle == potential_moves[selected_move].triangle_to.triangle){
            black_pieces[i].move_to(0, 1, board);
        }
    }
    white_pieces[potential_moves[selected_move].counter].move_to(potential_moves[selected_move].triangle_to.triangle, potential_moves[selected_move].triangle_to.height, board);

    board.print();
    if(check_win() == "none"){
        if(roll_1_used == false){
            white_turn(roll_1, 99);
        }   else{   if(roll_2_used == false){
                        white_turn(99, roll_2);
                    }
            }
    }
}

//Turn wrapper and UI
void round(){
    std::cout << "It's black's turn!" << std::endl;
    std::vector<int> black_roll = roll_the_dice(), white_roll;
    black_turn(black_roll[0], black_roll[1]);
    if(check_win() != "black"){
        if(black_roll[0] == black_roll[1]){
            std::cout << "You rolled doubles, you get another turn!" << std::endl;
            black_turn(black_roll[0], black_roll[1]);
        }
        if(check_win() != "black"){
            std::cout << "It's white's turn!" << std::endl;
            white_roll = roll_the_dice();
            white_turn(white_roll[0], white_roll[1]);
            if(check_win() != "white"){
                if (white_roll[0] == white_roll[1]){
                    std::cout << "You rolled doubles, you get another turn!" << std::endl;
                    white_turn(white_roll[0], white_roll[1]);
                }
            }
        }
    }
    

    /*
    check_win()
    repeat for white
    check_win()
    */
}

int main(){

    for(int i{0}; i < 15; i++) {
        black_pieces.push_back(counters::black_counter{0, 0});
        white_pieces.push_back(counters::white_counter{0, 0});
    }
    setup(black_pieces, white_pieces, board);

    std::cout <<    "Welcome to Backgammon!" << 
                    "\nThis is a game as old as chess, if not older, hailing from ancient Mesopotamia." << 
                    "\nIt is still widely played around the world too, much like chess." <<
                    "\nIt is a simple enough concept, all you have to do is move your pieces around the board according to two dice,"
                    "\nuntil they may escape off the opposing side." <<
                    "\nIf you can do this quicker before your opponent, you win!" <<
                    "\nHowever, there are a few stipulations." << 
                    "\nBoth sides move in opposite directions, the black, or 'x', pieces ascending from 0 to 25, where they bear off the board,"
                    "\nand the white, or 'o', pieces, descending from  25 to 0, where they bear off." <<
                    "\nIn order to successfully bear a piece off the board, the exact number to let is escape must be rolled on the dice."
                    "\nNo piece may land on a triangle, or rank, occupied by 5 of its own kind, or 2 or more of their opponent's pieces." <<
                    "\nHowever, if a piece is left out on its own, their opponent may take advantage of this by landing on it," <<
                    "\nsending it to the center, which counts as the begginning rank for both sides." <<
                    "\nIf possible, you must use both dice to make your moves each turn. " <<
                    "\nAnd finally, roll of two of the same number is doubles, and gives the player who rolled it an extra turn using those same numbers."<< std::endl;

    board.print();

    while(check_win() == "none"){
        round();
    }
    std::cout << "=====================================" << std::endl;
    std::cout << "Congratulations to " << check_win() << " for winning!" << std::endl;
    std::cout << "=====================================" << std::endl;
    
    //Stops program closing immediately, so you can revel in your victory.
    int a;
    std::cin >> a;


    return 0;
}