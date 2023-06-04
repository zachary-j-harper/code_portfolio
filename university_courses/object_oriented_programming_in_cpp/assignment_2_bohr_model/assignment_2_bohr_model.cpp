#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>

double calc_transition_energy(int z, int n_1, int n_2) {        //'separate function to return energy of level'
    return 13.6*pow(z, 2)*(1/pow(n_1, 2) - (1/pow(n_2, 2)));
}

int main(){
    bool cont = true;       //initialise variables
    bool pass;
    int atomic_number;
    int n_initial;
    int n_final;
    std::string choice;
    std::string unit;
    std::string greeting = "Welcome to the Transition Calculator! \nHere you can calculate the energy of any electron transition for any element, in either Joules or Electron Volts, according to the Bohr Model."; //let's test strings, because I can
    std::cout << greeting << std::endl;
    while(cont == true) {
        pass = false;
        while(pass == false) {       //Atomic number (z) input sanitisation loop
            std::cout << "What is the atomic number of the element you would like to calculate the transition for?" << std::endl;
            std::cin >> atomic_number;
            if(std::cin.fail() == false) {      //fail checks bad/fail-bit. Defeats all invalid inputs besidse a float or int followed by non-numeric characters
                if(std::cin.peek() == '\n') {       //checks if the int was the only information entered (lit. 'was next keypress Enter?' )
                    if(atomic_number > 0) {
                        pass = true;        //acquired a valid input, escape loop!
                    }   else {
                            std::cout << "Sorry, your value needs to be a single positive integer." << std::endl;
                        }
                }   else {
                        std::cout << "Sorry, your value needs to be a single positive integer." << std::endl;
                    }
            }   else {  if(std::cin.fail() == true) {
                            std::cout << "Sorry, your value needs to be a single positive integer." << std::endl;
                        }
                }
            std::cin.clear();
            std::cin.ignore(1000, '\n');   //resets input stream by removing 1000 leftover characters. Techinically entering an invalid input over
        }                                  //this limit may produce an error, but this seems very improbable.
        pass = false;
        while(pass == false) {      //Inital n value input sanitisation loop. Near identical to previous.
            std::cout << "What is the inital principle quantum nuber of the transitioning electron?" << std::endl;
            std::cin >> n_initial;
            if(std::cin.fail() == false) {
                if(std::cin.peek() == '\n') {
                    if(n_initial > 0) {
                        pass = true;        
                    }   else {
                            std::cout << "Sorry, your value needs to be a single positive integer." << std::endl;
                        }
                }   else {
                        std::cout << "Sorry, your value needs to be a single positive integer." << std::endl;
                    }
            }   else {  if(std::cin.fail() == true) {
                            std::cout << "Sorry, your value needs to be a single positive integer." << std::endl;
                        }
                }
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
        pass = false;
        while(pass == false){ //Final n value input sanitisation loop. Very similar to previous, however has a few numerical execptions to catch too.
            std::cout << "What is the final principle quantum number of the transitioning electron?" << std::endl;
            std::cin >> n_final;
            if(std::cin.fail() == false) {
                if(std::cin.peek() == '\n') {
                    if(n_final > 0) {
                        if(n_final > n_initial) {
                            pass = true;
                        }   else {  if(n_final == n_initial) {
                                        std::cout << "Sorry, there is no net movement of the electron, therefore this is not a valid transition." << std::endl;
                                    }   else {
                                            std::cout << "Sorry, that is an invalid transition." << std::endl;
                                        }
                            std::cout << "Please ensure your final principle quantum number is HIGHER than the initial." << std::endl;
                            }              
                    }   else {
                            std::cout << "Sorry, your value needs to be a single positive integer." << std::endl;
                        }                    
                }   else {
                        std::cout << "Sorry, your value needs to be a single positive integer." << std::endl;
                    }
            }   else {  if(std::cin.fail() == true) {
                            std::cout << "Sorry, your value needs to be a single positive integer." << std::endl;
                        }
                }
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
        double transition_energy_eV = calc_transition_energy(atomic_number, n_initial, n_final);        //call function
        pass = false;
        while(pass == false) {      //unit choice sanitisation loop
            std::cout << "Would you like the transition energy in Joules (J) or Electron Volts (eV)?" << std::endl;
            std::getline(std::cin, unit);    //electron volts is two words, so need the whole line for it to be recognised in a string
            std::transform(unit.begin(), unit.end(), unit.begin(), ::tolower);      //Makes input lowercase for less checks
            if( unit == "joules" || unit == "j" ) {
                pass = true;
                double transition_energy_J = transition_energy_eV * (1.6*pow(10, -19));
                std::cout.precision(3);     //Rounds next numerical output to 3sf
                std::cout << "The energy of this transition is "<< transition_energy_J <<"J" << std::endl;
            }   else {  if( unit == "electron volts" || unit == "ev") {
                            pass = true;
                            std::cout.precision(3);
                            std::cout << "The energy of this transition is "<< transition_energy_eV <<"eV" << std::endl;
                        }   else {
                                std::cout << "Sorry, that's not a unit I understand." << std::endl;
                            }           
                }
            std::cin.clear();
            //std::cin.ignore(1000, '\n');
        }
        pass = false;
        while(pass == false) {      //Repeat input sanitisaion loop
            std::cout << "Would you like to calculate the energy of another transition? [y/n]" << std::endl;
            std::cin >> choice;
            std::transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
            if( choice == "n" || choice == "no") {
                cont = false;
                pass = true;
            }   else {  if( choice != "y" && choice != "yes") {
                            std::cout << "Sorry, I'm not sure if that's a yes or no." << std::endl;
                        }   else {
                                pass = true;
                            }
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            }
        }
    }
    return 0;
}
