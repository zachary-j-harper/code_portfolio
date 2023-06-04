#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include <algorithm>

class imaginary_number{

    private:
        double real, imaginary;     //Can't be made constant due to input function (operator>> needs ability to write to real/imaginary)

    public:

        //Constructors
        imaginary_number() = default;

        imaginary_number(double input_real, double input_imaginary):
            real{input_real}, imaginary{input_imaginary}
            {}

        ~imaginary_number(){}

        //Return Functions
        double get_real() const {       
            return real;
        } 

        double get_imaginary() const {
            return imaginary;
        }

        double get_modulus() const {
            return sqrt(pow(real, 2)+pow(imaginary, 2));
        }

        double get_argument() const {
            return atan2(imaginary, real); //Atan2 is a modified arctan function for the purpose of calculating arguments
        }

        imaginary_number get_conjugate() const {
            return imaginary_number{real, -imaginary};
        }

        //Maths operator overload functions
        imaginary_number operator+(imaginary_number input) const {
            return imaginary_number{real+input.get_real(), imaginary+input.get_imaginary()};
        }

        imaginary_number operator-(imaginary_number input) const {
            return imaginary_number{real-input.get_real(), imaginary-input.get_imaginary()};
        }

        imaginary_number operator*(imaginary_number input) const {
            return imaginary_number{real*input.get_real(), real*input.get_imaginary()} + 
                imaginary_number{-(imaginary*input.get_imaginary()), imaginary*input.get_real()};
        }

        imaginary_number operator/(imaginary_number input) const {
            double denominator = (input*input.get_conjugate()).get_real();
            return imaginary_number{real*input.get_real()/denominator, real*input.get_conjugate().get_imaginary()/denominator} + 
                imaginary_number{-(imaginary*input.get_conjugate().get_imaginary()/denominator), imaginary*input.get_real()/denominator};
        }

        //I/O Friends
        friend std::ostream &operator<<(std::ostream &output,imaginary_number input);

        friend std::istream &operator>>(std::istream &input, imaginary_number &output);
        
};

//Non member functions
//Friend functions
//Cannot be made const as they are non-member
std::ostream &operator<<(std::ostream &output, imaginary_number input){
    output << input.get_real();
    if(input.get_imaginary() > 0){ //If/else works out if a + needs to be added
        output << "+" << input.get_imaginary() << "i";
    }   else{   if(input.get_imaginary() < 0){
                    output << input.get_imaginary() << "i";
                }//Won't print 0i for numbers without imaginary component
        }
    return output;
};

std::istream &operator>>(std::istream &input, imaginary_number &output){ //Assumes perfect input. Can take either a+ib or a+bi
    double buffer;
    char sign;
    std::stringstream builder;
    input >> output.real;
    sign = input.get();
    if(input.peek() ==  'i'){
        input.ignore(1, '\n');
    }
    input >> buffer;
    builder << sign;
    builder << buffer;
    builder >> output.imaginary;
    if(input.peek() ==  'i'){
        input.ignore(1, '\n');
    }
    return input;
}
//Main Code, Functionality Demonstration
int main(){
    imaginary_number number1;
    imaginary_number number2;
    std::cout << "Please enter your first complex number in the format [a(+/-)bi] or [a(+/i)ib]." << std::endl;
    std::cin >> number1; //Input operator
    std::cout << "Please enter your second complex number in the format [a(+/-)bi] or [a(+/i)ib]." << std::endl;
    std::cin >> number2; 
    std::cout << "For your first complex number, " << number1 << ", the real part is " << number1.get_real() << " and the imaginary part is " 
        << number1.get_imaginary() << ". The argument is " << number1.get_argument() << " radians and the modulus is " << number1.get_modulus() 
        << ". It has complex conjugate " << number1.get_conjugate() << std::endl; //Output operator overload and get_x functions
    std::cout << "For your second complex number, " << number2 << ", the real part is " << number2.get_real() << " and the imaginary part is " 
        << number1.get_imaginary() << ". The argument is " << number2.get_argument() << " radians and the modulus is " << number2.get_modulus() 
        << ". It has complex conjugate " << number2.get_conjugate() << std::endl;
    std::cout << "Their sum is " << number1+number2 << std::endl; //Mathematical operator overloads
    std::cout << "Their difference is " << number1-number2 << std::endl;
    std::cout << "Their product is " << number1*number2 << std::endl;
    std::cout << "Their quotient is " << number1/number2 << std::endl;
    return 0;
}


