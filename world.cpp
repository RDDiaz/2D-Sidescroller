#include "world.h"
#include <cassert>
#include <algorithm>
#include "sprite.h"
#include "baddie.h"
#include "player.h"
#include "keyboard_manager.h"
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include "player_sprite.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "allegro5/allegro_audio.h"
#include "allegro5/allegro_acodec.h"
#include "obstruction_sprite.h"
#include "GUI_sprite.h"
#include "collision.h"
#include "image_library.h"
#include "image_sequence.h"
#include "collectible.h"
#include <algorithm>
#include <sstream>


using namespace std;

namespace labX
{

const float gravity = 5;

void free_sprite(sprite* s)
{
    delete s;
}

world::world(ALLEGRO_DISPLAY *display,size_t width, size_t height)
{
    screen_width = width;
    screen_height = height;
    ALLEGRO_BITMAP *image1=image_library::get()->get("characterWalk.png");
    ALLEGRO_BITMAP *image2=image_library::get()->get("baddie.png");
    ALLEGRO_BITMAP *rock=image_library::get()->get("rock.png");
    ALLEGRO_BITMAP *atom=image_library::get()->get("atom.png");
    menu_sprites.push_back(menu = new menu_sprite(width/2-256/2 ,height/2-132/2));
    sprites.push_back(new obstruction_sprite(100,150,rock));
    sprites.push_back(new obstruction_sprite(400,125,rock));
    sprites.push_back(new obstruction_sprite(570,150,rock));
    sprites.push_back(new obstruction_sprite(800,125,rock));
    sprites.push_back(new obstruction_sprite(1200,150,rock));
    sprites.push_back(new obstruction_sprite(1600,125,rock));
    sprites.push_back(Player = new player(image1,width,height,10,230,this,menu));
    sprites.push_back(new baddie(image2,width,height,320,250,0,0,this));
    sprites.push_back(new baddie(image2,width,height,400,75,0,0,this));
    sprites.push_back(new baddie(image2,width,height,750,250,0,0,this));
    sprites.push_back(new baddie(image2,width,height,1000,250,0,0,this));
    sprites.push_back(new baddie(image2,width,height,1250,250,0,0,this));
    sprites.push_back(new baddie(image2,width,height,2000,250,0,0,this));
    sprites.push_back(new collectible(atom,100,100,0,0));
    sprites.push_back(new collectible(atom,400,75,0,0));
    sprites.push_back(new collectible(atom,570,100,0,0));
    sprites.push_back(new collectible(atom,800,75,0,0));
    sprites.push_back(new collectible(atom,1200,100,0,0));
    sprites.push_back(new collectible(atom,1600,75,0,0));
    stats.push_back(new GUI_sprite(0,0,'h'));
    stats.push_back(new GUI_sprite (53,6,'r'));
    stats.push_back(new GUI_sprite (64,24,'b'));
    stats.push_back(new GUI_sprite (59,39,'y'));

    font = al_load_ttf_font("font/calibri.ttf", 18, 0);
    assert(font);

}

world::world(const world& other)
{
    assert(false); // do not copy worlds
}

world& world::operator=(const world& other)
{
    assert(false); // do not assign worlds
}

world::~world()
{
    for_each(sprites.begin(), sprites.end(), free_sprite);
    sprites.clear();
}

void world::handle_event(ALLEGRO_EVENT ev)
{
    if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
    {
        keyboard_manager::get()->key_down(ev.keyboard.keycode);
    }
    else if(ev.type == ALLEGRO_EVENT_KEY_UP)
    {
        keyboard_manager::get()->key_up(ev.keyboard.keycode);
    }

    if(ev.type == ALLEGRO_EVENT_KEY_DOWN && keyboard_manager::get()->is_key_down(ALLEGRO_KEY_SPACE) && currentLevel != 0)
    {
        if (getPause() == false)
        {
            setPause(true);
            pauseDraw();
        }
        else
        {
            setPause(false);
        }
    }

    //inventory menu
    if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && paused == true)
    {

        if(ev.mouse.x < menu->get_x()+43 && ev.mouse.x > menu->get_x()+13 && ev.mouse.y < menu->get_y()+45 && ev.mouse.y > menu->get_y() && menu->hasItem(0) == true)
        {
            ALLEGRO_BITMAP* item1 = al_create_sub_bitmap(image_library::get()->get("items.png"),0,0,35,52);
            al_draw_bitmap(item1, menu->get_x()+200, menu->get_y()+40,0);
            al_flip_display();
            al_rest(1);
            menu->set_equipped("sword");
            setPause(false);
        }
        if(ev.mouse.x < menu->get_x()+86 && ev.mouse.x > menu->get_x()+44 && ev.mouse.y < menu->get_y()+45 && ev.mouse.y > menu->get_y() && menu->hasItem(1) == true)
        {
            ALLEGRO_BITMAP* item2 = al_create_sub_bitmap(image_library::get()->get("items.png"),35,0,30,45);
            al_draw_bitmap(item2, menu->get_x()+200, menu->get_y()+40,0);
            al_flip_display();
            al_rest(1);
            menu->set_equipped("gun");
            setPause(false);
        }
        if(ev.mouse.x < menu->get_x()+129 && ev.mouse.x > menu->get_x()+87 && ev.mouse.y < menu->get_y()+45 && ev.mouse.y > menu->get_y() && menu->hasItem(2) == true)
        {
            ALLEGRO_BITMAP* item3 = al_create_sub_bitmap(image_library::get()->get("items.png"),75,0,40,52);
            al_draw_bitmap(item3, menu->get_x()+200, menu->get_y()+40,0);
            al_flip_display();
            al_rest(1);
            menu->set_equipped("axe");
            setPause(false);
        }
        if(ev.mouse.x < menu->get_x()+43 && ev.mouse.x > menu->get_x()+13 && ev.mouse.y < menu->get_y()+90 && ev.mouse.y > menu->get_y()+45 && menu->hasItem(3) == true)
        {
            ALLEGRO_BITMAP* item4 = al_create_sub_bitmap(image_library::get()->get("items.png"),110,0,25,52);
            al_draw_bitmap(item4, menu->get_x()+200, menu->get_y()+40,0);
            al_flip_display();
            al_rest(1);
            menu->set_equipped("claw");
            setPause(false);
        }
        if(ev.mouse.x < menu->get_x()+86 && ev.mouse.x > menu->get_x()+44 && ev.mouse.y < menu->get_y()+90 && ev.mouse.y > menu->get_y()+45 && menu->hasItem(4) == true)
        {
            ALLEGRO_BITMAP* item5 = al_create_sub_bitmap(image_library::get()->get("items.png"),135,0,30,52);
            al_draw_bitmap(item5, menu->get_x()+200, menu->get_y()+40,0);
            al_flip_display();
            al_rest(1);
            menu->set_equipped("crossbow");
            setPause(false);
        }
        if(ev.mouse.x < menu->get_x()+129 && ev.mouse.x > menu->get_x()+87 && ev.mouse.y < menu->get_y()+90 && ev.mouse.y > menu->get_y()+45 && menu->hasItem(5) == true)
        {
            ALLEGRO_BITMAP* item6 = al_create_sub_bitmap(image_library::get()->get("items.png"),190,10,30,30);
            al_draw_bitmap(item6, menu->get_x()+210, menu->get_y()+50,0);
            al_flip_display();
            al_rest(1);
            menu->set_equipped("bow");
            setPause(false);
        }

    }
    Player->handle_event(ev);
}

