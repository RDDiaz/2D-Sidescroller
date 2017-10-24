#include "keyboard_manager.h"
#include <cstdlib>


namespace labX
{
keyboard_manager *keyboard_manager::default_instance = NULL;

keyboard_manager *keyboard_manager::get()
{
    if (default_instance == NULL)
        default_instance = new keyboard_manager();
    return default_instance;
}

keyboard_manager::keyboard_manager()
{
}

bool keyboard_manager::is_key_down(int keycode)
{
    return down.find(keycode) != down.end();
}

void keyboard_manager::key_down(int keycode)
{
    down.insert(keycode);
}

void keyboard_manager::key_up(int keycode)
{
    down.erase(keycode);
}

bool keyboard_manager::no_key_down() const
{
    return down.size() == 0;
}

}
