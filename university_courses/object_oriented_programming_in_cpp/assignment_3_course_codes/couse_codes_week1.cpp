#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <new>
#include <cmath>

double calc_mean(int n, double *mark) {
    int i;
    double sum;
    for(i = 0; i < n; i++) {
        sum += mark[i];
    }
    return sum/n;

}

double calc_standard_deviation(int n, double mean, double *mark) {
    int i;
    double sum, step1, step2;
    for(i = 0; i < n; i++) {
        sum += pow(mark[i] - mean, 2);
    }
    step1 = n-1;
    step2 = 1/step1;
    return sqrt(step2*sum);

}



int main() {
    double mean, standard_deviation, standard_error; // Declare variables
    double root;
    std::string line, filename;
    std::stringstream string_stream;
    int length = 0;
    int hundred = 100;
    double* mark = new double[hundred];     //declare arrays using new
    int * code = new int [hundred];         //Using variable length because this form allows it
    std::string * name = new std::string[hundred];
    bool pass = false;

    while(pass == false ) { //Get File
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

    std::fstream file{filename}; //Dislikes being defined in a loop, so redefine here
    while(!file.eof()) {
        std::getline(file, line);
        string_stream << line;              //Using multiple arrays to test arrays
        string_stream >> mark[length];      //Also adds in some future-proofing
        string_stream >> code[length];
        std::getline(string_stream, name[length]);
        string_stream.clear();
        length++; //Finds amount of courses in file
    }

    mean = calc_mean(length, mark);     //Calculate outputs and output them

    std::cout << "There are " << length << " courses in the file, and the mean course mark is " << mean << std::endl;

    standard_deviation = calc_standard_deviation(length, mean, mark);
    root = sqrt(length);
    standard_error = standard_deviation/root;

    std::cout << "The mark standard deviation is " << standard_deviation << " with standard error " << standard_error << std::endl;
 
    delete[] mark, code, name; //Clear memory

    return 0;
}