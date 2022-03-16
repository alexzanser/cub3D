#ifndef RAYCAST_H
#define RAYCAST_H

#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "../mlx/mlx.h"


#define MAP_WIDTH 24
#define MAP_HEIGHT 24
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

typedef struct s_vector {
	float x;
	float y;
} t_vector ;

typedef struct	 s_mlx {
	void			*mlx_ptr;
	void			*win_ptr;
}t_mlx;

typedef struct   s_ray {
	t_vector		*ray_dir;
	int 			map_x;
	int 			map_y;
	float 			side_dist_y;
	float 			side_dist_x;
	float 			delta_dist_x;
	float 			delta_dist_y;
	float 			perp_wall_dist;
	int 			step_x;
	int 			step_y;
	int 			hit;
	int 			side;
	int 			line_height;
	int 			draw_start;
	int 			draw_end;
} t_ray;

typedef struct s_raycast {
	t_vector 		*dir;
	t_vector 		*pos;
	t_vector 		*plane;
	float			camera_x;
	int 			pos_x;
	int 			pos_y;
	long long int	time;
	long long int	prev_time;
	int 			color;
	void			*image;
	char 			*buffer;
} t_raycast;

t_raycast  *init_raycast(void);
t_vector *init_vector(void);
t_ray  *init_ray(void);

int init_pos_and_dir(t_raycast *cast_data);
int casting_rays(t_raycast *cast_data, t_ray *ray, t_mlx *mlx);

#endif
