// This class is for creation of cells, used for recording data.
// Data interacts with Cell.

// #define NDEBUG
#ifndef _CELL_H_
#define _CELL_H_

#include <assert.h>
#include <stdint.h>

typedef unsigned char byte;

enum direction {north, south, east, west}; 

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
      
    }
    
    template<typename value_type = byte>
    constexpr Cell(value_type v) : value(static_cast<byte>(v)) {
      
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
    
#endif