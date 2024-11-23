#include "cell.h"
#include <stdexcept>

//ctor
Cell::Cell(char c = ' ', int life = -1): 
    c{c}, life{life} {}

int Cell::getLife(){
    return life;
}


char Cell::getC(){
    return c;
}