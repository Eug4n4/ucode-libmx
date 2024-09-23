#include "libmx.h"


unsigned long mx_hex_to_nbr(const char *hex)
{
    if (hex)
    {
        int str_len = mx_strlen(hex);
        unsigned long res = 0;
        int digit = 0;

        for (int i = 0; i < str_len; i++)
        {
            if (mx_isdigit(hex[i]))
            {
                digit = hex[i] - '0';
            }
            else if (mx_isalpha(hex[i]))
            {
                if (mx_islower(hex[i]) && hex[i] <= 'f')
                {
                    digit = hex[i] - 'a';
                }

                else if (mx_isupper(hex[i]) && hex[i] <= 'F')
                {
                    digit = hex[i] - 'A';
                }
                else
                {
                    return 0;
                }

                digit += 10;

            }
            else
            {
                return 0;
            }

            unsigned int pow = str_len - 1 - i;
            unsigned long multiply = mx_pow(16, pow);

            res += digit * multiply;
        }
        return res;
    }
    return 0;

}




