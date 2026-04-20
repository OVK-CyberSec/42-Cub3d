


char	*get_map(int fd)
{
	char	*line_map;
	char	*buff;
	int		char_count;
	char	*tmp_buff;

	line_map = ft_strdup("");
	buff = ft_strdup("");
	char_count = gnl(fd, &line_map);
	if (char_count > 0)
	{
		tmp_buff = buff;
		while (char_count > 0)
		{
			buff = ft_strjoin(buff, line_map);
			free(tmp_buff);
			free(line_map);
			line_map = ft_strdup("");
			char_count = gnl(fd, &line_map);
			tmp_buff = buff;
		}
		return (buff);
	}
	ft_error("Error\nWrong lecture map\n");
	return (NULL);
}

void	*free_map(t_data *data)
{
	int		i;

	i = 0;
	while (data->map[i])
	{
		free(data->map[i]);
		i++;
	}
	free(data->map);
	data->map = NULL;
	return (0);
}

char	**parse_map(int fd, t_data *data)
{
	int		i;

	i = 1;
	data->map = ft_split(get_map(fd), '\n');
	check_content(data);
	if (!(check_dimension(data->map)))
		return (free_map(data));
	if (!(check_line(data->map[0], data->content.wall)))
		return (free_map(data));
	while (data->map[i] != NULL)
	{
		if (!(check_col(data->map[i], data->content.wall, data)))
			return (free_map(data));
		else if (!(check_exeption(data->map[i], &(data->content))))
			return (free_map(data));
		i++;
	}
	data->height = i;
	if (!(check_line(data->map[i - 1], data->content.wall)))
		return (free_map(data));
	return (data->map);
}

char	**map_core(char **str, t_data *data)
{
	int		fd;
	size_t	len;

	data->map = NULL;
	if (!str || !str[1])
		return (ft_error("Error\nMissing file path\n"));
	len = ft_strlen(str[1]);
	if (len < 4 || ft_strncmp(str[1] + len - 4, ".ber", 4) != 0)
		return (ft_error("Error\nInvalid file extension\n"));
	fd = open(str[1], O_RDONLY);
	if (fd < 0)
		return (ft_error("Error\nFailed to open file\n"));
	data->map = parse_map(fd, data);
	close(fd);
	if (!data->map)
		return (NULL);
	if (data->content.count_c == 0 || data->content.count_e != 1
		|| data->content.count_p != 1)
	{
		free_map(data);
		return (ft_error("Error\nNeed 1 Player/Exit and at least 1 Object\n"));
	}
	return (data->map);
}
