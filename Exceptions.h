#ifndef GAME_PROJECT_EXCEPTIONS_H
#define GAME_PROJECT_EXCEPTIONS_H

#include <iostream>

namespace mtm
{
    /**
    * class Exception
    * inherits from class std::exception.
    * represents general exception in our game.
    */
    class Exception : public std::exception {
    private:
        std::string msg;
        static const char* BASE_MSG;
    public:
        /**
        * what: method the returns an info string about the exception.
        * @return information about of the exception.
        */
        const char* what() const noexcept override;
        /**
        * constructor that receives 1 parameter.
        * @param error : error message to print as part of the what method.
        */
        explicit Exception(const std::string& error);
        /**
        * ~Exception: class destructor.
        */
        ~Exception() override = default;
    };
    /**
    * class IllegalArgument
    * inherits from class Exception.
    * exception is called when the user tries to perform an action with illegal parameter
    */
    class IllegalArgument : public Exception {
    public:
        IllegalArgument();
    };
    /**
    * class IllegalCell
    * inherits from class Exception.
    * exception is called when dst coordinates of a given action ate not inside the board ranges
    */
    class IllegalCell : public Exception {
    public:
        IllegalCell();
    };
    /**
    * class CellEmpty
    * inherits from class Exception.
    * exception is called when the user tries to perform an action over an empty cell although it is invalid
    */
    class CellEmpty : public Exception {
    public:
        CellEmpty();
    };
    /**
    * class MoveTooFar
    * inherits from class Exception.
    * exception is called when the user tries to move a character further than his range limitation
    */
    class MoveTooFar : public Exception {
    public:
        MoveTooFar();
    };
    /**
    * class CellOccupied
    * inherits from class Exception.
    * exception is called when the user tries to add/move character to an occupied cell
    */
    class CellOccupied : public Exception {
    public:
        CellOccupied();
    };
    /**
    * class OutOfRange
    * inherits from class Exception.
    * exception is called when character tries to attack target that is out of his range limitations
    */
    class OutOfRange : public Exception {
    public:
        OutOfRange();
    };
    /**
    * class OutOfAmmo
    * inherits from class Exception.
    * exception is called when the character tries to perform an attack but he doesn't have enough ammo to perform it.
    */
    class OutOfAmmo : public Exception {
    public:
        OutOfAmmo();
    };
    /**
    * class IllegalTarget
    * inherits from class Exception.
    * exception is called when character cannot perform the attack from different reasons than ammo or range
    */
    class IllegalTarget : public Exception {
    public:
        IllegalTarget();
    };
}

#endif //GAME_PROJECT_EXCEPTIONS_H
