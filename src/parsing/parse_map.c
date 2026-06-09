#include "../includes/cub3d.h"

/*
** read_line: reads one line from fd into a dynamically allocated buffer.
** Returns the line (caller frees), or NULL on EOF / error.
** Strips trailing newline.
*/
static char	*read_line(int fd)
{
	char	*buf;
	char	tmp;
	int		len;
	int		ret;
	char	*new;

	buf = malloc(1);
	if (!buf)
		return (NULL);
	buf[0] = '\0';
	len = 0;
	while ((ret = read(fd, &tmp, 1)) == 1 && tmp != '\n')
	{
		new = malloc(len + 2);
		if (!new)
		{
			free(buf);
			return (NULL);
		}
		memcpy(new, buf, len);
		new[len] = tmp;
		new[len + 1] = '\0';
		free(buf);
		buf = new;
		len++;
	}
	if (ret == 0 && len == 0)
	{
		free(buf);
		return (NULL);
	}
	return (buf);
}

/*
** count_players: counts N/S/E/W occurrences across the whole map.
*/
static int	count_players(char **map)
{
	int	count;
	int	y;
	int	x;

	count = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'S'
				|| map[y][x] == 'E' || map[y][x] == 'W')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

/*
** is_valid_char: returns 1 if c is an allowed map character.
*/
static int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == ' '
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

/*
** validate_chars: checks every character in the map is valid.
*/
static int	validate_chars(char **map)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (!is_valid_char(map[y][x]))
				return (ft_error(ERR_INV_LETTER));
			x++;
		}
		y++;
	}
	return (0);
}

/*
** cell_at: returns the character at (row, col), treating out-of-bounds as ' '.
*/
static char	cell_at(char **map, int rows, int row, int col)
{
	if (row < 0 || row >= rows)
		return (' ');
	if (col < 0 || col >= (int)strlen(map[row]))
		return (' ');
	return (map[row][col]);
}

/*
** flood_fill: fills reachable '0'/player cells from (row, col) with 'X'.
** Returns 1 if an open border is reached (map not closed).
*/
static int	flood_fill(char **map, int rows, int row, int col)
{
	char	c;

	c = cell_at(map, rows, row, col);
	if (c == ' ' || c == '\0')
		return (1);
	if (c == '1' || c == 'X')
		return (0);
	map[row][col] = 'X';
	if (flood_fill(map, rows, row - 1, col))
		return (1);
	if (flood_fill(map, rows, row + 1, col))
		return (1);
	if (flood_fill(map, rows, row, col - 1))
		return (1);
	if (flood_fill(map, rows, row, col + 1))
		return (1);
	return (0);
}

/*
** copy_map: duplicates a NULL-terminated map array.
*/
static char	**copy_map(char **map, int rows)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (rows + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < rows)
	{
		copy[i] = ft_strdup(map[i]);
		if (!copy[i])
		{
			free_split(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

/*
** find_start: finds the first walkable cell in the map.
*/
static void	find_start(char **map, int rows, int *row, int *col)
{
	int	y;
	int	x;

	y = 0;
	while (y < rows)
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '0' || map[y][x] == 'N' || map[y][x] == 'S'
				|| map[y][x] == 'E' || map[y][x] == 'W')
			{
				*row = y;
				*col = x;
				return ;
			}
			x++;
		}
		y++;
	}
}

/*
** validate_closed: ensures the map is fully enclosed by walls via flood fill.
** Returns 0 if closed, 1 if open.
*/
static int	validate_closed(t_config *cfg)
{
	char	**copy;
	int		start_row;
	int		start_col;
	int		result;

	copy = copy_map(cfg->map, cfg->map_height);
	if (!copy)
		return (ft_error(ERR_MALLOC));
	start_row = 0;
	start_col = 0;
	find_start(copy, cfg->map_height, &start_row, &start_col);
	result = flood_fill(copy, cfg->map_height, start_row, start_col);
	free_split(copy);
	if (result)
		return (ft_error(ERR_MAP_NO_WALLS));
	return (0);
}

/*
** validate_map: runs all map validation checks.
** Returns 0 if valid, 1 on error.
*/
int	validate_map(t_config *cfg)
{
	int	player_count;

	if (!cfg->map || cfg->map_height == 0)
		return (ft_error(ERR_MAP_MISSING));
	if (cfg->map_height < 3)
		return (ft_error(ERR_MAP_TOO_SMALL));
	if (validate_chars(cfg->map))
		return (1);
	player_count = count_players(cfg->map);
	if (player_count == 0)
		return (ft_error(ERR_PLAYER_DIR));
	if (player_count > 1)
		return (ft_error(ERR_NUM_PLAYER));
	if (validate_closed(cfg))
		return (1);
	return (0);
}

/*
** grow_map: appends a line to *lines, growing the array.
** Returns 0 on success, 1 on allocation failure.
*/
static int	grow_map(char ***lines, int *count, char *line)
{
	char	**new;
	int		i;

	new = malloc(sizeof(char *) * (*count + 2));
	if (!new)
		return (ft_error(ERR_MALLOC));
	i = 0;
	while (i < *count)
	{
		new[i] = (*lines)[i];
		i++;
	}
	new[*count] = ft_strdup(line);
	if (!new[*count])
	{
		free(new);
		return (ft_error(ERR_MALLOC));
	}
	new[*count + 1] = NULL;
	if (*lines)
		free(*lines);
	*lines = new;
	(*count)++;
	return (0);
}

/*
** compute_map_width: sets cfg->map_width to the longest row length.
*/
static void	compute_map_width(t_config *cfg)
{
	int	i;
	int	len;

	cfg->map_width = 0;
	i = 0;
	while (cfg->map[i])
	{
		len = ft_strlen(cfg->map[i]);
		if (len > cfg->map_width)
			cfg->map_width = len;
		i++;
	}
}

/*
** parse_map: reads the map section from fd starting with first_line.
** The map must be the last element in the .cub file.
** Returns 0 on success, 1 on error.
*/
int	parse_map(int fd, t_config *cfg, char *first_line)
{
	char	**lines;
	char	*line;
	int		count;

	lines = NULL;
	count = 0;
	if (grow_map(&lines, &count, first_line))
		return (1);
	while ((line = read_line(fd)) != NULL)
	{
		if (grow_map(&lines, &count, line))
		{
			free(line);
			free_split(lines);
			return (1);
		}
		free(line);
	}
	cfg->map = lines;
	cfg->map_height = count;
	compute_map_width(cfg);
	return (0);
}
