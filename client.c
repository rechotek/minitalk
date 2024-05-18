/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrechuli <mrechuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 16:44:21 by mrechuli          #+#    #+#             */
/*   Updated: 2024/05/17 15:54:24 by mrechuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_sig(pid_t pid, char c)
{
	int	bit;

	bit = 0;
	while (bit <= 7)
	{
		if (1 & (c >> bit))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
		bit++;
	}
}

int	main(int argc, char *argv[])
{
	pid_t	pid;
	int		x;

	x = 0;
	if (argc != 3)
	{
		ft_printf("Error: Invaid format.\nUsage: %s <pid> <string>\n", argv[0]);
		return (1);
	}
	pid = ft_atoi(argv[1]);
	if (kill(pid, 0) == -1)
	{
		ft_printf("Error: Invalid PID\n");
		return (1);
	}
	while (argv[2][x])
	{
		send_sig(pid, argv[2][x]);
		x++;
	}
	send_sig(pid, '\n');
	return (0);
}
