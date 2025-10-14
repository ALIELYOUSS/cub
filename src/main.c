#include "../header/cub.h"

int extract_credantials(t_cub **cb_st, int fd)
{
	t_cred_list	*list;

	list = grap_credantials(fd);
	if (!list)
		return (0);
	if (!missing_or_dup(list) || !check_content_order(list))
		return (0);
	if (!asign_texters(list, cb_st))
		return (0);
	if (!asign_colors(list, cb_st))
		return (0);
	return (1);
}

int	parse_arguments(t_cub **cb_st, char **av)
{
	int fd;

	if (cb_st || !valid_map_arg(av[1]))
		return (0);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (perror(""), 0);
	(*cb_st)->map = NULL;
	(*cb_st)->map_h = 0;
	(*cb_st)->map_w = 0;
	(*cb_st)->no_texture = NULL;
	(*cb_st)->so_texture = NULL;
	(*cb_st)->we_texture = NULL;
	(*cb_st)->ea_texture = NULL;
	if (!extract_credantials(cb_st, fd))
		return (0);
	return (1);
}

int main(int ac, char **av)
{
	t_cub   *cub_st;

	cub_st = NULL;
	if (ac <= 1)
		return (printf("invalid arguments !"), 1);
	cub_st = malloc(sizeof(t_cub));
	if (!cub_st)
		return (printf("malloc failed !"), 1);
	if (!parse_arguments(&cub_st, av))
		return (1);
		printf("%s\n", cub_st->ea_texture);
	printf("%s\n", cub_st->no_texture);
	printf("%s\n", cub_st->so_texture);
	printf("%s\n", cub_st->we_texture);
	return (0);
}