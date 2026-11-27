/*
 * The definitions file for various functions and enums.
 */

#include <conio.h>
#include <stdio.h>
#include <graph.h>
#include <string.h>
#include <stdlib.h>
#define BACKSPACE '\b'
#define ENTER '\r'
#define ESCAPE 27

/// @brief Definitions for the function keys (F1-F12)
enum FunctionKeys
{
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
enum ArrowKeys
{
    KEY_UP = 72,
    KEY_DOWN = 80,
    KEY_LEFT = 75,
    KEY_RIGHT = 77,
};

/// @brief The char gap buffer.
typedef struct _char_buffer
{
    char *buf_;
    char *ccur_;
    char *cend_;
    unsigned int size_; // to get the end, buf_ + size_
} char_buffer;





/// @brief Grow the character buffer.
/// @param cb the character buffer
/// @param min_needed minimum amount to grow the buffer
/// @return -1 if it passes the 64KB limit OR if OOM
int cb_grow(char_buffer *cb, unsigned int min_needed)
{
    unsigned int old_size = cb->size_;
    unsigned int gap_start_off = (unsigned int)(cb->ccur_ - cb->buf_);
    unsigned int gap_end_off = (unsigned int)(cb->cend_ - cb->buf_);
    unsigned int suffix_len = old_size - gap_end_off;
    unsigned int new_size;
    char *new_buf;

    if (old_size >= 65500u)
        return -1;

    new_size = old_size + (old_size >> 1) + min_needed;
    if (new_size < old_size || new_size > 65500u)
    {
        new_size = 65500u;
    }
    if (new_size - old_size < min_needed)
        return -1;

    new_buf = (char *)realloc(cb->buf_, new_size);
    if (!new_buf)
        return -1;

    if (suffix_len > 0) {
        memmove(new_buf + new_size - suffix_len, new_buf + gap_end_off, suffix_len);
    
    }
    cb->buf_ = new_buf;
    cb->ccur_ = new_buf + gap_start_off;
    cb->cend_ = new_buf + (new_size - suffix_len);
    cb->size_ = new_size;
    return 0;
}

/// @brief Insert a character into the buffer.
/// @param cb the character buffer
/// @param c the character to insert
/// @return -1 if growing the buffer errors 
int cb_insert_char(char_buffer *cb, char* c) {
    if (cb->ccur_ == cb->cend_) {
        if (cb_grow(cb, 1) != 0) {
            return - 1;
        }
    }

    *cb->ccur_++ = c;
    return 0;
}
/// @brief Move the character buffer cursor to the left.
/// @param cb the character buffer
void cb_cur_left(char_buffer *cb) {
    if (cb->ccur_ > cb->buf_) {
        *--cb->cend_ = *--cb->ccur_;
    }
}

/// @brief Move the character buffer cursor to the right.
/// @param cb the character buffer
void cb_cur_right(char_buffer *cb) {
    if (cb->cend_ < cb->buf_ + cb->size_) {
        *cb->ccur_++ = *cb->cend_++;
    }
}

/// @brief Go backwards in the buffer
/// @param cb the character buffer
void cb_back(char_buffer *cb) {
    if (cb->ccur_ > cb->buf_) {
        cb->ccur_--;
    }
}

/// @brief Delete from the buffer
/// @param cb the character buffer
void cb_del(char_buffer *cb) {
    if (cb->cend_ < cb->buf_ + cb->size_) {
        cb->cend_++;
    }
}

/// @brief Rendering function, used to display what is in the buffer on the screen
/// @param cb the character buffer
void renderer(char_buffer *cb) {
    short row = 1, col = 1;
    short cur_row = 1, cur_col = 1;

    char *p;
    char str[2] = {0, 0};

    _clearscreen(_GCLEARSCREEN);
    _settextposition(1, 1);

    for (p = cb->buf_; p < cb->ccur_; p++) {
        if (*p == '\n') {
            row++;
            col = 1;
            _settextposition(row, col);
        } else {
            str[0] = *p;
            _outtext(str);
            col++;
        }
    }

    cur_row = row;
    cur_col = col;

    for (p = cb->cend_; p < cb->buf_ + cb->size_; p++) {
        if (*p = '\n') {
            row++;
            col = 1;
            _settextposition(row, col);
        } else {
            str[0] = *p;
            _outtext(str);
            col++;
        }
    } 
    _settextposition(cur_row, cur_col);
}