/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 22:04:27 by jyriarte          #+#    #+#             */
/*   Updated: 2025/03/05 12:17:31 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <dirent.h>
#include <errno.h>
#include <stdio.h>

static int	cmp_files(char *str1, char *str2);
static void	sort_files(char **sorted_exp);
static int	check_entry(struct dirent *entry, char ***res, int hidden);
static int	check_filename(char *filename, int hidden);

char	**get_files(int hidden)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**res;

	dir = opendir(".");
	if (dir == NULL)
	{
		perror("bashbros: opendir:");
		return (NULL);
	}
	res = ft_calloc(1, sizeof(char *));
	if (res == NULL)
		print_error(ERR_MALLOC);
	while (res != NULL)
	{
		entry = readdir(dir);
		if (check_entry(entry, &res, hidden))
			break ;
	}
	closedir(dir);
	sort_files(res);
	return (res);
}

static int	check_entry(struct dirent *entry, char ***res, int hidden)
{
	char	*filename;

	if (entry == NULL)
	{
		if (errno != 0)
			perror("bashbros: readdir:");
		return (1);
	}
	else
	{
		if (check_filename(entry->d_name, hidden))
			return (0);
		filename = ft_strdup(entry->d_name);
		if (filename == NULL)
		{
			ft_free_strs(*res);
			print_error(ERR_MALLOC);
		}
		*res = ft_strscat(*res, filename);
		if (*res == NULL)
			print_error(ERR_MALLOC);
	}
	return (0);
}

static int	check_filename(char *filename, int hidden)
{
	if (hidden && filename[0] != '.')
		return (1);
	else if (!hidden && filename[0] == '.')
		return (1);
	return (0);
}

static void	sort_files(char **sorted_exp)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while (sorted_exp[i])
	{
		j = i + 1;
		while (sorted_exp[j])
		{
			if (cmp_files(sorted_exp[i], sorted_exp[j]) > 0)
			{
				tmp = sorted_exp[i];
				sorted_exp[i] = sorted_exp[j];
				sorted_exp[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static int	cmp_files(char *str1, char *str2)
{
	int	i;
	int	char1;
	int	char2;

	i = 0;
	while (1)
	{
		char1 = str1[i];
		if (char1 >= 'A' && char1 <= 'Z')
			char1 += 32;
		char2 = str2[i];
		if (char2 >= 'A' && char2 <= 'Z')
			char2 += 32;
		if (char1 == '\0' || char2 == '\0' || char1 != char2)
			break ;
		i++;
	}
	return (char1 - char2);
}
