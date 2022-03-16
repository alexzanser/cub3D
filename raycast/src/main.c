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

void perform_dda(t_ray *ray)
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

void set_color(t_ray *ray, t_raycast  *cast_data)
{
	if (worldMap[ray->map_x][ray->map_y] == 1)
		cast_data->color = 0x00FF0000;
	else if (worldMap[ray->map_x][ray->map_y] == 2)
		cast_data->color = 0x0000FF00;
	else if (worldMap[ray->map_x][ray->map_y] == 3)
		cast_data->color = 0x000000FF;
	else if (worldMap[ray->map_x][ray->map_y] == 4)
		cast_data->color = 0x00FFFFFF;
	else
		cast_data->color = 0x00FFFF00;
}

void draw_line(int x, t_ray *ray, t_mlx *mlx, t_raycast *cast_data) {
	int	y;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		cast_data->buffer[y * SCREEN_WIDTH + x * 4] = 0x00FF0000;
		y++;
	}
}

int casting_rays(t_raycast *cast_data, t_ray *ray, t_mlx *mlx)
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

		perform_dda(ray);
		calc_perp_wall_dist(ray);
		calc_draw_limits(ray);
		set_color(ray, cast_data);
		draw_line(x, ray, mlx, cast_data);
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, cast_data->image, 0, 0);
	}

	return (0);
}

int main(void)
{
	t_mlx 		*mlx;
	t_raycast	*cast_data;
	t_ray 		*ray;
	int		done;


	done = 0;
	cast_data = init_raycast();
	init_pos_and_dir(cast_data);
	ray = init_ray();

	done = 1;
	cast_data->image = mlx_new_image(mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	int pixel_bits;
	int line_bytes;
	int endian;
	cast_data->buffer = mlx_get_data_addr(cast_data->image, &pixel_bits, &line_bytes, &endian);

	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT , "SO_LONG");
	casting_rays(cast_data, ray, mlx);

	mlx_loop(mlx->mlx_ptr);
	printf("posX :%f,  posY :%f\n", ray->ray_dir->x, ray->ray_dir->y);
    return 0;
}
