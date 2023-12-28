/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idelfag <idelfag@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 23:05:59 by idelfag           #+#    #+#             */
/*   Updated: 2023/12/28 21:40:45 by idelfag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "parse.h"

void parse_line(char **line, t_parse *parse, int *index)
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
        message_exit("Error\nbad configue file", 1);
}

int count_objs(char **line)
{
    int i = 0;
    int count = 0;
    char **res;
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
    return(count);
}

void get_content(t_vars *vars, t_parse *parse)
{
    int i = 0;
    char **res;
    int index = 0;
    int flag = 0;
    
    parse->obj = malloc(sizeof(t_object) * (count_objs(vars->lines) + 1));
    while(vars->lines[i])
    {
        res = ft_split_two(vars->lines[i], "\t\n\v\f\r ");
        if (!ft_strcmp(res[0], "C") || !ft_strcmp(res[0], "L"))
            flag++;
        if (!res || !res[0])
        {
            i++;
            continue;
        }
        parse_line(res, parse, &index);
        free_tab(res);
        i++;
    }
    if (flag != 2)
        message_exit("Error\nparse file is not correct\n", 1);
    free_tab(vars->lines);
}