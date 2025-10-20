#include "../header/cub.h"

void    print_td(char **str)
{
	int i = 0;
	while (str && str[i])
	{
		printf("%s", str[i]);
		i++;
	}
}

void	print_cred(t_cub *cb)
{
	printf("%s\n %s\n %s\n %s\n", cb->no_texture, cb->we_texture,cb->so_texture, cb->ea_texture);
	printf("%d, %d, %d\n", cb->floor_color[0], cb->floor_color[1], cb->floor_color[2]);
	printf("%d, %d, %d\n", cb->ceiling_color[0], cb->ceiling_color[1], cb->ceiling_color[2]);
	print_td(cb->map);
	printf("\nx == %d  | y == %d | spn_or == %d\n", cb->plyer_pos.x, cb->plyer_pos.y, cb->plyer_pos.spg_or);
}