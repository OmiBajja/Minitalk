/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:58:58 by obajja            #+#    #+#             */
/*   Updated: 2025/03/12 22:47:19 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk.h>

static char	*str = 0;

char	*str_extender(char append)
{
	char	*extendo;
	char	*temp;
	int		len;

	temp = ft_strdup(str);
	free(str);
	if (temp)
		len = ft_strlen(temp);
	else
		len = 1;
	extendo = ft_calloc(len + 2, 1);
	ft_memcpy(extendo, temp, len);
	extendo[len] = append;
	free(temp);
	return (extendo);
}

void	byte_aggregator(int sig, siginfo_t *info, void *txt)
{
	static char	byte = 0;
	static int	count = 0;

	(void)txt;
	if (!str)
		str = ft_calloc(2,1);
	byte <<= 1;
	if (sig  == SIGUSR2)
		byte |= 1;
	count++;
	if (count == 8)
	{
		str = str_extender(byte);
		if (byte == '\0')
		{
			ft_printf("%s\n", str);
			byte = 0;
			count = 0;
			free(str);
			str = NULL;
			usleep(100);
			kill(info->si_pid, SIGUSR2);
			return ;
		}
		byte = 0;
		count = 0;
	}
	usleep(100);
	kill(info->si_pid, SIGUSR1);
}

void	listening(void)
{
	struct sigaction	ear;

	sigemptyset(&ear.sa_mask);
	ear.sa_sigaction = byte_aggregator;
	ear.sa_flags = SA_RESTART | SA_SIGINFO;
	sigaction(SIGUSR1, &ear, NULL);
	sigaction(SIGUSR2, &ear, NULL);
	while (1)
		pause();
	return ;
}

int	main(void)
{
	ft_printf("PID: %d\n", getpid());
	listening();
	return (0);
}
