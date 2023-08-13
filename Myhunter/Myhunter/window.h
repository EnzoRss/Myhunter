



#ifndef WINDOW_H
#define WINDOW_H

//Include
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <list>



//Namespace
using namespace sf;


class Mob
{
public:
	Mob();
	~Mob();
	void Move();
	void MoveR();
	void MoveL();
	void RorL();
	Texture mob;
	Sprite mobS;
	int t;
	int x = 74;
	int y =76;
	int anim = 0;
	int position = 0;
	int t_move =500;
	int sens;
	int axe_y;
	std::list<Mob*> enemy;
};


struct background
{
	Sprite img;
	Texture text_fond;
	void back();
};

struct life
{
	Sprite coeur;
	Texture coeur_fond;
	void heart();
};

#endif