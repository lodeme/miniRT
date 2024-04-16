/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:19:32 by ubazzane          #+#    #+#             */
/*   Updated: 2024/03/04 19:57:13 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char *s, char c);
static void	allocate_words(char **dest_str, char *original_str, char separator);
void		free_double_pointer(char **arr);

char	**ft_split(char const *s, char c)
{
	int		word_count;
	char	**substrs;
	char	**empty;

	if (!s)
		return (NULL);
	if (s[0] == '\0')
	{
		empty = malloc(sizeof(char *));
		if (!empty)
			return (NULL);
		empty[0] = NULL;
		return (empty);
	}
	word_count = count_words((char *)s, c);
	substrs = (char **)malloc((word_count + 1) * sizeof(char *));
	if (!substrs)
		return (NULL);
	allocate_words(substrs, (char *)s, c);
	return (substrs);
}

static void	allocate_words(char **dest_str, char *original_str, char separator)
{
	char	*str_index;
	char	**final;

	str_index = original_str;
	final = dest_str;
	while (*str_index)
	{
		while (*original_str == separator)
			original_str++;
		str_index = original_str;
		while (*str_index && *str_index != separator)
			str_index++;
		if (*str_index == separator || str_index > original_str)
		{
			*final = ft_substr(original_str, 0, str_index - original_str);
			if (!(*final))
			{
				free_double_pointer(final);
				return ;
			}
			original_str = str_index;
			final++;
		}
	}
	*final = NULL;
}

static int	count_words(char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

void	free_double_pointer(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	arr = NULL;
}
