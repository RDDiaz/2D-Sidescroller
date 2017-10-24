#ifndef _INTERFACE_SPRITE_H
#define _INTERFACE_SPRITE_H

#include "allegro5/allegro.h"
#include <cstdlib>
#include "vec2d.h"
#include "image_sequence.h"
#include "sprite.h"

namespace csis3700
{
class interface_sprite
{
public:
    interface_sprite(float initial_x, float initial_y, char type);

    ~interface_sprite();

    interface_sprite(const interface_sprite& other);
    interface_sprite& operator =(const interface_sprite& other);

    float get_x() const;

    float get_y() const;

    void set_image_sequence(image_sequence *s);

    void draw(ALLEGRO_DISPLAY *display);

    void advance_by_time(double dt, float x);

    void setHealth(int i);

    void setMana(int i);

    void setOther(int i);


private:

    vec2d position;
    image_sequence *sequence;
    char interface_type;
    double time;
    image_sequence *Health;
    image_sequence *Mana;
    image_sequence *Other;
};
}

#endif // _INTERFACE_SPRITE_H

