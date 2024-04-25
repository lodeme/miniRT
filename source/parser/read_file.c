/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:27:28 by ubazzane          #+#    #+#             */
/*   Updated: 2024/04/25 17:02:20 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*read_file(char *str);
char	***split_parameters(char *file);
void	check_objs(char ***content);
void	append_line(char *line, char **file);

char	***extract_content(char *str)
{
	char	***objects;
	char	*file;

	file = read_file(str);
	objects = split_parameters(file);
	check_objs(objects);
	return (objects);
}

char	*read_file(char *str)
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

void	append_line(char *line, char **file)
{
	char *temp;

	if (ft_strncmp(line, "\n", 1))
	{
		temp = ft_strjoin(*file, line);
		free(*file);
		*file = temp;
	}
	free(line);
}

char	***split_parameters(char *file)
{
	char	**split_lines;
	char	***split_properties;
	int		i;

	split_lines = ft_split(file, '\n');
	split_properties = malloc(ft_arrlen(split_lines) * sizeof(char **) + 1);
	i = -1;
	while (split_lines[++i])
	{
		split_properties[i] = ft_split(split_lines[i], ' ');
		if (!split_properties[i])
		{
			quit_parsing("Error: malloc() fail\n");
			free(file);
			free_double_pointer(split_lines);
			free_triple_pointer(split_properties);
		}
	}
	split_properties[i] = NULL;
	free(file);
	free_double_pointer(split_lines);
	return (split_properties);
}

void	check_objs(char ***content)
{
	int	i;

	i = -1;
	while (content[++i])
	{
		if (!ft_strcmp(is_obj(content[i][0]), "error"))
		{
			free_triple_pointer(content);
			quit_parsing("Error: invalid object detected\n");
		}
	}
}
