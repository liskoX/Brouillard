#include "QuadTree.hpp"
#include <vector>


using namespace std;

QuadTree::QuadTree(float _x, float _y, float _width, float _height, int _level, int _maxLevel) :
    x	(_x),
    y	(_y),
    width	(_width),
    height	(_height),
    level	(_level),
    maxLevel(_maxLevel),
    enable(true),
    intensite(haute)
{
    color = sf::Color::Green;
    shape.setPosition(x, y);
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(sf::Color(0, 0, 0, 0));
    shape.setOutlineThickness(1.0f);
    shape.setOutlineColor(color);

    if (level == maxLevel)
    {
        return;
    }

    NW = new QuadTree(x, y, width / 2.0f, height / 2.0f, level+1, maxLevel,this);
    NE = new QuadTree(x + width / 2.0f, y, width / 2.0f, height / 2.0f, level+1, maxLevel,this);
    SW = new QuadTree(x, y + height / 2.0f, width / 2.0f, height / 2.0f, level+1, maxLevel,this);
    SE = new QuadTree(x + width / 2.0f, y + height / 2.0f, width / 2.0f, height / 2.0f, level+1, maxLevel,this);
}

QuadTree::QuadTree(float _x, float _y, float _width, float _height, int _level, int _maxLevel,QuadTree *_parent) :
    x	(_x),
    y	(_y),
    width	(_width),
    height	(_height),
    level	(_level),
    maxLevel(_maxLevel),
    enable(true),
    intensite(haute),
    parent(_parent)
{
    color = sf::Color::Green;
    shape.setPosition(x, y);
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(sf::Color(0, 0, 0, 0));
    shape.setOutlineThickness(1.0f);
    shape.setOutlineColor(color);

    if (level == maxLevel)
    {
        return;
    }

    NW = new QuadTree(x, y, width / 2.0f, height / 2.0f, level+1, maxLevel,this);
    NE = new QuadTree(x + width / 2.0f, y, width / 2.0f, height / 2.0f, level+1, maxLevel,this);
    SW = new QuadTree(x, y + height / 2.0f, width / 2.0f, height / 2.0f, level+1, maxLevel,this);
    SE = new QuadTree(x + width / 2.0f, y + height / 2.0f, width / 2.0f, height / 2.0f, level+1, maxLevel,this);
}

QuadTree::~QuadTree()
{
    if (level == maxLevel)
    return;

    delete NW;
    delete NE;
    delete SW;
    delete SE;
}

void QuadTree::AddObject(sf::RectangleShape *object) {
    if (level == maxLevel)
    {
        objects.push_back(object);
        return;
    }
    if (contains(NW, object))
    {
        NW->AddObject(object);
        return;
    }
    else if (contains(NE, object))
    {
        NE->AddObject(object);
        return;
    }
    else if (contains(SW, object))
    {
        SW->AddObject(object);
        return;
    }
    else if (contains(SE, object))
    {
        SE->AddObject(object);
        return;
    }
    if (contains(this, object))
    {
        objects.push_back(object);
    }
}

vector<sf::RectangleShape*> QuadTree::GetObjectsAt(float _x, float _y)
{
    if (level == maxLevel)
    {
        return objects;
    }
    vector<sf::RectangleShape*> returnObjects, childReturnObjects;
    if (!objects.empty())
    {
        returnObjects = objects;
    }
    if (_x > x + width / 2.0f && _x < x + width)
    {
        if (_y > y + height / 2.0f && _y < y + height)
        {
            childReturnObjects = SE->GetObjectsAt(_x, _y);
            returnObjects.insert(returnObjects.end(), childReturnObjects.begin(), childReturnObjects.end());
            return returnObjects;
        }
        else if (_y >= y && _y <= y + height / 2.0f)
        {
            childReturnObjects = NE->GetObjectsAt(_x, _y);
            returnObjects.insert(returnObjects.end(), childReturnObjects.begin(), childReturnObjects.end());
            return returnObjects;
        }
    }
    else if (_x > x && _x < x + width / 2.0f) //_x = 500    x=0    width = 3200   _y=0   y=0
    {
        if (_y > y + height / 2.0f && _y < y + height)
        {
            childReturnObjects = SW->GetObjectsAt(_x, _y);
            returnObjects.insert(returnObjects.end(), childReturnObjects.begin(), childReturnObjects.end());
            return returnObjects;
        }
        else if (_y >= y && _y <= y + height / 2.0f)
        {
            childReturnObjects = NW->GetObjectsAt(_x, _y);
            returnObjects.insert(returnObjects.end(), childReturnObjects.begin(), childReturnObjects.end());
            return returnObjects;
        }
    }
    return returnObjects;
}

vector<sf::RectangleShape*>	QuadTree::GetObjects(float x, float y)
{
    vector<sf::RectangleShape*> returnObjects;
    for (int i(0);i<objects.size();i++)
    {
        if (objects[i]->getPosition().x >= x && objects[i]->getPosition().x<= x+width&&objects[i]->getPosition().y >= y &&objects[i]->getPosition().y <= y+height)
            returnObjects.push_back(objects[i]);
    }
    return returnObjects;
}

