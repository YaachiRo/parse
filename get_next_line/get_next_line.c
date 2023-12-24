/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idelfag <idelfag@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 16:49:04 by idelfag           #+#    #+#             */
/*   Updated: 2022/12/21 21:12:31 by idelfag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_and_save(int fd, char *holder)
{
	char	*buff;
	int		readed;

	readed = 1;
	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	if (!holder)
		holder = put_zero(1, 1);
	while (!str_search(holder, '\n') && readed != 0)
	{
		readed = read(fd, buff, BUFFER_SIZE);
		if (readed < 0)
		{
			free(buff);
			free(holder);
			return (NULL);
		}
		buff[readed] = 0;
		holder = str_join(holder, buff);
	}
	free(buff);
	return (holder);
}

char	*get_the_line(char *holder)
{
	char	*line;
	int		i;

	if (!*holder)
		return (NULL);
	i = 0;
	while (holder[i] && holder[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (holder[i] && holder[i] != '\n')
	{
		line[i] = holder[i];
		i++;
	}
	if (holder[i] == '\n')
		line[i++] = '\n';
	line[i] = 0;
	return (line);
}

char	*update_holder(char *holder)
{
	char	*new_holder;
	int		i;
	int		j;

	i = 0;
	while (holder[i] && holder[i] != '\n')
		i++;
	if (!holder[i])
	{
		free(holder);
		return (NULL);
	}
	new_holder = (char *)malloc(sizeof(char) * (str_len(holder) - i + 1));
	if (!new_holder)
	{
		free(holder);
		return (NULL);
	}
	i++;
	j = 0;
	while (holder[i])
		new_holder[j++] = holder[i++];
	new_holder[j] = 0;
	free(holder);
	return (new_holder);
}

char	*get_next_line(int fd)
{
	static char	*holder;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	holder = read_and_save(fd, holder);
	if (!holder)
		return (NULL);
	line = get_the_line(holder);
	holder = update_holder(holder);
	return (line);
}
