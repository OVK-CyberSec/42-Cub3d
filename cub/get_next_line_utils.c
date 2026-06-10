/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajai <hajai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 08:28:54 by hajai             #+#    #+#             */
/*   Updated: 2025/05/26 09:29:59 by hajai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(char *s)
{
	char	*str;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(s);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*find_backslash(char *s)
{
	int		i;
	int		start;
	char	*str;

	i = 0;
	start = 0;
	while (s[i] != '\n' && s[i])
		i++;
	str = malloc((i + 2) * sizeof(char));
	if (!str)
		return (NULL);
	while (start < i + 1)
	{
		str[start] = s[start];
		start++;
	}
	str[start] = '\0';
	return (str);
}

int	is_backslash(char *tmp)
{
	int	i;

	i = 0;
	while (tmp[i] != '\0' && tmp[i])
	{
		if (tmp[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (s1[i] != '\0' && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (j < ft_strlen(s2))
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}
