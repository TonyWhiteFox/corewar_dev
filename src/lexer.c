/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanhack <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 11:05:25 by mmanhack          #+#    #+#             */
/*   Updated: 2020/06/28 11:05:26 by mmanhack         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"
#include "op.h"
#include <errno.h>

void			add_token(t_serv *s, t_token *new)
{
	t_token			*ptr;

	if (!s->tokens)
		s->tokens = new;
	else
	{
		ptr = s->tokens;
		while (ptr && ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
	if (s->flag & FLAG_DEBUG)
	{
		if (s->out_line != s->i_line)
			ft_printf("%d: ", (s->out_line = s->i_line));
		ft_printf(" // %s", new->content);
		if (new->type == NEW_LINE)
			s->i_line++;
	}
}

t_token			*init_token(t_serv *s, t_type type, char *str, size_t len)
{
	t_token		*new;

	if (!(new = ft_memguru(sizeof(*new), &s->memguru)))
		ft_error(ERR_MALLOC, s, ENOMEM);
	new->type = type;
	if (!(new->content = ft_memguru(len + 1, &s->memguru)))
		ft_error(ERR_MALLOC, s, ENOMEM);
	ft_strncpy(new->content, str, len);
	new->content[len] = '\0';
	new->next = NULL;
	return (new);
}

static void		skip_whitespace(t_serv *s)
{
	while (ft_strchr(WHITESPACE_CHARS, *s->ptr1))
		s->ptr1++;
}

static void		get_tokens(t_serv *s)
{
	s->ptr1 = s->buff;
	while (*s->ptr1)
	{
		skip_whitespace(s);
		if (*s->ptr1 == COMMENT_CHAR || *s->ptr1 == ALT_COMMENT_CHAR)
			parse_comment(s);
		else if (*s->ptr1 == '\"' || ft_strchr(LABEL_CHARS, *s->ptr1))
			parse_str(s);
		else if (*s->ptr1 == SEPARATOR_CHAR)
			add_token(s, init_token(s, SEPARATOR, s->ptr1++, 1));
		else if (*s->ptr1 == '\n')
			add_token(s, init_token(s, NEW_LINE, s->ptr1++, 1));
		else if (*s->ptr1 == '.')
			parse_command(s);
		else if (*s->ptr1 == DIRECT_CHAR)
			add_token(s, init_token(s, DIRECT, s->ptr1++, 1));
		else if (*s->ptr1 == LABEL_CHAR)
			parse_ref_label(s);
		else if (*s->ptr1 == '-' || *s->ptr1 == '+')
			parse_num(s);
		else
			ft_error(ERR_STR_SPLIT, s, EINVAL);
	}
}

void			lexer(t_serv *s)
{
	char		buf[READ_SIZE + 1];
	char		*tmp;
	ssize_t		size;

	size = 0;
	ft_bzero(buf, READ_SIZE + 1);
	while ((size = read(s->fd, buf, READ_SIZE)))
	{
		if (!(tmp = ft_strjoin(s->buff, (const char *)buf)))
			ft_error(ERR_MALLOC, s, ENOMEM);
		ft_memguru_add(tmp, &s->memguru);
		s->buff = tmp;
		ft_bzero(buf, READ_SIZE + 1);
	}
	close(s->fd);
	if (size < 0 || !s->buff)
		ft_error(ERR_READ_FILE, s, errno);
	get_tokens(s);
}
