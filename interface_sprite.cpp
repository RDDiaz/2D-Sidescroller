#include "interface_sprite.h"
#include "image_library.h"
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"

namespace csis3700
{
interface_sprite::interface_sprite(float initial_x, float initial_y, char type)
{
    position = vec2d(initial_x, initial_y);
    time = 0;
    if (type == 'h'){
        image_sequence *Healthbar = new image_sequence;
        Healthbar->add_image(image_library::get()->get("Healthbar.png"), 0);
        set_image_sequence(Healthbar);
    }
    if (type == 'r'){
        image_sequence *Health = new image_sequence;
        Health->add_image(image_library::get()->get("Health.png"), 0);
        set_image_sequence(Health);
    }
    if (type == 'b'){
        image_sequence *Mana = new image_sequence;
        Mana->add_image(image_library::get()->get("Mana.png"), 0);
        set_image_sequence(Mana);
    }
    if (type == 'y'){
        image_sequence *Other = new image_sequence;
        Other->add_image(image_library::get()->get("Other.png"), 0);
        set_image_sequence(Other);
    }
    interface_type = type;
}

interface_sprite::~interface_sprite()
{
}

float interface_sprite::get_x() const
{
    return position.get_x();
}

float interface_sprite::get_y() const
{
    return position.get_y();
}

void interface_sprite::set_image_sequence(image_sequence *s)
{
    sequence = s;
}

void interface_sprite::draw(ALLEGRO_DISPLAY *display)
{
    sequence->draw(time, get_x(), get_y());
}

void interface_sprite::advance_by_time(double dt, float x)
{
    if (interface_type =='r'){
        setHealth(100);
    }
}

 void interface_sprite::setHealth(int i){
        image_sequence *CurrentHealth = new image_sequence;
        CurrentHealth->add_image(al_create_sub_bitmap(image_library::get()->get("Health.png"),0,0,195-i,75), 0);
        set_image_sequence(CurrentHealth);

 }
 void interface_sprite::setMana(int i){
        image_sequence *CurrentMana = new image_sequence;
        CurrentMana->add_image(al_create_sub_bitmap(image_library::get()->get("Mana.png"),0,0,195-i,75), 0);
        set_image_sequence(CurrentMana);

 }
 void interface_sprite::setOther(int i){
        image_sequence *CurrentOther = new image_sequence;
        CurrentOther->add_image(al_create_sub_bitmap(image_library::get()->get("Other.png"),0,0,195-i,75), 0);
        set_image_sequence(CurrentOther);

 }

}

