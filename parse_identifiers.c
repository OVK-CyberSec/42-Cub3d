/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_identifiers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohifdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 16:57:03 by mohifdi           #+#    #+#             */
/*   Updated: 2026/06/10 16:57:04 by mohifdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

/*
** skip_spaces: advances pointer past spaces and tabs.
*/
static char	*skip_spaces(char *s)
{
	while (*s == ' ' || *s == '\t')
		s++;
	return (s);
}

/*
** check_xpm: verifies the path ends with ".xpm".
** Returns 0 if valid, 1 otherwise.
*/
static int	check_xpm(const char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 5 || strcmp(path + len - 4, ".xpm") != 0)
		return (ft_error(ERR_FILE_NOT_XPM));
	return (0);
}

/*
** parse_texture: extracts the path from a texture identifier line.
** e.g.: "NO ./path/to/texture.xpm"
** Stores a heap-allocated copy in *dest.
** Returns 0 on success, 1 on error.
*/
int	parse_texture(char *line, char **dest)
{
	char	*path;
	char	*trimmed;

	if (*dest)
		return (ft_error(ERR_TEX_INVALID));
	path = skip_spaces(line + 2);
	if (!*path)
		return (ft_error(ERR_TEX_MISSING));
	trimmed = ft_strtrim(path);
	if (!trimmed)
		return (ft_error(ERR_MALLOC));
	if (check_xpm(trimmed))
	{
		free(trimmed);
		return (1);
	}
	*dest = trimmed;
	return (0);
}

/*
** parse_color_component: parses one RGB component from *s,
** advances *s past the value and optional separator ','.
** Returns 0 on success, 1 on error.
*/
static int	parse_color_component(char **s, int *component)
{
	char	buf[16];
	int		i;

	i = 0;
	while (**s >= '0' && **s <= '9' && i < 15)
	{
		buf[i++] = **s;
		(*s)++;
	}
	buf[i] = '\0';
	if (i == 0)
		return (1);
	if (ft_atoi_strict(buf, component))
		return (1);
	if (**s == ',')
		(*s)++;
	return (0);
}

/*
** parse_color: parses a color line of the form "F 220,100,0" or "C 225,30,0".
** Stores the three components in *r, *g, *b.
** Returns 0 on success, 1 on error.
*/
int	parse_color(char *line, int *r, int *g, int *b)
{
	char	*s;

	if (*r != -1)
		return (ft_error(ERR_FLOOR_CEILING));
	s = skip_spaces(line + 1);
	if (parse_color_component(&s, r)
		|| parse_color_component(&s, g)
		|| parse_color_component(&s, b))
		return (ft_error(ERR_TEX_RGB_VAL));
	s = skip_spaces(s);
	if (*s != '\0' && *s != '\n')
		return (ft_error(ERR_FLOOR_CEILING));
	return (0);
}

/*
** handle_identifier: dispatches a line to the correct parser
** based on its leading identifier token (NO, SO, WE, EA, F, C).
** Returns  0 on success,
**          1 on parse error,
**         -1 if the line is not an identifier (start of map section).
*/
int	handle_identifier(char *line, t_config *cfg)
{
	char	*l;

	l = line;
	while (*l == ' ' || *l == '\t')
		l++;
	if (!*l || *l == '\n')
		return (0);
	if (l[0] == 'N' && l[1] == 'O' && (l[2] == ' ' || l[2] == '\t'))
		return (parse_texture(l, &cfg->tex_no));
	if (l[0] == 'S' && l[1] == 'O' && (l[2] == ' ' || l[2] == '\t'))
		return (parse_texture(l, &cfg->tex_so));
	if (l[0] == 'W' && l[1] == 'E' && (l[2] == ' ' || l[2] == '\t'))
		return (parse_texture(l, &cfg->tex_we));
	if (l[0] == 'E' && l[1] == 'A' && (l[2] == ' ' || l[2] == '\t'))
		return (parse_texture(l, &cfg->tex_ea));
	if (l[0] == 'F' && (l[1] == ' ' || l[1] == '\t'))
		return (parse_color(l, &cfg->floor_r, &cfg->floor_g, &cfg->floor_b));
	if (l[0] == 'C' && (l[1] == ' ' || l[1] == '\t'))
		return (parse_color(l, &cfg->ceil_r, &cfg->ceil_g, &cfg->ceil_b));
	return (-1);
}
