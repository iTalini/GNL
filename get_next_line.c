/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurilen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 17:19:09 by akurilen          #+#    #+#             */
/*   Updated: 2018/02/04 17:19:12 by akurilen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static char		*where_n(int k, char *a, char *b)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	if (k == 1)
	{
		ret = ft_strjoin(a, b);
		ft_strdel(&a);
		ft_strdel(&b);
		return (ret);
	}
	while (b[j] != '\n' && b[j] != '\0')
		j++;
	ret = ft_strnew(j);
	while (b[i] != '\n' && b[i] != '\0')
	{
		ret[i] = b[i];
		i++;
	}
	ret[i] = '\0';
	ft_strdel(&a);
	return (ret);
}

static char		*after_n(char *n)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	while (n[i])
	{
		if (n[i] == '\n')
		{
			while (n[i + 1 + j])
				j++;
			ret = ft_strnew(j);
			j = 0;
			while (n[i + 1])
				ret[j++] = n[++i];
			ret[j] = '\0';
		}
		i++;
	}
	return (ret);
}

static int		get_append(int fd, int i, char **buf, char **line)
{
	char		*free;
	char		*temp;

	if (i == 1)
	{
		if (ft_strchr(buf[fd], '\n') == 0)
		{
			*line = ft_strdup(buf[fd]);
			ft_memdel((void **)&buf[fd]);
		}
		else
			get_append(fd, 0, buf, line);
		return (0);
	}
	free = buf[fd];
	free = where_n(0, 0, free);
	temp = ft_strdup(buf[fd]);
	*line = ft_strdup(free);
	ft_memdel((void **)&buf[fd]);
	buf[fd] = after_n(temp);
	ft_memdel((void **)&free);
	ft_memdel((void **)&temp);
	return (0);
}

static int		osn(char **buf, char *temp, char **line, int fd)
{
	char	*free;

	if (ft_strchr(temp, '\n') != 0)
	{
		if (buf[fd] != NULL)
		{
			free = where_n(0, 0, temp);
			buf[fd] = where_n(1, buf[fd], free);
		}
		else
			buf[fd] = ft_strdup(where_n(0, 0, temp));
		*line = ft_strdup(buf[fd]);
		ft_memdel((void **)&buf[fd]);
		buf[fd] = after_n(temp);
		ft_memdel((void **)&temp);
		return (1);
	}
	if (buf[fd] == NULL)
		buf[fd] = ft_strdup(temp);
	else
	{
		free = where_n(0, 0, temp);
		buf[fd] = where_n(1, buf[fd], free);
	}
	return (0);
}

int				get_next_line(int const fd, char **line)
{
	static char *buf[400000];
	char		*temp;

	temp = ft_strnew(BUFF_SIZE);
	if (line == NULL || fd < 0 || fd > 4096 || read(fd, temp, 0) == -1)
		return (-1);
	if (buf[fd] != NULL && buf[fd][0] != '\0')
	{
		if (ft_strchr(buf[fd], '\n') != 0 && get_append(fd, 0, buf, line) == 0)
			return (1);
		*line = ft_strdup(buf[fd]);
	}
	while (read(fd, temp, BUFF_SIZE) != 0)
	{
		if (osn(buf, temp, line, fd) == 1)
			return (1);
		ft_strclr(temp);
	}
	if (buf[fd] != NULL && buf[fd][0] != '\0')
		if (get_append(fd, 1, buf, line) == 0)
			return (1);
	ft_memdel((void **)&temp);
	ft_memdel((void **)&buf[fd]);
	*line = (void*)0;
	return (0);
}


int  main()
{
   int fd1;
   int fd2;
   int fd3;
   
   char    *line;

   int     check;
   int     count;

   fd1 = open("gnl1_1.txt", O_RDONLY);
   fd2 = open("gnl1_2.txt", O_RDONLY);
   fd3 = open("gnl1_3.txt", O_RDONLY);

   count = 1;
   check = 1;

   while (check != 0 && check != -1)
   {
       check = get_next_line(fd1, &line);
       printf("\nLine #%d: %s\nCheck is %d\n", count++, line, check);
       free(line);
       check = get_next_line(fd2, &line);
       printf("Line #%d: %s\nCheck is %d\n", count++, line, check);
       free(line);
       check = get_next_line(fd3, &line);
       printf("Line #%d: %s\nCheck is %d\n", count++, line, check);
       free(line);
   }
   return (0);
}
