/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idelfag < idelfag@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 23:36:15 by idelfag           #+#    #+#             */
/*   Updated: 2023/12/22 07:08:01 by idelfag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parse.h"

int ft_tablen(char **tab)
{
	int i = 0;

	while (tab[i])
		i++;
	return(i);
}

int check_cam_error(t_camera *cam)
{
	if (cam->fov >= 180)
		return(0);
	if (cam->lookat.x < -1.0f || cam->lookat.x > 1.0f)
		return(0);
	if (cam->lookat.y < -1.0f || cam->lookat.y > 1.0f)
		return(0);
	if (cam->lookat.z < -1.0f || cam->lookat.z > 1.0f)
		return(0);
	return(1);
}

void parse_camera(char **line, t_parse *parse)
{
	int i = 1;
	int j = 0;
	
	if (ft_tablen(line) != 4)
		message_exit("Error while parcing camera infos\n", 1);
	parse->cam.origin.x = parse_number(line[i], &j);
	skip_char(line[i], ',', &j);
	parse->cam.origin.y = parse_number(line[i], &j);
	skip_char(line[i], ',', &j);
	parse->cam.origin.z = parse_number(line[i], &j);
	i++;
	j = 0;
	parse->cam.lookat.x = parse_number(line[i], &j);
	skip_char(line[i], ',', &j);
	parse->cam.lookat.y = parse_number(line[i], &j);
	skip_char(line[i], ',', &j);
	parse->cam.lookat.z = parse_number(line[i], &j);
	i++;
	parse->cam.fov = ft_atoi(line[i]);
	if (!check_cam_error(&(parse->cam)))
		message_exit("Error while parcing camera infos\n", 1);
}

int check_ambient_error(t_ambient *ambient)
{
	if ((ambient->rgb.x < 0.0f) || (ambient->rgb.x > 255.0f))
		return(0);
	if ((ambient->rgb.y < 0.0f) || (ambient->rgb.y > 255.0f))
		return(0);
	if ((ambient->rgb.z < 0.0f) || (ambient->rgb.z > 255.0f))
		return(0);
	if (ambient->ambient_ratio < 0.0f || ambient->ambient_ratio > 1.0f)
		return(0);
	return(1);
}

void parse_ambient(char **line,t_parse *parse)
{
    int i = 1;
	int j = 0;

	if (ft_tablen(line) != 3)
		message_exit("Error while parcing ambient lightning infos\n", 1);
    parse->ambient_light.ambient_ratio = parse_number(line[i], &j);
	i++;
	j = 0;
	parse->ambient_light.rgb.x = parse_number(line[i], &j);
	skip_char(line[i], ',', &j);
	parse->ambient_light.rgb.y = parse_number(line[i], &j);
	skip_char(line[i], ',', &j);
	parse->ambient_light.rgb.z = parse_number(line[i], &j);
	if (!check_ambient_error(&(parse->ambient_light)))
		message_exit("Error while parcing ambient lightning infos\n", 1);
	parse->ambient_light.rgb.x = (parse->ambient_light.rgb.x / 255.0f);
	parse->ambient_light.rgb.y = (parse->ambient_light.rgb.y / 255.0f);
	parse->ambient_light.rgb.z = (parse->ambient_light.rgb.z / 255.0f);
}

int light_error_check(t_light *light)
{
	if ((light->color.x < 0.0f) || (light->color.x > 255.0f))
		return(0);
	if ((light->color.y < 0.0f) || (light->color.y > 255.0f))
		return(0);
	if ((light->color.z < 0.0f) || (light->color.z > 255.0f))
		return(0);
	if (light->intensity < 0.0f || light->intensity > 1.0f)
		return(0);
	return(1);
}

void parse_light(char **line, t_parse *parse)
{
	int i = 1;
	int j = 0;
	
	if (ft_tablen(line) != 4)
		message_exit("Error while parcing light infos\n", 1);
	parse->light.position.x = parse_number(line[i], &j);
	skip_char(line[i], ',', &j);
	parse->light.position.y = parse_number(line[i], &j);
	skip_char(line[i], ',', &j);
	parse->light.position.z = parse_number(line[i], &j);
	i++;
	j = 0;
	parse->light.intensity = parse_number(line[i], &j);
	i++;
	j = 0;
	parse->light.color.x = parse_number(line[i], &j);
	skip_char(line[i], ',', &j);
	parse->light.color.y = parse_number(line[i], &j);
	skip_char(line[i], ',', &j);
	parse->light.color.z = parse_number(line[i], &j);
	if (!light_error_check(&(parse->light)))
		message_exit("Error while parcing light infos\n", 1);
	parse->light.color.x = (parse->light.color.x / 255.0f);
	parse->light.color.y = (parse->light.color.y / 255.0f);
	parse->light.color.z = (parse->light.color.z / 255.0f);
}
