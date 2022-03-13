#ifndef RAYCAST_H
#define RAYCAST_H

#include "stdlib.h"
#include "unistd.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1920

typedef struct s_vector {
	float x;
	float y;
} t_vector ;

typedef struct s_raycast {
	t_vector 		*dir;
	t_vector 		*pos;
	t_vector 		*plane;
	t_vector		*ray;
	t_vector		*ray_dir;
	float			camera_x;
	int 			pos_x;
	int 			pos_y;
	long long int	time;
	long long int	prev_time;
} t_raycast;

t_raycast  *init_raycast(void);
t_vector *init_vector(void);
int init_pos_and_dir(t_raycast *cast_data);

#endif
