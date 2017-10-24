#include "menu_sprite.h"
#include "image_library.h"
#include "keyboard_manager.h"
#include "player.h"


namespace labX
{
menu_sprite::menu_sprite(float initial_x, float initial_y)
{
    position = vec2d(initial_x, initial_y);
    time = 0;
    image_sequence *Inventory = new image_sequence;
    Inventory->add_image(image_library::get()->get("inventory.png"), 0);
    set_image_sequence(Inventory);

}

menu_sprite::~menu_sprite()
{
}

float menu_sprite::get_x() const
{
    return position.get_x();
}

float menu_sprite::get_y() const
{
    return position.get_y();
}

void menu_sprite::set_image_sequence(image_sequence *s)
{
    sequence = s;
}

void menu_sprite::handle_event(ALLEGRO_EVENT ev)
{

}

void menu_sprite::draw(ALLEGRO_DISPLAY *display)
{
    sequence->draw(time, get_x(), get_y());

}

void menu_sprite::drawItems()
{
    menuItems[0] = {true};
    menuItems[1] = {true};
    menuItems[2] = {true};
    menuItems[3] = {true};
    menuItems[4] = {true};
    menuItems[5] = {true};

    if(menuItems[0] == true)
    {
        ALLEGRO_BITMAP* item1 = al_create_sub_bitmap(image_library::get()->get("items.png"),0,0,35,52);
        al_draw_bitmap(item1, get_x()+13, get_y()+5,0);

    }
    if(menuItems[1] == true)
    {
        ALLEGRO_BITMAP* item2 = al_create_sub_bitmap(image_library::get()->get("items.png"),35,0,30,45);
        al_draw_bitmap(item2, get_x()+50, get_y()+5,0);

    }
    if(menuItems[2] == true)
    {
        ALLEGRO_BITMAP* item3 = al_create_sub_bitmap(image_library::get()->get("items.png"),75,0,40,52);
        al_draw_bitmap(item3, get_x()+85, get_y()+3,0);

    }
    if(menuItems[3] == true)
    {
        ALLEGRO_BITMAP* item4 = al_create_sub_bitmap(image_library::get()->get("items.png"),110,0,25,52);
        al_draw_bitmap(item4, get_x()+13, get_y()+40,0);

    }
    if(menuItems[4] == true)
    {
        ALLEGRO_BITMAP* item5 = al_create_sub_bitmap(image_library::get()->get("items.png"),135,0,30,52);
        al_draw_bitmap(item5, get_x()+45, get_y()+40,0);
    }
    if(menuItems[5] == true)
    {
        ALLEGRO_BITMAP* item6 = al_create_sub_bitmap(image_library::get()->get("items.png"),190,10,30,30);
        al_draw_bitmap(item6, get_x()+95, get_y()+50,0);

    }

}

void menu_sprite::advance_by_time(double dt, float x)
{


}

void menu_sprite::drawIcon(){

    if(equipped == "sword")
    {
        ALLEGRO_BITMAP* item1 = al_create_sub_bitmap(image_library::get()->get("items.png"),0,0,35,52);
        al_draw_bitmap(item1, 15, 10,0);
    }
    if(equipped == "gun")
    {
        ALLEGRO_BITMAP* item2 = al_create_sub_bitmap(image_library::get()->get("items.png"),35,0,30,45);
        al_draw_bitmap(item2, 15, 10,0);
    }
    if(equipped == "axe")
    {
        ALLEGRO_BITMAP* item3 = al_create_sub_bitmap(image_library::get()->get("items.png"),75,0,40,52);
        al_draw_bitmap(item3, 15, 10,0);
    }
    if(equipped == "claw")
    {
        ALLEGRO_BITMAP* item4 = al_create_sub_bitmap(image_library::get()->get("items.png"),110,0,25,52);
        al_draw_bitmap(item4, 15, 10,0);
    }
    if(equipped == "crossbow")
    {
        ALLEGRO_BITMAP* item5 = al_create_sub_bitmap(image_library::get()->get("items.png"),135,0,30,52);
        al_draw_bitmap(item5, 10, 10,0);
    }
    if(equipped == "bow")
    {
        ALLEGRO_BITMAP* item6 = al_create_sub_bitmap(image_library::get()->get("items.png"),190,10,30,30);
        al_draw_bitmap(item6, 25, 20,0);
    }
}

}



