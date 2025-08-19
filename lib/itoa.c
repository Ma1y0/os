#include <lib/itoa.h>

char *itoa(int value, char *str, int base) {
    if (value == 0) {
        str = "0";
    }

    return str;
}