void QuadTree::Clear()
{
    if (level == maxLevel)
    {
        objects.clear();
        return;
    }
    else {
    NW->Clear();
    NE->Clear();
    SW->Clear();
    SE->Clear();
}
    if (!objects.empty())
    {
        objects.clear();
    }
}

void QuadTree::Draw(sf::RenderTarget &canvas)
{
    if (enable)
    {
        canvas.draw(shape);
        if (level != maxLevel)
        {
            NW->Draw(canvas);
            NE->Draw(canvas);
            SW->Draw(canvas);
            SE->Draw(canvas);
        }
    }

}

bool QuadTree::contains(QuadTree *child, sf::RectangleShape *object) {
return	!(  object->getPosition().x >= child->x + child->width ||
            object->getPosition().y >= child->y + child->height ||
            object->getPosition().x + 32 <= child->x ||
            object->getPosition().y + 32 <= child->y );
}

void QuadTree::AfficherTree()
{
    if (level == maxLevel)
        return;
    //std::cout << level << std::endl;
    NW->AfficherTree();
    NE->AfficherTree();
    SW->AfficherTree();
    SE->AfficherTree();
}
void QuadTree::SetColor(sf::Color couleur)
{
    if (enable)
    {
        color = couleur;
        shape.setOutlineColor(color);

        if (level == maxLevel)
            return;

        NW->SetColor(color);
        NE->SetColor(color);
        SW->SetColor(color);
        SE->SetColor(color);
    }
}

void QuadTree::Disable()
{
    enable = false;
}

void QuadTree::Init()
{
    sf::RectangleShape *rect;
    rect = new sf::RectangleShape(sf::Vector2f(GetMinWidth(),GetMinHeight()));
    rect->setFillColor(sf::Color(128,128,128,128));
    rect->setPosition(x,y);
    objects.push_back(rect);
    //AddObject(rect);

    if (level == maxLevel)
        return;

    NW->Init();
    NE->Init();
    SW->Init();
    SE->Init();

}

vector<sf::RectangleShape*> QuadTree::GetObjects()
{
    vector<sf::RectangleShape*> returnObjects, childReturnObjects;

    if (level == maxLevel)
        return objects;

    childReturnObjects = NW->GetObjects();
    for (int i(0);i<childReturnObjects.size();i++)
    {
        returnObjects.push_back(childReturnObjects[i]);
    }
    childReturnObjects = NE->GetObjects();
    for (int i(0);i<childReturnObjects.size();i++)
    {
        returnObjects.push_back(childReturnObjects[i]);
    }
    childReturnObjects = SW->GetObjects();
    for (int i(0);i<childReturnObjects.size();i++)
    {
        returnObjects.push_back(childReturnObjects[i]);
    }
    childReturnObjects = SE->GetObjects();
    for (int i(0);i<childReturnObjects.size();i++)
    {
        returnObjects.push_back(childReturnObjects[i]);
    }

    return returnObjects;
}

void QuadTree::Update(sf::Vector2i coord)
{
    if (objects[0]->getPosition() == sf::Vector2f(coord.x-coord.x%GetMinWidth(),coord.y-coord.y%GetMinHeight()))
    {
        QuadTree* quad;
        intensite = 0;
        objects[0]->setFillColor(sf::Color(128,128,128,intensite*alphaIntensite));
        quad = ClimbUp();
        quad->UpdateNearest(sf::Vector2i(coord.x-coord.x%GetMinWidth(),coord.y-coord.y%GetMinHeight()),intensite+1);
    }

    if (level != maxLevel)
    {
        NW->Update(coord);
        NE->Update(coord);
        SW->Update(coord);
        SE->Update(coord);
    }


}

void QuadTree::UpdateNearest(sf::Vector2i v,int _intensite)//Met a jour les cotés adjacents d'un quad
{
    if ((objects[0]->getPosition() == sf::Vector2f(v.x+GetMinWidth(),v.y) ||
        objects[0]->getPosition() == sf::Vector2f(v.x-GetMinWidth(),v.y) ||
        objects[0]->getPosition() == sf::Vector2f(v.x,v.y-GetMinHeight()) ||
        objects[0]->getPosition() == sf::Vector2f(v.x,v.y+GetMinHeight())) && intensite != 0)
    {
        intensite = 1;
        objects[0]->setFillColor(sf::Color(128,128,128,intensite*alphaIntensite));
    }

    if (level != maxLevel)
    {
        NW->UpdateNearest(v,_intensite);
        NE->UpdateNearest(v,_intensite);
        SW->UpdateNearest(v,_intensite);
        SE->UpdateNearest(v,_intensite);
    }
}

QuadTree* QuadTree::ClimbUp()
{
    if (level == 0)
        return this;
    else
        parent->ClimbUp();
}

void QuadTree::DeleteObjectsAt(float x, float y)
{
    vector<sf::RectangleShape*> rect = GetObjectsAt(x,y);
    for (int i(0);i<rect.size();i++)
        delete rect[0];
}

int QuadTree::GetMinWidth()
{
    if (level == maxLevel)
        return width;
    else
        return NE->GetMinWidth();
}

int QuadTree::GetMinHeight()
{
    if (level == maxLevel)
        return height;
    else
        return NE->GetMinHeight();
}
