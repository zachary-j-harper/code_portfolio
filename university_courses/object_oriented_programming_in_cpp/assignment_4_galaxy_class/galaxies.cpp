#include <iostream>
#include <string>
#include <vector>


class galaxy {

    private:
        std::string name;           //Private information, only variables
        std::string hubble_type;
        double redshift;
        double mass_total;
        double mass_stellar;
        double fraction_mass_stellar;
        std::vector<galaxy> satellites;     //class can store objects of the same class! Recursive!

    public:
        galaxy() = default;     //Default Constructor

        galaxy(std::string galaxy_name, std::string galaxy_hubble_type, double galaxy_redshift,         //Parameterized constructor
                double galaxy_mass_total, double galaxy_fraction_mass_stellar):         
            name{galaxy_name}, hubble_type{galaxy_hubble_type}, redshift{galaxy_redshift}, mass_total{galaxy_mass_total},
            fraction_mass_stellar{galaxy_fraction_mass_stellar}, mass_stellar{galaxy_fraction_mass_stellar*galaxy_mass_total} {}

        ~galaxy() {     //Destructor
            std::cout << "Deleting " << name << std::endl;
        }

        int add_satellite(std::string galaxy_name, std::string galaxy_hubble_type, double galaxy_redshift,  //Function to add satellite Galaxy
                            double galaxy_mass_total, double galaxy_fraction_mass_stellar) {                //Returns position of satellite in list for easy recall
            satellites.push_back(galaxy {galaxy_name, galaxy_hubble_type, galaxy_redshift, galaxy_mass_total, galaxy_fraction_mass_stellar});
            return (satellites.size() - 1);
        }
        std::string get_name() {        //Extra functions to return a specific quality about the galaxy.
            return name;                //Possibly a little excessive for this code but a nice demonstration. Potentially very useful later?        
        }

        std::string get_hubble_type() {
            return hubble_type;
        }

        double get_redshift() {
            return redshift;
        }

        double get_total_mass() {
            return mass_total;
        }

        double get_stellar_mass() {
            return mass_stellar;
        }

        double get_stellar_mass_fraction() {
            return fraction_mass_stellar;
        }

        std::vector<galaxy> get_all_satellite() {
            return satellites;
        }

        galaxy get_specific_satellite(int i) {
            return satellites[i];
        }

        void print_all();  //For functions defined outside of class

        void change_hubble(std::string hubble);

};

void galaxy::print_all() { //Print all information about a galaxy. Function also recursive, since class can be recursive.
    int n;
    std::cout << "The galaxy " << name << " is of hubble type " << hubble_type << ", with redshift " << redshift <<
            ", total mass " << mass_total << ", stellar mass " << mass_stellar << ", which makes a stellar mass fraction " 
            << fraction_mass_stellar << ". It has " << satellites.size() << " satellites."  << std::endl; 
    if(!satellites.empty()){        //Satellite number and information
        std::cout << "These are: " << std::endl;
        for(n = 0; n < satellites.size(); n++) {
            satellites[n].print_all();
        }
    }
     std::cout << "End description of " << name << "." << std::endl;
    return;
};

void galaxy::change_hubble(std::string hubble) {
    hubble_type = hubble;
    return;
}

//===========//
//=Main=Code=//
//===========//

int main() {

    std::vector<galaxy> galaxies;

    galaxy milky_way; //Default Constructor
    milky_way = {"Milky Way", "Sbc", 0, 1.5e12, 0.0405};
    milky_way.add_satellite("Satellite Galaxy 1", "E3", 0.01, 8e8, 0.03);
    int satellite2 = milky_way.add_satellite("Satellite Galaxy 2", "E0", 0.04, 6e7, 0.02);

    std::cout << "\nMilky Way prepared, printing... \n" << std::endl;
    milky_way.print_all(); //Demonstrate print all functions and satellites

    std::cout << "\nRetrieving second Milky Way satellite... \n" << std::endl;
    std::cout << milky_way.get_specific_satellite(satellite2).get_name() << " is the second satellite of the " << milky_way.get_name() << std::endl;
    //Class functions can be strung together quite intuitively.

    galaxy andromeda{"Andromeda", "Sa", 0.001001, 1.5e12, 0.05}; //Parameterized Constructor
    std::cout << "\nAndromeda prepared, printing... \n" << std::endl;
    andromeda.print_all();
    andromeda.change_hubble("Sb"); //Changed hubble value
    std::cout << "\nAndromeda Hubble Type Altered... \n" << std::endl;

    galaxies.push_back(milky_way);
    galaxies.push_back(andromeda);

    std::cout << "\nGalaxies added to vector, proceeding with iterative print method... \n" << std::endl;

    std::vector<galaxy>::iterator galaxies_begin{galaxies.begin()}; //Print using iterators
    std::vector<galaxy>::iterator galaxies_end{galaxies.end()};
    std::vector<galaxy>::iterator galaxies_iterator;

    for(galaxies_iterator = galaxies_begin; galaxies_iterator < galaxies_end; galaxies_iterator++) {
        (*galaxies_iterator).print_all(); // () Brackets required to make pointers work with class functions.
    }

    return 0;
}
