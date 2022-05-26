#include "cub3d.h"

char	*ft_join(char *s1, char *s2)
{
	char	*result;
	int		s1_len;
	int		s2_len;
	int		i;

	if (!s1 && !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	result = malloc(s1_len + s2_len + 1);
	i = 0;
	while (i < s1_len)
		result[i] = s1[i++];
	i = 0;
	while (i < s2_len)
		result[s1_len++] = s2[i++];
	result[s1_len] = NULL;
	return result;
}

int read_cub_file(t_game *game, char *filename)
{
	int		fd;
	char	*add_prefix_dir_filename;

	add_prefix_dir_filename = ft_join("./map/", filename);
	fd = open(add_prefix_dir_filename, "O_RDONLY");
}