void world::resolve_collisions()
{

    vector<collision> collisions;

    for(std::vector<sprite*>::iterator it = sprites.begin(); it!= sprites.end(); it++)
    {

        for(std::vector<sprite*>::iterator it2=it+1; it2!=sprites.end(); it2++)
        {

            if ( (*it)->collides_with(**it2) )
            {
//                cout << "Collision Detected" << sprites.size() << endl;
                collisions.push_back(collision(*it, *it2));
            }
        }
    }

    //Sort Here

    for(std::vector<collision>::iterator it3 = collisions.begin(); it3!=collisions.end(); it3++)
    {
        it3->resolve();
    }
}

void world::advance_by_time(double dt)
{
    for(vector<sprite*>::iterator it = sprites.begin(); it != sprites.end(); ++it)
    {
        (*it)->advance_by_time(dt);
    }

    for(vector<menu_sprite*>::iterator it = menu_sprites.begin(); it != menu_sprites.end(); ++it)
    {
        (*it)->advance_by_time(dt, Player->get_x());
    }

    resolve_collisions();

    for(vector<sprite*>::iterator it = addSprites.begin(); it != addSprites.end(); ++it)
    {
        sprites.push_back(*it);
    }

    addSprites.clear();

    for(vector<sprite*>::iterator it = removeSprites.begin(); it != removeSprites.end(); ++it)
    {
        if (find(sprites.begin(), sprites.end(), *it) != sprites.end())
        {
            vector<sprite*>::iterator temp = find(sprites.begin(), sprites.end(), *it);
            sprites.erase(temp);
        }
    }
    removeSprites.clear();

}

