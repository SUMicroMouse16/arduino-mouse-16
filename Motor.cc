#include<stdio.h>
#include"cell.h"
#include"data.h"
#include"algorithm.h"
#include"cell.h"
#include"wheel.h"

using namespace std;

    bool moveleft(int amount); 
    bool moveRight(int amount);
    bool moveBack(int amount);
    bool moveFwd(int amount);
    //make a enum for the four directions and just have one function for the moving
    //and pass it as a parameter
    
    bool moveWheelLeft(int amount); //parameters wil be ints either 1 or -1 for direction
    bool moveWheelRight(int amount);

    void update(int change_in_pulseL, int change_in_pulseR);

