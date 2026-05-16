#include "../includes/cub3d.h"

/*
** ft_error: prints "Error\n<msg>\n" to stderr and returns 1.
** Used everywhere a parse error must be reported.
*/
int	ft_error(const char *msg)
{
	write(2, "Error\n", 6);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	return (1);
}

/*
** ft_strlen: returns length of string s.
*/
int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

/*
** ft_strdup: duplicates string s, returns new allocation or NULL.
*/
char	*ft_strdup(const char *s)
{
	char	*dup;
	int		len;
	int		i;

	len = ft_strlen(s);
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

/*
** ft_strchr: returns pointer to first occurrence of c in s, or NULL.
*/
char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if ((unsigned char)*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)s);
	return (NULL);
}

/*
** ft_strtrim: returns a duplicate of s with leading/trailing whitespace removed.
** Caller must free the result.
*/
char	*ft_strtrim(const char *s)
{
	int		start;
	int		end;
	char	*result;

	if (!s)
		return (NULL);
	start = 0;
	end = ft_strlen(s) - 1;
	while (s[start] == ' ' || s[start] == '\t')
		start++;
	while (end > start && (s[end] == ' ' || s[end] == '\t'
			|| s[end] == '\n' || s[end] == '\r'))
		end--;
	result = malloc(end - start + 2);
	if (!result)
		return (NULL);
	memcpy(result, s + start, end - start + 1);
	result[end - start + 1] = '\0';
	return (result);
}

/*
** ft_atoi_strict: converts string s to int stored in *out.
** Returns 0 on success, 1 on failure (non-digit, out of [0,255], or empty).
*/
int	ft_atoi_strict(const char *s, int *out)
{
	int		i;
	long	n;

	i = 0;
	n = 0;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	if (!s[i])
		return (1);
	while (s[i] >= '0' && s[i] <= '9')
	{
		n = n * 10 + (s[i] - '0');
		if (n > 255)
			return (1);
		i++;
	}
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	if (s[i] != '\0' && s[i] != '\n')
		return (1);
	*out = (int)n;
	return (0);
}

/*
** free_split: frees a NULL-terminated array of strings.
*/
void	free_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

/*
** free_config: frees all heap-allocated members of cfg.
*/
void	free_config(t_config *cfg)
{
	if (!cfg)
		return ;
	if (cfg->tex_no)
		free(cfg->tex_no);
	if (cfg->tex_so)
		free(cfg->tex_so);
	if (cfg->tex_we)
		free(cfg->tex_we);
	if (cfg->tex_ea)
		free(cfg->tex_ea);
	if (cfg->map)
		free_split(cfg->map);
	cfg->tex_no = NULL;
	cfg->tex_so = NULL;
	cfg->tex_we = NULL;
	cfg->tex_ea = NULL;
	cfg->map = NULL;
}
