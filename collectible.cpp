#include "collectible.h"
#include "image_library.h"

namespace labX
{
collectible::collectible(ALLEGRO_BITMAP* initial_bitmap, float initial_x, float initial_y, float initial_vx, float initial_vy)
    : phys_sprite(initial_x, initial_y, initial_vx, initial_vy)
{
    image_sequence *collect = new image_sequence;
    collect->add_image(initial_bitmap,0);
    set_image_sequence(collect);

    ALLEGRO_BITMAP *eAtom = image_library::get()->get("emptyAtom.png");
    image_sequence *gone = new image_sequence;
    gone->add_image(eAtom,0);

    gone_sequence = gone;
    passive = true;
}

collectible::~collectible()
{
}

bool collectible::is_passive() const
{
    return passive;
}

void collectible::set_passive(bool b)
{
    passive = b;
}

void collectible::handle_event(ALLEGRO_EVENT ev)
{

}

void collectible::resolve(const collision& collision, sprite* other)
{

}

void collectible::advance_by_time(double dt)
{
    phys_sprite::advance_by_time(dt);
}

}



