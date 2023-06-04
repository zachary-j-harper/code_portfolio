#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include <algorithm>
#include <vector>



class matrix{
    private:
        double *values{nullptr};
        int m;
        int n;

        std::vector<double> parse(std::string input){   //Turns an input string into a useable data list
            std::stringstream processor;
            std::vector<double> data;
            double buffer;
            int columns = 0;
            int rows = 1;

            processor << input;

            while(processor.peek() != '\n'){
                processor >> buffer;
                data.push_back(buffer);

                if(processor.peek() == ','){
                    rows++;
                    if(columns == 0){
                        columns = data.size();
                    }
                    processor.ignore(1); 
                }
            }

            data.push_back(rows);
            data.push_back(columns);
            return data;   
        };

    public:

        //Constructors//

        //Default Constructor
        matrix(){}

        //Parameterised Constructor
        matrix(std::string input){
            const std::vector<double> data = parse(input);
            int length = data.size();
            m = data[length-2];
            n = data[length-1];

            values = new double[length-2];
            for(int i{0}; i < m*n; i++){
                values[i] = data[i];
            }

        };
        //Parameterised Constructor - Empty matrix of given dimensions
        matrix(int rows, int columns){
            m = rows;
            n = columns;
            values = new double[m*n];
        }

        //Copy Constructor
        matrix(matrix &input){
            std::cout << "Copy Constructor" << std::endl;
            values = nullptr;
            m = input.m;
            n = input.n;

            values = new double[m*n];
            for(int i{0}; i < (m*n); i++){
                values[i] = input.get_value(i);
            }
        }

        //Move Constructor
        matrix(matrix &&input){
            std::cout << "Move Constructor" << std::endl;
            m = input.m;
            n = input.n;
            values = input.values;

            input.m = 0;
            input.n = 0;
            input.values = nullptr;
        }

        //Destructor
        ~matrix(){delete[] values;};

        //Functions//

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

        void set_element(int i, int j, const double value){
            values[(i-1)*n + (j-1)] = value;
        }

        matrix delete_row(int row) const {
            matrix output{m-1, n};
            int removal_start = n*(row-1);
            int removal_end = n*row;
            int i{0};
            for(i; i < removal_start; i++){
                output.values[i] = values[i];
            }
            for(int j{removal_end}; j < m*n; j++){
                output.values[i] = values[j];
                i++;
            }
            return output;
        }

        matrix delete_column(int column) const {
            matrix output{m, (n)-1};

            for(int i{0}, j{0}; i < m*n; i++){
                if( ((i - (column-1)) % n) != 0){
                    output.values[j] = values[i];
                    j++;
                }
                
            }
            return output;
        }

        matrix delete_row_column(int row, int column) const {
            return matrix{delete_row(row).delete_column(column)};
        }

        double calculate_determinant() const {
            if(m == n){
                if(m*n == 1){
                    return values[0];
                }   else {  double determinant{0};
                            for(int j{1}; j <= n; j++ ){
                                if(j % 2 == 0){
                                     determinant = determinant - get_element(1, j)*(delete_row_column(1, j).calculate_determinant());
                                }   else {
                                        determinant = determinant + get_element(1, j)*(delete_row_column(1, j).calculate_determinant());
                                    }
                            }
                            return determinant;
                    }
            }   else {
                    std::cout << "Cannot calculate the determinant for a non-square matrix" << std::endl;
                    return 0;
                }
        }

        //Operator Overloads//
        
        //Copy Assigment Operator overload
        matrix &operator=(matrix &input){
            std::cout << "Copy Assignment" << std::endl;
            if(&input == this){
                return *this;
            }

            delete[] values;
            values = nullptr;
            m = 0;
            n = 0;

            m = input.m;
            n = input.n;

            values = new double[m*n];
            for(int i{0}; i < (m*n); i++){
                values[i] = input.get_value(i);
            }

            return *this;
        }
        
