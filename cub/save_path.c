#include "cub.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	signe;
	int	nb;

	i = 0;
	signe = 1;
	nb = 0;
	while ((nptr[i] == ' ') || (nptr[i] >= '\a' && nptr[i] <= '\r'))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			signe = -signe;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = nb * 10;
		nb += nptr[i] - '0';
		i++;
	}
	return (nb * signe);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if ((unsigned char) s1[i] != (unsigned char)s2[i])
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		i++;
	}
	return (0);
}

int	count_split(char **tab)
{
	int	i = 0;

	while (tab[i])
		i++;
	return (i);
}

void	free_split(char **tab)
{
	int	i = 0;

	while (tab[i])
		free(tab[i++]);
	free(tab);
}


int	parse_color(char *str)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;

	rgb = ft_split(str, ',');
	if (!rgb || count_split(rgb) != 3)
		return (-1);

	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);

	free_split(rgb);

	if (r < 0 || r > 255
		|| g < 0 || g > 255
		|| b < 0 || b > 255)
		return (-1);

	return ((r << 16) | (g << 8) | b);
}

char	*ft_strtrim(char *tmp)
{
	int i = 0;
	int j = 0; 
	char *str;

	while (tmp[i])
		i++;

	str = malloc(sizeof(char) * (i - 1));
	if (!str)
		return NULL;
	while (j < i - 1)
	{
		str[j] = tmp[j];
		j++;
	}
	str[i] = '\0';
	return (str);
}

void	parse_line(t_minfo *info, char *line, char *tmp)
{
	tmp = strdup(line + 3);
	if (!strncmp(line, "NO ", 3))
		info->path_north = ft_strtrim(tmp);
	else if (!strncmp(line, "SO ", 3))
		info->path_south = ft_strtrim(tmp);
	else if (!strncmp(line, "WE ", 3))
		info->path_west = ft_strtrim(tmp);
	else if (!strncmp(line, "EA ", 3))
		info->path_east = ft_strtrim(tmp);
	else if (!ft_strncmp(line, "F ", 2))
		info->ground_color = parse_color(line + 2);
	else if (!ft_strncmp(line, "C ", 2))
		info->ceiling_color = parse_color(line + 2);
	if (tmp)
		free(tmp);
}

void freeminfo(t_minfo *s)
{
	free(s->path_north);
	free(s->path_south);
	free(s->path_east);
	free(s->path_west);
}

t_minfo	catch_path()
{
	t_minfo	info;
	char	*line;
	int		fd;
	
	fd = open("test.cub", O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		parse_line(&info, line, NULL);
		free(line);
	}
	return info;
}