#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include <vector>

#include "global.hpp"

#include <memory> 


class StaticElement;


class Element
{
protected:
    Vector2<float> position = {0, 0};
    Color color = 0xFF0000FF;
    bool visible = true;
    Vector2<float> origin = {0, 0};



public:
    Element() {};
    virtual ~Element() {} 

    static std::vector<std::shared_ptr<StaticElement>> elements;

};

typedef std::vector <Vector2<float>> Polygon;

class StaticElement : public Element
{
protected:
    Polygon polygon;
    Polygon offset_ploygon;
    float angle = 0;
    float scale = 1;
    bool fill = false;
    int thickness = 1;
    Color border_color = 0xFF0000FF;

public:
    StaticElement() {};
    virtual ~StaticElement() {}

    void setPolygon(Polygon polygon) { this->polygon = polygon; }
    Polygon getPolygon() { return polygon; }
};


class DynamicElement : public Element
{
    protected:
    Vector2<float> velocity = {0, 1};
    Vector2<float> acceleration = {0, 0};
    float mass = 1.0f;
    float detection_radius = 100.0f;

    public:
    DynamicElement() {};
    ~DynamicElement() {};
};





#endif