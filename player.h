#ifndef _PLAYER_H
#define _PLAYER_H

#include "world.h"
#include "player_sprite.h"
#include "vec2d.h"
#include "collision.h"
#include "allegro5/allegro.h"
#include "GUI_sprite.h"
#include <vector>
#include <cstdlib>


namespace labX
{

class player : public player_sprite
{
public:

    player(ALLEGRO_BITMAP* initial_bitmap, std::size_t world_width, std::size_t world_height, float initial_x, float initial_y, world* w,menu_sprite*);

    /**
     * Destructor
     */
    virtual ~player();

    /**
     * these two should cause errors, no copying!
     */
    player(const player& other);
    player& operator =(const player& other);

    virtual void set_velocity(const vec2d& v);
    virtual vec2d get_velocity() const;
    virtual void handle_event(ALLEGRO_EVENT ev);
    virtual void resolve(const collision& collision, sprite* other);
    virtual void advance_by_time(double dt);
    virtual void add_force(vec2d f);
    virtual vec2d get_acceleration() const;
    void create_sequences();
    void shootGun();
    double getHealth()
    {
    return health;
    }

    bool is_passive() const
    {
        return false;
    }
    virtual bool is_player()
    {
        return true;
    }


private:

    ALLEGRO_BITMAP *bitmap; // DELETE
    std::size_t height;
    std::size_t width;
    vec2d velocity;
    world *theWorld;
    GUI_sprite *statBar;
    GUI_sprite *myHealth;
    GUI_sprite *myMana;
    GUI_sprite *myOther;
    menu_sprite *menu;
    std::vector<vec2d> forces;
    std::vector<image_sequence*> sequences;
    char last_direction;
    bool is_falling;
    bool is_attacking;
    bool on_ground;
    double health;
    double max_health = 100;
    double mana;
    double max_mana = 100;
    double other;
    double max_other = 100;
    double attack_time = 0;
    double jump_time = 0;
    double ground;
};

}

#endif // _PLAYER_H

