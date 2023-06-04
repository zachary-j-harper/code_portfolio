#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <math.h>

class shape{       //Pure abtract shape base class
    public:
        virtual ~shape(){}

        virtual std::string get_type() = 0;     //Type of shape

        virtual double get_area() = 0;

        virtual double get_volume() = 0;

        virtual double get_perimeter() = 0;     //For 2D shapes for use in the prism class later
};

class shape_2D: public shape {      //2D Shape class. Requires few additions to shape, besides making volume function 0.
    protected:      //Use of protected so derived classes can access area. shape_2D acts a data store
        double area;
    public:

        shape_2D(double area_in):
            area{area_in} {}        

        virtual ~shape_2D(){}

        double get_volume(){
            return 0;
        }

};

class shape_3D: public shape {      //3D Shape class.
    private:                //Uses private data, in opposition to shape_2D. This is because volume/area return functions are defined here,
        double volume;      //meaning that they do not need to be re-defined identically later in every derived class. 
        double area;        //This means derived classes only contain unique functions. Possibly a more effective method?
    public:

        shape_3D(double area_in, double volume_in):
            area{area_in}, volume{volume_in} {}
        
        virtual ~shape_3D(){};

        double get_volume(){
            return volume;
        }

        double get_area(){
            return area;
        }

        double get_perimeter(){ //3D shape perimeter not required
            return 0;
        }
};

class square: public shape_2D {
    private:
        double length;
        std::string type = "Square"; //Types can be hard-coded at derived class level 

    public:
        square() = default;

        square(double length_in):
            shape_2D{length_in*length_in}, length{length_in} {}

        ~square(){}

        double get_length(){
            return length;
        }

        double get_perimeter(){
            return length*4;
        }
        
        double get_area(){
            return area;
        }

        std::string get_type(){
            return type;
        }       
};

class rectangle: public shape_2D {
    private:
        double length, width;
        std::string type = "Rectangle"; 

    public:
        rectangle() = default;

        rectangle(double length_in, double width_in):
            shape_2D{length_in*width_in}, length{length_in}, width{width_in} {}

        ~rectangle(){}

        double get_length(){
            return length;
        }

        double get_perimeter(){
            return (length + width)*2;
        }

        double get_width(){
            return width;
        }
        
        double get_area(){
            return area;
        }

        std::string get_type(){
            return type;
        }
        
};

class triangle: public shape_2D {
    private:
        double base, height;
        std::string type = "Triangle"; 

    public:
        triangle() = default;

        triangle(double base_in, double height_in):
            shape_2D{0.5*base_in*height_in}, base{base_in}, height{height_in} {}

        ~triangle(){}

        double get_base(){
            return base;
        }

        double get_perimeter(){
            return base + 2*(sqrt( pow(base/2, 2) + pow(height, 2) ));  //Only an approximation, assumes max height is at half base
        }                                                               //Aka, triangle is isoscelses or equilateral

        double get_height(){
            return height;
        }
        
        double get_area(){
            return area;
        }

        std::string get_type(){
            return type;
        }
        
};

class circle: public shape_2D {
    private:
        double radius;
        std::string type = "Circle"; 

    public:
        circle() = default;

        circle(double radius_in):
            shape_2D{radius_in*radius_in*M_PI}, radius{radius_in} {}

        ~circle(){}

        double get_radius(){
            return radius;
        }

        double get_perimeter(){
            return 2*M_PI*radius;
        }

        double get_area(){
            return area;
        }

        std::string get_type(){
            return type;
        }
};

class ellipse: public shape_2D {
    private:
        double major_radius, minor_radius;
        std::string type = "Ellipse"; 

    public:
        ellipse() = default;

        ellipse(double major_in, double minor_in):
            shape_2D{major_in*minor_in*M_PI}, major_radius{major_in}, minor_radius{minor_in} {}

        ~ellipse(){}

        double get_major(){
            return major_radius;
        }

        double get_minor(){
            return minor_radius;
        }

        double get_perimeter(){
            return M_PI*(major_radius + minor_radius); //A simple approximation, as no general formula exists
        }

        double get_area(){
            return area;
        }

        std::string get_type(){
            return type;
        }
};

class cube: public shape_3D {
    private:
        double length;
        std::string type = "Cube";
    public:
        cube() = default;

