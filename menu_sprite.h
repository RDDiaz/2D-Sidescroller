#ifndef _menu_SPRITE_H
#define _menu_SPRITE_H

#include "allegro5/allegro.h"
#include <cstdlib>
#include "vec2d.h"
#include "image_sequence.h"
#include "sprite.h"
#include <vector>

namespace labX
{
class menu_sprite
{
public:
    menu_sprite(float initial_x, float initial_y);

    ~menu_sprite();

    menu_sprite(const menu_sprite& other);
    menu_sprite& operator =(const menu_sprite& other);

    float get_x() const;

    float get_y() const;

    void set_image_sequence(image_sequence *s);

    void draw(ALLEGRO_DISPLAY *display);

    void drawItems();

    void advance_by_time(double dt, float x);

    void handle_event(ALLEGRO_EVENT ev);

    bool hasItem(size_t i)
    {
        return menuItems[i];
    }

    void drawIcon();

    void set_equipped(std::string item){
        equipped = item;
    }
    std::string get_equipped(){
       return equipped;
    }



private:
    ALLEGRO_BITMAP *bitmap;
    vec2d position;
    image_sequence *sequence;
    bool menuItems[5]= {0};
    std::string equipped = "empty";
    double time;
};
}

#endif // _menu_SPRITE_H


