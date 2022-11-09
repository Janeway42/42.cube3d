#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include "../includes/libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1200
# endif

int		get_next_line(int fd, char **line);
char	*ft_strjoin_str(char *s1, char *s2);
char	*ft_line(const char *str, char c);
char	*ft_leftover(const char *str, char c);
int		ft_strlength(const char *str, char c);
size_t	ft_strlen(const char *str);

#endif