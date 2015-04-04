// This class is for creation of cells, used for recording data.
// Data interacts with Cell.

// #define NDEBUG
#ifndef _CELL_H_
#define _CELL_H_

#include <assert.h>
#include <stdint.h>

typedef unsigned char byte;

enum direction : byte {north=B1000, south=B0100, east=B0010, west=B0001}; 

union Cell{
  //uint8_t 
  byte value;
  struct {
    byte WallN : 1; ///< B00000001
    byte WallE : 1; ///< B00000010
    byte WallS : 1; ///< B00000100
    byte WallW : 1; ///< B00001000
    
    byte visited : 1; ///< B00010000
    byte :3;
  };
    struct {
      byte lower : 4; ///< 0x0f
      byte upper : 4; ///< 0xf0
    };
    
    constexpr Cell() : value(0x0) {
      // not sure what this will be used for
    }
    
    template<typename value_type = byte>
    constexpr Cell(value_type v) : value(static_cast<byte>(v)) {
      // not sure what this will be used for
    }
    
    constexpr inline operator byte()
    {
      return value;
    }
    
  };

    static_assert(sizeof(Cell)==1, "Size of Cell incorrect, should be 1 B.");
    static_assert(Cell(1<<0).WallN == 1, "Bit N mismatch.");
    static_assert(Cell(1<<1).WallE == 1, "Bit E mismatch."); 
    static_assert(Cell(1<<2).WallS == 1, "Bit S mismatch.");
    static_assert(Cell(1<<3).WallW == 1, "Bit W mismatch.");
    static_assert(Cell(1<<4).visited == 1, "Bit visited mismatch.");

class Cell;



//NEW CODE 3/29
class Cell{
  Wall dat;
  int been_there = 0; //have we been in this cell before, intiialize all to 0
  //int row; //which row of the grid are we in
  //int col; //which col of the grid are we in
  //direction facing; //enum type, are we facing N, S, E, or W
  Cell* previous_Cell = NULL; //pointer to the previous cell we just came from
  
  //bool endCell(int row, int col); //is this an end cell, i.e. end of the maze
  //bool beginningCell(); //is this the beginning cell
 void detectWall(); //this may be in "wall" instead of here
};


//struct for the pair of x, y values of the grid 
struct coordinate{
  uint8_t X, Y;
}


class Grid{
  
  extern Cell mazeGrid[16][16]; 
  
  Cell & operator [] (coordinate coord)
  {
    return mazeGrid[];     
  }
  
  bool endCell(byte row, byte col); //is this an end cell, i.e. end of the maze
  bool beginningCell(); //is this the beginning cell
  
  
  //an example of how to use the operator, pass in the row/col like 
  //how here has 0,1 
  //int call()  { return (*this)[{0,1}].endCell()};
}

#endif





