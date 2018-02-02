# Ghost Vendetta

A game for [Arduboy](https://www.arduboy.com/) in the style of Bomberman.

https://github.com/kenprice/ghost-vendetta/assets/8813522/0537538c-f140-4542-98f1-2b8ebb0d1d30

## ???

Back in Christmas 2017, a dear friend of mine gifted me an Arduboy, an extremely limited game system with a monochrome, 1-bit-per-pixel display and limited memory (32KB Flash, 2.5KB RAM, and 1KB EEPROM for storage).
The limitation is the point! I've played with the Arduino before, but this device challenged me to write code in an unforgiving environment, coming from a world that doesn't concern itself with such
mundane details as how much memory we consume (and memory leaks - what's that?)

Some of the early lessons involved memory optimization and management, of course. Keep consts in `PROGMEM`, bitfield `struct`s (need only 3 bits? pack it into 3 bits), and avoiding dynamic memory allocation. Why?
Well, I could've used it, but RAM is extremely limited, so it was more pragmatic to use a static array for things like entities, sprites to render, etc. rather than potentially `malloc`ing beyond what the system
can handle. In the context of a simple game like this, it's easy to handle a case where there are too many entitites - just don't create too many. I've reinvented the wheel, as this is a common technique for old-
school games and embedded applications in general.

A rare entry into my graveyard of side-projects, as this project was actually (something that can be considered) completed!
