/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:27:22 by jyriarte          #+#    #+#             */
/*   Updated: 2025/03/06 16:03:36 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// clang-format off
#include <stdio.h>
#include <readline/readline.h>
// clang-format on
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void	handle_int(int s)
{
	extern unsigned long	rl_readline_state;

	(void)s;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	if (rl_readline_state & RL_STATE_READCMD)
		rl_redisplay();
}

void	handle_quit(int s)
{
	(void)s;
	if (set_signal(SIGQUIT, SIG_IGN))
		return ;
	kill(0, SIGQUIT);
	write(STDOUT_FILENO, "Quit (core dumped)\n\0", 20);
}

void	handle_heredoc(int s)
{
	(void)s;
	rl_on_new_line();
	exit(1);
}

int	set_signal(int signal, void (*f)(int s))
{
	struct sigaction	sa;

	sa.sa_handler = f;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	if (sigaction(signal, &sa, NULL) == -1)
		return (1);
	return (0);
}