        cube(double length_in):
            shape_3D{6*length_in*length_in, length_in*length_in*length_in}, length{length_in}{}

        ~cube(){}

        double get_length(){
            return length;
        }

        std::string get_type(){
            return type;
        }
};

class cuboid: public shape_3D {
    private:
        double length, width, height;
        std::string type = "Cuboid";
    public:
        cuboid() = default;

        cuboid(double length_in, double width_in, double height_in):
            shape_3D{2*(length_in*width_in + length_in*height_in + width_in*height_in), length_in*width_in*height_in}, length{length_in}, width{width_in}, height{height_in} {}

        ~cuboid(){}

        double get_length(){
            return length;
        }

        double get_width(){
            return width;
        }

        double get_height(){
            return height;
        }

        std::string get_type(){
            return type;
        }
};

class ellipsoid: public shape_3D {
    private:
        double semiaxis_a, semiaxis_b, semiaxis_c;
        std::string type = "Ellipsoid";
    public:
        ellipsoid() = default;

        ellipsoid(double semiaxis_a_in, double semiaxis_b_in, double semiaxis_c_in):
            shape_3D{4*M_PI*pow(( pow(semiaxis_a_in*semiaxis_b_in, 1.6) + pow(semiaxis_b_in*semiaxis_c_in, 1.6) + pow(semiaxis_a_in*semiaxis_c_in, 1.6) )/3, (1/1.6) ), (4*M_PI*semiaxis_a_in*semiaxis_b_in*semiaxis_c_in)/3}, semiaxis_a{semiaxis_a_in}, semiaxis_b{semiaxis_b_in}, semiaxis_c{semiaxis_c_in} {}

        ~ellipsoid(){}

        double get_semiaxis_a(){
            return semiaxis_a;
        }

        double get_semiaxis_b(){
            return semiaxis_b;
        }

        double get_semiaxis_c(){
            return semiaxis_c;
        }

        std::string get_type(){
            return type;
        }
};

class sphere: public shape_3D {
    private:
        double radius;
        std::string type = "Sphere";
    public:
        sphere() = default;

        sphere(double radius_in):
            shape_3D{4*M_PI*pow(radius_in, 2), (4*M_PI*pow(radius_in, 3))/3}, radius{radius_in}{}

        ~sphere(){}

        double get_radius(){
            return radius;
        }

        std::string get_type(){
            return type;
        }
};

class prism: public shape_3D { //is_a 3D shape, has_a (2D) shape
    private:
        double length;
        shape* base;
        std::string type; //Defintion creates compound type depending on 2D shape used.

    public:
        prism() = default;

        prism(double length_in, shape* shape_in): 
            shape_3D{length_in*(shape_in->get_perimeter()) + 2*(shape_in->get_area()), 0}, length{length_in}, base{shape_in}, type{(shape_in->get_type()) + " Prism"} {}
                    //2D shape perimeter needed here ^ to get surface area.
        ~prism(){}

        double get_volume(){ //Overrides a non-pure-virtual function. Class contains a function to return the volume of the prism
            return length*(base->get_area());
        }

        std::string get_type(){
            return type;
        }

        
};

void print_shape(shape* shape_in){
    std::cout << "Shape: " << shape_in->get_type() << ", Area: " << shape_in->get_area() << ", Volume: " << shape_in->get_volume() << std::endl;
}

//Main Program//

int main(){
    square square{2};
    rectangle rectangle{3, 4};
    triangle triangle{1, 3};
    circle circle{4};
    ellipse ellipse{2, 4};
    cube cube{3};
    cuboid cuboid{2, 3, 4};
    ellipsoid ellipsoid{3, 4, 5};
    sphere sphere{5};
    prism prism{4, &triangle};

    std::vector<shape*> shapes;
    shapes.push_back(&square);
    shapes.push_back(&rectangle);
    shapes.push_back(&triangle);
    shapes.push_back(&circle);
    shapes.push_back(&ellipse);
    shapes.push_back(&cube);
    shapes.push_back(&cuboid);
    shapes.push_back(&ellipsoid);
    shapes.push_back(&sphere);
    shapes.push_back(&prism);

    for(int i{0}; i < shapes.size(); i++){
        print_shape(shapes[i]);
    }

    return 0;
}

