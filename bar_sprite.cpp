#include "bar_sprite.h"
#include "image_library.h"
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"

namespace csis3700
{
bar_sprite::bar_sprite(float initial_x, float initial_y, char color):interface_sprite(initial_x, initial_y)
{
    position = vec2d(initial_x, initial_y);
    time = 0;
    if (color == 'r'){
        image_sequence *Health = new image_sequence;
        Health->add_image(image_library::get()->get("Health.png"), 0);
        set_image_sequence(Health);

    }
    if (color == 'b'){
        image_sequence *Mana = new image_sequence;
        Mana->add_image(image_library::get()->get("Mana.png"), 0);
        set_image_sequence(Mana);

    }
    if (color == 'y'){
        image_sequence *Other = new image_sequence;
        Other->add_image(image_library::get()->get("Other.png"), 0);
        set_image_sequence(Other);
    }
}

bar_sprite::~bar_sprite()
{
}

float bar_sprite::get_x() const
{
    return position.get_x();
}

float bar_sprite::get_y() const
{
    return position.get_y();
}

void bar_sprite::set_image_sequence(image_sequence *s)
{
    sequence = s;
}

void bar_sprite::draw(ALLEGRO_DISPLAY *display)
{
    sequence->draw(time, get_x(), get_y());
}

void bar_sprite::advance_by_time(double dt, float x)
{
    time += dt;
    if(x >= (800/3)-24){
        position = vec2d(x-(800/3)+24,0);
    }
}

 void bar_sprite::decreaseHealth(){

        image_sequence *Healthbar60 = new image_sequence;
        Healthbar60->add_image(al_create_sub_bitmap(image_library::get()->get("Healthbar.png"),436,168,180,22), 0);
        set_image_sequence(Healthbar60);

 }

}