        //Move Assignment Operator Overload
        matrix operator=(matrix &&input){
            std::cout << "Move Assignment" << std::endl;
            std::swap(m, input.m);
            std::swap(n, input.n);
            std::swap(values, input.values);
            return *this; 
        }

        //Addition Operator Overload
        matrix operator+(matrix input){
            if(m != input.m || n != input.n){
                std::cout << "Could not perform addition, matrices not the same size." << std::endl;
                return *this;
            }
            matrix output{m, n};
            for(int i{0}; i < m*n; i++){
                output.values[i] = values[i] + input.values[i];
            }
            return output;
        }

        //Subration Operator Overload
        matrix operator-(matrix input){
            if(m != input.m || n != input.n){
                std::cout << "Could not perform subtraction, matrices not the same size." << std::endl;
                return *this;
            }
            matrix output{m, n};
            for(int i{0}; i < m*n; i++){
                output.values[i] = values[i] - input.values[i];
            }
            return output;
        }

        //Multiplication Operator Overload
        matrix operator*(matrix input){
            if(n != input.m){
                std::cout << "Could not perform multiplication, matrices not compatible sizes" << std::endl;
                return *this;
            }
            matrix output{m, input.n};
            for(int i{1}; i <= m; i++){
                for(int j{1}; j <= input.n; j++){
                    double sum{0};
                    for(int k{1}; k <= n; k++){
                        sum = sum + (get_element(i, k)*input.get_element(k, j));
                    }
                    output.set_element(i, j, sum);
                } 
            }
            return output;

        }

        //Friend Functions
        friend std::ostream &operator<<(std::ostream &output, matrix &input);

        friend std::istream &operator>>(std::istream &input, matrix &output);
};

std::ostream &operator<<(std::ostream &output, matrix &input){
    for(int i = 1; i <= input.m; i++){
        output << "| ";
        for(int j = 1; j <= input.n; j++){
            output << input.get_element(i,j) << " ";
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

//Main Code//

int main(){
    std::cout << "Creating Matrix 1" << std::endl;
    matrix matrix1 = {"1 2 3, 4 5 6, 7 8 9\n"};
    std::cout << matrix1 << std::endl;
    std::cout << "Copying Matrix 1 to Matrix 2" << std::endl;
    matrix matrix2;
    matrix2 = matrix1;
    std::cout << matrix2 << std::endl;
    std::cout << "Creating Matrix 3 by moving Matrix 1" << std::endl;
    matrix matrix3 = std::move(matrix1);
    std::cout << matrix3 << std::endl;
    std::cout << "Matrix 1 is now empty\n" << matrix1 << "Refilling Matrix 1 with a new matrix, using a move assigment." << std::endl;
    matrix1 = matrix{"12 11 10 9, 8 7 6 5, 4 3 2 1\n"};
    std::cout << matrix1 << "\nMatrices 2 and 3 remain unchanged\n" << matrix2 << '\n' << matrix3 << std::endl;
    std::cout << "Adding Matrix 2 to Matrix 3" << std::endl;
    matrix matrix_sum = matrix2+matrix3;
    std::cout << matrix_sum << std::endl;
    std::cout << "Subtracting the sum from Matrix 2" << std::endl;
    matrix matrix_diff = matrix2 - matrix_sum;
    std::cout << matrix_diff << std::endl;
    std::cout << "Multiplying Matrix 2 by Matrix 3" << std::endl;
    matrix matrix_product = matrix2*matrix3;
    std::cout << matrix_product << std::endl;
    std::cout << "Please emter a matrix. If it is square its determinant will be calculated. Use a space between values, and place a comma to separate rows.\nFor Example: \n12 11 10 9, 8 7 6 5, 4 3 2 1\nproduces\n" << matrix1 << std::endl;
    matrix matrix4;
    std::cin >> matrix4;
    std::cout << matrix4 << "The determinant of this matrix is:" << matrix4.calculate_determinant() << std::endl;
}