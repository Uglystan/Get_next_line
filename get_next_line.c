/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 04:01:17 by lgirault          #+#    #+#             */
/*   Updated: 2023/04/03 17:47:36 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

int	ft_strchr(char *temp, char c)
{
	int	i;

	i = 0;
	while (temp[i] != '\0')
	{
		if (temp[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_strlen(char *str)
{
	int	i;
	
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	size_no_nl(char *temp, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (temp[i] == -1)
		i++;
	while (temp[i] != c)
	{
		i++;
		j++;
	}
	return (j);
}

void	init_temp(char * temp)
{
	int	i;

	 i = 0;
	 while (temp[i] != '\n' && temp[i] != '\0')
	{
		temp[i] = -1;
		i++;
	}
	if (temp[i] == '\n')
		temp[i] = -1;
}

char	*join(char *buff, char *temp)
{
	int	i;
	int	j;
	char	*new_buff;

	i = 0;
	j = 0;
	new_buff = malloc(sizeof(char) * (ft_strlen(buff) + size_no_nl(temp, '\0') + 1));// + pour /0
	while (buff[j] != '\0')
	{
		new_buff[j] = buff[j];
		j++;
	}
	while (temp[i] == -1)
		i++;
	while (temp[i] != '\0' && temp[i] != -1)
	{
		new_buff[j] = temp[i];
		i++;
		j++;
	}
	new_buff[j] = '\0';
	free(buff);
	init_temp(temp);
	return (new_buff);
	
}

char	*newline(char *buff, char *temp)
{
	int	i;
	int	j;
	char	*new_buff;

	i = 0;
	j = 0;
	new_buff = malloc(sizeof(char) * (ft_strlen(buff) +  size_no_nl(temp, '\n') + 2));//+ pour /n et + pour /0
	while (buff[j] != '\0')
	{
		new_buff[j] = buff[j];
		j++;
	}
	while (temp[i] == -1)
		i++;
	while (temp[i] != '\n')
	{
		new_buff[j] = temp[i];
		i++;
		j++;
	}
	new_buff[j] = '\n';
	j++;
	new_buff[j] = '\0';
	free(buff);
	init_temp(temp);
	return (new_buff);
}

int	only_one(char *temp)
{
	int	i;

	i = 0;
	while (temp[i] != '\0')
	{
		if (temp[i] != -1)
			return (1);
		i++;
	}
	return (0);
}

char	*get_next_line(int fd)//temp premier cara /n pb
{
	static char	temp[BUFFER_SIZE + 1];
	char	*line;
	
	if (fd == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	line = malloc(sizeof(char) * 1);
	line[0] = '\0';
	while (1)
	{
		if (only_one(temp) == 0)
			if (read(fd, temp, BUFFER_SIZE) == 0)
				break ;
		if (ft_strchr(temp, '\n') == 0)//pas de \n
			line = join(line, temp);
		else if (ft_strchr(temp, '\n') == 1)//\n
		{
			line = newline(line, temp);
			break;
		}
	}
	if (line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}

int    main(void)
{
    int    fd;
    char    *t;
    int    i;
    int j = 2;

    i = 0;

    fd = open("test.txt", O_RDONLY);
    t = malloc(sizeof(char) * 1);
    printf("%c\n", -1);
    t[0] = '\0';
    while (i != j)
    {
      	free(t);
        printf("APPEL %d :\n", i);
        t = get_next_line(fd);
        printf("%s", t);
        i++;
    }
	free(t);
}