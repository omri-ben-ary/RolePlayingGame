#ifndef GAME_PROJECT_MEDIC_H
#define GAME_PROJECT_MEDIC_H

#include "Character.h"

namespace mtm
{
    /**
    * class Medic:
    *      represents the character of type Medic.
    */
    class Medic : public Character{
    private:
        static const units_t MEDIC_MOVEMENT_RANGE;
        static const units_t MEDIC_RELOAD_AMMO_ADDITION;
        static const units_t MEDIC_ATTACK_AMMO_COST;
        static const char IDENTIFIER_CHAR_POWERLIFTERS;
        static const char IDENTIFIER_CHAR_CROSSFITTERS;

    public:
        /**
        * constructor to medic that receives 5 parameters.
        * @param health_points : represents the life of the medic - when it gets to 0 the medic is dead.
        * @param ammo : the medic need ammo in order to perform an attack.
        * @param range : represents which coordinates can be attacked by the medic from it current place.
        * @param power : the damage that the medic do to the target when it attacks the target.
        * @param team : the team that the medic is being part of, might be Crossfitters or powerlifters.
        */
        Medic(units_t health_points, units_t ammo_points, units_t range, units_t power, mtm::Team team);
        /**
        * Medic's copy constructor.
        * initializes new Medic with the fields of given Medic.
        */
        Medic(const Medic&) = default;
        /**
        * operator= sets class's Medic fields to the entered Medic fields.
        * @return reference to the class's Medic.
        */
        Medic& operator=(const Medic&) = default;
        /**
        * ~Medic: default constructor of the Medic.
        * destroys the class and all of his inner fields.
        */
        ~Medic() override = default;
        /**
        * clone: creates a copy of the Medic instance.
        * @return absolute copy of the Medic and his inner fields.
        */
        std::shared_ptr<Character> clone() const override;
        /**
        * isCharacterHasEnoughAmmo : checks if the medic has enough ammo to perform attack.
        * @param target_ptr : pointer to the target.
        * @return true - if the target is team member of the medic or the medic itself.
        *         false - if the medic has less ammo than his attack's ammo cost.
        */
        bool isCharacterHasEnoughAmmo(const std::shared_ptr<Character>& target_ptr) const override;
        /**
        * isTargetInStrikeRange: checks if the target is closer to the medic than his maximum attack range.
        * @param src_coordinates : the coordinates of the medic.
        * @param dst_coordinates : the target to attack.
        * @return true if the target is in the medic strike range according to his range limitation.
        */
        bool isTargetInStrikeRange(const mtm::GridPoint& src_coordinates,
                                   const mtm::GridPoint& dst_coordinates) const override;
        /**
        * isStrikeLegal: checks if strike can be performed by the medic.
        * more specifically checks the target is not empty and that the medic doesn't try to heal himself.
        * @param src_coordinates : the coordinates of the medic.
        * @param dst_coordinates : the coordinates of the target.
        * @param target : the character at the target.
        * @return true if the strike can be performed by the medic.
        */
        bool isStrikeLegal(const mtm::GridPoint& src_coordinates, const mtm::GridPoint& dst_coordinates,
                           std::shared_ptr<Character> target) const override;
        /**
        * performStrike: performs the medic strike. the medic attacks only one time in one place.
        * if his target is one of his teammates the attack is free and the medic heals him according to his power
        * field.
        * if the target is an enemy the attack cost the normal medic attack cost and he hits him according to his
        * power field.
        * @param src_coordinates : the coordinates of the medic.
        * @param main_target_coordinates  : the medic main attack target coordinates.
        * @param current_target_coordinates : current attacked coordinates which can be any coordinates in the board.
        * @param target : the character that is being attacked.
        * @return medic power if the target is his teammate. minus medic power if the target is his enemy.
        */
        units_t performStrike(const mtm::GridPoint& src_coordinates, const mtm::GridPoint& main_target_coordinates,
                          const mtm::GridPoint& current_target_coordinates, std::shared_ptr<Character> target)
                          override;
    };
}

#endif //GAME_PROJECT_MEDIC_H
