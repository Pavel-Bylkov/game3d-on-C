#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <sys/types.h>
# include "libft.h"

typedef struct		s_data
{
	char			*str;
	size_t			len;
	unsigned char	flag;
	ssize_t			width;
	ssize_t			precision;
	int				length;
	char			type;
	int				upper;
	size_t			shift;
	int				len_print;
	size_t			i;
	int				error;
	int				zero;
}					t_data;

int					ft_printf(const char *format, ...);
void				get_chars(va_list *ap, t_data *new);
void				ft_get_str_number(char *str, t_data *new, size_t len_nbr);
void				ft_get_p(char *str, t_data *new);
void				ft_get_x(char *str, t_data *new, size_t len_nbr);
char				*ft_itoa_base(unsigned long long int res, char *base,
									int b, int flag);
int					check_precision(char *str, t_data *new, size_t len_nbr,
									size_t *len_buf);
size_t				change_str(char **str, t_data *new, char **tmp,
									size_t len_buf);
void				get_str_from_param(va_list *ap, t_data *new);
void				fill_with_char(char **buf, size_t bufsize,
									char *c, ssize_t len_nbr);
size_t				print_string(const char *str, t_data *new);
size_t				scan_params(va_list *ap, const char *str, t_data *new);

#endif
