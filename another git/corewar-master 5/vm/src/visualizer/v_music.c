/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_music.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/14 23:46:41 by vbrazas           #+#    #+#             */
/*   Updated: 2018/12/15 19:04:09 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>
#define TMP			t->play_start

static t_smi		g_all_music_info[] = {
	{0, 0, NULL, NULL, NULL},
	{14, 14, "venom/", NULL, NULL},
	{8, 4, "skibidi/", NULL, NULL},
	{18, 12, "bigshaq/", NULL, NULL},
	{0, 0, NULL, NULL, NULL}
};

static bool			init(t_vm *v)
{
	t_smi			*const t = (g_all_music_info + M.music);

	TMP = ft_strjoin(
	"afplay /Users/akupriia/projects/corewar/vm/music/"
	, TMP);
	t->play_die = ft_strjoin(TMP, "die.mp3 &> /dev/null &");
	t->play_end = ft_strjoin(TMP, "end.mp3 &> /dev/null &");
	t->play_start = ft_strjoin(TMP, "start.mp3 &> /dev/null &");
	M.cmi = (t_smi*)t;
	return (true);
}

void				play_music(t_vm *v, int flag)
{
	static bool		is_allocate = false;

	if (!A.is_ncurses || !M.music)
		return ;
	!is_allocate && init(v) && (is_allocate = true);
	if (flag == MSTART)
	{
		system(M.cmi->play_start);
		M.to_wait = M.cmi->start_duration;
		M.playing = time(NULL);
	}
	else if (flag == MDIE
	&& M.playing + M.to_wait < time(NULL))
	{
		system(M.cmi->play_die);
		M.to_wait = M.cmi->die_duration;
		M.playing = time(NULL);
	}
	else if (flag == MEND)
	{
		system("pkill afplay");
		system(M.cmi->play_end);
	}
}
