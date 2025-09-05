#include <lib/fmt.h>
#include <lib/itoa.h>
#include <lib/stdarg.h>
#include <lib/string.h>

// FIX: Only supports two char long formatting specifiers
// Internal logic of printf family functions
size_t vsnprintf(char *restrict s, size_t maxlen, const char *restrict format, va_list args) {
    if (maxlen == 0)
        return 0;

    size_t written = 0;
    for (size_t i = 0; written < maxlen && format[i] != 0; i++) {
        if (format[i] == '%' && format[i + 1] != 0) {
            char specifier = format[i + 1];
            i++; // Skip %

            switch (specifier) {
                // Signed decimal
            case 'd':
            case 'i': {
                int value = va_arg(args, int);
                char literal[32] = {0};
                itoa(value, literal, 10);

                size_t len = strlen(literal);
                for (size_t j = 0; j < len && written < maxlen - 1; j++)
                    s[written++] = literal[j];
                break;
            }
                // HEX
            case 'x': {
                unsigned int value = va_arg(args, unsigned int);
                char literal[32] = {0};
                itoa(value, literal, 16);

                size_t len = strlen(literal);
                for (size_t j = 0; j < len && written < maxlen - 1; j++)
                    s[written++] = literal[j];
                break;
            }
                // Char
            case 'c': {
                char ch = (char)va_arg(args, int);
                if (written < maxlen - 1)
                    s[written++] = ch;
                break;
            }
                // NULL terminated string
            case 's': {
                const char *str = va_arg(args, const char *);
                if (!str)
                    str = "<NULL>";
                for (size_t j = 0; str[j] && written < maxlen - 1; j++)
                    s[written++] = str[j];
                break;
            }
            default: {
                if (written < maxlen - 1)
                    s[written++] = '%';
                if (written < maxlen - 1)
                    s[written++] = specifier;
                break;
            }
            }
        } else {
            s[written++] = format[i];
        }
    }

    s[written] = '\0';
    return written;
}


size_t snprintf(char *restrict s, size_t maxlen, const char *restrict format, ...) {
    va_list args;
    va_start(args, format);

    size_t written = vsnprintf(s, maxlen, format, args);

    va_end(args);
    return written;
}
