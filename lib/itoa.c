#include <lib/itoa.h>
#include <lib/stdarg.h>
#include <lib/string.h>
#include <lib/types.h>

char *itoa(int value, char *str, int base) {
    if (value == 0) {
        str[0] = '0';
        return str;
    }

    // itoa handles all non base 10 numbers as unsigned
    bool is_negative = value < 0 && base == 10;
    if (is_negative)
        value *= -1;

    size_t i = 0;
    while (value != 0) {
        int rem = value % base;
        str[i] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        value = value / base;
        i++;
    }

    if (is_negative) {
        str[i] = '-';
        i++;
    }

    // Add the null terminator
    str[i] = 0;

    strrev(str);

    return str;
}
