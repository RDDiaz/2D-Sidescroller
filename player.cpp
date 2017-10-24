#include "keyboard_manager.h"
#include "image_library.h"
#include "player.h"
#include "baddie.h"
#include "projectile.h"
#include "GUI_sprite.h"
#include "menu_sprite.h"
#include "obstruction_sprite.h"
#include "collectible.h"
#include <vector>
#include <iostream>
#include <typeinfo>
#include "allegro5/allegro_audio.h"
#include "allegro5/allegro_acodec.h"

namespace labX
{
player::player(ALLEGRO_BITMAP* initial_bitmap, size_t world_width, size_t world_height, float initial_x, float initial_y, world* w, menu_sprite* m) :
    player_sprite(initial_x, initial_y)
{
    height = world_height;
    width = world_width;
    theWorld = w;
    is_falling = false;
    is_attacking = false;
    health = max_health;
    mana = max_mana;
    other = 0;

    menu = m;

    create_sequences();

    set_image_sequence(sequences.at(8));
    last_direction = 'r';
    ground = height-70;
}

player::~player()
{
}


void player::handle_event(ALLEGRO_EVENT ev)
{

    if(ev.type == ALLEGRO_EVENT_KEY_DOWN && keyboard_manager::get()->is_key_down(ALLEGRO_KEY_Q)
            && mana >= 20 && (menu->get_equipped() == "gun" || menu->get_equipped() == "bow" || menu->get_equipped() == "crossbow")
            && !keyboard_manager::get()->is_key_down(ALLEGRO_KEY_DOWN))
    {
        shootGun();
        is_attacking = true;
    }

//    if(ev.type == ALLEGRO_EVENT_KEY_DOWN && keyboard_manager::get()->is_key_down(ALLEGRO_KEY_Q)
//            && (!keyboard_manager::get()->is_key_down(ALLEGRO_KEY_RIGHT) || !keyboard_manager::get()->is_key_down(ALLEGRO_KEY_LEFT))
//            && !keyboard_manager::get()->is_key_down(ALLEGRO_KEY_DOWN) && mana >= 20 && (menu->get_equipped()) == "gun")
//    {
//        shootGun();
//        is_attacking = true;
//    }
    if(ev.type == ALLEGRO_EVENT_KEY_DOWN && (keyboard_manager::get()->is_key_down(ALLEGRO_KEY_Q) ||
            keyboard_manager::get()->is_key_down(ALLEGRO_KEY_DOWN)))
    {
        is_attacking = true;
    }
}

void player::advance_by_time(double dt)
{
    theWorld->getStatBar('b')->setMana(mana);
    theWorld->getStatBar('g')->setOther(other);
    vec2d downforce(0,5);
    vec2d wait(0,0);
    set_velocity(wait);
    velocity += downforce;
    mana += dt*1;
    if(mana > max_mana)
    {
        mana = max_mana;
    }

    if(position.get_y() >= ground )
    {
        vec2d floor(get_x(), ground);
        position = floor;
        on_ground = true;
        is_falling = false;
        if(last_direction == 'r')
        {
            set_image_sequence(sequences.at(0));
        }
        else
        {
            set_image_sequence(sequences.at(1));
        }
    }

    if(position.get_x() <= 0 )
    {
        vec2d edge(0, get_y());
        position = edge;
    }

    if(position.get_x() >= 3150 )
    {
        vec2d edge2(3150, get_y());
        position = edge2;
    }

    if(position.get_y() <= 0)
    {
        vec2d top(get_x(), 0);
        position = top;
    }

    if(keyboard_manager::get()->is_key_down(ALLEGRO_KEY_RIGHT))
    {
        set_image_sequence(sequences.at(0));
        vec2d right(2,.5);
        position += right;
        last_direction = 'r';

    }
    else if(keyboard_manager::get()->is_key_down(ALLEGRO_KEY_LEFT))
    {
        set_image_sequence(sequences.at(1));
        vec2d left(-2,.5);
        position += left;
        last_direction = 'l';
    }

    if(keyboard_manager::get()->is_key_down(ALLEGRO_KEY_UP))
    {
        on_ground = false;
        is_falling = true;
        if(last_direction == 'r')
        {
            set_image_sequence(sequences.at(12));
            jump_time += dt;
            if(jump_time < .2)
            {
                vec2d up(5,-12);
                position += up;
            }
            else
            {
                jump_time = 0;
                keyboard_manager::get()->key_up(ALLEGRO_KEY_UP);
            }

        }
        else
        {
            set_image_sequence(sequences.at(12));
            jump_time += dt;
            if(jump_time < .2)
            {
                vec2d up(-5,-12);
                position += up;
            }
            else
            {
                jump_time = 0;
                keyboard_manager::get()->key_up(ALLEGRO_KEY_UP);
            }
        }
    }

    if(on_ground && keyboard_manager::get()->is_key_down(ALLEGRO_KEY_UP)&& keyboard_manager::get()->is_key_down(ALLEGRO_KEY_RIGHT))
    {
        on_ground = false;
        is_falling = true;
        last_direction = 'r';
        set_image_sequence(sequences.at(12));
        jump_time += dt;
        if(jump_time < .2)
        {
            vec2d up(5,-20);
            position += up;
        }
        else
        {
            jump_time = 0;
            keyboard_manager::get()->key_up(ALLEGRO_KEY_UP);
        }
    }
    else if(on_ground && keyboard_manager::get()->is_key_down(ALLEGRO_KEY_UP)&& keyboard_manager::get()->is_key_down(ALLEGRO_KEY_LEFT))
    {
        on_ground = false;
        is_falling = true;
        last_direction = 'l';
        set_image_sequence(sequences.at(12));
        jump_time += dt;
        if(jump_time < .2)
        {
            vec2d up(-5,-20);
            position += up;
        }
        else
        {
            jump_time = 0;
            keyboard_manager::get()->key_up(ALLEGRO_KEY_UP);
        }
    }

    if(keyboard_manager::get()->is_key_down(ALLEGRO_KEY_DOWN) && keyboard_manager::get()->is_key_down(ALLEGRO_KEY_RIGHT)
            && !keyboard_manager::get()->is_key_down(ALLEGRO_KEY_UP) && !keyboard_manager::get()->is_key_down(ALLEGRO_KEY_W)
            && !keyboard_manager::get()->is_key_down(ALLEGRO_KEY_Q) && !is_falling && is_attacking)
    {
        is_attacking = true;
        set_image_sequence(sequences.at(6));
        attack_time += dt;
        if(attack_time < .25)
        {
            vec2d friction(5,0);
            position += friction;
        }
        else
        {
            attack_time = 0;
            keyboard_manager::get()->key_up(ALLEGRO_KEY_DOWN);
            is_attacking = false;
        }
        last_direction = 'r';
    }
    else if(keyboard_manager::get()->is_key_down(ALLEGRO_KEY_DOWN)&& keyboard_manager::get()->is_key_down(ALLEGRO_KEY_LEFT)
            && !keyboard_manager::get()->is_key_down(ALLEGRO_KEY_UP) && !keyboard_manager::get()->is_key_down(ALLEGRO_KEY_W)
            && !keyboard_manager::get()->is_key_down(ALLEGRO_KEY_Q) && !is_falling)
    {
        is_attacking = true;
        set_image_sequence(sequences.at(7));
        attack_time += dt;
        if(attack_time < .25)
        {
            vec2d friction(-5,0);
            position += friction;
        }
        else
        {
            attack_time = 0;
            keyboard_manager::get()->key_up(ALLEGRO_KEY_DOWN);
            is_attacking = false;
        }
        last_direction = 'l';
    }

    if(keyboard_manager::get()->is_key_down(ALLEGRO_KEY_Q))
    {
        if(last_direction == 'r')
        {
            is_attacking = true;
            attack_time += dt;
            if(attack_time < .25)
            {
                if((menu->get_equipped()) == "sword")
                {
                    set_image_sequence(sequences.at(13));
                }
                else if((menu->get_equipped()) == "gun")
                {
                    set_image_sequence(sequences.at(15));
                }
                else if((menu->get_equipped()) == "axe")
                {
                    set_image_sequence(sequences.at(17));
                }
                else if((menu->get_equipped()) == "claw")
                {
                    set_image_sequence(sequences.at(19));
                }
                else if((menu->get_equipped()) == "crossbow")
                {
                    set_image_sequence(sequences.at(21));
                }
                else if((menu->get_equipped()) == "bow")
                {
                    set_image_sequence(sequences.at(23));
                }
                else if((menu->get_equipped()) == "yPot")
                {
                    set_image_sequence(sequences.at(25));
                }
                else if((menu->get_equipped()) == "rPot")
                {
                    set_image_sequence(sequences.at(27));
                }
                else if((menu->get_equipped()) == "bPot")
                {
                    set_image_sequence(sequences.at(29));
                }

                else
                {
                    set_image_sequence(sequences.at(4));
                }
            }
            else
            {
                attack_time = 0;
                keyboard_manager::get()->key_up(ALLEGRO_KEY_Q);
                is_attacking = false;
            }
        }
        else
        {
            is_attacking = true;
            attack_time += dt;
            if(attack_time < .25)
            {

                if((menu->get_equipped()) == "sword")
                {
                    set_image_sequence(sequences.at(14));
                }
                else if((menu->get_equipped()) == "gun")
                {
                    set_image_sequence(sequences.at(16));
                }
                else if((menu->get_equipped()) == "axe")
                {
                    set_image_sequence(sequences.at(18));
                }
                else if((menu->get_equipped()) == "claw")
                {
                    set_image_sequence(sequences.at(20));
                }
                else if((menu->get_equipped()) == "crossbow")
                {
                    set_image_sequence(sequences.at(22));
                }
                else if((menu->get_equipped()) == "bow")
                {
                    set_image_sequence(sequences.at(24));
                }
                else
                {
                    set_image_sequence(sequences.at(5));
                }
            }
            else
            {
                attack_time = 0;
                keyboard_manager::get()->key_up(ALLEGRO_KEY_Q);
                is_attacking = false;
            }
        }
    }

    if(keyboard_manager::get()->no_key_down())
    {
        if(last_direction == 'r')
        {
            set_image_sequence(sequences.at(8));
        }
        else
        {
            set_image_sequence(sequences.at(9));
        }
    }

    if(velocity.get_y() >= 2)
    {
        ground = height - 70;
        is_falling = true;
    }


    if(is_falling && !on_ground && jump_time == 0)
    {
        if(last_direction == 'r')
        {
            vec2d right(1,0);
            set_image_sequence(sequences.at(2));
            velocity += right + downforce;
        }
        else
        {
            vec2d left(-1,0);
            set_image_sequence(sequences.at(3));
            velocity += left + downforce;
        }
    }

//    std::cout << velocity.get_x() << "   " << velocity.get_y() << "\n";
    time += dt;
    position += velocity;

}

void player::resolve(const collision& collision, sprite* other)
{
    if(!other->is_baddie() || !other->is_collectible() || other->is_projectile())
    {
//        std::cout << "OBSTRUCTION SPRITE\n";
        ground = other->get_y()-get_height()+10;
        is_falling = false;
        vec2d v(0,-1);
        velocity += v;
    }

    if(other->is_collectible())
    {
        other->set_passive(false);
        theWorld->increaseScore(1);
        theWorld->removeSprite(other);
//        std::cout << "COLLECTED\n";
    }

    if(other->is_baddie() && !is_attacking)
    {
        if (last_direction == 'r')
        {
            health -= 5;
            theWorld->getStatBar('r')->setHealth(health);
            set_velocity(vec2d (-5,get_y()));
            position+=velocity;
        }
        if (last_direction == 'l')
        {
            health -= 5;
            theWorld->getStatBar('r')->setHealth(health);
            set_velocity(vec2d (5,get_y()));
            position+=velocity;
        }
        if(health <= 0)
        {
            theWorld->removeSprite(this);
            al_rest(1);
            ALLEGRO_BITMAP *background=image_library::get()->get("youLose.png");
            al_draw_bitmap(background,0,0,0);
            al_flip_display();
            al_rest(2);
            theWorld->set_exit(true);
        }
    }

    if(other->is_baddie() && is_attacking)
    {
        theWorld->removeSprite(other);
    }

}

void player::set_velocity(const vec2d& v)
{
    velocity = v;
}

vec2d player::get_acceleration() const
{
    vec2d a(0,0);
    for(std::vector<vec2d>::const_iterator it = forces.begin(); it != forces.end(); ++it)
        a += *it;
    return a;
}

vec2d player::get_velocity() const
{
    return velocity;
}

void player::add_force(vec2d f)
{
    forces.push_back(f);
}

void player::create_sequences()
{

    image_sequence *PlayerRight = new image_sequence;
    PlayerRight->add_image(al_create_sub_bitmap(image_library::get()->get("characterWalk.png"),0,96,48,48), .3);
    PlayerRight->add_image(al_create_sub_bitmap(image_library::get()->get("characterWalk.png"),48,96,48,48), .3);
    PlayerRight->add_image(al_create_sub_bitmap(image_library::get()->get("characterWalk.png"),96,96,48,48), .3);
    PlayerRight->add_image(al_create_sub_bitmap(image_library::get()->get("characterWalk.png"),48,96,48,48), .3);

    image_sequence *PlayerLeft = new image_sequence;
    PlayerLeft->add_image(al_create_sub_bitmap(image_library::get()->get("characterWalk.png"),0, 48,48,48), .3);
    PlayerLeft->add_image(al_create_sub_bitmap(image_library::get()->get("characterWalk.png"),48,48,48,48), .3);
    PlayerLeft->add_image(al_create_sub_bitmap(image_library::get()->get("characterWalk.png"),96,48,48,48), .3);
    PlayerLeft->add_image(al_create_sub_bitmap(image_library::get()->get("characterWalk.png"),48,48,48,48), .3);

    image_sequence *PlayerFallRight = new image_sequence;
    PlayerFallRight->add_image(al_create_sub_bitmap(image_library::get()->get("characterBattlerRight.png"),0, 0,40,48), .2);
    PlayerFallRight->add_image(al_create_sub_bitmap(image_library::get()->get("characterBattlerRight.png"),48, 0,40,48), .2);

    image_sequence *PlayerFallLeft = new image_sequence;
    PlayerFallLeft->add_image(al_create_sub_bitmap(image_library::get()->get("characterBattlerLeft.png"),400, 0,40,48), .2);
    PlayerFallLeft->add_image(al_create_sub_bitmap(image_library::get()->get("characterBattlerLeft.png"),352, 0,40,48), .2);

    image_sequence *PlayerAtkRight = new image_sequence;
    PlayerAtkRight->add_image(al_create_sub_bitmap(image_library::get()->get("characterBattlerRight.png"),146,0,48,48), .1);

    image_sequence *PlayerAtkLeft = new image_sequence;
    PlayerAtkLeft->add_image(al_create_sub_bitmap(image_library::get()->get("characterBattlerLeft.png"),194,0,48,48), .1);

    image_sequence *PlayerSlideRight = new image_sequence;
    PlayerSlideRight->add_image(al_create_sub_bitmap(image_library::get()->get("characterBattlerRight.png"),2,245,48,48), .1);

    image_sequence *PlayerSlideLeft = new image_sequence;
    PlayerSlideLeft->add_image(al_create_sub_bitmap(image_library::get()->get("characterBattlerLeft.png"),390,245,48,48), .1);

    image_sequence *PlayerWaitRight = new image_sequence;
    PlayerWaitRight->add_image(al_create_sub_bitmap(image_library::get()->get("characterWalk.png"),0,96,48,48), 0);

    image_sequence *PlayerWaitLeft = new image_sequence;
    PlayerWaitLeft->add_image(al_create_sub_bitmap(image_library::get()->get("characterWalk.png"),0, 48,48,48), 0);

    image_sequence *PlayerSpellRight = new image_sequence;
    PlayerSpellRight->add_image(al_create_sub_bitmap(image_library::get()->get("characterBattlerRight.png"),148,98,40,48),.1);

    image_sequence *PlayerSpellLeft = new image_sequence;
    PlayerSpellLeft->add_image(al_create_sub_bitmap(image_library::get()->get("characterBattlerLeft.png"),251,97,40,48),.1);

    image_sequence *FlashOut = new image_sequence;
    FlashOut->add_image(al_create_sub_bitmap(image_library::get()->get("effects.png"),128,43,21,20),.25);
    FlashOut->add_image(al_create_sub_bitmap(image_library::get()->get("effects.png"),107,43,20,20),.25);
    FlashOut->add_image(al_create_sub_bitmap(image_library::get()->get("effects.png"),86,43,20,20),.25);
    FlashOut->add_image(al_create_sub_bitmap(image_library::get()->get("effects.png"),67,46,15,15),.25);

    image_sequence *FlashIn = new image_sequence;
    FlashIn->add_image(al_create_sub_bitmap(image_library::get()->get("effects.png"),128,43,21,20),.1);
    FlashIn->add_image(al_create_sub_bitmap(image_library::get()->get("effects.png"),107,43,20,20),.1);
    FlashIn->add_image(al_create_sub_bitmap(image_library::get()->get("effects.png"),86,43,20,20),.1);
    FlashIn->add_image(al_create_sub_bitmap(image_library::get()->get("effects.png"),67,46,15,15),.1);

    image_sequence *SwordRight = new image_sequence;
    SwordRight->add_image(al_create_sub_bitmap(image_library::get()->get("characterAttackR.png"),148,0,56,48),.1);

    image_sequence *AxeRight = new image_sequence;
    AxeRight->add_image(al_create_sub_bitmap(image_library::get()->get("characterAttackR.png"),0,0,75,48),.1);

    image_sequence *GunRight = new image_sequence;
    GunRight->add_image(al_create_sub_bitmap(image_library::get()->get("characterAttackR.png"),76,0,65,48),.1);

    image_sequence *ClawRight = new image_sequence;
    ClawRight->add_image(al_create_sub_bitmap(image_library::get()->get("characterAttackR.png"),148,50,65,48),.1);

    image_sequence *CrossbowRight = new image_sequence;
    CrossbowRight->add_image(al_create_sub_bitmap(image_library::get()->get("characterAttackR.png"),76,50,65,48),.1);

    image_sequence *BowRight = new image_sequence;
    BowRight->add_image(al_create_sub_bitmap(image_library::get()->get("characterAttackR.png"),0,50,65,48),.1);


    image_sequence *SwordLeft = new image_sequence;
    SwordLeft->add_image(al_create_sub_bitmap(image_library::get()->get("characterAttackL.png"),0,0,65,48),.1);

    image_sequence *AxeLeft = new image_sequence;
    AxeLeft->add_image(al_create_sub_bitmap(image_library::get()->get("characterAttackL.png"),130,0,75,48),.1);

    image_sequence *GunLeft = new image_sequence;
    GunLeft->add_image(al_create_sub_bitmap(image_library::get()->get("characterAttackL.png"),70,0,55,48),.1);

    image_sequence *ClawLeft = new image_sequence;
    ClawLeft->add_image(al_create_sub_bitmap(image_library::get()->get("characterAttackL.png"),0,50,65,48),.1);

    image_sequence *CrossbowLeft = new image_sequence;
    CrossbowLeft->add_image(al_create_sub_bitmap(image_library::get()->get("characterAttackL.png"),60,50,65,48),.1);

    image_sequence *BowLeft = new image_sequence;
    BowLeft->add_image(al_create_sub_bitmap(image_library::get()->get("characterAttackL.png"),148,50,65,48),.1);

    sequences.push_back(PlayerRight); // 0
    sequences.push_back(PlayerLeft); // 1
    sequences.push_back(PlayerFallRight); // 2
    sequences.push_back(PlayerFallLeft); // 3
    sequences.push_back(PlayerAtkRight); // 4
    sequences.push_back(PlayerAtkLeft); // 5
    sequences.push_back(PlayerSlideRight); // 6
    sequences.push_back(PlayerSlideLeft); // 7
    sequences.push_back(PlayerWaitRight); // 8
    sequences.push_back(PlayerWaitLeft); // 9
    sequences.push_back(PlayerSpellRight); // 10
    sequences.push_back(PlayerSpellLeft); // 11
    sequences.push_back(FlashOut); // 12
    sequences.push_back(SwordRight); //13
    sequences.push_back(SwordLeft); //14
    sequences.push_back(GunRight); //15
    sequences.push_back(GunLeft); //16
    sequences.push_back(AxeRight); //17
    sequences.push_back(AxeLeft); //18
    sequences.push_back(ClawRight); //19
    sequences.push_back(ClawLeft); //20
    sequences.push_back(CrossbowRight); //21
    sequences.push_back(CrossbowLeft); //22
    sequences.push_back(BowRight); //23
    sequences.push_back(BowLeft); //24



}

void player::shootGun()
{
    mana -= 20;
    if(mana < 0)
        mana = 0;

    if(last_direction == 'r')
    {
        theWorld->addSprite(new projectile(width,height,get_x()+85,get_y()+15,get_velocity().get_x()+200,0,'r',theWorld));
        theWorld->getStatBar('b')->setMana(mana);
        if(mana >=20)
        {
            ALLEGRO_SAMPLE *shoot=al_load_sample("music/shoot.ogg");
            al_play_sample(shoot, .5, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
        }

    }
    else
    {
        theWorld->addSprite(new projectile(width,height,get_x()-20,get_y()+25,get_velocity().get_x()-200,0,'l',theWorld));
        theWorld->getStatBar('b')->setMana(mana);
        if(mana >=20)
        {
            ALLEGRO_SAMPLE *shoot=al_load_sample("music/shoot.ogg");
            al_play_sample(shoot, .5, 0, 10, ALLEGRO_PLAYMODE_ONCE, 0);
        }
    }
}
}

