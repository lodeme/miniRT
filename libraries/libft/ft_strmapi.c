/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane < ubazzane@student.42berlin.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:28:17 by ubazzane          #+#    #+#             */
/*   Updated: 2023/11/16 17:31:34 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		len;
	char	*output;
	int		i;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	output = (char *)malloc(sizeof(char) * (len + 1));
	if (!output)
		return (NULL);
	i = 0;
	while (s[i] && i < len)
	{
		output[i] = (*f)(i, s[i]);
		i++;
	}
	output[i] = '\0';
	return (output);
}
