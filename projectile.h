#ifndef projectile_H
#define projectile_H

#include "sprite.h"
#include "phys_sprite.h"
#include "vec2d.h"
#include "collision.h"
#include "allegro5/allegro.h"
#include <cstdlib>
#include "world.h"
#include "vec2d.h"

namespace labX
{
class projectile : public phys_sprite
{
public:
    /**
     * Construct a projectile giving it a bitmap to display when it is
     * drawn and the position of its upper-left hand corner in the
     * world.  Also specify the initial velocity of the projectile.
     */
    projectile(std::size_t world_width, std::size_t world_height, float initial_x, float initial_y, float initial_vx,
               float initial_vy, char direction, world* w);

    /**
     * Destructor
     */
    virtual ~projectile();

    /**
     * these two should cause errors, no copying!
     */
    projectile(const projectile& other);
    projectile& operator =(const projectile& other);

    virtual void advance_by_time(double dt);
    virtual void set_velocity(const vec2d& v);
    virtual vec2d get_velocity() const;
    virtual void resolve(const collision& collision, sprite* other);
    bool is_passive() const
    {
        return false;
    }
    virtual bool is_projectile()
    {
        return true;
    }


private:

    ALLEGRO_BITMAP *bitmap;
    std::size_t height;
    std::size_t width;
    world *theWorld;
    double run_time;
};
}
#endif /* projectile_H */

