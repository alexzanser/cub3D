#include "raycast.h"


#include "stdio.h"

int main( )
{
	t_raycast *cast_data;

	cast_data = init_raycast();
	init_pos_and_dir(cast_data);

	printf("posX :%f,  posY :%f\n", cast_data->ray_dir->x, cast_data->ray_dir->y);
    return 0;
}
