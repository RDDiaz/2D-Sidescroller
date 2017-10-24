#ifndef __CDS_OBSTRUCTION_SPRITE_H
#define __CDS_OBSTRUCTION_SPRITE_H

#include "sprite.h"

namespace labX
{

/**
 * obstruction_sprites don't typically move and when they
 * participate in a collision they are unimpacted by it. They
 * typically render themslves as a single, static bitmap.
 */
class obstruction_sprite : public sprite
{
public:
    obstruction_sprite(float initial_x, float initial_y, ALLEGRO_BITMAP *image);
    virtual void set_velocity(const vec2d& v);
    virtual vec2d get_velocity() const;
    virtual void resolve(const collision& collision, sprite* other);
};
}


#endif /* OBSTRUCTION_SPRITE_H */