void world::draw(ALLEGRO_DISPLAY *display, float time)
{
    if (currentLevel == 0 && keyboard_manager::get()->is_key_down(ALLEGRO_KEY_ENTER))
    {
        al_stop_samples();
        currentLevel++;
        al_rest(1);

    }

    if (currentLevel == 0 && inIntro == true)
    {
        ALLEGRO_BITMAP *background=image_library::get()->get("logo.png");
        al_flip_display();
        ALLEGRO_SAMPLE *startup = al_load_sample("music/start.ogg");
        al_play_sample(startup, 1,0,1, ALLEGRO_PLAYMODE_ONCE, 0);
        al_clear_to_color(al_map_rgb (0,0,0));
        al_rest(1);
        al_draw_bitmap(background,180,50,0);
        al_flip_display();
        al_rest(1);
        ALLEGRO_BITMAP *main=image_library::get()->get("main.png");
        al_draw_bitmap (main,160,-50,0);
        al_flip_display();
        ALLEGRO_SAMPLE *title = al_load_sample("music/title.ogg");
        al_play_sample(title, 1,0,1, ALLEGRO_PLAYMODE_ONCE, 0);
        inIntro = false;
    }

    if (currentLevel == 1)
    {
        ALLEGRO_BITMAP *background=image_library::get()->get("levelOne.png");
        al_draw_bitmap(background,0,0,0);
        al_flip_display();
        currentLevel++;
        al_rest(1);
        ALLEGRO_SAMPLE *song1=al_load_sample("music/song1.ogg");
        al_play_sample(song1, .5, 0, 1, ALLEGRO_PLAYMODE_LOOP, 0);
    }

    if (currentLevel == 2)
    {

        ALLEGRO_TRANSFORM t;
        al_identity_transform(&t);
        updateView(viewCor, Player->get_x(), Player->get_y(), 48, 48);
        al_translate_transform(&t, -viewCor[0],-viewCor[1]);
        al_use_transform(&t);

        ALLEGRO_BITMAP *background=image_library::get()->get("background.png");
        al_draw_bitmap(background,0,0,0);
        al_draw_bitmap(background,screen_width,0,0);
        al_draw_bitmap(background,screen_width*2,0,ALLEGRO_FLIP_HORIZONTAL);
        al_draw_bitmap(background,screen_width*3,0,ALLEGRO_FLIP_HORIZONTAL);

        for(vector<sprite*>::iterator it = sprites.begin(); it != sprites.end(); ++it)
            (*it)->draw(display);

        ALLEGRO_TRANSFORM atZero;
        al_identity_transform (&atZero);
        al_translate_transform(&atZero,0,0);
        al_use_transform(&atZero);
        std::stringstream ss;
        ss << score;
        al_draw_text(font, al_map_rgb(255,150,0), 575, 5, ALLEGRO_ALIGN_LEFT, "ATOMS COLLECTED: ");
        al_draw_textf(font, al_map_rgb(255,150,0), 765, 5, ALLEGRO_ALIGN_RIGHT, ss.str().c_str());

        for(std::vector<GUI_sprite*>::iterator it = stats.begin(); it != stats.end(); ++it)
            (*it)->draw(display);

        menu->drawIcon();

        if(Player->get_x() >= 3000)
        {
            ALLEGRO_BITMAP *background=image_library::get()->get("levelTwo.png");
            al_draw_bitmap(background,0,0,0);
            al_flip_display();
            currentLevel=3;
            al_rest(1);
            sprites.clear();
            stats.clear();
            menu_sprites.clear();
        }
    }

    if(currentLevel == 3)
    {
        ALLEGRO_BITMAP *image1=image_library::get()->get("characterWalk.png");
        ALLEGRO_BITMAP *image2=image_library::get()->get("baddie.png");
        ALLEGRO_BITMAP *rock=image_library::get()->get("rock.png");
        ALLEGRO_BITMAP *atom=image_library::get()->get("atom.png");
        menu_sprites.push_back(menu = new menu_sprite(screen_width/2-256/2 ,screen_height/2-132/2));
        sprites.push_back(new obstruction_sprite(100,125,rock));
        sprites.push_back(new obstruction_sprite(400,150,rock));
        sprites.push_back(new obstruction_sprite(570,150,rock));
        sprites.push_back(new obstruction_sprite(800,125,rock));
        sprites.push_back(new obstruction_sprite(1200,175,rock));
        sprites.push_back(new obstruction_sprite(1600,100,rock));
        sprites.push_back(Player = new player(image1,screen_width,screen_height,10,230,this,menu));
        sprites.push_back(new baddie(image2,screen_width,screen_height,400,75,0,0,this));
        sprites.push_back(new baddie(image2,screen_width,screen_height,750,250,0,0,this));
        sprites.push_back(new baddie(image2,screen_width,screen_height,1000,250,0,0,this));
        sprites.push_back(new baddie(image2,screen_width,screen_height,1250,250,0,0,this));
        sprites.push_back(new baddie(image2,screen_width,screen_height,2000,250,0,0,this));
        sprites.push_back(new collectible(atom,100,100,0,0));
        sprites.push_back(new collectible(atom,400,125,0,0));
        sprites.push_back(new collectible(atom,570,125,0,0));
        sprites.push_back(new collectible(atom,800,100,0,0));
        sprites.push_back(new collectible(atom,1200,150,0,0));
        sprites.push_back(new collectible(atom,1600,75,0,0));
        stats.push_back(new GUI_sprite(0,0,'h'));
        stats.push_back(new GUI_sprite (53,6,'r'));
        stats.push_back(new GUI_sprite (64,24,'b'));
        stats.push_back(new GUI_sprite (59,39,'y'));

        font = al_load_ttf_font("font/calibri.ttf", 18, 0);
        assert(font);
        currentLevel=4;
        score = 0;
    }


    if(currentLevel == 4)
    {
        ALLEGRO_TRANSFORM t;
        al_identity_transform(&t);
        updateView(viewCor, Player->get_x(), Player->get_y(), 48, 48);
        al_translate_transform(&t, -viewCor[0],-viewCor[1]);
        al_use_transform(&t);

        ALLEGRO_BITMAP *background=image_library::get()->get("forest.png");
        al_draw_bitmap(background,0,0,0);
        al_draw_bitmap(background,screen_width,0,0);
        al_draw_bitmap(background,screen_width*2,0,ALLEGRO_FLIP_HORIZONTAL);
        al_draw_bitmap(background,screen_width*3,0,ALLEGRO_FLIP_HORIZONTAL);

        for(vector<sprite*>::iterator it = sprites.begin(); it != sprites.end(); ++it)
            (*it)->draw(display);

        ALLEGRO_TRANSFORM atZero;
        al_identity_transform (&atZero);
        al_translate_transform(&atZero,0,0);
        al_use_transform(&atZero);

        std:stringstream ss;
        ss << score;
        al_draw_text(font, al_map_rgb(255,150,0), 575, 0, ALLEGRO_ALIGN_LEFT, "ATOMS COLLECTED: ");
        al_draw_textf(font, al_map_rgb(255,150,0), 765, 0, ALLEGRO_ALIGN_RIGHT, ss.str().c_str());

        for(std::vector<GUI_sprite*>::iterator it = stats.begin(); it != stats.end(); ++it)
            (*it)->draw(display);

        menu->drawIcon();

        if(Player->get_x() >= 3000)
        {
            ALLEGRO_BITMAP *background=image_library::get()->get("youWin.png");
            al_draw_bitmap(background,0,0,0);
            al_flip_display();
            currentLevel=5;
            al_rest(1);
            sprites.clear();
            stats.clear();
            menu_sprites.clear();
        }
    }

}

