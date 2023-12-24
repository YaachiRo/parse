/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idelfag < idelfag@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 23:05:53 by idelfag           #+#    #+#             */
/*   Updated: 2023/12/22 06:47:15 by idelfag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef PARSE_H
# define PARSE_H

# include "libft/libft.h"
# include "get_next_line/get_next_line.h"

typedef struct s_vec3
{
	float x;
	float y;
	float z;
} t_vec3;

typedef struct s_color
{
	float r;
	float g;
	float b;
}				t_color;


typedef struct s_vec2
{
	float u;
	float v;
}	t_vec2;

typedef struct s_image
{
	float **red;
	float **green;
	float **blue;
}	t_image;

typedef struct s_light
{
	t_vec3 position;
	t_vec3 color;
	float intensity;
}	t_light;

typedef struct s_camera
{
	t_vec3 origin;
	t_vec3 lookat;
	t_vec3 up_vector;
	t_vec3 cam_w;
	t_vec3 cam_u;
	t_vec3 cam_v;
	t_vec3 screen_center;
	t_vec3 screen_u;
	t_vec3 screen_v;
	float aspect_ratio;
	float focal_length;
	float hor_size;
	int fov;
} t_camera;

typedef struct s_ray
{
	t_vec3 point1;
	t_vec3 point2;
	t_vec3 dir;
} t_ray;

typedef struct s_matrix
{
	int rows;
	int cols;
	float **matrix;
} t_matrix;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_info
{
	struct s_object *e;
	t_vec3 hitpoint;
	t_vec3 localnormal;
	t_vec2 uv;
}	t_info;

typedef struct s_object
{
	int type;
	t_vec3 base_color;
	t_vec3 translation;
	t_vec3 rotation;
	t_vec3 scale;
	t_vec3 d_normal;
	t_matrix **gtfm;
	float radius;
	float shininess;
	float reflectivity;
	int has_texture;
	int has_material;
	t_matrix *checker_matrix;
	t_data *image;
	t_data *imgnormal;
	int  (*intersect)(t_ray*, struct s_info *);
}	t_object;

typedef struct s_ambient
{
	float ambient_ratio;
	t_vec3 rgb;
}				t_ambient;


typedef struct s_vars
{
    char **lines;
    int c;
    int a;
    int l;
}               t_vars;

typedef struct s_parse
{
	t_camera cam;
	t_light light;
	t_ambient ambient_light;
	t_object obj;
}				t_parse;


void	free_tab(char **tab);
int		ft_isspace(int c);
void	message_exit(char *msg, int n);
char    **ft_split_two(char *str, char *charset);
float	parse_number(char *str, int *index);
void	skip_char(char *line, char c, int *index);
void	get_content(t_vars *vars, t_parse *parse);
void	parse_camera(char **line, t_parse *parse);
void	parse_ambient(char **line,t_parse *parse);
void	parse_light(char **line, t_parse *parse);

#endif