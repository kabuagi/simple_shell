#include "shell.h"

/**
 * get_line - reads line stdin
 * @lineptr:pointer to a pointer line
 * @stream:fd
 *
 * Return:pointer to line
 */

ssize_t get_line(char **lineptr, size_t *n, FILE *stream)
{
        static size_t buffer_pos;

        static char buffer[MAX_COMMAND_LENGTH];

        ssize_t bytes_read = 0;

        ssize_t total_bytes_read = 0;

        char *line = *lineptr;

        if (line == NULL)
        {
                *n = MAX_COMMAND_LENGTH;
                line = (char *)malloc(*n);
                if (line == NULL)
                {
                        perror("malloc");
                        exit(EXIT_FAILURE);
                }
                *lineptr = line;
        }

        while (1)
        {
                if (buffer_pos == 0)
                {
                        bytes_read = read(fileno(stream), buffer, sizeof(buffer));
                        if (bytes_read == -1)
                        {
                                perror("read");
                                exit(EXIT_FAILURE);
                        }
                        else if (bytes_read == 0)
                        {
                                return (-1);
                        }
                        total_bytes_read += bytes_read;
                }
                while (buffer_pos < (size_t)bytes_read)
                {
                        if (buffer[buffer_pos] == '\n')
                        {
                                line[buffer_pos] = '\0';
                                buffer_pos++;
                                return (total_bytes_read);
                        }
                        else
                        {
                                line[buffer_pos] = buffer[buffer_pos];
                                buffer_pos++;
                                if (buffer_pos == *n)
                                {
                                        *n += MAX_COMMAND_LENGTH;
                                        line = (char *)realloc(line, *n);
                                        if (line == NULL)
                                        {
                                                perror("realloc");
                                                exit(EXIT_FAILURE);
                                        }
                                        *lineptr = line;
                                }
                        }
                }
                buffer_pos = 0;
        }
}