void world::pauseDraw()
{
    ALLEGRO_TRANSFORM atZero;
    al_identity_transform (&atZero);
    al_translate_transform(&atZero,0,0);
    al_use_transform(&atZero);

    al_draw_tinted_bitmap(image_library::get()->get("background.png"), al_map_rgba_f(0, 0, 0, 0.5), 0, 0, 0);

    menu->draw(display);
    menu->drawItems();
    al_flip_display();
}


bool world::should_exit()
{
    return game_over;;
}

void world::addSprite(sprite* s)
{

    addSprites.push_back(s);
}

void world::removeSprite(sprite* s)
{

    removeSprites.push_back(s);
}

void world::updateView(float* viewCor, float x, float y, int width, int height)
{
    viewCor[0] = -(screen_width/3) + (Player->get_x() + width / 2);
    viewCor[2] = -(screen_height/3) + (Player->get_y() + height /2);

    if(viewCor[0] < 0)
    {
        viewCor[0] = 0;
    }
    if(viewCor[0] >= screen_width*3)
    {
        viewCor[0] = screen_width*3;
    }
    if(viewCor[1]<0)
    {
        viewCor[1]=0;
    }


}

GUI_sprite* world::getStatBar(char c)
{
    if(c =='r')
    {

        return stats.at(1);

    }
    if(c =='b')
    {
        return stats.at(2);

    }

    if(c =='g')
    {
        return stats.at(3);
    }

}



}
