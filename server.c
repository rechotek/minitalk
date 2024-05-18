/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrechuli <mrechuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:18:47 by mrechuli          #+#    #+#             */
/*   Updated: 2024/05/17 16:01:48 by mrechuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_state	g_state = {0, 0};

void	sig_1(int sig)
{
	(void)sig;
	g_state.character |= (1 << g_state.index);
	g_state.index++;
	if (g_state.index == 8)
	{
		write (1, &g_state.character, 1);
		g_state.character = 0;
		g_state.index = 0;
	}
}

void	sig_2(int sig)
{
	(void)sig;
	g_state.index++;
	if (g_state.index == 8)
	{
		write (1, &g_state.character, 1);
		g_state.character = 0;
		g_state.index = 0;
	}
}

void	setup_signal_handler(void)
{
	struct sigaction	sa1;
	struct sigaction	sa2;

	sa1.sa_handler = sig_1;
	sigemptyset(&sa1.sa_mask);
	sa1.sa_flags = 0;
	sa2.sa_handler = sig_2;
	sigemptyset(&sa2.sa_mask);
	sa2.sa_flags = 0;
	sigaction(SIGUSR1, &sa1, NULL);
	sigaction(SIGUSR2, &sa2, NULL);
}

int	main(void)
{
	pid_t	pid;

	pid = getpid();
	ft_printf("Your PID: %d\n", pid);
	setup_signal_handler();
	while (1)
	{
	}
	return (0);
}
