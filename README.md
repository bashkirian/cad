# Test task for CADExchanger
 Simple program for 3d curves

# Welcome!

Here is short explanation of my realization of your task.  

1. I created parent class Curve, which has 4 pure virtual methods:  
    1.1 equation - takes t as parameter, returns struct vector3d, which represents, obviously, 3d vector.  
    1.2 der1 - takes t as parameter, returns first derivative of curve at paramteter.  
    1.3 GetRadius() - returns radius of curve. In case of Ellipse, it returns sum of two ellipse's radiuses.
2. Each curve is represented by inheritant of base class, i.e Curve, and implements each virtual method by overriding.  
    For example,  
    2.1 Circle equation is {x0 + r*cos(t), y0 + r*sin(t)}, so equation implemements onle this equation.  
    2.2 Spiral equation is {x0 + r*cos(t), y0 + r*sin(t), a*t}, where a is step of the curve on Z-axis.  
    I calculated derivatives myself, so der1 will be returning 3d vector of coordinates: {-r*sin(t), r*cos(t), a}.
3. Each and every inheritant takes same two arguments in constructor: x0 and y0. This double numbers reperesent center of curve on 2d plane. But other arguments vary: for circle is radius, for ellipse is two radiuses, for spiral is additional step parameter.  

# Main program

Let's take a look at line.cpp file:  

1. I created list<unique_ptr<Curve>> of curves. I choose unique_ptr<Curve> as template because of copying easability. 
2. After that, all tasks, which where declared in document, are implemented. Curves are choosen randomly by case-switch.   
3. At last, for 4 task recognition of Circle object is justified by dynamic_cast.  
It is worth noting, that i used OpenMP library for paralleling of summation of radiuses.  

P.S. Unfortunately, I don't possess enough knowledge to create .dll file from my project. Although I'm always ready to improve upon my begginings!

# Clone and build

You can clone and build, then run my project with this simple command:  

git clone https://github.com/bashkirian/cad  
cd cad  
g++ -g line.cpp line  
./line