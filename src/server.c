/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:58:58 by obajja            #+#    #+#             */
/*   Updated: 2025/03/12 13:05:02 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk.h>

static char	*str = 0;

char	*str_extender(char *s, char append)
{
	char	*extendo;
	char	*temp;
	int		len;

	temp = ft_strdup(s);
	free(s);
	if (temp)
		len = ft_strlen(temp);
	else
		len = 1;
	extendo = ft_calloc(len + 2, 1);
	ft_memcpy(extendo, temp, len);
	ft_strlcat(extendo, &append, len + 2);
	free(temp);
	return (extendo);
}

void	byte_aggregator(int sig, siginfo_t *info, void *txt)
{
	static char	byte = 0;
	static int	count = 0;

	(void)txt;
	if (sig == SIGUSR1)
		byte = byte << 1;
	else if (sig == SIGUSR2)
		byte = (byte << 1) | 1;
	count++;
	kill(info->si_pid, SIGUSR1);
	if (count == 8)
	{
		str = str_extender(str, byte);
		if (byte == '\0')
		{
			kill(info->si_pid, SIGUSR2);
			ft_printf("%s\n", str);
			free(str);
			str = ft_strdup("");
		}
		byte = 0;
		count = 0;
	}
}

void	listening(void)
{
	struct sigaction	ear;

	sigemptyset(&ear.sa_mask);
	ear.sa_sigaction = byte_aggregator;
	ear.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &ear, NULL);
	sigaction(SIGUSR2, &ear, NULL);
	while (1)
		pause();
	return ;
}

int	main(void)
{
	str = ft_strdup("");
	ft_printf("PID: %d\n", getpid());
	listening();
	return (0);
}
