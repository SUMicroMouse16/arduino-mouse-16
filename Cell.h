// This class is for creation of cells, used for recording data.
// Data interacts with Cell.

/*typedef struct 
{
    
    
} Cell;*/

#define NDEBUG
#include <assert.h>

enum direction {north, south, east, west}; 

union Cell {
  uint8_t value;
  struct {
    uint8_t WallN : 1;
    uint8_t WallE : 1;
    uint8_t WallS : 1;
    uint8_t WallW : 1;
    
    uint8_t visited : 1;
    
    static_assert(Cell {.value = 0x40}.WallE == 1, "Bit E wrong");
    static_assert(Cell {.value = 0x20}.WallS == 1, "Bit S wrong"); 
    static_assert(Cell {.value = 0x10}.WallW == 1, "Bit W wrong");
    static_assert(Cell {.value = 0x08}.visited == 1, "Bit visited wrong");
  };
  
};

/*
    static_assert(Cell {.value = 0x88}.WallN == 1, "Bit ___ wrong");
    or
    static_assert(Cell {.WallN = 1}.WallN == 1, "Bit ___ wrong");
    or something
    
    #define NDEBUG
    #include <cassert> <assert>
             <assert.h>
    assert(<boolean expression> && "Error msg"); // if false, print out message + abort
                                                 // for checking if code is valid
*/

//HW: CELL (UNION{STRUCT})
