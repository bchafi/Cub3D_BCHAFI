/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkali <bkali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 00:16:58 by bchafi            #+#    #+#             */
/*   Updated: 2026/01/15 05:43:48 by bkali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parcing.h"

static int	counter_words(char const *s, char c)
{
	int	i;
	int	count_words;

	i = 0;
	count_words = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			count_words++;
		i++;
	}
	return (count_words);
}

static void	free_str(int len, char **s)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free(s[i]);
		i++;
	}
	free(s);
}

char	**ft_other_split(char const *s, char c, t_var *var)
{
	int		i;
	int		index_word;
	int		len_word;
	char	**he;

	i = 0;
	he = (char **)malloc(((counter_words(s, c)) + 1) * sizeof(char *));
	if (!he)
		return (NULL);
	(1) && (var->count_rgb = counter_words(s, c), index_word = 0);
	while (s[i] && index_word < (counter_words(s, c)))
	{
		while (s[i] == c)
			i++;
		len_word = 0;
		while (s[i + len_word] != c && s[i + len_word] != '\0')
			len_word++;
		he[index_word] = ft_substr(s, i, len_word);
		if (!he[index_word])
			return (free_str(index_word, he), NULL);
		(1) && (i += len_word, index_word++);
	}
	he[index_word] = NULL;
	return (he);
}

char	**ft_split(char const *s, char c, t_var *var)
{
	if (!s)
		return (NULL);
	return (ft_other_split(s, c, var));
}

void	ft_free_alls(t_var *vars, t_unit *player)
{
	if (vars->map)
		free2d(vars->map);
	if (vars->map_s)
		free2d(vars->map_s);
	free_texture(vars);
	if (vars->read_file)
		free2d(vars->read_file);
	free(vars);
	if (player)
	{
		if (player->screen.img)
			mlx_destroy_image(player->mlx, player->screen.img);
		if (player->win)
			mlx_destroy_window(player->mlx, player->win);
		if (player->mlx)
			free(player->mlx);
	}
}
