#include "InputPlayer.h"
//ça ne prend en charge que deux joueur (number 0 ou 1)
InputPlayer::InputPlayer(int number)
    : moveUp((number == 0) ? input::Up : input::Z),
    moveDown((number == 0) ? input::Down : input::S),
    moveLeft((number == 0) ? input::Left : input::Q),
    moveRight((number == 0) ? input::Right : input::D),
    button1((number == 0) ? input::R : input::U),
    button2((number == 0) ? input::T : input::I),
    button3((number == 0) ? input::Y : input::O),
    button4((number == 0) ? input::F : input::J),
    button5((number == 0) ? input::G : input::K),
    button6((number == 0) ? input::H : input::L)
{
}
