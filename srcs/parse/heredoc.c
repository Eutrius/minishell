/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:07:52 by jyriarte          #+#    #+#             */
/*   Updated: 2025/03/05 12:17:11 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
// clang-format off
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
// clang-format on
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>

static int	heredoc(int filefd, char *limiter);
static int	has_quotes(char *limiter);
static int	expand_line(char **line, int expand_flag);
static int	assign_fd(t_token *token, int filefd);

int	parse_heredoc(t_token *token)
{
	int	filefd;

	filefd = open(".bashbros_tmp", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (filefd == -1)
	{
		perror("bashbros: open:");
		return (1);
	}
	if (heredoc(filefd, (char *)token->content))
	{
		free(token->content);
		token->content = NULL;
		close(filefd);
		return (1);
	}
	close(filefd);
	filefd = open(".bashbros_tmp", O_RDONLY);
	if (filefd == -1)
	{
		perror("bashbros: open:");
		return (1);
	}
	return (assign_fd(token, filefd));
}

static int	assign_fd(t_token *token, int filefd)
{
	int	*fd;

	free(token->content);
	token->content = NULL;
	fd = malloc(sizeof(int));
	if (fd == NULL)
	{
		close(filefd);
		if (unlink(".bashbros_tmp") == -1)
			perror("bashbros: unlink:");
		return (print_error(ERR_MALLOC));
	}
	*fd = filefd;
	token->content = fd;
	if (unlink(".bashbros_tmp") == -1)
		perror("bashbros: unlink:");
	return (0);
}

static int	heredoc(int filefd, char *limiter)
{
	char	*line;
	int		expand_flag;

	expand_flag = !has_quotes(limiter);
	remove_quotes(limiter);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, limiter) == 0)
			break ;
		if (expand_line(&line, expand_flag))
			return (1);
		ft_putstr_fd(line, filefd);
		ft_putchar_fd('\n', filefd);
		free(line);
	}
	free(line);
	return (0);
}

static int	expand_line(char **line, int flag)
{
	char	*tmp;

	if (flag)
	{
		tmp = expand_var(*line);
		if (tmp == NULL)
		{
			free(*line);
			return (1);
		}
		free(*line);
		*line = tmp;
	}
	return (0);
}

static int	has_quotes(char *limiter)
{
	int	i;

	i = 0;
	while (limiter[i] != '\0')
	{
		if (is_quote(limiter[i]) && is_dquote(limiter[i]))
			return (1);
		i++;
	}
	return (0);
}
