#include "libmx.h"

char *mx_strnew(const int size)
{
	if (size >= 0)
	{
		char *str = malloc(size + 1);
		if (str)
		{
			for (int i = 0; i <= size; i++)
			{
				str[i] = '\0';
			}
			return str;
		}
	}
	return NULL;
	
}



