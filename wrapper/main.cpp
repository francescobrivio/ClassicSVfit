#include <iostream>
#include <pybind11/pybind11.h>
#include <TMath.h> // Include the ROOT header for mathematical functions

int square(int num) {
    return num * num;
}

double rootSquare(int num) {
    return TMath::Sqrt(num); // Use the Sqrt function from ROOT's TMath class
}

class SampleClass {
public:
    int add(int a, int b) {
        return a + b;
    }
};

PYBIND11_MODULE(pybintest_simple, m) {
    m.def("square", &square, "A function that returns the square of a number");
    m.def("rootSquare", &rootSquare, "A function that returns the square root of a number using ROOT");
    
    pybind11::class_<SampleClass>(m, "SampleClass")
        .def(pybind11::init<>())
        .def("add", &SampleClass::add, "A function that adds two numbers");
}
