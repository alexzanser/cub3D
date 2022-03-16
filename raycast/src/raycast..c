#include "raycast.h"

t_ray  *init_ray(void) {
	t_ray *ray;

	ray = (t_ray *) malloc(sizeof (t_ray));
	ray->ray_dir = init_vector();
	if (NULL == ray || NULL == ray->ray_dir)
		return NULL;
	ray->ray_dir->x = -1.0;
	ray->ray_dir->y = 0.0;
	ray->map_x = 0;
	ray->map_y = 0;
	ray->delta_dist_x = 0.0;
	ray->delta_dist_y = 0.0;
	ray->side_dist_x = 0.0;
	ray->side_dist_y = 0.0;
	ray->perp_wall_dist = 0.0;
	ray->step_x = 0;
	ray->step_y = 0;
	ray->hit = 0;
	ray->side = 0;
	ray->line_height = 0;
	ray->draw_start = 0;
	ray->draw_end = 0;
	return (ray);
}

int init_pos_and_dir(t_raycast *cast_data)
{
	cast_data->pos_x = 22;
	cast_data->pos_y = 12;
	cast_data->camera_x = 0.0;
	cast_data->plane->x = 0.0;
	cast_data->plane->y = 0.66;
	return (0);
}

t_vector *init_vector(void)
{
	t_vector *vector;

	vector = (t_vector *) malloc(sizeof (t_vector));
	if (NULL == vector)
		return NULL;
	vector->x = 0.0;
	vector->y = 0.0;
	return (vector);
}

t_raycast  *init_raycast(void)
{
	t_raycast *cast_data;

	cast_data = (t_raycast *) malloc(sizeof (t_raycast));
	if (NULL == cast_data)
		return NULL;
	cast_data->camera_x = 0.0;
	cast_data->time = 0;
	cast_data->prev_time = 0;
	cast_data->dir = init_vector();
	cast_data->pos = init_vector();
	cast_data->plane = init_vector();
	if (NULL == cast_data->dir || NULL == cast_data->pos ||
			NULL == cast_data->plane)
		return NULL;
	return (cast_data);
}
