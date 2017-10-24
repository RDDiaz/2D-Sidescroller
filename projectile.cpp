#include "projectile.h"
#include "image_library.h"
#include <iostream>
#include <typeinfo>
#include "baddie.h"
using namespace std;


namespace labX
{

projectile::projectile(size_t world_width, size_t world_height, float initial_x, float initial_y, float initial_vx, float initial_vy, char direction,world* w) :
    phys_sprite(initial_x, initial_y, initial_vx, initial_vy)
{
    height = world_height;
    width = world_width;
    if (direction == 'r')
    {
        image_sequence *projectileRight = new image_sequence;
    projectileRight->add_image(al_create_sub_bitmap(image_library::get()->get("effects.png"),22,259,20,13), .5);
        set_image_sequence(projectileRight);
    }
    else
    {
        image_sequence *projectileLeft = new image_sequence;
    projectileLeft->add_image(al_create_sub_bitmap(image_library::get()->get("effects.png"),64,259,20,13), .5);
        set_image_sequence(projectileLeft);

    }

    theWorld = w;
    run_time = 0;
}

projectile::~projectile()
{
}
void projectile::advance_by_time(double dt)
{
    phys_sprite::advance_by_time(dt);
    run_time += dt;
    if(run_time >= 1.5)
    {
        theWorld->removeSprite(this);
    }
}

void projectile::set_velocity(const vec2d& v) {}
vec2d projectile::get_velocity() const
{
//    return 0;
}
void projectile::resolve(const collision& collision, sprite* other)
{
    if(other->is_baddie())
    {
        theWorld->removeSprite(other);
    }
}

}


