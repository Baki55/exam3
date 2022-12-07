/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkhatib <bkhatib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 15:03:42 by bkhatib           #+#    #+#             */
/*   Updated: 2022/12/07 19:58:20 by bkhatib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int	width;
int	height;
char	backg_char;

char	type;
float	x;
float	y;
float	rad;
char	symb;

FILE *fd;
char **tab;
int	res;
float	sqr;

int	print_msg(FILE *fd, int error)
{
	if (fd)
		fclose(fd);
	if (error == 1)
		write(1, "Error: argument\n", 16);
	else if (error == 2)
	{
		write(1, "Error: Operation file corrupted\n", 32);
		return (1);
	}
	else
	{
		for (int i =0; i < height; i++)
		{
			write(1, tab[i], width);
			write(1, "\n", 1);
		}
	}
	return (error);
}

int	main(int argc, char **argv)
{
	fd = NULL;
	
	if (argc != 2)
		return(print_msg(fd, 1));
	if ((fd = fopen(argv[1], "r")) == NULL)
		return(print_msg(fd, 2));
	if ((res = fscanf(fd, "%d %d %c", &width, &height, &backg_char)) != 3)
		return (print_msg(fd, 2));
	if (width > 0 && width < 301 && height > 0 && height < 301)
	{
		tab = malloc(height * sizeof(char *));
		for (int i = 0; i < height; i++)
		{
			tab[i] = malloc (width * sizeof(char));
			memset(tab[i], backg_char, width);
		}
		while (1)
		{
			res = fscanf(fd, "%c %f %f %f %c", &type, &x, &y, &rad, &symb);
			if (res == -1)
				return(print_msg(fd, 0));
			else if (res != 5 || rad <= 0 || type != 'c' || type != 'C')
				break;
			for (int line = 0; line < height; line++)
			{
				for (int col = 0; col < width; col++)
				{
					sqr = sqrtf((col - x) * (col - x) + (line - y) * (line - y));
					if (sqr <= rad)
					{
						if (type == 'c' && sqr + 1 > rad)
							tab[line][col] = symb;
						if (type == 'C')
							tab[line][col] = symb;
					}
				}
			}
		}
	}
	print_msg(fd, 2);
}