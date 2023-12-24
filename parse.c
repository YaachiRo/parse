/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idelfag < idelfag@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 22:46:37 by idelfag           #+#    #+#             */
/*   Updated: 2023/12/22 07:06:58 by idelfag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parse.h"

int check_validity(char *name)
{
    int i = (ft_strlen(name) - 1);
    if (name[i] == 't' && name[i - 1] == 'r' && name[i - 2] == '.' && name[i - 3] != '.')
        return(1);
    return(0); 
}

int count_lines(int ac, char **av)
{
    int i = 0;
    char *line;
    int fd;
    (void)ac;

    fd = open(av[1], O_RDONLY);
    if (fd == -1)
        return(0);
    while ((line = get_next_line(fd)))
    {
        i++;
        free(line);
    }
    close(fd);
    return(i);
}

int read_file(int ac, char **av, t_vars* vars)
{
    int i;
    char *line;
    int fd;

    i = count_lines(ac, av);
    fd = open(av[1], O_RDONLY);
    if (fd == -1)
        return(0);
    vars->lines = malloc(sizeof(char *) * (i + 1));
    if (!vars->lines)
        return(0);
    i = 0;
    while ((line = get_next_line(fd)))
    {
        vars->lines[i] = malloc(sizeof(char) * (ft_strlen(line) + 1));
        if (!(vars->lines[i]))
            return(0);
        vars->lines[i] = line;
        i++;
    }
    vars->lines[i] = NULL;
    return(1);
}

int parse(int ac, char **av)
{
    t_vars vars;
    t_parse parse;
    if (ac != 2)
    {
        write(2, "Invalid args !\n", 16);
        exit(1);
    }
    if (!check_validity(av[1]))
    {
        write(2, "filename format is not valid\n", 30);
        exit(1);   
    }
    if (!read_file(ac, av, &vars))
    {
        write(2, "Something gone wrong\n", 22);
        exit(1);
    }
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
    
    return(1);
}

int main(int ac, char **av)
{
    parse(ac, av);
}