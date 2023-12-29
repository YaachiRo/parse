/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idelfag <idelfag@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 22:46:37 by idelfag           #+#    #+#             */
/*   Updated: 2023/12/29 14:41:42 by idelfag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	check_validity(char *name)
{
	int	i;

	i = (ft_strlen(name) - 1);
	if (name[i] == 't' && name[i - 1] == 'r'
		&& name[i - 2] == '.' && name[i - 3] != '.')
		return (1);
	return (0);
}

int	read_file(int fd, t_vars *vars)
{
	char	*buff;
	char	*file;
	int		readed;

	readed = 1;
	buff = malloc(sizeof(char) * 11);
	file = (char *)ft_calloc(1, 1);
	while (readed)
	{
		readed = read(fd, buff, 10);
		if (readed < 0)
		{
			free(buff);
			free(file);
			return (0);
		}
		buff[readed] = 0;
		file = ft_strjoin(file, buff);
	}
	free(buff);
	vars->lines = ft_split(file, '\n');
	free(file);
	return (1);
}

void	print_vector(t_vec3 a)
{
	printf("%f %f %f\n", a.x, a.y, a.z);
}

void	parse(int ac, char **av)
{
	t_vars	vars;
	t_parse	parse;
	int		fd;

	if (ac != 2)
		message_exit("Invalid args !\n", 1);
	if (!check_validity(av[1]))
		message_exit("filename format is not valid\n", 1);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		message_exit("failed to open the file\n", 1);
	if (!read_file(fd, &vars))
		message_exit("Something gone wrong\n", 1);
	get_content(&vars, &parse);
	printf("ambient light shit is\n");
    printf("ambient ratio : %f\nr : %f\ng : %f\nb : %f\n", parse.ambient_light.ambient_ratio, parse.ambient_light.rgb.x, parse.ambient_light.rgb.y, parse.ambient_light.rgb.z);
    printf("origins\n");
    printf("x : %f\ny: %f\nz: %f\n", parse.cam.origin.x,parse.cam.origin.y,parse.cam.origin.z);
    printf("lookat");
    printf("x : %f\ny: %f\nz: %f\n", parse.cam.lookat.x,parse.cam.lookat.y,parse.cam.lookat.z);
    printf("fov is : %d\n", parse.cam.fov);
    printf("light shit is\n");
    printf("position\n");
    printf("x : %f\ny: %f\nz: %f\n", parse.light.position.x,parse.light.position.y,parse.light.position.z);
    printf("brightness and colors\n");
    printf("brightness : %f\nr : %f\ng : %f\nb : %f\n", parse.light.intensity, parse.light.color.x, parse.light.color.y, parse.light.color.z);
    printf("cylender\ntranslation ");
    print_vector(parse.obj[0].translation);
    printf("normal ");
    print_vector(parse.obj[0].d_normal);
    printf("radius ");
    printf("%f\n", parse.obj[0].scale.x);
    printf("height ");
    printf("%f\n", parse.obj[0].scale.z);
    printf("base color ");
    print_vector(parse.obj[0].base_color);
    printf("sphere\nposition ");
    print_vector(parse.obj[1].translation);
    printf("radius ");
    printf("%f\n", parse.obj[1].radius);
    printf("base color ");
    print_vector(parse.obj[1].base_color);
    printf("plane\nposition ");
    print_vector(parse.obj[2].translation);
    printf("normal ");
    print_vector(parse.obj[2].d_normal);
    printf("base color ");
    print_vector(parse.obj[2].base_color);
}

int	main(int ac, char **av)
{
	parse(ac, av);
}
