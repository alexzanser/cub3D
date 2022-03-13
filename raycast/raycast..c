#include "raycast.h"


int init_pos_and_dir(t_raycast *cast_data) {

	cast_data->pos_x = 22;
	cast_data->pos_y = 12;
	cast_data->camera_x = 2 * x / ((float)SCREEN_WIDTH) - 1;

	cast_data->ray_dir->x = -1.0;
	cast_data->ray_dir->y = 0.0;
	cast_data->plane->x = 0.0;
	cast_data->plane->y = 0.66;
}

t_vector *init_vector(void) {
	t_vector *vector;

	vector = (t_vector *) malloc(sizeof (t_vector));
	if (NULL == vector)
		return NULL;
	vector->x = 0.0;
	vector->y = 0.0;

	return (vector);
}

t_raycast  *init_raycast(void) {
	t_raycast *cast_data;

	cast_data = (t_raycast *) malloc(sizeof (t_raycast));
	if (NULL == cast_data)
		return NULL;
	cast_data->camera_x = 0;
	cast_data->time = 0;
	cast_data->prev_time = 0;
	cast_data->dir = init_vector();
	cast_data->pos = init_vector();
	cast_data->plane = init_vector();
	cast_data->ray = init_vector();
	cast_data->ray_dir = init_vector();
	if (NULL == cast_data->dir || NULL == cast_data->pos ||
			NULL == cast_data->plane || NULL == cast_data->ray)
		return NULL;
	return (cast_data);
}
