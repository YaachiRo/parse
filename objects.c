/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idelfag <idelfag@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 08:09:37 by idelfag           #+#    #+#             */
/*   Updated: 2023/12/28 21:00:32 by idelfag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parse.h"

int check_sphere(t_object *obj)
{
    if ((obj->base_color.x < 0.0f) || (obj->base_color.x > 255.0f))
		return(0);
	if ((obj->base_color.y < 0.0f) || (obj->base_color.y > 255.0f))
		return(0);
	if ((obj->base_color.z < 0.0f) || (obj->base_color.z > 255.0f))
		return(0);
    return(1);
}

void parse_sphere(char **line, t_parse *parse, int *index)
{
    int i = 1;
    int j = 0;
    
    if (ft_tablen(line) != 4)
		message_exit("Error while parcing sphere infos\n", 1);
    parse->obj[*index].type = SPHERE;
    parse->obj[*index].translation.x = parse_number(line[i], &j);
    skip_char(line[i], ',', &j, "sphere");
    parse->obj[*index].translation.y = parse_number(line[i], &j);
    skip_char(line[i], ',', &j, "sphere");
    parse->obj[*index].translation.z = parse_number(line[i], &j);
	if (line[i][j])
		message_exit("Error while parcing sphere infos\n", 1);
    i++;
    j = 0;
    parse->obj[*index].radius = (parse_number(line[i],&j) / 2.0f);
	if (line[i][j])
		message_exit("Error while parcing sphere infos\n", 1);
    i++;
    j = 0;
    parse->obj[*index].base_color.x = parse_number(line[i], &j);
    skip_char(line[i], ',', &j, "sphere");
    parse->obj[*index].base_color.y = parse_number(line[i], &j);
    skip_char(line[i], ',', &j, "sphere");
    parse->obj[*index].base_color.z = parse_number(line[i], &j);
    if (line[i][j])
		message_exit("Error while parcing sphere infos\n", 1);
    if (!check_sphere(&(parse->obj[*index])))
        message_exit("found error while parsing sphere\n", 1);
    parse->obj[*index].base_color.x = (parse->obj[*index].base_color.x / 255.0f);
	parse->obj[*index].base_color.y = (parse->obj[*index].base_color.y / 255.0f);
	parse->obj[*index].base_color.z = (parse->obj[*index].base_color.z / 255.0f);
    (*index)++;
}

int check_plane(t_object *obj)
{
    if ((obj->d_normal.x < -1.0f) || (obj->d_normal.x > 1.0f))
		return(0);
	if ((obj->d_normal.y < -1.0f) || (obj->d_normal.y > 1.0f))
		return(0);
	if ((obj->d_normal.z < -1.0f) || (obj->d_normal.z > 1.0f))
		return(0);
    if ((obj->base_color.x < 0.0f) || (obj->base_color.x > 255.0f))
		return(0);
	if ((obj->base_color.y < 0.0f) || (obj->base_color.y > 255.0f))
		return(0);
	if ((obj->base_color.z < 0.0f) || (obj->base_color.z > 255.0f))
		return(0);
    return(1);
}

void parse_plane(char **line, t_parse *parse, int *index)
{
    int i = 1;
    int j = 0;
    
    if (ft_tablen(line) != 4)
		message_exit("Error while parcing plane infos\n", 1);
    parse->obj[*index].type = PLANE;
    parse->obj[*index].translation.x = parse_number(line[i], &j);
    skip_char(line[i], ',', &j, "plane");
    parse->obj[*index].translation.y = parse_number(line[i], &j);
    skip_char(line[i], ',', &j, "plane");
    parse->obj[*index].translation.z = parse_number(line[i], &j);
	if (line[i][j])
		message_exit("Error while parcing plane infos\n", 1);
    i++;
    j = 0;
    parse->obj[*index].d_normal.x = parse_number(line[i], &j);
    skip_char(line[i], ',', &j, "plane");
    parse->obj[*index].d_normal.y = parse_number(line[i], &j);
    skip_char(line[i], ',', &j, "plane");
    parse->obj[*index].d_normal.z = parse_number(line[i], &j);
    parse->obj->d_normal = normalized(parse->obj->d_normal);
	if (line[i][j])
		message_exit("Error while parcing plane infos\n", 1);
    i++;
    j = 0;
    parse->obj[*index].base_color.x = parse_number(line[i], &j);
    skip_char(line[i], ',', &j, "plane");
    parse->obj[*index].base_color.y = parse_number(line[i], &j);
    skip_char(line[i], ',', &j, "plane");
    parse->obj[*index].base_color.z = parse_number(line[i], &j);
	if (line[i][j])
		message_exit("Error while parcing plane infos\n", 1);
    if (!check_plane(&(parse->obj[*index])))
        message_exit("found error while parsing plane\n", 1);
    parse->obj[*index].base_color.x = (parse->obj[*index].base_color.x / 255.0f);
	parse->obj[*index].base_color.y = (parse->obj[*index].base_color.y / 255.0f);
	parse->obj[*index].base_color.z = (parse->obj[*index].base_color.z / 255.0f);
    (*index)++;
}

int check_cylender(t_object *obj)
{
    if ((obj->d_normal.x < -1.0f) || (obj->d_normal.x > 1.0f))
		return(0);
	if ((obj->d_normal.y < -1.0f) || (obj->d_normal.y > 1.0f))
		return(0);
	if ((obj->d_normal.z < -1.0f) || (obj->d_normal.z > 1.0f))
		return(0);
    if ((obj->base_color.x < 0.0f) || (obj->base_color.x > 255.0f))
		return(0);
	if ((obj->base_color.y < 0.0f) || (obj->base_color.y > 255.0f))
		return(0);
	if ((obj->base_color.z < 0.0f) || (obj->base_color.z > 255.0f))
		return(0);
    return(1);
}

void parse_cylender(char **line, t_parse *parse, int *index)
{
    int i = 1;
    int j = 0;
    
    if (ft_tablen(line) != 6)
		message_exit("Error while parcing cylender infos\n", 1);
    parse->obj[*index].type = CYLINDER;
    parse->obj[*index].translation.x = parse_number(line[i], &j);
    skip_char(line[i], ',', &j, "cylender");
    parse->obj[*index].translation.y = parse_number(line[i], &j);
    skip_char(line[i], ',', &j, "cylender");
    parse->obj[*index].translation.z = parse_number(line[i], &j);
	if (line[i][j])
		message_exit("Error while parcing cylender infos\n", 1);
    i++;
    j = 0;
    parse->obj[*index].d_normal.x = parse_number(line[i], &j);
    skip_char(line[i], ',', &j, "cylender");
    parse->obj[*index].d_normal.y = parse_number(line[i], &j);
    skip_char(line[i], ',', &j, "cylender");
    parse->obj[*index].d_normal.z = parse_number(line[i], &j);
    parse->obj[*index].d_normal = normalized(parse->obj->d_normal);
	if (line[i][j])
		message_exit("Error while parcing cylender infos\n", 1);
    i++;
    j = 0;
    parse->obj[*index].scale.x = (parse_number(line[i], &j) / 2.f);
    j = 0;
    parse->obj[*index].scale.y = (parse_number(line[i], &j) / 2.f);
    i++;
    j = 0;
    parse->obj[*index].scale.z = parse_number(line[i], &j);
    if (line[i][j])
		message_exit("Error while parcing cylender infos\n", 1);
    i++;
    j = 0;
    parse->obj[*index].base_color.x = parse_number(line[i], &j);
    skip_char(line[i], ',', &j, "cylender");
    parse->obj[*index].base_color.y = parse_number(line[i], &j);
    skip_char(line[i], ',', &j, "cylender");
    parse->obj[*index].base_color.z = parse_number(line[i], &j);
    if (line[i][j])
		message_exit("Error while parcing cylender infos\n", 1);
    if (!check_cylender(&(parse->obj[*index])))
        message_exit("found error while parsing cylender\n", 1);
    parse->obj[*index].base_color.x = (parse->obj[*index].base_color.x / 255.0f);
	parse->obj[*index].base_color.y = (parse->obj[*index].base_color.y / 255.0f);
	parse->obj[*index].base_color.z = (parse->obj[*index].base_color.z / 255.0f);
    (*index)++;
}