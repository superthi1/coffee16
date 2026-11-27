#include "fdefs.h"

/// @brief A helper function for outputting the welcome text.
/// @param
void welcomeText(void)
{
    _setbkcolor(1);
    _settextcolor(7);
    _clearscreen(_GCLEARSCREEN);
    _settextposition(1, 1);
    _outtext("Welcome to the Coffee16 text editor!\n");
    _outtext("Developed by Luka V.");
    _settextposition(2, 1);
}

int main(void)
{
    int ch;
    // initialize the buffer
    char_buffer cb = {0};

    welcomeText();
    renderer(&cb);
    // main loop
    while (1)
    {

        struct rccoord currentPos = _gettextposition();
        if (kbhit())
        {
            ch = getch();

            if (ch == 0 || ch == 0xE0)
            {
                int ext = getch();

                switch (ext)
                {
                case KEY_F1:
                {
                    /* TODO: Help section*/
                    break;
                }
                case KEY_DOWN:
                {
                    /* TODO: make this work */
                    _settextposition(currentPos.row + 1, 1);
                    break;
                }
                case KEY_LEFT:
                {
                    cb_cur_left(&cb);
                    break;
                }
                case KEY_RIGHT:
                {
                    cb_cur_right(&cb);
                    break;
                }
                case KEY_UP:
                {
                    /* TODO: make this work */
                    _settextposition(currentPos.row - 1, 1);
                    break;
                }
                }
            }
            else if (ch == ENTER)
            {
                cb_insert_char(&cb, '\n');
            }
            else if (ch == BACKSPACE)
            {
                cb_back(&cb);
            }
            else if (ch == ESCAPE)
            {
                _setbkcolor(0);
                _settextcolor(7);
                _clearscreen(_GCLEARSCREEN);
                printf("Goodbye!\n");
                break;
            }
            else
            {
                cb_insert_char(&cb, (char)ch);
            }
        }
    }
    free(cb.buf_);
    return 0;
}
