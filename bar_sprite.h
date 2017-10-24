#ifndef _bar_SPRITE_H
#define _bar_SPRITE_H

#include "allegro5/allegro.h"
#include <cstdlib>
#include "vec2d.h"
#include "image_sequence.h"
#include "interface_sprite.h"
#include "sprite.h"

namespace csis3700
{
class bar_sprite : public interface_sprite
{
public:
    bar_sprite(float initial_x, float initial_y, char color);

    virtual ~bar_sprite();

    virtual float get_x() const;

    virtual float get_y() const;

    virtual void set_image_sequence(image_sequence *s);

    virtual void draw(ALLEGRO_DISPLAY *display);

    virtual void advance_by_time(double dt, float x);

    virtual void decreaseHealth();


private:

    vec2d position;
    image_sequence *sequence;
    double time;
};
}

#endif // _bar_SPRITE_H


