#include "Medic.h"

namespace mtm
{
    const units_t Medic::MEDIC_MOVEMENT_RANGE = 5;
    const units_t Medic::MEDIC_RELOAD_AMMO_ADDITION = 5;
    const units_t Medic::MEDIC_ATTACK_AMMO_COST = 1;
    const char Medic::IDENTIFIER_CHAR_POWERLIFTERS = 'M';
    const char Medic::IDENTIFIER_CHAR_CROSSFITTERS = 'm';

    Medic::Medic(units_t health_points, units_t ammo_points, units_t range, units_t power, mtm::Team team) :
            Character(health_points, ammo_points,range, power, team, MEDIC_MOVEMENT_RANGE, MEDIC_RELOAD_AMMO_ADDITION,
                      MEDIC_ATTACK_AMMO_COST, IDENTIFIER_CHAR_POWERLIFTERS, IDENTIFIER_CHAR_CROSSFITTERS){
    }

    std::shared_ptr<Character>Medic::clone() const {
        return static_cast<std::shared_ptr<Character>>(new Medic(*this));
    }

    bool Medic::isCharacterHasEnoughAmmo(const std::shared_ptr<Character> &target_ptr) const {
        if (target_ptr == nullptr)
        {
            return (this->getCharacterAmmo() >= this->getCharacterAttackAmmoCost());
        }
        else
        {
            if (isTargetOnSameTeam(target_ptr))
            {
                return true;
            }
        }
        return (this->getCharacterAmmo() >= this->getCharacterAttackAmmoCost());
    }

    bool Medic::isTargetInStrikeRange(const mtm::GridPoint& src_coordinates,const mtm::GridPoint& dst_coordinates)
    const
    {
        return (mtm::GridPoint::distance(src_coordinates, dst_coordinates) <= getCharacterRange());
    }

    bool Medic::isStrikeLegal(const mtm::GridPoint& src_coordinates, const mtm::GridPoint& dst_coordinates,
                              std::shared_ptr<Character> target) const {
        return !(isTargetEmpty(target) || (src_coordinates == dst_coordinates));
    }

    units_t Medic::performStrike(const mtm::GridPoint &src_coordinates, const mtm::GridPoint &main_target_coordinates,
                             const mtm::GridPoint &current_target_coordinates, std::shared_ptr<Character>target){
        if (!(main_target_coordinates == current_target_coordinates))
        {
            return 0;
        }
        else
        {
            if (isTargetOnSameTeam(target))
            {
                return (getCharacterPower());
            }
            setCharacterAmmo(-getCharacterAttackAmmoCost());
            return (-getCharacterPower());
        }
    }

}
