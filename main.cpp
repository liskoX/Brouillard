#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <time.h>
#include <vector>
#include <ctime>
//#include "ParticleSystem.hpp"
#include "QuadTree.hpp"
using namespace std;

#define PRECISION 5

int main ()
{
    srand((unsigned)time(0));
    sf::RenderWindow App (sf::VideoMode (512, 256, 32),"Test Implementation SFML");
    App.setFramerateLimit(60);
    sf::Event events;

    //Déclation et initialisation du système de fog
    QuadTree quad(0,0,512.0f,256.0f,0,PRECISION);
    quad.Init(); // Initialisation du brouillard
    //

    /*
    //Déclation et initialisation du système de particule
    ParticleSystem systeme(10000);
    systeme.setEmitter(sf::Vector2f(256,128));
    //

    //Déclaration de la translation
    Translation trans;
    trans.initPos = sf::Vector2f(50,50);
    trans.endPos = sf::Vector2f(300,50);
    trans.length = 150; // 150 frames
    systeme.setTranslation(trans);
    //

    //Test de shader
    sf::Shader shader;
    shader.loadFromFile("shader.txt", sf::Shader::Vertex);
    //
    */

    //Variables liées au brouillard
    vector<sf::RectangleShape*> ensRect;
    sf::Vector2i localPosition;
    bool released(true);
    //

    //Variables générales
    clock_t deb,fin;
    //

    while( App.isOpen() )
	{
	    while (App.pollEvent(events))
		{
		    if( events.type == sf::Event::Closed)
                App.close();
		}
		/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            systeme.updateEmitter(sf::Vector2f(2,0));
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            systeme.updateEmitter(sf::Vector2f(0,2));
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            systeme.updateEmitter(sf::Vector2f(-2,0));
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            systeme.updateEmitter(sf::Vector2f(0,-2));
        }*/
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
             localPosition = sf::Mouse::getPosition(App); // Récupération de la position du clic souris
             quad.Update(localPosition); // Mise à jour du quadTree
        }

        ensRect = quad.GetObjects(); // Récupération de tous les objets de la scène
		App.clear(sf::Color::White);
		deb = clock();
        for (int i(0);i<ensRect.size();i++)
        {
            App.draw(*ensRect[i]); // Draw de tous les objets
        }
        App.display();
        fin = clock();
	}
}
