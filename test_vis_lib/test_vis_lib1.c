/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vis_lib1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldonnor- <ldonnor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 18:41:55 by ldonnor-          #+#    #+#             */
/*   Updated: 2020/03/01 19:31:34 by ldonnor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include <stdio.h>

int main()
{
	WINDOW *win1;
	int a;
	int b;
	initscr(); // инициализация окна
	noecho(); // не отображает вводимые символы
	start_color(); // инициализация цвета

	win1 = newwin(28, 18, 0, 0);//создаёт окно ращмером 28 на 18 с отступами 0 0 
	
	a = getch(); //создаёт рамочку вокруг окна
	init_pair(1, COLOR_CYAN, COLOR_BLACK); // биндит 1 как пару цветов цвет шрифта и фона
	wattron(win1, 1);
	box(win1, 25, 15);
	wrefresh(win1);
	a = getch(); // обработка ввода с клавиатуры с бесконечной задержкой
	wattron(win1, 1);
	mvwprintw(win1, 3, 3, "%daaa", a);
	mvwprintw(win1, 15, 1, "%d", a);
	wrefresh(win1);//обновляет указанное окно
	// mvwprintw(win1, 15, 1, "%d", a);
	// mvwprintw(win1, 3, 13, "%d", a);
	b = getch();
	wattroff(win1, 1);


	// printf("\n%d %d", a, b);
	
	return (0);
}