/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 00:30:42 by user42            #+#    #+#             */
/*   Updated: 2020/10/04 13:55:55 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm.h"

void test_strlen(char *str)
{
	printf("str : \"%s\"\n", str);
	printf("strlen ret :\t\t%lu\n", strlen(str));
	printf("ft_strlen ret :\t\t%lu\n", ft_strlen(str));
	printf("\n");
}

void test_strcpy(char *src)
{
	char dst[512];

	printf("str : \"%s\"\n", src);
	bzero(dst, 512);
	printf("strcpy ret :\t\t\"%s\"\n", strcpy(dst, src));
	bzero(dst, 512);
	printf("ft_strcpy ret :\t\t\"%s\"\n", ft_strcpy(dst, src));
	printf("\n");
}

void test_strcmp(char *dst, char *src)
{
	printf("dst : \"%s\" | src : \"%s\"\n", dst, src);
	printf("strcmp ret :\t\t%d\n", strcmp(dst, src));
	printf("ft_strcmp ret :\t\t%d\n", ft_strcmp(dst, src));
	printf("\n");
}

void test_write(int fd, char *str)
{
	int ret;
	int err;

	err = errno = 0;
	ret = write(fd, str, strlen(str));
	err = errno;
	printf("write ret :\t\t%d\nerrno : \t\t%s\n", ret, strerror(err));
	
	err = errno = 0;
	ret = ft_write(fd, str, strlen(str));
	err = errno;
	printf("ft_write ret :\t\t%d\nerrno : \t\t%s\n", ret, strerror(err));
	printf("\n");
}

void test_read(int fd, char *file, int oflag, char *buff, int buff_size)
{
	int ret;
	int err;

	printf("fd : %d | file : %s | oflag : %d | buff_size : %d\n", fd, file, oflag, buff_size);

	bzero(buff, buff_size);
	if (file)
		fd = open(file, oflag);
	err = errno = 0;
	ret = read(fd, buff, buff_size);
	err = errno;
	printf("\nread ret :\t\t%d\n", ret);
	if (ret >= 0)
		printf("reads :\t\t\t\"%s\"\n", buff);
	printf("error :\t\t\t%s\n", strerror(err));
	if (file)
		close(fd);

	bzero(buff, buff_size);
	if (file)
		fd = open(file, oflag);
	err = errno = 0;
	ret = ft_read(fd, buff, buff_size);
	err = errno;
	printf("\nft_read ret :\t\t%d\n", ret);
	if (ret >= 0)
		printf("reads :\t\t\t\"%s\"\n", buff);
	printf("error :\t\t\t%s\n", strerror(err));
	printf("\n");
	if (file)
		close(fd);
}

void test_strdup(char *str)
{
	char *dup;
	
	printf("str : \"%s\" of address : %p\n", str, &str);

	dup = strdup(str);
	printf("strdup duplicate :\t\"%s\"\tof address : %p\n", dup, &dup);
	free(dup);
	
	dup = ft_strdup(str);
	printf("ft_strdup duplicate :\t\"%s\"\tof address : %p\n", dup,  &dup);
	free(dup);
	printf("\n");
}

int	main(int argc, char **argv)
{
	if (argc < 1 || argc > 2 )
		return (-1);
		
	if (argc == 1 || strcmp("strlen", argv[1]) == 0)
	{
		printf("\n>--------------| strlen |--------------<\n");
		
		test_strlen("");
		test_strlen("a");
		test_strlen("azertyuiop");
	}

	if (argc == 1 || strcmp("strcmp", argv[1]) == 0)
	{
		printf("\n>--------------| strcmp |--------------<\n");

		test_strcmp("", "");
		test_strcmp("azertyuiop", "azertyuiop");
		test_strcmp("azertyuiop", "azerty");
		test_strcmp("azerty", "azertyuiop");
	}

	if (argc == 1 || strcmp("strcpy", argv[1]) == 0)
	{
		printf("\n>--------------| strcpy |--------------<\n");

		test_strcpy("");
		test_strcpy("a");
		test_strcpy("azertyuiop");
	}

	if (argc == 1 || strcmp("write", argv[1]) == 0)
	{
		int fd;
		
		printf("\n>--------------| write |--------------<\n");

		test_write(STDOUT_FILENO, "Hello world !\n");
		test_write(STDOUT_FILENO, "");
		test_write(-50, "Hello world !\n");

		if ((fd = open("test_file.txt", O_RDONLY)) == -1)
			return(-1);
		test_write(fd, "Hello world !\n");
		close(fd);
		
		if ((fd = open("test_file.txt", O_WRONLY)) == -1)
			return(-1);
		test_write(fd, "Hello world !\n");
		close(fd);
	}
	
	if (argc == 1 || strcmp("read", argv[1]) == 0)
	{
		char buff[512];
		
		printf("\n>--------------| read |--------------<\n");
		test_read(STDIN_FILENO, 0, 0, buff, 20);
		test_read(-50, 0, 0, buff, 20);
		test_read(0, "test_file.txt", O_RDONLY, buff, 20);
		test_read(0, "test_file.txt", O_WRONLY, buff, 20);
	}

	if (argc == 1 || strcmp("strdup", argv[1]) == 0)
	{
		printf("\n>--------------| strdup |--------------<\n");
		
		test_strdup("");
		test_strdup("Hello world !");
	}
	
	return (0);
}