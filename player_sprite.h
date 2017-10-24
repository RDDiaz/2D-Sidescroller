#ifndef __CDS_PLAYER_SPRITE_H
#define __CDS_PLAYER_SPRITE_H
#include "phys_sprite.h"

namespace labX
{
class player_sprite : public phys_sprite
{
public:
    player_sprite(float initial_x=0, float initial_y=0);
    virtual bool is_passive() const;
    virtual void set_on_ground(bool v);
    virtual void advance_by_time(double dt);
    virtual void resolve(const collision& collision, sprite* other);
protected:
    bool on_ground;
};
}


#endif /* PLAYER_SPRITE_H */
