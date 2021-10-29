#include <stdlib.h>

size_t	ft_strlen(const char *str)
{
	size_t	size;

	size = 0;
	while (str[size] != '\0')
		size++;
	return (size);
}

void	*ft_memcpy(void *dst, void *src, size_t n)
{
	char	*d;
	char	*s;

	d = dst;
	s = src;
	while (n)
	{
		n--;
		d[n] = s[n];
	}
	return (dst);
}

char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	len;

	len = ft_strlen(s1);
	str = malloc(len + 1);
	if (!str)
		return (0);
	ft_memcpy(str, (void *)s1, len + 1);
	return ((char *)str);
}

int	malloc_empty_string(char **str)
{
	*str = ft_strdup("");
	if (!*str)
		return (-1);
	else
		return (0);
}
