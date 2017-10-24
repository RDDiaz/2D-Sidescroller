#include "GUI_sprite.h"
#include "image_library.h"

namespace labX
{
GUI_sprite::GUI_sprite(float initial_x, float initial_y, char type)
{
    position = vec2d(initial_x, initial_y);
    time = 0;
    if (type == 'h')
    {
        image_sequence *Healthbar = new image_sequence;
        Healthbar->add_image(image_library::get()->get("healthbar.png"), 0);
        set_image_sequence(Healthbar);
    }
    if (type == 'r')
    {
        image_sequence *Health = new image_sequence;
        Health->add_image(image_library::get()->get("health.png"), 0);
        set_image_sequence(Health);
    }
    if (type == 'b')
    {
        image_sequence *Mana = new image_sequence;
        Mana->add_image(image_library::get()->get("mana.png"), 0);
        set_image_sequence(Mana);
    }
    if (type == 'y')
    {
        image_sequence *Other = new image_sequence;
        Other->add_image(image_library::get()->get("other.png"), 0);
        set_image_sequence(Other);
    }
    GUI_type = type;
}

GUI_sprite::~GUI_sprite()
{
}

float GUI_sprite::get_x() const
{
    return position.get_x();
}

float GUI_sprite::get_y() const
{
    return position.get_y();
}

void GUI_sprite::set_image_sequence(image_sequence *s)
{
    sequence = s;
}

void GUI_sprite::draw(ALLEGRO_DISPLAY *display)
{
    sequence->draw(time, get_x(), get_y());
}

void GUI_sprite::advance_by_time(double dt, float x)
{
}

void GUI_sprite::setHealth(float i)
{

    image_sequence *CurrentHealth = new image_sequence;
    CurrentHealth->add_image(al_create_sub_bitmap(image_library::get()->get("health.png"),0,0,(140*i/100),75), 0);
    set_image_sequence(CurrentHealth);
}
void GUI_sprite::setMana(float i)
{
    image_sequence *CurrentMana = new image_sequence;
    CurrentMana->add_image(al_create_sub_bitmap(image_library::get()->get("mana.png"),0,0,(140*i/100),75), 0);
    set_image_sequence(CurrentMana);

}
void GUI_sprite::setOther(float i)
{
    image_sequence *CurrentOther = new image_sequence;
    CurrentOther->add_image(al_create_sub_bitmap(image_library::get()->get("other.png"),0,0,(140*i/100),75), 0);
    set_image_sequence(CurrentOther);

}

}



