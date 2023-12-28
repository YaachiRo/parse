/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idelfag <idelfag@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 23:05:45 by idelfag           #+#    #+#             */
/*   Updated: 2023/12/28 19:49:15 by idelfag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parse.h"

float length2(t_vec3 a)
{
	return (pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2));
}

float length(t_vec3 a)
{
	return (sqrtf(length2(a)));
}

t_vec3 scale_vector(t_vec3 a, float t)
{
	return ( (t_vec3) {a.x * t, a.y * t, a.z * t} );
}

t_vec3 normalized(t_vec3 a)
{
	t_vec3 new;
	float l;

	new = a;
	l = length(new);
	if (l != 0)
		new = scale_vector(new, 1.0f / l);
	return (new);
}

void skip_char(char *line, char c, int *index, char* str)
{
    if (line[*index] != c || !line[*index])
    {
		// printf("line char %c\nchar is %c\n", line[*index], c);
		// while(1);
        write(2,"error while parcing ",21);
		ft_putendl_fd(str, 2);
        exit(1);
    }
    (*index)++;
    if (!line[*index])
    {
        write(2,"error while parcing ",21);
		ft_putendl_fd(str, 2);
        exit(1);
    }  
}

void err_exit(int n)
{
	write(2,"Error\n",6);
	exit(n);
}

void message_exit(char *msg, int n)
{
	write(2,msg,ft_strlen(msg));
	exit(n);
}

int	ft_isspace(int c)
{
	if (ft_strchr("\t\n\v\f\r ", c))
		return (1);
	return(0);
}

float	get_floating_part(char *str, int *index, int sign)
{
	float	res;
	int		i;
	float	j;

	i = *index;
	res = 0.0;
	if (str[i] == '.')
	{
		i++;
		j = 0.1;
		while (ft_isdigit(str[i]))
		{
			res = res + sign * j * (str[i] - '0');
			j /= 10;
			i++;
		}
	}
	*index = i;
	return (res);
}

float	get_number(char *str, int *index, int sign)
{
	float	res;
	int		i;

	i = *index;
	res = 0.0;
	if (!ft_isdigit(str[i]))
		err_exit(0);
	while (ft_isdigit(str[i]))
	{
		res = 10 * res + sign * (str[i] - '0');
		i++;
	}
	res += get_floating_part(str, &i, sign);
	*index = i;
	return (res);
}

float	parse_number(char *str, int *index)
{
	int		i;
	float	res;
	int		sign;

	i = *index;
	res = 0.0;
	sign = 1;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (ft_strchr("+-", str[i]))
	{
		if (str[i] == '-')
			sign = -1;
		skip_char(str, str[i], &i, "number");
	}
	res = get_number(str, &i, sign);
	while (str[i] && ft_isspace(str[i]))
		i++;
	*index = i;
	return (res);
}

int ft_strcmp(char *s1, char *s2)
{
	int i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return(s1[i] - s2[i]);
		i++;
	}
	if (s1[i] != s2[i])
			return(s1[i] - s2[i]);
	return(0);
}

void free_tab(char **tab)
{
    int i = 0;

    while (tab[i])
	{
        free(tab[i]);
		i++;
	}
    free(tab);
}