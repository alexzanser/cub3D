#include "raycast.h"

#include <stdio.h>


int worldMap[MAP_WIDTH][MAP_HEIGHT]=
		{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
		};

float calc_delta_dist(float ray_dir_side)
{
	if (ray_dir_side != 0 ) {
		return  (fabs(1 / ray_dir_side));
	}
	else
		return (1000000000.0);
}

void calc_side_dist(t_ray *ray, t_raycast  *cast_data)
{
	if (ray->ray_dir->x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (cast_data->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else {
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - cast_data->pos_x) * ray->delta_dist_x;
	}
	if (ray->ray_dir->y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (cast_data->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else {
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - cast_data->pos_y) * ray->delta_dist_y;
	}
}

void perform_dda(t_ray *ray, t_raycast  *cast_data)
{
	while (ray->hit == 0) {
		if (ray->side_dist_x < ray->side_dist_y) {
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else {
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (worldMap[ray->map_x][ray->map_y] > 0) {
			ray->hit = 1;
		}
	}
}

void calc_perp_wall_dist(t_ray *ray)
{
	if (ray ->side == 0) {
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	}
	else {
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
	}
}

void calc_draw_limits(t_ray *ray) {
	ray->line_height = (int) (SCREEN_HEIGHT / ray->perp_wall_dist);

	ray->draw_start = -ray->line_height / 2 + SCREEN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + SCREEN_HEIGHT / 2;
	if (ray->draw_end >= SCREEN_HEIGHT)
		ray->draw_end = SCREEN_HEIGHT - 1;
}

int casting_rays(t_raycast *cast_data, t_ray *ray)
{
	int x;

	x = -1;
	while (++x < SCREEN_WIDTH)
	{
		cast_data->camera_x = 2 * x / ((float) SCREEN_WIDTH) - 1;
		ray->ray_dir->x = cast_data->dir->x + cast_data->plane->x * cast_data->camera_x;
		ray->ray_dir->y = cast_data->dir->y + cast_data->plane->y * cast_data->camera_x;

		ray->map_x = cast_data->pos_x;
		ray->map_y = cast_data->pos_y;

		ray->delta_dist_x = calc_delta_dist(ray->ray_dir->x);
		ray->delta_dist_x = calc_delta_dist(ray->ray_dir->y);
		calc_side_dist(ray, cast_data);

		perform_dda(ray, cast_data);
		calc_perp_wall_dist(ray);
		calc_draw_limits(ray);
	}

	return (0);
}

int main(void)
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_raycast	*cast_data;
	t_ray 		*ray;
	int		done;


	done = 0;
	cast_data = init_raycast();
	init_pos_and_dir(cast_data);
	ray = init_ray();

	done = 1;
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT , "SO_LONG");
	while (done) {
		casting_rays(cast_data, ray);
	}
	mlx_loop(mlx_ptr);
	printf("posX :%f,  posY :%f\n", ray->ray_dir->x, ray->ray_dir->y);
    return 0;
}
