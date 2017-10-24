#ifndef baddie_H
#define baddie_H

#include "phys_sprite.h"
#include "vec2d.h"
#include "collision.h"
#include "allegro5/allegro.h"
#include <cstdlib>
#include "world.h"

namespace labX
{
class baddie : public phys_sprite
{
public:
    /**
     * Construct a baddie giving it a bitmap to display when it is
     * drawn and the position of its upper-left hand corner in the
     * world.  Also specify the initial velocity of the baddie.
     */
    baddie(ALLEGRO_BITMAP* initial_bitmap, std::size_t world_width, std::size_t world_height, float initial_x, float initial_y, float initial_vx, float initial_vy,world* w);

    /**
     * Destructor
     */
    virtual ~baddie();

    /**
     * these two should cause errors, no copying!
     */
    baddie(const baddie& other);
    baddie& operator =(const baddie& other);

    /**
     * Draw this baddie. See world.draw for discussion of the display
     * variable.
     */

    virtual void advance_by_time(double dt);

    virtual void set_velocity(const vec2d& v);
    virtual vec2d get_velocity() const;

    virtual void resolve(const collision& collision, sprite* other);
    bool is_passive() const;
    virtual void set_passive(bool b);
    virtual bool is_baddie()
    {
        return true;
    }



private:

    ALLEGRO_BITMAP *bitmap; // DELETE
    int steps = 0;
    std::size_t height;
    std::size_t width;
    vec2d velocity;
    bool passive;
    world *theWorld;
};
}
#endif /* baddie_H */
