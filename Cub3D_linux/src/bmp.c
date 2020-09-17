/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 12:46:36 by prebeca           #+#    #+#             */
/*   Updated: 2020/06/17 12:39:01 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	*reverse(char *str, size_t len, int line_size)
{
	size_t			i;
	unsigned char	*tmp;

	tmp = malloc(sizeof(unsigned char) * line_size);
	--len;
	i = 0;
	while (i < len - i)
	{
		ft_memcpy(tmp, str + i * line_size, line_size);
		ft_memcpy(str + i * line_size, str + (len * line_size - i * line_size),
		line_size);
		ft_memcpy(str + (len * line_size - i * line_size), tmp, line_size);
		++i;
	}
	free(tmp);
	return (str);
}

static void	bmp_basic_header(unsigned char *header, unsigned int file_size)
{
	header[0] = 'B';
	header[1] = 'M';
	header[2] = file_size;
	header[3] = file_size >> 8;
	header[4] = file_size >> 16;
	header[5] = file_size >> 24;
	header[10] = BMP_HEADER_OFFSET;
	header[11] = BMP_HEADER_OFFSET >> 8;
	header[12] = BMP_HEADER_OFFSET >> 16;
	header[13] = BMP_HEADER_OFFSET >> 24;
}

static void	bmp_dib_header(unsigned char *header, t_img *img)
{
	header[14] = BMP_DIBHEADER_SIZE;
	header[15] = BMP_DIBHEADER_SIZE >> 8;
	header[16] = BMP_DIBHEADER_SIZE >> 16;
	header[17] = BMP_DIBHEADER_SIZE >> 24;
	header[18] = img->width;
	header[19] = img->width >> 8;
	header[20] = img->width >> 16;
	header[21] = img->width >> 24;
	header[22] = img->height;
	header[23] = img->height >> 8;
	header[24] = img->height >> 16;
	header[25] = img->height >> 24;
	header[26] = BMP_COLOR_PLANE;
	header[27] = BMP_COLOR_PLANE >> 8;
	header[28] = img->bpp;
	header[29] = img->bpp >> 8;
}

static int	bmp_write_header(unsigned char *header,
	unsigned int img_size, t_img *img)
{
	int		fd;
	void	*buffer;

	if ((buffer = malloc(sizeof(unsigned char) * img_size)) == 0)
		return (-1);
	buffer = ft_memcpy(buffer, img->data_address, img_size);
	buffer = reverse(buffer, img->height, img->line_size);
	if ((fd = open("save.bmp", O_WRONLY)) == -1)
		return (-1);
	write(fd, header, BMP_HEADER_OFFSET);
	write(fd, buffer, img_size);
	free(buffer);
	close(fd);
	return (0);
}

int			img_to_bmp(t_img *img)
{
	int				fd;
	unsigned char	header[BMP_HEADER_OFFSET];
	unsigned int	file_size;
	int				img_size;

	ft_bzero(header, BMP_HEADER_OFFSET);
	if ((fd = open("save.bmp", O_CREAT, S_IRWXU)) == -1)
		return (-1);
	close(fd);
	if ((fd = open("save.bmp", O_TRUNC)) == -1)
		return (-1);
	close(fd);
	img_size = img->width * img->height * (img->bpp / 8);
	file_size = img_size + BMP_HEADER_OFFSET;
	bmp_basic_header(header, file_size);
	bmp_dib_header(header, img);
	return (bmp_write_header(header, img_size, img));
}
