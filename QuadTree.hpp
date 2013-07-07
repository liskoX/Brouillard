#ifndef QUADTREE_H_INCLUDED
#define QUADTREE_H_INCLUDED

#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <list>
#include <vector>
#include <iostream>
#include <string.h>
#include <time.h>

#define alphaIntensite 64
enum intensite{nulle,basse,haute};
using namespace std;

class QuadTree
{

    public:

    QuadTree(float x, float y, float width, float height, int level, int maxLevel);
    QuadTree(float x, float y, float width, float height, int level, int maxLevel,QuadTree *_parent);

    ~QuadTree();

    vector<sf::RectangleShape*>	GetObjectsAt(float x, float y);
    vector<sf::RectangleShape*>	GetObjects(float x, float y);
    vector<sf::RectangleShape*> GetObjects();
    QuadTree* ClimbUp();
    void	AddObject(sf::RectangleShape *object);
    void    DeleteObjectsAt(float x, float y);
    void	Clear();
    void    AfficherTree();
    void	Draw(sf::RenderTarget &canvas);
    void    SetColor(sf::Color couleur);
    void    Disable();
    void    Init();
    void    Update(sf::Vector2i coord);
    void    UpdateNearest(sf::Vector2i v,int _intensite);//Met a jour les cotés adjacents d'un quad
    int     GetMinWidth();
    int     GetMinHeight();

    private:

    bool enable;
    float	x;
    float	y;
    float	width;
    float	height;
    int	level;
    int	maxLevel;
    int intensite;
    vector<sf::RectangleShape*>	objects;

    sf::Color color;

    QuadTree *	parent;
    QuadTree *	NW;
    QuadTree *	NE;
    QuadTree *	SW;
    QuadTree *	SE;

    sf::RectangleShape	shape;

    bool	contains(QuadTree *child, sf::RectangleShape *object);

};

#endif
