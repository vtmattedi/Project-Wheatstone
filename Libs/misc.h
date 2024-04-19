#include <stdarg.h>
#include <string>

#define FORMAT_BUFFER_SIZE 1024
/// 'Ported' from NightMareNetwork misc.h https://github.com/vtmattedi/NightMareNetwork/
/// @brief Uses `printf` to format a String object. 
/// @param format The string with the placeholders '%d', '%x' etc.
/// @param args... The args to match the string passed.
/// @return The formatted String.
std::string formatString(const char *format, ...)
{
    // Create a buffer to store the formatted string
    char buffer[FORMAT_BUFFER_SIZE]; // You can adjust the size as needed
    va_list args;
    va_start(args, format);
    // Format the string into the buffer
    int len = vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    if (len < 0)
    {
        // Error occurred during formatting
        return std::string();
    }
    // Convert the formatted buffer to a String
    return std::string(buffer);
}
