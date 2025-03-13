/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:58:53 by obajja            #+#    #+#             */
/*   Updated: 2025/03/13 10:29:15 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk.h>

int		g_ok = 0;

void	listener(int sig)
{
	if (sig == SIGUSR1)
		g_ok = 1;
	else
		exit(0);
}

void	end_printer(int pid)
{
	int		byte;
	char	text;
	int		encoded;

	text = '\0';
	byte = 7;
	while (byte >= 0)
	{
		g_ok = 0;
		encoded = (text >> byte) & 1;
		if (encoded == 0)
			kill(pid, SIGUSR1);
		if (encoded == 1)
			kill(pid, SIGUSR2);
		while (!g_ok)
			pause();
		byte--;
	}
}

void	byte_printer(int pid, char *text)
{
	int	i;
	int	byte;
	int	encoded;

	i = 0;
	while (text[i])
	{
		byte = 7;
		while (byte >= 0)
		{
			g_ok = 0;
			encoded = (text[i] >> byte) & 1;
			if (encoded == 0)
				kill(pid, SIGUSR1);
			else if (encoded == 1)
				kill(pid, SIGUSR2);
			byte--;
			while (!g_ok)
				pause();
		}
		i++;
	}
	end_printer(pid);
	return ;
}

int	main(int argc, char **argv)
{
	int					pid;
	int					i;
	struct sigaction	ear;

	if (argc != 3)
		return (1);
	i = 0;
	sigemptyset(&ear.sa_mask);
	ear.sa_handler = listener;
	ear.sa_flags = SA_RESTART;
	sigaction(SIGUSR1, &ear, NULL);
	sigaction(SIGUSR2, &ear, NULL);
	while (argv[1][i])
	{	
		if (!ft_isdigit(argv[1][i]))
			return (1);
		i++;
	}
	pid = ft_atoi(argv[1]);
	if (pid < 0 || kill(pid, 0) == -1)
		return (1);
	byte_printer(pid, argv[2]);
	return (0);
}
