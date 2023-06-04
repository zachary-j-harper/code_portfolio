#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <new>
#include <cmath>
#include <vector>
#include <algorithm>

struct course{
    std::string name;
    int name;
    double mark;

};

bool compare_name(course c1, course c2) {
    return c1.name < c2.name;

bool compare_code(course c1, course c2) {
    return c1.code < c2.code;

/*
std::vector<std::string> flip(std::vector<std::string> input) {

    int size = input.size();
    std::stringstream store_stream;
    std::vector<std::string> output(size);
    std::string piece1, piece2;
    int i;

    for( i = 0; i < size; i++) {
        store_stream << input[i];
        store_stream >> piece1;
        store_stream >> piece2;
        output[i] = piece2 + " " + piece1;
    }
    return output;
}
*/

double calc_mean(int n, std::vector<double> mark){
    int i;
    double sum;
    for(i = 0; i < n; i++) {
        sum += mark[i];
    }
    return sum/n;

}

double calc_standard_deviation(int n, double mean, std::vector<double> mark){
    int i;
    double sum, step1, step2;
    for(i = 0; i < n; i++) {
        sum += pow(mark[i] - mean, 2);
    }
    step1 = n-1;
    step2 = 1/step1;
    return sqrt(step2*sum);

}



int main(){
    double mean, standard_deviation, standard_error, mark_buffer;
    double root;
    std::string code_buffer, line, filename, name_buffer, yes_no, title_buffer, code_name_buffer, name_code_buffer;
    int  length, iterator;
    std::vector<double> mark;
    std::vector<std::string> code, name, title, code_name, name_code; 
    std::stringstream string_stream, naming_stream;
    bool pass = false;
    while(pass == false ) {
        std::cout << "Please enter the name of the file you would like to open (Please include the file extension)." << std::endl;
        std::cin >> filename;
        std::cin.clear();
        std::cin.ignore();
        std::fstream file{filename};
        if(file.good()) {
            pass = true;
        }   else {    std::cout << "Sorry, that's not a valid filename. " << std::endl; 
            }
    }
    std::fstream file{filename};

    while(!file.eof()) {
        std::getline(file, line);
        string_stream << line;
        string_stream >> mark_buffer;
        mark.push_back(mark_buffer);
        string_stream >> code_buffer;
        code.push_back(code_buffer);
        //while (string_stream.peek() == " ") {
        string_stream.ignore(3);
        //}
        std::getline(string_stream, name_buffer);
        name.push_back(name_buffer);
        string_stream.clear();
    }
    length = mark.size();

    for(iterator = 0; iterator < length; iterator++) {
        code_name_buffer = code[iterator] + " " + name[iterator];
        name_code_buffer = name[iterator] + " " + code[iterator];
        code_name.push_back(code_name_buffer);
        name_code.push_back(name_code_buffer);
    }


    /*
    for (iterator = 0; iterator < length; iterator++) {
            naming_stream << code[iterator];
            naming_stream << " ";
            naming_stream << name[iterator];
            std::getline(naming_stream, title_buffer);
            naming_stream.clear();
            title.push_back(title_buffer);

        }
         for (iterator = 0; iterator < length; iterator++) {
            naming_stream << "PHYS ";
            naming_stream << code[iterator];
            naming_stream << " ";
            naming_stream << name[iterator];
            std::getline(naming_stream, title_buffer);
            naming_stream.clear();
            title.push_back(title_buffer);
    
    
    std::vector<std::string>::iterator title_begin{title.begin()};
    std::vector<std::string>::iterator title_end{title.end()};
    std::vector<std::string>::iterator title_iterator;
    reverse(title_begin, title_end);
    for(title_iterator = title_begin; title_iterator < title_end; title_iterator++) {
        std::cout << *title_iterator << std::endl;
    }

    */


    mean = calc_mean(length, mark);

    std::cout << "There are " << length << " courses in the file, and the mean course mark is " << mean << std::endl;

    standard_deviation = calc_standard_deviation(length, mean, mark);
    root = sqrt(length);
    standard_error = standard_deviation/root;
    std::cout << "The mark standard deviation is " << standard_deviation << " with standard error " << standard_error << std::endl;

    std::cout << "Would you like a list of all courses? (y/n)" << std::endl;
    std::cin >> yes_no;
    std::cin.clear();
    std::cin.ignore();
    if( yes_no == "y") {
       for(iterator = 0; iterator < length; iterator ++) 
       std::cout << title[iterator] << std::endl;
    }



    return 0;
}