/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idelfag < idelfag@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 23:05:59 by idelfag           #+#    #+#             */
/*   Updated: 2023/12/22 07:10:52 by idelfag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "parse.h"

void parse_line(char **line, t_parse *parse)
{
    if (!ft_strncmp(line[0], "C", ft_strlen(line[0])))
        parse_camera(line, parse);
    else if (!ft_strncmp(line[0], "A", ft_strlen(line[0])))
        parse_ambient(line, parse);
    else if (!ft_strncmp(line[0], "L", ft_strlen(line[0])))
        parse_light(line, parse);
    // else if (ft_strncmp(line[0], "sp", ft_strlen(line[0])))
    //     parse_sphere(line, parse);
    // else if (ft_strncmp(line[0], "pl", ft_strlen(line[0])))
    //     parse_plane(line, parse);
    // else if (ft_strncmp(line[0], "cy", ft_strlen(line[0])))
    //     parse_cylender(line, parse);
}

void get_content(t_vars *vars, t_parse *parse)
{
    int i = 0;
    char **res;

    while(vars->lines[i])
    {
        res = ft_split_two(vars->lines[i], "\t\n\v\f\r ");
        if (!res || !res[0])
        {
            i++;
            continue;
        }
        parse_line(res, parse);
        i++;
    }
}