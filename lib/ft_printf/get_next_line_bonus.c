/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemorais <jemorais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:14:34 by jemorais          #+#    #+#             */
/*   Updated: 2025/02/10 14:25:29 by jemorais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	*read_line[1024];
	char		*buffer;
	char		*remainder;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (read_line[fd] == NULL)
		read_line[fd] = ft_strdup("");
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (free(read_line[fd]), read_line[fd] = NULL);
	read_line[fd] = ft_receive_buffer(fd, buffer, read_line[fd]);
	if (read_line[fd] == NULL)
		return (NULL);
	line = ft_line(read_line[fd]);
	remainder = ft_strdup(read_line[fd] + ft_strlen(line));
	free(read_line[fd]);
	read_line[fd] = remainder;
	return (line);
}

char	*ft_line(char *read_line)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (read_line[i] != '\n' && read_line[i])
		i++;
	if (read_line[i] == '\n')
		i++;
	line = malloc(i + 1);
	while (j < i)
	{
		line[j] = read_line[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

char	*ft_receive_buffer(int fd, char *buffer, char *read_line)
{
	char	*temp;
	int		bytes_read;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0 || (!*read_line && bytes_read == 0))
			return (free(buffer), free(read_line), read_line = NULL);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(read_line, buffer);
		free(read_line);
		read_line = temp;
		if (ft_strchr(read_line, '\n') != NULL)
			break ;
	}
	free(buffer);
	return (read_line);
}

// // #include <stdio.h>
// // #include <fcntl.h>

// // int	main(void)
// // {
// // 	char	*line;
// // 	int		fd;

// // 	fd = open("lifesdog.txt", O_RDONLY);
// // 	if (fd == -1)
// // 	{
// // 		perror("ERROR");
// // 		return (1);
// // 	}
// // 	while ((line = get_next_line(fd)) != NULL)
// // 	{
// // 		printf("call is:%s", line);
// // 		free(line);
// // 	}
// // 	close(fd);
// // 	return (0);
// // }

// // // cc -Wall -Wextra -Werror -D BUFFER_SIZE=42
// // // get_next_line_bonus.c get_next_line_utils_bonus.c get_next_line_bonus.h

// #include <stdio.h>
// #include <fcntl.h>
// int main()
// {
// 	char *line;
// 	int fd1;
// 	int fd2;
// 	int i = 1;
// 	int j = 1;

// 	printf("BUFFER_SIZE:%d\n", BUFFER_SIZE);

// 	printf("\nFIRST TEST\n");
// 	fd1 = open("copy.txt", O_RDONLY);
// 	while (i < 5)
// 	{
// 		line = get_next_line(fd1);
// 		printf("call %d is:%s", i, line);
// 		free(line);
// 		i++;
// 	}

// 	printf("\nSECOND TEST\n");
// 	fd2 = open("line.txt", O_RDONLY);
// 	while (j < 6)
// 	{
// 		line = get_next_line(fd2);
// 		if (ft_strchr(line, '\n') == 0)
// 			printf("call %d is:%s\n", j, line);
// 		else
// 			printf("call %d is:%s", j, line);
// 		free(line);
// 		j++;
// 	}

// 	printf("\nFIRST TEST AGAIN\n");
// 	while ((line = get_next_line(fd1)) != NULL)
// 	{
// 		printf("call %d is:%s", i, line);
// 		free(line);
// 		i++;
// 	}
// 	close(fd1);

// 	printf("\nSECOND TEST AGAIN\n");
// 	while ((line = get_next_line(fd2)) != NULL)
// 	{
// 		if (ft_strchr(line, '\n') == 0)
// 			printf("call %d is:%s\n", j, line);
// 		else
// 			printf("call %d is:%s", j, line);
// 		free(line);
// 		j++;
// 	}
// 	close(fd2);

// 	printf("\nTHIRD TEST\n");
// 	printf("negative fd:%s\n", get_next_line(fd1));

// 	printf("\nFOURTH TEST\n");
// 	fd1 = open("text copy.txt", O_RDONLY);
// 	close(fd1);
// 	printf("close fd:%s\n", get_next_line(fd1));
// }
