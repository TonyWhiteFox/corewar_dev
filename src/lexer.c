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

static void		add_token(t_serv *s, t_token *new)
{
	t_token		*ptr;

	if (!s->tokens)
		s->tokens = new;
	else
	{
		ptr = s->tokens;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
	ft_printf("%s ", new->content);
}

static t_token	*init_token(t_serv *s, t_type type, char *str, size_t len)
{
	t_token		*new;

	new = ft_memguru(sizeof(*new), &s->memguru);
	new->type = type;
	new->content = ft_memguru(len + 1, &s->memguru);
	ft_strncpy(new->content, str, len);
	new->content[len] = '\0';
	new->next = NULL;
	return (new);
}

static void		parse_num(t_serv *s)
{
	int		len;

	len = 0;
	s->ptr2 = s->ptr1;
	if (*s->ptr2 == '-')
	{
		len++;
		s->ptr2++;
	}
	while (ft_isdigit(*s->ptr2++))
		len++;
	add_token(s, init_token(s, NUM, s->ptr1, len));
	s->ptr1 += len;
}

size_t			len_to_end(t_serv *s, char end)
{
	size_t	len;

	len = 0;
	while (*s->ptr2 != end)
	{
		if (!*s->ptr2++)
			ft_error(ERR_STR_SPLIT, s);
		len++;
	}
	return (len);
}

static void		parse_comment(t_serv *s)
{
	size_t	len;
	char	c;

	s->ptr1++;
	s->ptr2 = s->ptr1;
	len = len_to_end(s, '\n');
	add_token(s, init_token(s, COMMENT, s->ptr1, len));
	s->ptr1 += len;
	if (*s->ptr1 == '\"')
		s->ptr1++;

}

static void		parse_str(t_serv *s)
{
	size_t	len;
	char	c;

	s->ptr2 = s->ptr1;
	len = 0;
	if (*s->ptr1 == '\"')
	{
		s->ptr1++;
		s->ptr2++;
		len = len_to_end(s, '\"');
	}
	else while (ft_strchr(LABEL_CHARS, *s->ptr2++))
		len++;
	add_token(s, init_token(s, STRING, s->ptr1, len));
	s->ptr1 += len;
	if (*s->ptr1 == '\"')
		s->ptr1++;
}

static void		parse_command(t_serv *s)
{
	size_t		len;

	s->ptr2 = s->ptr1;
	if (!ft_strncmp(s->ptr1, NAME_CMD_STRING, (len = ft_strlen
	(NAME_CMD_STRING))))
		add_token(s, init_token(s, PROG_NAME, s->ptr1, len));
	else if (!ft_strncmp(s->ptr1, COMMENT_CMD_STRING, (len = ft_strlen
	(COMMENT_CMD_STRING))))
		add_token(s, init_token(s, PROG_COMMENT, s->ptr1,len));
	s->ptr1 += len;
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
		if (*s->ptr1 == COMMENT_CHAR)
			parse_comment(s);
		else if (*s->ptr1 == ALT_COMMENT_CHAR || *s->ptr1 == '\"'
			|| ft_isalpha(*s->ptr1))
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
			add_token(s, init_token(s, LABEL, s->ptr1++, 1));
		else
			parse_num(s);
	}
}

void			print_tokens(t_serv *s)
{
	t_token		*ptr;

	ptr = s->tokens;
	while (ptr)
	{
		ft_printf("%s :: ", ptr->content);
		ptr = ptr->next;
	}
}

void			lexer(t_serv *s)
{
	char		*buf[READ_SIZE];
	char		*tmp;
	ssize_t		size;

	size = 0;
	s->buff = (char *)malloc(1);
	s->buff[0] = 0;
	while ((size = read(s->fd, buf, READ_SIZE)))
	{
		tmp = s->buff;
		s->buff = ft_strjoin(tmp, (const char *)buf);
		free(tmp);
	}
	if (size < 0 || !s->buff)
		ft_error(ERR_READ_FILE, s);
	get_tokens(s);
	print_tokens(s);
}
