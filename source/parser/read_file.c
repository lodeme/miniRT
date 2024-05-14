/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:27:28 by ubazzane          #+#    #+#             */
/*   Updated: 2024/05/14 16:56:48 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static char	*read_file(char *str);
static char	***split_parameters(char *file);
static void	append_line(char *line, char **file);
static void	external_free(char *file, char **split_lines, char *str);

char	***extract_content(char *str)
{
	char	***objects;
	char	*file;

	file = read_file(str);
	objects = split_parameters(file);
	check_objs(objects);
	return (objects);
}

static char	*read_file(char *str)
{
	char	*file;
	char	*line;
	int		fd;

	fd = open(str, O_RDONLY);
	if (fd == -1)
		quit_parsing("Error: unable to open file");
	file = strdup("");
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		append_line(line, &file);
	}
	close(fd);
	if (!file || *file == '\0')
	{
		free(file);
		quit_parsing("Error: empty file\n");
	}
	return (file);
}

static void	append_line(char *line, char **file)
{
	char	*temp;

	if (ft_strncmp(line, "\n", 1) && ft_strncmp(line, "#", 1))
	{
		temp = ft_strjoin(*file, line);
		free(*file);
		*file = temp;
	}
	free(line);
}

static char	***split_parameters(char *file)
{
	char	**split_lines;
	char	***split_properties;
	int		i;

	split_lines = ft_split(file, '\n');
	split_properties = malloc(ft_arrlen(split_lines) * sizeof(char **) + 1);
	if (!split_properties)
		external_free(file, split_lines, "Error: malloc() fail\n");
	i = -1;
	while (split_lines[++i])
	{
		split_properties[i] = ft_split(split_lines[i], ' ');
		if (!split_properties[i])
		{
			free_triple_pointer(split_properties);
			external_free(file, split_lines, "Error: malloc() fail\n");
		}
	}
	split_properties[i] = NULL;
	free(file);
	free_double_pointer(split_lines);
	return (split_properties);
}

static void	external_free(char *file, char **split_lines, char *str)
{
	free(file);
	free_double_pointer(split_lines);
	if (str)
		quit_parsing(str);
}
