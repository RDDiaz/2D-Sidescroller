#include "mouse_manager.h"
#include <cstdlib>


namespace csis3700
{
mouse_manager *mouse_manager::default_instance = NULL;

mouse_manager *mouse_manager::get()
{
    if (default_instance == NULL)
        default_instance = new mouse_manager();
    return default_instance;
}

mouse_manager::mouse_manager()
{
}

bool mouse_manager::is_key_down(int keycode)
{
    return down.find(keycode) != down.end();
}

void mouse_manager::key_down(int keycode)
{
    down.insert(keycode);
}

void mouse_manager::key_up(int keycode)
{
    down.erase(keycode);
}

}
