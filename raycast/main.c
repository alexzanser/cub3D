#include "raycast.h"

#include "stdio.h"

int casting_rays(t_raycast *cast_data)
{
	int x;

	x = -1;
	while (++x < w)
	{
		cast_data->camera_x = 2 * x / ((float) SCREEN_WIDTH) - 1;
		cast_data->ray_dir->x = cast_data->dir->x + cast_data->plane->x * cast_data->camera_x;
		cast_data->ray_dir->y = cast_data->dir->y + cast_data->plane->y * cast_data->camera_x;
	}
}

int main(void)
{
	t_raycast	*cast_data;
	done		int;

	done = 0;

	cast_data = init_raycast();
	init_pos_and_dir(cast_data);

	while (done) {
		casting_rays(t_raycast *cast_data);
	}
	printf("posX :%f,  posY :%f\n", cast_data->ray_dir->x, cast_data->ray_dir->y);
    return 0;
}
