// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   gameLoop.cpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/21 22:22:12 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/21 23:09:52 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "retro.hpp"

static void		 randomPop(Obstacle **o, Enemy **e)
{
	for (int i = 0; i < NB_OBSTACLE; i++)
	{
		if (!(o[i]->getAlive()) && !(rand() %  NB_OBSTACLE))// REPOP DES OBSTACLES
		{
			o[i]->setX(WIDTH - 1);
			o[i]->setY(rand() % (HEIGHT - 1));
			o[i]->setAlive(true);
		}
	}
	for (int i = 0; i < NB_ENEMY; i++)
	{
		if (!(e[i]->getAlive())  && !(rand() %  NB_ENEMY)) // REPOP DES ENEMYS
		{
			e[i]->setX(WIDTH - 1);
			e[i]->setY(rand() % (HEIGHT - 1));
			e[i]->setAlive(true);
		}
		else if (!(rand() % 5))
		{
			if (e[i]->getAlive())
				e[i]->shoot(false);
		}
	}
}

static void drawBorder(void)
{
    mvprintw(0, 0, "+-------------------------------------------------+");

    for (int i = 1; i < HEIGHT - 1; i++)
        mvprintw(i, 0, "|");
    for (int i = 1; i < HEIGHT - 1; i++)
        mvprintw(i, WIDTH, "|");

    mvprintw(HEIGHT - 1, 0, "+-------------------------------------------------+");
}

void		gameLoop(void)
{
	struct timeval	tick;
	struct timeval	tack;
	struct timeval	start;
	Obstacle	**o;
	Enemy		**e;
	Player		*p = new Player('P');
	char		key;
    int         coolStuff = 0;
    

	o = new Obstacle*[NB_OBSTACLE];
	for (int i = 0; i < NB_OBSTACLE; i++)
		o[i] = new Obstacle;

	e = new Enemy*[NB_ENEMY];
	for (int i = 0; i < NB_ENEMY; i++)
		e[i] = new Enemy;

    gettimeofday(&start, NULL);

	while (true)
	{
        coolStuff++;
        if (!(coolStuff % 2))
            p->setScore(p->getScore() + 1);
		gettimeofday(&tick, NULL);
		key = promptUser();
		if (key == SHOOT) //cf. AStuff.class.hpp for defines
			p->shoot();

        
        randomPop(o, e);


        moveAll( key, o, e, p );
		if (checkAllCollisions(o, e, p) == false)
		{
			clear();
			drawBorder();
			mvprintw(25, 20, "GAME OVER");
			refresh();
			sleep(5);
            endwin();
			exit(0);
		}
		framePrint(o, e, *p);
        mvprintw(HEIGHT + 1, WIDTH / 2 - 16, "Score: %d  Lives: %d  Time: %d", p->getScore(), p->getLives(), static_cast<unsigned int>(tick.tv_sec - start.tv_sec));
		drawBorder();
        refresh();
		gettimeofday(&tack, NULL);
		if (tack.tv_usec < tick.tv_usec)
			tack.tv_usec = tick.tv_usec;
        
		usleep(FRAME * 1000 - static_cast<unsigned int>(tack.tv_usec - tick.tv_usec));
//        sleep(1);
	}

}
