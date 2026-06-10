/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajai <hajai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 08:28:42 by hajai             #+#    #+#             */
/*   Updated: 2025/05/26 09:29:57 by hajai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*extract_after_new(char *s)
{
	int		i;
	int		start;
	int		end;
	char	*str;

	i = 0;
	start = 0;
	if (!s || !*s)
		return (NULL);
	while (s[start] && s[start] != '\n')
		start++;
	if (!s[start] || !s[start + 1])
		return (NULL);
	start++;
	end = ft_strlen(s);
	str = malloc((end - start + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (s[start + i])
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	*handle_backslash(char *line, char **stockAfter, char *buf)
{
	char	*tmp;

	free(*stockAfter);
	*stockAfter = extract_after_new(line);
	tmp = find_backslash(line);
	free(line);
	free(buf);
	return (tmp);
}

static char	*read_and_build_line(int fd, char *line, char **stockAfter)
{
	char	*buf;
	char	*tmp;
	int		track;

	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (free(line), NULL);
	track = 1;
	while (track != 0)
	{
		track = read(fd, buf, BUFFER_SIZE);
		if (track < 0)
			return (free(buf), free(line), NULL);
		buf[track] = '\0';
		tmp = ft_strjoin(line, buf);
		free(line);
		if (!tmp)
			return (free(buf), NULL);
		line = tmp;
		if (is_backslash(line))
			return (handle_backslash(line, stockAfter, buf));
	}
	free(buf);
	return (line);
}

static char	*prepare_line(char **stockAfter)
{
	char	*line;

	if (*stockAfter)
	{
		line = ft_strdup(*stockAfter);
		free(*stockAfter);
		*stockAfter = NULL;
	}
	else
	{
		line = ft_strdup("");
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stockafter;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = prepare_line(&stockafter);
	if (!line)
		return (NULL);
	line = read_and_build_line(fd, line, &stockafter);
	if (!line || *line == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}
