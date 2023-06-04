#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include <algorithm>
#include <vector>



class matrix{
    private:
        std::vector<double> values;
        int m;
        int n;

        std::vector<double> parse(std::string input){
           
            return data;   
        };

    public:
        //matrix() = default;

        matrix(std::string input){
            std::stringstream processor;
            double buffer;
            n = 0;
            m = 1;

            processor << input;

            while(processor.peek() != '\n'){
                processor >> buffer;
                values.push_back(buffer);

                if(processor.peek() == ','){
                    m++;
                    if(n == 0){
                        m = values.size();
                    }
                    processor.ignore(1); 
                }
            }

        };

        matrix(matrix &input){

            values.clear();
            m = input.get_m();
            n = input.get_n();

            values = new double[m*n];
            for(int i{0}; i < (m*n); i++){
                values[i] = input.get_value(i);
            }
        }



        ~matrix(){delete values; std::cout << "Call" << std::endl;};

        double get_element(int i, int j) const {

            return values[(i-1)*n + (j-1)];
        };

        double  get_value(int i) const {
            return values[i];
        };

        double get_m() const {
            return m;
        };

        double get_n() const {
            return n;
        };
        
        matrix &operator=(matrix &input){

            if(&input == this){
                return *this;
            }

            delete[] values;
            values = nullptr;
            m = 0;
            n = 0;

            m = input.get_m();
            n = input.get_n();

            values = new double[m*n];
            for(int i{0}; i < (m*n); i++){
                values[i] = input.get_value(i);
            }

            return *this;
        };
        
        

        friend std::ostream &operator<<(std::ostream &output, matrix &input);

        friend std::istream &operator>>(std::istream &input, matrix &output);
};

std::ostream &operator<<(std::ostream &output, matrix &input){
    for(int i = 1; i <= input.m; i++){
        output << "| ";
        for(int j = 1; j <= input.n; j++){
            output << input.get_element(i,j) << ", ";
        }
        output << "|\n";
    }
    return output;
}

std::istream &operator>>(std::istream &input, matrix &output){
    std::vector<double> data;
    double buffer;
    output.m = 1;
    output.n = 0;
    int i;

    while(input.peek() != '\n'){
        input >> buffer;
        data.push_back(buffer);

        if(input.peek() == ','){
            output.m++;
            if(output.n == 0){
                output.n = data.size();
            }
            input.ignore(1); 
        }
    } 
    int length = data.size();

    output.values = new double[length];
    for(i = 0; i < length; i++){
        output.values[i] = data[i];
    }
    return input;
};


int main(){
    matrix matrix1 = {"1 2 3, 4 5 6, 7 8 9\n"};
    //std::cout << matrix1.get_value(3) << ' ' << matrix1.get_m() << ' ' << matrix1.get_n() << std::endl;
    //std::cout << matrix1.get_element(1,3) << ' ' << matrix1.get_element(2,1) << std::endl;
    std::cout << matrix1 << std::endl;
    matrix matrix2 = matrix1;
    std::cout << matrix2 << std::endl;
    std::cin >> matrix1;
    //matrix1 = {"9 8 7, 6 5 4, 3 2 1\n"};
    std::cout << matrix1 << '\n' << matrix2 << std::endl;


}