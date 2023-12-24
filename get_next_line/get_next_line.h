/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idelfag < idelfag@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 16:40:42 by idelfag           #+#    #+#             */
/*   Updated: 2023/12/20 23:04:52 by idelfag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 33
# endif

# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>

size_t	str_len(char *str);
char	*str_cpy(char *dst, char *src);
void	*put_zero(size_t size, size_t count);
char	*str_join(char *str1, char *str2);
char	*str_search(char *str, char c);
char	*get_next_line(int fd);

#endif