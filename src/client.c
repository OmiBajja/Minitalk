/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:58:53 by obajja            #+#    #+#             */
/*   Updated: 2025/03/12 12:51:10 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk.h>

int	ft_atoi(const char *str)
{
	int	i;
	int	n;
	int	s;

	i = 0;
	n = 0;
	s = 1;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == ' '))
	{
		i++;
	}
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			s *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + (str[i] - '0');
		i++;
	}
	return (n * s);
}

void	listener(int sig)
{
	if (sig == SIGUSR1)
		return ;
	else if (sig == SIGUSR2)
		exit(1);
}

void	confirmation(void)
{
	struct sigaction	ear;

	sigemptyset(&ear.sa_mask);
	ear.sa_handler = listener;
	ear.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &ear, NULL);
	sigaction(SIGUSR2, &ear, NULL);
}
void	end_printer(int PID)
{
	int		byte;
	char	text;
	int		encoded;

	text = '\0';
	byte = 7;
	while (byte >= 0)
	{
		encoded = (text >> byte) & 1;
		if (encoded == 0)
			kill(PID, SIGUSR1);
		if (encoded == 1)
			kill(PID, SIGUSR2);
		confirmation();
		pause();
		usleep(100);
		byte--;
	}
}

void	byte_printer(int PID, char *text)
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
			encoded = (text[i] >> byte) & 1;
			if (encoded == 0)
				kill(PID, SIGUSR1);
			if (encoded == 1)
				kill(PID, SIGUSR2);
			confirmation();
			pause();
			usleep(100);
			byte--;
		}
		i++;
	}
	end_printer(PID);
	return ;
}

int	main(int argc, char **argv)
{
	int PID;
	int i;

	i = 0;
	(void)argc;
	PID = ft_atoi(argv[1]);
	byte_printer(PID, argv[2]);
	return (0);
}