#include "window.h"


bool verif_posx(int a, int b) {
    return a > b && a < b + 111;
}
bool verif_posy(int a, int b) {
    return a > b && a < (b + 114);
}

Mob::Mob() {
    mob.loadFromFile("../assets/mob.png");
    Sprite mob1;
    mobS.setTexture(mob);
    mobS.setScale(1.5, 1.5);
    RorL();
}

Mob::~Mob() {
    std::cout << "le mob est mort";
}

void Mob :: MoveR() {
    t = clock();

    mobS.setTextureRect(IntRect(anim, 0, 74, 76));
    if (t % 220 == 0) {
        anim += 74;
    }
    if (anim >= 888) {
        anim = 0;
    }
    if (t % t_move == 0) {
        position += 10;
        mobS.setPosition(position, axe_y);
    }

}

void Mob::MoveL() {
    t = clock();
    mobS.setTextureRect(IntRect(anim, y, 74, 76));
    if (t % 220 == 0) {
        anim += 74;
    }
    if (anim >= 888) {
        anim = 0;
    }
    if (t % t_move == 0) {
        position -= 10;
        mobS.setPosition(position, axe_y);
    }

}

void Mob::RorL() {
    
    int nb = rand() % 2;
    axe_y = rand() % 900;
    if (nb == 1) {
        anim = 0;
        position = 0;
        mobS.setPosition(position, axe_y);
        sens = 1;
    }
    else if (nb == 0) {
        anim =0;
        position = 1800;
        mobS.setPosition(position,  axe_y);
        sens = 0;
    }
}

void Mob::Move() {
    if (sens == 1) {
        MoveR();
    }
    else if (sens == 0)
    {
        MoveL();
    }
}



 void background::back() {
     text_fond.loadFromFile("../assets/fondresize.png");
     img.setScale(Vector2f(1, 1));
     img.setOrigin(Vector2f(0, 0));
     img.setTexture(text_fond, true);
 }

 void life::heart() {
     coeur_fond.loadFromFile("../assets/coeur.png");
     coeur.setScale(Vector2f(0.2, 0.2));
     coeur.setOrigin(Vector2f(0, 0));
     coeur.setTexture(coeur_fond, true);
 }

 int main() {
     srand(unsigned(time(NULL)));
     //window
     RenderWindow window(VideoMode(1920, 1080), "Space shooter");
     //backgroud
     background Back;
     Back.back();
     //life
     life vie;
     vie.heart();
     int pv = 3;
     //point
     Text strpoint;
     Font fontpoint;
     int point = 0;
     fontpoint.loadFromFile("../assets/Genos/static/Genos-ThinItalic.ttf");
     strpoint.setFont(fontpoint);
     strpoint.setCharacterSize(57);
     strpoint.setPosition(1850, 0);
     strpoint.setString(std::to_string(point));
     //mob
     std::list<Mob*> enemy;
     Mob* mob1 = new Mob();
     enemy.push_back(mob1);
     int sposx = 0;
     int sposy = 0;
     int mposy = 0;
     int mposx = 0;
     int spawn = 0;
     //cursor
     Texture crosshair;
     Sprite cursor;
     crosshair.loadFromFile("../assets/cursor.png");
     cursor.setTexture(crosshair, true);
     cursor.setScale(0.4, 0.4);
     //time 
     int T_spawn = 4000;

     while (window.isOpen()) {
         if (point <= 500 || pv == 0) {
            cursor.setPosition(Mouse::getPosition(window).x - 96.5, Mouse::getPosition(window).y-103);
            spawn = clock();
            if (spawn % 4000 == 0) {
                T_spawn -= 50;
                std::cout << "augmente la vitesse de spawn \n";
            }
            if (spawn % T_spawn == 0) {
                 Mob* mob1 = new Mob();
                 enemy.push_back(mob1);
            }
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed) {
                     window.close();
                }
                if (event.type == sf::Event::MouseButtonPressed && Mouse::isButtonPressed(Mouse::Left)){
                    for (std::list<Mob*>::iterator it = enemy.begin(); it != enemy.end(); it++) {
                        mposx = Mouse::getPosition(window).x;
                        mposy = Mouse::getPosition(window).y;
                        if ((*it) != NULL) {
                            sposx = (*it)->mobS.getPosition().x;
                            sposy = (*it)->mobS.getPosition().y;
                        }
                        if (verif_posx(mposx, sposx) && verif_posy(mposy, sposy)) {
                            if ((*it) != NULL) {
                                delete (*it);
                                (*it) = NULL;
                                point += 10;
                                enemy.erase(it);
                                break;
                            }
                        }  
                    }
                }
            }
         
            for (std::list<Mob*>::iterator it = enemy.begin(); it != enemy.end(); it++) {
                sposx = (*it)->mobS.getPosition().x;
                if ((*it) != NULL) {
                    if (sposx < -10 || sposx > 2000){
                        delete (*it);
                        (*it) = NULL;
                        enemy.remove((*it));
                        pv--;
                        break;
                    }
                }
            }

             window.clear();
         
             window.draw(Back.img);

             int posx = 0;

             for (int i = 0; i < pv; i++) {
                 vie.coeur.setPosition(posx, 0);
                 posx += 75;
                 window.draw(vie.coeur);
             }

             for (std::list<Mob*>::iterator it = enemy.begin(); it != enemy.end(); it++) {
                 if (spawn % 7000 == 0) {
                     (*it)->t_move -= 15;
                     std::cout << "augmente la vitesse\n";
                 }
                 if ((*it) != NULL) {
                     (*it)->Move();
                     window.draw((*it)->mobS);
                 }
             }
             strpoint.setString(std::to_string(point));
             window.draw(strpoint);
             window.setMouseCursorVisible(false);
             window.draw(cursor);
         }
         if (point == 300) {
            window.clear(sf::Color(0, 0, 0, 0.5));
            Font font;
            Text result;
            font.loadFromFile("../assets/Rubik_Iso/RubikIso-Regular.ttf");
            result.setFont(font);
            result.setCharacterSize(100);
            result.setPosition(500, 400);
            result.setString("Vous avez gagnez");
            result.setFillColor(Color::Green);
            strpoint.setPosition(900, 600);
            strpoint.setCharacterSize(80);
            strpoint.setFont(font);
            window.draw(strpoint);
            window.draw(result);
         }
         else if (pv == 0) {
             window.clear(sf::Color(0, 0, 0, 0.5));
             Font font;
             Text result;
             font.loadFromFile("../assets/Rubik_Iso/RubikIso-Regular.ttf");
             result.setFont(font);
             result.setCharacterSize(100);
             result.setPosition(500, 400);
             result.setString("Vous avez perdu");
             result.setFillColor(Color::Red);
             strpoint.setPosition(900, 600);
             strpoint.setCharacterSize(80);
             strpoint.setFont(font);
             window.draw(strpoint);
             window.draw(result);
         }
         window.display();
     }

    return 0;
}


