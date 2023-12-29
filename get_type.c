/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idelfag <idelfag@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 23:05:59 by idelfag           #+#    #+#             */
/*   Updated: 2023/12/29 14:29:26 by idelfag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	parse_line(char **line, t_parse *parse, int *index)
{
	if (!ft_strcmp(line[0], "C"))
		parse_camera(line, parse);
	else if (!ft_strcmp(line[0], "A"))
		parse_ambient(line, parse);
	else if (!ft_strcmp(line[0], "L"))
		parse_light(line, parse);
	else if (!ft_strcmp(line[0], "sp"))
		parse_sphere(line, parse, index);
	else if (!ft_strcmp(line[0], "pl"))
		parse_plane(line, parse, index);
	else if (!ft_strcmp(line[0], "cy"))
		parse_cylender(line, parse, index);
	else
	{
		free_tab(line);
		message_exit("Error\nbad configue file", 1);
	}
	free_tab(line);
}

int	count_objs(char **line)
{
	int		i;
	int		count;
	char	**res;

	i = 0;
	count = 0;
	while (line[i])
	{
		res = ft_split_two(line[i], "\t\n\v\f\r ");
		if (!ft_strcmp(res[0], "sp"))
			count++;
		if (!ft_strcmp(res[0], "cy"))
			count++;
		if (!ft_strcmp(res[0], "pl"))
			count++;
		free_tab(res);
		i++;
	}
	return (count);
}

void	get_content(t_vars *vars, t_parse *parse)
{
	int		i;
	char	**res;
	int		index;
	int		flag;

	i = 0;
	flag = 0;
	index = 0;
	parse->obj = malloc(sizeof(t_object) * (count_objs(vars->lines) + 1));
	while (vars->lines[i])
	{
		res = ft_split_two(vars->lines[i], "\t\n\v\f\r ");
		if (!ft_strcmp(res[0], "C") || !ft_strcmp(res[0], "L"))
			flag++;
		if (!res || !res[0])
		{
			i++;
			continue ;
		}
		parse_line(res, parse, &index);
		i++;
	}
	if (flag != 2)
		message_exit("Error\nparse file is not correct\n", 1);
	free_tab(vars->lines);
}
