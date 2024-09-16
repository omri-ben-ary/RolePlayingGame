//
// Created by DELL on 10/06/2021.
//

#include "Sniper.h"

namespace mtm
{
    const units_t Sniper::SNIPER_MOVEMENT_RANGE = 4;
    const units_t Sniper::SNIPER_RELOAD_AMMO_ADDITION = 2;
    const units_t Sniper::SNIPER_ATTACK_AMMO_COST = 1;
    const int Sniper::SNIPER_STRIKE_RANGE_FACTOR = 2;
    const int Sniper::CEILING_FACTOR = 1;
    const int Sniper::STRIKE_FACTOR = 2;
    const int Sniper::NO_STRIKE_FACTOR = 1;
    const int Sniper::NUM_OF_SUCCESSFUL_STRIKE_FOR_FACTOR = 3;
    const char Sniper::IDENTIFIER_CHAR_POWERLIFTERS = 'N';
    const char Sniper::IDENTIFIER_CHAR_CROSSFITTERS = 'n';

    Sniper::Sniper(units_t health_points, units_t ammo_points, units_t range, units_t power, mtm::Team team) :
            Character(health_points, ammo_points,range, power, team,
                      SNIPER_MOVEMENT_RANGE,SNIPER_RELOAD_AMMO_ADDITION,
                      SNIPER_ATTACK_AMMO_COST, IDENTIFIER_CHAR_POWERLIFTERS, IDENTIFIER_CHAR_CROSSFITTERS),
            successful_strikes_counter(0) {}

    std::shared_ptr<Character>Sniper::clone() const {
        return static_cast<std::shared_ptr<Character>>(new Sniper(*this));
    }

    bool Sniper::isTargetInStrikeRange(const mtm::GridPoint& src_coordinates, const mtm::GridPoint& dst_coordinates)
    const{
        units_t character_strike_range = getCharacterRange();
        int distance_from_target = mtm::GridPoint::distance(src_coordinates, dst_coordinates);
        return ((distance_from_target <= character_strike_range) &&
                (distance_from_target >= (character_strike_range + CEILING_FACTOR)/ SNIPER_STRIKE_RANGE_FACTOR));
    }

    bool Sniper::isStrikeLegal(const mtm::GridPoint& src_coordinates, const mtm::GridPoint& dst_coordinates,
                               std::shared_ptr<Character> target) const {
        return !(isTargetEmpty(target) || isTargetOnSameTeam(target));
    }

    units_t Sniper::performStrike(const mtm::GridPoint &src_coordinates,
                                  const mtm::GridPoint &main_target_coordinates,
                                  const mtm::GridPoint &current_target_coordinates,
                                  std::shared_ptr<Character>target) {
        if (!(main_target_coordinates == current_target_coordinates))
        {
            return 0;
        }
        else
        {
            setCharacterAmmo(-getCharacterAttackAmmoCost());
            successful_strikes_counter++;
            int current_attack_factor =((successful_strikes_counter % NUM_OF_SUCCESSFUL_STRIKE_FOR_FACTOR == 0)
                                        ? STRIKE_FACTOR : NO_STRIKE_FACTOR);
            return (-getCharacterPower() * current_attack_factor);
        }
    }
}
