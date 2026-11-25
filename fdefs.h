/*
* The definitions file for various F1-F12 commands.
*/

#include <conio.h>
#include <stdio.h>
#include <graph.h>



 /// @brief Definitions for the function keys (F1-F12)
 enum FunctionKeys {
    KEY_F1 = 59,
    KEY_F2,  
    KEY_F3,  
    KEY_F4,  
    KEY_F5,  
    KEY_F6,  
    KEY_F7,  
    KEY_F8,  
    KEY_F9, 
    KEY_F10, 
    KEY_F11 = 133,
    KEY_F12 
};


 /// @brief Definitions for the arrow keys.
 enum ArrowKeys {
    KEY_UP = 72,
    KEY_DOWN = 80,
    KEY_LEFT = 75,
    KEY_RIGHT = 77,
};



/// @brief The char gap buffer.
typedef struct _char_buffer {
    char* buf_;
    char* ccur_;
    char* cend_;
    int size_;  // to get the end, buf_ + size_
} char_buffer;


/// @brief The line gap buffer, used to track line sizes.
typedef struct _line_buffer {
    int* line_size_;
    char* ccur_;
    char* cend_;
    int size_;

} line_buffer;

typedef struct _editor {
    char_buffer cb_;
    line_buffer lb;
} editor;




