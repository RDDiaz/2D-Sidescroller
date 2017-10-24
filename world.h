#ifndef __CDS_WORLD_H
#define __CDS_WORLD_H

#include "allegro5/allegro.h"
#include "sprite.h"
#include "player_sprite.h"
#include "GUI_sprite.h"
#include "menu_sprite.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include <vector>
#include <sstream>

namespace labX
{
class world;
}
#include "player.h"
#include "projectile.h"
#include "baddie.h"

namespace labX
{
class player;
class projectile;
class baddie;

class world
{
public:
    /**
     * Construct the world. The display is passed in simply to make it
     * possible to modify options or access the backbuffer. DO NOT
     * store the display in an instance variable. DO NOT start drawing
     * on the screen. Just load bitmaps etc.
     */
    world(ALLEGRO_DISPLAY *display,std::size_t window_width, std::size_t window_height);

    /**
     * Free any resources being used by the world.
     */
    ~world();

    /**
     * Block the copy constructor.  Worlds should not be copied to
     * just assert(false)
     */
    world(const world& other);

    /**
     * Block operator =.  Worlds should not be assigned.
     */
    world& operator =(const world& other);

    /**
     * Update the state of the world based on the event ev.
     */
    void handle_event(ALLEGRO_EVENT ev);

    /**
     * Advance the state of the world forward by the specified time.
     */
    void advance_by_time(double dt);

    /**
     * Draw the world. Note that the display variable is passed only
     * because it might be needed to switch the target bitmap back to
     * the backbuffer.
     */
    void draw(ALLEGRO_DISPLAY *display, float time);
    void pauseDraw();

    /**
     * Return true iff game is over and window should close
     */
    bool should_exit();

    void set_exit(bool b)
    {
        game_over = b;
    }

    void updateView(float* viewCor, float x, float y, int width, int height);

    void addSprite(sprite* s);

    void removeSprite(sprite* s);

    GUI_sprite* getStatBar(char c);

    void setPause(bool b)
    {
        paused = b;
    }

    bool getPause()
    {
        return paused;
    }

    bool getIntro()
    {
        return inIntro;
    }

    void increaseScore(int i)
    {
        score += i;
    }



private:
    float screen_width;
    float screen_height;
    void resolve_collisions();
    player *Player;
    menu_sprite *menu;
    int currentLevel = 0;
    ALLEGRO_DISPLAY *display;
    ALLEGRO_FONT *font;
    float viewCor[3] {0,0,0};
    std::vector<sprite*> sprites;
    std::vector<menu_sprite*> menu_sprites;
    std::vector<GUI_sprite*> stats;
    std::vector<sprite*> addSprites;
    std::vector<sprite*> removeSprites;
    bool paused = false;
    bool inIntro = true;
    int score = 0;
    bool game_over = false;
};
}

#endif /* WORLD_H */
