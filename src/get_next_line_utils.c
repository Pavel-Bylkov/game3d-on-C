#include "get_next_line.h"

char	*ft_strjoin(char *s1, char const *s2)
{
	char	*res;
	char	*tmp;
	size_t	len1;
	size_t	len2;

	if (s2 == NULL)
		return (NULL);
	len1 = (s1 == NULL) ? 0 : ft_strlen(s1);
	len2 = ft_strlen(s2);
	res = (char *)malloc(len1 + len2 + 1);
	if (res == NULL)
		return (NULL);
	tmp = res;
	while (len1 != 0 && len1-- != 0)
		*tmp++ = *s1++;
	while (len2 != 0 && len2-- != 0)
		*tmp++ = *s2++;
	*tmp = '\0';
	return (res);
}

char	*ft_str_endl(char *s)
{
	char	*str;

	if (s == NULL)
		return (NULL);
	str = s;
	while (*str)
	{
		if (*str == '\n')
			return (str);
		str++;
	}
	return (NULL);
}
