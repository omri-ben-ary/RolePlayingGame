#include "Soldier.h"

namespace mtm
{
    const units_t Soldier::SOLDIER_MOVEMENT_RANGE = 3;
    const units_t Soldier::SOLDIER_RELOAD_AMMO_ADDITION = 3;
    const units_t Soldier::SOLDIER_ATTACK_AMMO_COST = 1;
    const int Soldier::SOLDIER_SUB_STRIKE_RANGE = 3;
    const int Soldier::SOLDIER_SUB_STRIKE_DAMAGE = 2;
    const int Soldier::CEILING_FACTOR = 1;
    const char Soldier::IDENTIFIER_CHAR_POWERLIFTERS = 'S';
    const char Soldier::IDENTIFIER_CHAR_CROSSFITTERS = 's';

    Soldier::Soldier(units_t health_points, units_t ammo_points, units_t range, units_t power, mtm::Team team) :
            Character(health_points, ammo_points,range, power, team, SOLDIER_MOVEMENT_RANGE,
                      SOLDIER_RELOAD_AMMO_ADDITION, SOLDIER_ATTACK_AMMO_COST, IDENTIFIER_CHAR_POWERLIFTERS,
                      IDENTIFIER_CHAR_CROSSFITTERS){
    }

    std::shared_ptr<Character>Soldier::clone() const {
        return static_cast<std::shared_ptr<Character>>(new Soldier(*this));
    }

    bool Soldier::isTargetInStrikeRange(const mtm::GridPoint& src_coordinates, const mtm::GridPoint& dst_coordinates)
    const {
        return (mtm::GridPoint::distance(src_coordinates, dst_coordinates) <= getCharacterRange());
    }

    bool Soldier::isStrikeLegal(const mtm::GridPoint& src_coordinates, const mtm::GridPoint& dst_coordinates,
                                std::shared_ptr<Character> target) const {
        return ((src_coordinates.row == dst_coordinates.row) || (src_coordinates.col == dst_coordinates.col));
    }

    units_t Soldier::performCharacterMainStrike(const mtm::GridPoint& src_coordinates,
                                            const mtm::GridPoint& dst_coordinates,
                                            const std::shared_ptr<Character>& target)  {
        setCharacterAmmo(-getCharacterAttackAmmoCost());
        if (isTargetEmpty(target) || isTargetOnSameTeam(target))
        {
            return 0;
        }
        return (-getCharacterPower());
    }

    bool Soldier::isTargetInSecondaryStrikeRange(const mtm::GridPoint& main_target_coordinates,
                                                 const mtm::GridPoint& secondary_target_coordinates) const {
        if (main_target_coordinates == secondary_target_coordinates)
        {
            return false;
        }
        int distance_between_targets = mtm::GridPoint::distance(main_target_coordinates,
                                                                secondary_target_coordinates);
        int soldier_strike_range = getCharacterRange();
        return (distance_between_targets <=
        ((soldier_strike_range+SOLDIER_SUB_STRIKE_RANGE-CEILING_FACTOR)/SOLDIER_SUB_STRIKE_RANGE));
    }

    int Soldier::performCharacterSecondaryStrike(const mtm::GridPoint& main_target_coordinates,
                                                 const mtm::GridPoint& secondary_target_coordinates,
                                                 const std::shared_ptr<Character>& target) const {
        if (isTargetEmpty(target) || isTargetOnSameTeam(target))
        {
            return 0;
        }
        if (!(isTargetInSecondaryStrikeRange(main_target_coordinates, secondary_target_coordinates)))
        {
            return 0;
        }
        return -((getCharacterPower()+SOLDIER_SUB_STRIKE_DAMAGE-CEILING_FACTOR)/SOLDIER_SUB_STRIKE_DAMAGE);
    }

    int Soldier::performStrike(const mtm::GridPoint &src_coordinates,
                               const mtm::GridPoint &main_target_coordinates,
                               const mtm::GridPoint &current_target_coordinates,
                               std::shared_ptr<Character>target)
    {
        if (src_coordinates == current_target_coordinates)
        {
            if (src_coordinates == main_target_coordinates)
            {
                setCharacterAmmo(-getCharacterAttackAmmoCost());
            }
            return 0;
        }
        else if (main_target_coordinates == current_target_coordinates)
        {
            return performCharacterMainStrike(src_coordinates, main_target_coordinates, target);
        }
        else
        {
            return performCharacterSecondaryStrike(main_target_coordinates, current_target_coordinates, target);
        }
    }
}
