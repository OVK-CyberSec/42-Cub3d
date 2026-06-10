/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohifdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 16:56:49 by mohifdi           #+#    #+#             */
/*   Updated: 2026/06/10 16:56:50 by mohifdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

/*
** check_extension: verifies the file path ends with ".cub".
** Returns 0 if valid, 1 otherwise.
*/
static int	check_extension(const char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 5 || strcmp(path + len - 4, ".cub") != 0)
		return (ft_error(ERR_FILE_NOT_CUB));
	return (0);
}

/*
** check_all_set: verifies all mandatory identifiers were parsed before the map.
** Returns 0 if all present, 1 otherwise.
*/
static int	check_all_set(t_config *cfg)
{
	if (!cfg->tex_no || !cfg->tex_so || !cfg->tex_we || !cfg->tex_ea)
		return (ft_error(ERR_TEX_MISSING));
	if (cfg->floor_r == -1 || cfg->ceil_r == -1)
		return (ft_error(ERR_COLOR_MISSING));
	return (0);
}

/*
** read_line_fd: minimal single-char line reader.
** Returns a heap-allocated string (caller frees), or NULL on EOF.
*/
static char	*read_line_fd(int fd)
{
	char	*buf;
	char	tmp;
	int		len;
	int		ret;
	char	*new_buf;

	buf = malloc(1);
	if (!buf)
		return (NULL);
	buf[0] = '\0';
	len = 0;
	while ((ret = read(fd, &tmp, 1)) == 1 && tmp != '\n')
	{
		new_buf = malloc(len + 2);
		if (!new_buf)
		{
			free(buf);
			return (NULL);
		}
		memcpy(new_buf, buf, len);
		new_buf[len] = tmp;
		new_buf[len + 1] = '\0';
		free(buf);
		buf = new_buf;
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
** parse_cub_file: top-level parser.
**   1. Validates .cub extension.
**   2. Opens the file.
**   3. Reads identifier lines (NO/SO/WE/EA/F/C) until the map begins.
**   4. Delegates map reading to parse_map().
**   5. Validates the map.
** Returns 0 on success, 1 on any error.
*/
int	parse_cub_file(const char *path, t_config *cfg)
{
	int		fd;
	char	*line;
	int		ret;

	memset(cfg, 0, sizeof(t_config));
	cfg->floor_r = -1;
	cfg->floor_g = -1;
	cfg->floor_b = -1;
	cfg->ceil_r = -1;
	cfg->ceil_g = -1;
	cfg->ceil_b = -1;
	if (check_extension(path))
		return (1);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (ft_error(strerror(errno)));
	while ((line = read_line_fd(fd)) != NULL)
	{
		ret = handle_identifier(line, cfg);
		if (ret == 1)
		{
			free(line);
			close(fd);
			return (1);
		}
		if (ret == -1)
		{
			if (check_all_set(cfg))
			{
				free(line);
				close(fd);
				return (1);
			}
			if (parse_map(fd, cfg, line))
			{
				free(line);
				close(fd);
				return (1);
			}
			free(line);
			close(fd);
			return (validate_map(cfg));
		}
		free(line);
	}
	close(fd);
	return (ft_error(ERR_MAP_MISSING));
}
