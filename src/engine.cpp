#include <iostream>
#include "Solver.hpp"

int main(int argc, char* argv[]){
    Solver s1;
    if(s1.init()){
        s1.run();
    }
    else{
        std::cout << "could not initialize solver";
    }
    return 0;
}