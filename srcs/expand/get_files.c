/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 22:04:27 by jyriarte          #+#    #+#             */
/*   Updated: 2025/03/04 12:30:41 by jyriarte         ###   ########.fr       */
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

char	**get_files(int hidden)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**res;

	dir = opendir(".");
	if (dir == NULL)
	{
		perror("b_bros: opendir:");
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
	// closedir(dir);
	sort_files(res);
	return (res);
}

static int	check_entry(struct dirent *entry, char ***res, int hidden)
{
	if (entry == NULL)
	{
		if (errno != 0)
			perror("b_bros: readdir:");
		else
			return (1);
	}
	else
	{
		if (hidden && entry->d_name[0] == '.')
		{
			*res = ft_strscat(*res, entry->d_name);
			if (*res == NULL)
				print_error(ERR_MALLOC);
		}
		else if (!hidden && entry->d_name[0] != '.')
		{
			*res = ft_strscat(*res, entry->d_name);
			if (*res == NULL)
				print_error(ERR_MALLOC);
		}
	}
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
