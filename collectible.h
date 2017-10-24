#ifndef _COLLECTIBLE_H
#define _COLLECTIBLE_H_H

#include "phys_sprite.h"
#include "allegro5/allegro.h"
#include "image_sequence.h"

namespace labX
{

/**
 * Physical sprites move using an approximation of newtonian
 * kinematics.
 */
class collectible : public phys_sprite
{
public:
//
    collectible(ALLEGRO_BITMAP* initial_bitmap, float initial_x, float initial_y, float initial_vx=0, float initial_vy=0);

    virtual ~collectible();

    bool is_passive() const;
    virtual void set_passive(bool b);
    virtual bool is_collectible()
    {
        return true;
    }
    virtual void handle_event(ALLEGRO_EVENT ev);
    virtual void resolve(const collision& collision, sprite* other);
    virtual void advance_by_time(double dt);

private:

        ALLEGRO_BITMAP *bitmap;
        image_sequence *gone_sequence;
        bool passive;

};

}
#endif /* _COLLECTIBLE_H_H */

