#ifndef SPACEOBJECT_H
#define SPACEOBJECT_H

class SpaceObject {

public:
    SpaceObject(int, int);
    void update();

    vec2i getPos() const;
    void setPos(vec2i);
   
private:
    vec2i pos;
};



class ObjectField {

public:
    void update();
    void erase(size_t);
    std::vector<SpaceObject> getData() const;

    void setBounds(rect);

private:
    rect field_bounds;
    std::vector<SpaceObject> object_set;

};

#endif
