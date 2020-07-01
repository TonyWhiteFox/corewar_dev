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

static size_t		move_ptr2(t_serv *s, char **ptr)
{
	size_t		len;

	len = 0;
	while (1)
	{
		if (ft_strchr(WHITESPACE_CHARS, **ptr))
			s->ptr_flag = WHITESPACE;
		else if (**ptr == '\n' || **ptr == '\0')
			s->ptr_flag = NEW_LINE;
		else if (**ptr == '\"')
			s->ptr_flag = QUOTE;
		else if (**ptr == LABEL_CHAR)
			s->ptr_flag = IDENTIFER;
		else if (**ptr == SEPARATOR_CHAR)
			s->ptr_flag = SEPARATOR;
		if (s->ptr_flag)
		{
			break;
		}
		(*ptr)++;
		len++;
	}
	return (len);
}

static void		add_instr(t_serv *s, t_instr *new)
{
	t_instr		*ptr;
	
	ptr = s->instr;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
}

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

t_op			*get_op(char *name)
{
	unsigned	i;

	i = 0;
	while (i < (sizeof(g_op) / sizeof(t_op)))
	{
		if (!ft_strcmp(g_op[i].name, name))
			return (&g_op[i]);
		i++;
	}
	return (NULL);
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

static void		parse_str(t_serv *s)
{
	size_t	len;
	char	*str;
	char	c;

	s->ptr2 = s->ptr1;
	len = 0;
	c = 0;
	if (*s->ptr1 == '\"' || *s->ptr1 == '#')
	{
		c = (*s->ptr1 == '#' ? '\n' : '\"');
		s->ptr1++;
		s->ptr2++;
		len = len_to_end(s, c);
	}
	else while (ft_strchr(LABEL_CHARS, *s->ptr2++))
		len++;
	add_token(s, init_token(s, (c == '#' ? COMMENT : STRING),
			s->ptr1, len));
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

static void		parse_sentence(t_serv *s)
{
	t_list	*word;
	char	*lexem;

	word = s->last_instr->sentence;
	while (word)
	{
		lexem = (char *)word->content;
		if (lexem[word->content_size - 1] == LABEL_CHAR)
		{
			if (!(s->last_instr->label = ft_strndup(lexem,word->content_size
			- 1)))
				ft_error(ERR_MALLOC, s);
			s->ptr_flag = FLAG_LABEL;
		}
//		else
//			parse_instruction(NULL, s);
		word = word->next;
	}
}

t_instr		*init_instr(t_serv *s, t_op op)
{
	t_instr		*new;

	if (!(new = ft_memguru(sizeof(*new), &s->memguru)))
		ft_error(ERR_MALLOC, s);
	new->type = op;
	new->label = NULL;
	new->opcode = 0;
	new->arg1 = 0;
	new->arg2 = 0;
	new->arg3 = 0;
	new->next = NULL;
	return (new);
}

static void		get_sentence(t_serv *s)
{
	char	*ptr;
	t_list	*new;
	char	*str;
	size_t	len;

	ptr = s->line;
	while (ptr && *ptr)
	{
		while (ft_strchr(WHITESPACE_CHARS, *ptr))
			ptr++;
		if (*ptr && !ft_strchr(WHITESPACE_CHARS, *ptr))
		{
			len = get_word_len(ptr, WHITESPACE_CHARS);
			if (!(str = ft_memguru(len + 1, &s->memguru)))
				ft_error(ERR_STR_SPLIT, s);
			ft_strncpy(str, ptr, len + 1);
			new = ft_lstnew(str, len);
			ft_lstpushback(&s->last_sentence, new);
			ptr += len;
		}
	}
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
		if ((*s->ptr1 == COMMENT_CHAR || *s->ptr1 == ALT_COMMENT_CHAR))
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
		else if (*s->ptr1 == '\"' || ft_isalpha(*s->ptr1))
			parse_str(s);
		else
			parse_num(s);
	}
}

static void		translate(t_serv *s)
{
	get_tokens(s);
//	if (!s->last_instr)
//		init_instr(s, g_op[1]);
//	get_sentence(s);
//	parse_sentence(s);
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
	int		size;

	s->buff[READ_SIZE] = '\0';
	while (read(s->fd, s->buff, READ_SIZE))
		translate(s);
//	{
//		free(s->line);
//		s->line = NULL;
//		if ((size = get_next_line(s->fd, &s->line)) < 1)
//			break ;
//	}
	if (size < 0)
		ft_error(ERR_READ_FILE, s);
//	print_tokens(s);
}
