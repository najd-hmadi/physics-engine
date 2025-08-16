#include <iostream>
#include "Solver.hpp"
// this will be a knightmare to debug, hopefully no problems
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