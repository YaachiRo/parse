/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idelfag <idelfag@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 16:19:21 by idelfag           #+#    #+#             */
/*   Updated: 2022/12/21 17:35:33 by idelfag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	str_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*str_cpy(char *dst, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}

void	*put_zero(size_t size, size_t count)
{
	void	*ptr;
	size_t	i;

	i = 0;
	if (count > 0 && size > SIZE_MAX / count)
		return (NULL);
	ptr = malloc(size * count);
	if (!ptr)
		return (NULL);
	while (i < (size * count))
	{
		((unsigned char *)ptr)[i] = '\0';
		i++;
	}
	return (ptr);
}

char	*str_join(char *str1, char *str2)
{
	char	*join;
	char	*start;

	join = malloc(sizeof(char) * str_len(str1) + str_len(str2) + 1);
	if (!join)
		return (NULL);
	start = join;
	join = str_cpy(join, str1);
	join += str_len(str1);
	join = str_cpy(join, str2);
	join += str_len(str2);
	join[0] = '\0';
	free(str1);
	return (start);
}

char	*str_search(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (&str[i]);
		str++;
	}
	if (str[i] == c)
		return (&str[i]);
	return (NULL);
}
