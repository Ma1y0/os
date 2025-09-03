#include <lib/itoa.h>
#include <lib/snprintf.h>
#include <lib/stdarg.h>
#include <lib/string.h>

// Only supports two char long formatting specifiers
size_t snprintf(char *restrict s, size_t maxlen, const char *restrict format, ...) {
    if (maxlen == 0)
        return 0;

    // Get the variadic args (...)
    va_list args;
    va_start(args, format);

    size_t written = 0;
    for (size_t i = 0; written < maxlen && format[i] != 0; i++) {
        if (format[i] == '%' && format[i + 1] != 0) {
            char specifier = format[i + 1];
            i++; // Skip the %

            switch (specifier) {
                // Signed decimal
            case 'd':
            case 'i': {
                int value = va_arg(args, int);
                char literal[32]; // Should be enough for 32-bit int
                itoa(value, literal, 10);

                size_t len = strlen(literal);
                for (size_t j = 0; j < len && written < maxlen - 1; j++) {
                    s[written] = literal[j];
                    written++;
                }
                break;
            }
                // HEX
            case 'x': {
                int value = va_arg(args, unsigned int);
                char literal[32];
                itoa(value, literal, 16);

                size_t len = strlen(literal);
                for (size_t j = 0; j < len && written < maxlen - 1; j++) {
                    s[written] = literal[j];
                    written++;
                }
                break;
            }
            // Char
            case 'c': {
                char ch = va_arg(args, int);

                if (written < maxlen - 1) {
                    s[written] = ch;
                    written++;
                }

                break;
            }
            // String
            case 's': {
                const char *str = va_arg(args, const char *);
                if (str == NULL) {
                    str = "<NULL>";
                }

                for (size_t j = 0; str[j] != '\0' && written < maxlen - 1; j++) {
                    s[written] = str[j];
                    written++;
                }
                break;
            }
                // Unknown format specifier
            default:
                if (written < maxlen - 1) {
                    s[written] = '%';
                    written++;
                }
                if (written < maxlen - 1) {
                    s[written] = specifier;
                    written++;
                }
                break;
            }
        } else {
            // Regular character
            s[written] = format[i];
            written++;
        }
    }

    // Make sure the string is NULL terminated
    s[written] = 0;

    va_end(args);
    return written;
}
