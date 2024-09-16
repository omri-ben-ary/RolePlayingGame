#include "Exceptions.h"

namespace mtm
{
    using std::string;
    static const char* const ILLEGAL_ARGUMENT_STR = "IllegalArgument";
    static const char* const ILLEGAL_CELL_STR = "IllegalCell";
    static const char* const CELL_EMPTY_STR = "CellEmpty";
    static const char* const MOVE_TOO_FAR_STR = "MoveTooFar";
    static const char* const CELL_OCCUPIED_STR = "CellOccupied";
    static const char* const OUT_OF_RANGE_STR = "OutOfRange";
    static const char* const OUT_OF_AMMO_STR = "OutOfAmmo";
    static const char* const ILLEGAL_TARGET_STR = "IllegalTarget";
    const char* mtm::Exception::BASE_MSG = "A game related error has occurred: ";

    const char *mtm::Exception::what() const noexcept {
        return this->msg.c_str();
    }

    mtm::Exception::Exception(const std::string& error) :
            msg(BASE_MSG + error)
    {}

    mtm::IllegalArgument::IllegalArgument() :
            Exception(ILLEGAL_ARGUMENT_STR)
    {}

    mtm::IllegalCell::IllegalCell() :
            Exception(ILLEGAL_CELL_STR)
    {}

    mtm::CellEmpty::CellEmpty() :
            Exception(CELL_EMPTY_STR)
    {}

    mtm::MoveTooFar::MoveTooFar() :
            Exception(MOVE_TOO_FAR_STR)
    {}

    mtm::CellOccupied::CellOccupied() :
            Exception(CELL_OCCUPIED_STR)
    {}

    mtm::OutOfRange::OutOfRange() :
            Exception(OUT_OF_RANGE_STR)
    {}

    mtm::OutOfAmmo::OutOfAmmo() :
            Exception(OUT_OF_AMMO_STR)
    {}

    mtm::IllegalTarget::IllegalTarget() :
            Exception(ILLEGAL_TARGET_STR)
    {}

}
