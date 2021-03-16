#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	32
# endif

int			get_next_line(int fd, char **line);
char		*ft_strjoin(char *s1, char const *s2);
char		*ft_str_endl(char *s);

#endif
