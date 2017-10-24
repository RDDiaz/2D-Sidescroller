#ifndef _GUI_SPRITE_H
#define _GUI_SPRITE_H

#include "allegro5/allegro.h"
#include <cstdlib>
#include "vec2d.h"
#include "image_sequence.h"
#include "sprite.h"

namespace labX
{
class GUI_sprite
{
public:
    GUI_sprite(float initial_x, float initial_y, char type);

    ~GUI_sprite();

    GUI_sprite(const GUI_sprite& other);
    GUI_sprite& operator =(const GUI_sprite& other);

    float get_x() const;

    float get_y() const;

    void set_image_sequence(image_sequence *s);

    void draw(ALLEGRO_DISPLAY *display);

    void advance_by_time(double dt, float x);

    void setHealth(float i);

    void setMana(float i);

    void setOther(float i);


private:

    vec2d position;
    image_sequence *sequence;
    char GUI_type;
    double time;
    image_sequence *Health;
    image_sequence *Mana;
    image_sequence *Other;
};
}

#endif // _GUI_SPRITE_H



