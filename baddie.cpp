#include "baddie.h"
#include "image_library.h"

using namespace std;


namespace labX
{

baddie::baddie(ALLEGRO_BITMAP* initial_bitmap, size_t world_width, size_t world_height, float initial_x, float initial_y, float initial_vx, float initial_vy,world* w) :
    phys_sprite(initial_x, initial_y, initial_vx, initial_vy)
{
    bitmap = initial_bitmap;
    height = world_height;
    width = world_width;
    image_sequence *BaddieRight = new image_sequence;
    BaddieRight->add_image(al_create_sub_bitmap(image_library::get()->get("baddie.png"),0,32,32,32), .5);
    BaddieRight->add_image(al_create_sub_bitmap(image_library::get()->get("baddie.png"),32,32,32,32), .5);
    BaddieRight->add_image(al_create_sub_bitmap(image_library::get()->get("baddie.png"),64,32,32,32), .5);
    set_image_sequence(BaddieRight);
    passive = true;

    theWorld = w;
}

baddie::~baddie()
{
}


void baddie::advance_by_time(double dt) {

    steps++;
    if (steps == 160){
        steps = 0;
    }
    if (steps < 80){
    vec2d right(1,0);
    position+=right;
    }
    if (steps > 80){
    vec2d left(-1,0);
    position+=left;
    }
    time += dt;
}


void baddie::set_velocity(const vec2d& v) {}
vec2d baddie::get_velocity() const
{
    return 0;
}
void baddie::resolve(const collision& collision, sprite* other)
{
    if(other->is_projectile())
    {
        theWorld->removeSprite(other);
    }
}

bool baddie::is_passive() const
{
    return passive;
}

void baddie::set_passive(bool b)
{
    passive = b;
}

}

