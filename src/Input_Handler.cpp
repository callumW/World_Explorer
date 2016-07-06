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

#include <irrlicht.h>
#include "Input_Handler.h"

using namespace irr;

bool Input_Handler::OnEvent(const SEvent& event)
{
    if (event.EventType == EET_KEY_INPUT_EVENT) // Is the event a key event?
        key_states[event.KeyInput.Key] = event.KeyInput.PressedDown;

    return false;   //The event may need to be used by something else
}

bool Input_Handler::is_key_down(EKEY_CODE key_code) const
{
    return key_states[key_code];
}

Input_Handler::Input_Handler()
{
}
