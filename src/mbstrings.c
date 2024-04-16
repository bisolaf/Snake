#include "mbstrings.h"

#include <stddef.h>

/* mbslen - multi-byte string length
 * - Description: returns the number of UTF-8 code points ("characters")
 * in a multibyte string. If the argument is NULL or an invalid UTF-8
 * string is passed, returns -1.
 *
 * - Arguments: A pointer to a character array (`bytes`), consisting of UTF-8
 * variable-length encoded multibyte code points.
 *
 * - Return: returns the actual number of UTF-8 code points in `src`. If an
 * invalid sequence of bytes is encountered, return -1.
 *
 *
 *
 * 
 */
size_t mbslen(const char* bytes) {

    size_t result = 0;

    while (*bytes != '\0') {
        unsigned char ch = *bytes;
        if ((ch & 0x80) == 0) { // 1-byte
            result++;
            bytes++;
        } else if ((ch & 0xE0) == 0xC0) { // 2-byte
            result++;
            bytes += 2;
        } else if ((ch & 0xF0) == 0xE0) { // 3-byte
            result++;
            bytes += 3;
        } else if ((ch & 0xF8) == 0xF0) { // 4-byte
            result++;
            bytes += 4;
        } else {
            // skip this byte
            bytes++;
        }
    }

    return result;
}
