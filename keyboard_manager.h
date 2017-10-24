#ifndef __CDS_KEYBOARD_MANAGER_H
#define __CDS_KEYBOARD_MANAGER_H
#include <set>

namespace labX
{
class keyboard_manager
{
public:
    static keyboard_manager *get();

    keyboard_manager();

    /**
     * Answers true iff the specified key currently held down
     */
    bool is_key_down(int keycode);

    /**
     * Called when a key is pressed
     */
    void key_down(int keycode);

    /**
     * Called when a key is released
     */
    void key_up(int keycode);

    bool no_key_down() const;

private:
    static keyboard_manager *default_instance;
    std::set<int> down;
};
}

#endif /* __CDS_KEYBOARD_MANAGER_H */

