#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <new>
#include <cmath>
#include <vector>
#include <algorithm>

struct course{          //structure for a course to hold data more effectively
    std::string name;
    int code;
    double mark;
};

bool compare_name(course c1, course c2) {       //these two bool functions are for the sort algorithm to sort the struct correctly
    return c1.name < c2.name;
}

bool compare_code(course c1, course c2) {
    return c1.code < c2.code;
}

double calc_mean(int n, std::vector<course> course_list){
    int i;
    double sum;
    for(i = 0; i < n; i++) {
        sum += course_list[i].mark;
    }
    return sum/n;

}

double calc_standard_deviation(int n, double mean, std::vector<course> course_list){
    int i;
    double sum, step1, step2;
    for(i = 0; i < n; i++) {
        sum += pow(course_list[i].mark - mean, 2);
    }
    step1 = n-1;
    step2 = 1/step1;
    return sqrt(step2*sum);

}



int main(){
    double mean, standard_deviation, standard_error, mark_buffer, root;
    std::string line, filename, name_buffer, yes_no, sort_type, title_buffer;
    int code_buffer, length, used_length, year, iterator;
    std::vector<std::string> title;
    course course_buffer;
    std::vector<course> courses, course_list;       //Can make a vector of custom structs
    std::stringstream string_stream, naming_stream;
    bool pass = false;

    while(pass == false ) { //Filename collection
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

    while(!file.eof()) {        //Data collection
        std::getline(file, line);
        string_stream << line;          //Much tidier using the struct, effectively a 2D array.
        string_stream >> mark_buffer;   //However, only of one object, allowing the sort function to work properly later!
        string_stream >> code_buffer;
        while (string_stream.peek() == ' ') {       //Removes excess spaces before 'getline'
            string_stream.ignore(1);
        }
        std::getline(string_stream, name_buffer);
        string_stream.clear();
        course_buffer.name = name_buffer;
        course_buffer.code = code_buffer;
        course_buffer.mark = mark_buffer;
        courses.push_back(course_buffer);

    }
    length = courses.size();

    std::cout << "Would you like a specific year of courses? (y/n)" << std::endl; //Select specfic year
    std::cin >> yes_no;
    if(yes_no == "y"){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Which year? (1/2/3/4)" << std::endl;
        std::cin >> year;
        if(year == 1){
            for(iterator = 0; iterator < length; iterator++){
                if(courses[iterator].code < 20000) {            //Add selected courses to used list from master list
                    course_list.push_back(courses[iterator]);

                }
            }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Ignores get a bit gross, but it's unfortunately necessary 
        }   else {  if(year == 2) {                                         //to have this many as any in a row halt the code
                        for(iterator = 0; iterator < length; iterator++) {
                            if(courses[iterator].code < 30000 && courses[iterator].code >= 20000) {
                                course_list.push_back(courses[iterator]);
                            }
                        }
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }   else {  if(year == 3){
                                    for(iterator = 0; iterator < length; iterator++) {
                                        if(courses[iterator].code < 40000 && courses[iterator].code >= 30000) {
                                            course_list.push_back(courses[iterator]);
                                        }
                                    }
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                }   else {  if(year == 4){
                                                for(iterator = 0; iterator < length; iterator++) {
                                                    if(courses[iterator].code >= 40000) {
                                                        course_list.push_back(courses[iterator]);
                                                        
                                                     }
                                                }
                                            std::cin.clear();
                                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                            }   else{
                                                    course_list = courses;
                                                    std::cin.clear();
                                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                                }

                                    }

                        }       
            
            }
    } else{
        course_list = courses;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cout << "Would you like the output to be sorted? (y/n)" << std::endl; //Determine output sort and type
    if(std::cin.peek() == 'y') {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Would you like the courses to be sorted by name or code? (name/code)" << std::endl;
        std::cin >> sort_type;
        if(sort_type == "name") {
            sort(course_list.begin(), course_list.end(), compare_name);     //Order alphabetically via name
        }   else {  if(sort_type == "code") {
                        sort(course_list.begin(), course_list.end(), compare_code); //Order numerically by code
        }

        }
    }

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    used_length = course_list.size();
    
    mean = calc_mean(used_length, course_list);  //Calculate data and output

    std::cout << "There are " << length << " courses in the file, and the mean course mark is " << mean << std::endl;

    standard_deviation = calc_standard_deviation(used_length, mean, course_list);
    root = sqrt(used_length);
    standard_error = standard_deviation/root;
    std::cout << "The mark standard deviation is " << standard_deviation << " with standard error " << standard_error << std::endl;

    for (iterator = 0; iterator < used_length; iterator++) {     //Assembles courses into desired form using a string stream
        naming_stream << "PHYS " << course_list[iterator].code << " " << course_list[iterator].name;
        std::getline(naming_stream, title_buffer);
        naming_stream.clear();
        title.push_back(title_buffer);
    }

    std::vector<std::string>::iterator title_begin{title.begin()};      //Uses iterators to print course list in desired format
    std::vector<std::string>::iterator title_end{title.end()};
    std::vector<std::string>::iterator title_iterator;
    for(title_iterator = title_begin; title_iterator < title_end; title_iterator++) {
        std ::cout << *title_iterator <<std :: endl;
    }      

    return 0;
}