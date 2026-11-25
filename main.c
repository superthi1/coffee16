#include "fdefs.h"


/// @brief A helper function for outputting the welcome text.
/// @param 
void welcomeText(void) {
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

    welcomeText();
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
                }
                case KEY_DOWN:
                {
                    _settextposition(currentPos.row + 1, 1);
                    break;
                }
                case KEY_LEFT:
                {
                    _settextposition(currentPos.row, currentPos.col - 1);
                    break;
                }
                case KEY_RIGHT:
                {
                    _settextposition(currentPos.row, currentPos.col + 1);
                    break;
                }
                case KEY_UP:
                {
                    _settextposition(currentPos.row - 1, 1);
                    break;
                }
                }
            }
            else if (ch == '\r')
            {
                _settextposition(currentPos.row + 1, 1);
            }
            /* TODO: Add a fdef.h definition for this. */
            else if (ch == '\b')
            {
                // this is fucking voodoo i swear to god 
                 
                /* TODO: Make backspace actually move UP a line */
                currentPos.col--;
                _settextposition(currentPos.row, currentPos.col);
                _outtext(" ");
                _settextposition(currentPos.row, currentPos.col);
            }
            else
            {
                char str[2];
                // ESC key
                if (ch == 27)
                {
                    _setbkcolor(0);
                    _settextcolor(7);
                    _clearscreen(_GCLEARSCREEN);
                    printf("Goodbye!\n");
                    break;
                }
                str[0] = (char)ch;
                str[1] = '\0';
                _outtext(str);
            }
        }
    }

    return 0;
}
