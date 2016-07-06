/*
COPYRIGHT (c) 2016 Callum Wilson

MIT License

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <irrlicht.h>
#include <array>

class Input_Handler : public irr::IEventReceiver {
public:
    /**
     * Called when an input event occurs
     * \param event The event that has occurred
     * \return true if the event has been completely handled, false otherwise
     */
    virtual bool OnEvent(const irr::SEvent& event);

    /**
     * Check whether the specified key is down
     * \param key_code The key code of the key to check
     * \return true if the key is down, false otherwise
     */
    virtual bool is_key_down(irr::EKEY_CODE key_code) const;

    /**
     * Constructor
     */
    Input_Handler();

private:
    std::array<bool,irr::KEY_KEY_CODES_COUNT> key_states{};    /**< Array of all the
                                                                key states */

};
#endif
