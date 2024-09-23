#include "../inc/libmx.h"

static void write_from_remainder(char **line, char *rmdr, char *buf, int bytes, int idx)
{
	mx_strncpy(*line, rmdr, bytes);
	mx_strncpy(*line + bytes, buf, idx);
	mx_memset(rmdr, 0, bytes);

}

static void write_to_remainder(char *line, char *buf, int buflen, int idx)
{
	if (idx != buflen - 1)
	{
		mx_strncpy(line,buf + idx + 1, buflen - idx);
	}
}

int mx_read_line(char **lineptr, size_t buf_size, char delim, const int fd)
{
	if (lineptr && *lineptr && fd > 0)
	{
		mx_memset(*lineptr, 0, mx_strlen(*lineptr) + 1);
		static char remainder[10240] = {0,};
		char buf[buf_size + 1];
		int bytes = 0;
		mx_memset(buf, 0, buf_size + 1);
		int bytesread = read(fd, buf, buf_size);

		if (bytesread > 0)
		{
			int idx = mx_get_char_index(buf, delim);
			int remainder_len = mx_strlen(remainder);

			if (idx != -1)
			{
				if (remainder_len > 0)
				{
					write_from_remainder(lineptr, remainder, buf, remainder_len, idx);
					bytes += remainder_len;
				}
				else
				{
					mx_strncpy(*lineptr, buf, idx);
				}
				write_to_remainder(remainder, buf, buf_size, idx);
				bytes += idx;

			}
			else
			{
				bytes += bytesread;
				if (remainder_len > 0)
				{
					write_from_remainder(lineptr, remainder, buf, remainder_len, bytes);
					bytes += remainder_len;
					remainder_len = 0;
				}
				else
				{
					mx_strncpy(*lineptr, buf, bytes);
				}

				while (bytesread > 0 && idx == -1)
				{
					bytesread = read(fd, buf, buf_size);
					if (bytesread > 0)
					{
						idx = mx_get_char_index(buf, delim);
						mx_strncpy(*lineptr + bytes + remainder_len, buf, idx == -1 ? buf_size : idx);
						bytes += idx == -1 ? bytesread : idx;
					}
				}
				write_to_remainder(remainder, buf, buf_size, idx);

			}

		}
		else
		{
			if (bytesread == -1)
			{
				return -2;
			}
			return -1;
		}
		(*lineptr)[bytes] = '\0';
		return bytes;
	}
	return -2;


}



