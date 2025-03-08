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

static int	readline_doc(int filefd, char *limiter, int expand_flag);
static int	expand_line(char **line, int expand_flag);
static int	fork_heredoc(t_parser *parser, int filefd, char *limiter);
static int	assign_fd(t_token *token, int filefd);

int	heredoc(t_parser *parser, t_token *token)
{
	int	filefd;

	filefd = open(TMP_HERE_DOC, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (filefd == -1)
		return (print_error1(ERR_OPEN, TMP_HERE_DOC, 1));
	if (fork_heredoc(parser, filefd, (char *)token->content))
	{
		free(token->content);
		token->content = NULL;
		if (close(filefd) == -1)
			print_error(ERR_CLOSEFD, 1);
		if (unlink(TMP_HERE_DOC) == -1)
			print_error1(ERR_UNLINK, TMP_HERE_DOC, 1);
		return (1);
	}
	if (close(filefd) == -1)
		print_error(ERR_CLOSEFD, 1);
	filefd = open(TMP_HERE_DOC, O_RDONLY);
	if (filefd == -1)
		return (print_error1(ERR_OPEN, TMP_HERE_DOC, 1));
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
		if (close(filefd) == -1)
			print_error(ERR_CLOSEFD, 1);
		if (unlink(TMP_HERE_DOC) == -1)
			print_error1(ERR_UNLINK, TMP_HERE_DOC, 1);
		return (print_error(ERR_MALLOC, 1));
	}
	*fd = filefd;
	token->content = fd;
	if (unlink(TMP_HERE_DOC) == -1)
		print_error1(ERR_UNLINK, TMP_HERE_DOC, 1);
	return (0);
}

static int	readline_doc(int filefd, char *limiter, int expand_flag)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			print_error3(WAR_EOF, " (wanted `", limiter, "')");
			break ;
		}
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

static int	fork_heredoc(t_parser *parser, int filefd, char *limiter)
{
	int		expand_flag;
	pid_t	pid;
	int		ret;

	expand_flag = has_quotes(limiter);
	remove_quotes(limiter);
	pid = fork();
	if (pid == 0)
	{
		if (set_signal(SIGINT, handle_heredoc))
		{
			ft_free_strs(parser->data->env);
			free_tokens(parser->tokens);
			rl_clear_history();
			exit(print_error(ERR_SIGACTION, 1));
		}
		ret = readline_doc(filefd, limiter, expand_flag);
		ft_free_strs(parser->data->env);
		free_tokens(parser->tokens);
		rl_clear_history();
		exit(ret);
	}
	waitpid(pid, &ret, 0);
	return (ret);
}

static int	expand_line(char **line, int expand_flag)
{
	char	*tmp;

	if (!expand_flag && ft_strlen(*line) != 0)
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
