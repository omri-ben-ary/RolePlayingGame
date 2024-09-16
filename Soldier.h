#ifndef GAME_PROJECT_SOLDIER_H
#define GAME_PROJECT_SOLDIER_H

#include "Character.h"

 namespace mtm
{
/**
  * class Soldier:
  *      represents the character of type Soldier.
  */
    class Soldier : public Character{
    private:
        static const units_t SOLDIER_MOVEMENT_RANGE;
        static const units_t SOLDIER_RELOAD_AMMO_ADDITION;
        static const units_t SOLDIER_ATTACK_AMMO_COST;
        static const int SOLDIER_SUB_STRIKE_RANGE;
        static const int SOLDIER_SUB_STRIKE_DAMAGE;
        static const int CEILING_FACTOR;
        static const char IDENTIFIER_CHAR_POWERLIFTERS;
        static const char IDENTIFIER_CHAR_CROSSFITTERS;

        /**
        * performCharacterMainStrike: performs the soldier main strike
        * @param src_coordinates : the coordinates of the soldier.
        * @param main_target_coordinates  : the soldier main attack target coordinates.
        * @param target : the character that is being attacked.
        * @return amount of health points to reduce from the target points.
        */
        units_t performCharacterMainStrike(const mtm::GridPoint& src_coordinates,
                                           const mtm::GridPoint& dst_coordinates,
                                           const std::shared_ptr<Character>& target);
        /**
         * performCharacterSecondaryStrike : performs the soldier secondary strike.
         * @param main_target_coordinates : the coordinates of the soldier.
         * @param current_target_coordinates : the soldier current attack target coordinates.
         * @param target : the current character that is being attacked.
         * @return amount of health points to reduce from the target points
         */
        units_t performCharacterSecondaryStrike(const mtm::GridPoint& main_target_coordinates,
                                            const mtm::GridPoint& current_target_coordinates,
                                            const std::shared_ptr<Character>& target) const;
        /**
         * isTargetInSecondaryStrikeRange: checks if given coordinates are in the range of the secondary attack
         * coordinates.
         * @param main_target_coordinates : the soldier main attack target coordinates.
         * @param secondary_target_coordinates : the soldier current attack target coordinates.
         * @return true if the current secondary target is in the secondary strike range and different than the main
         * coordinates.
         */
        bool isTargetInSecondaryStrikeRange(const mtm::GridPoint& main_target_coordinates,
                                            const mtm::GridPoint& secondary_target_coordinates) const;

    public:
        /**
        * constructor to Soldier that receives 5 parameters.
        * @param health_points : represents the life of the Soldier - when it gets to 0 the soldier is dead.
        * @param ammo : the Soldier need ammo in order to perform an attack.
        * @param range : represents which coordinates can be attacked by the Soldier from it current place.
        * @param power : the damage that the Soldier do to the target when it attacks the target.
        * @param team : the team that the Soldier is being part of, might be Crossfitters or powerlifters.
        */
        Soldier(units_t health_points, units_t ammo_points, units_t range, units_t power, mtm::Team team);
        /**
        * Soldier's copy constructor.
        * initializes new Soldier with the fields of given Soldier.
        */
        Soldier(const Soldier&) = default;
        /**
        * operator= sets class's Soldier fields to the entered Soldier fields.
        * @return reference to the class's Soldier.
        */
        Soldier& operator=(const Soldier&) = default;
        /**
        * ~Soldier: default constructor of the Soldier.
        * destroys the class and all of his inner fields.
        */
        ~Soldier() override = default;
        /**
        * clone: creates a copy of the Soldier instance.
        * @return absolute copy of the Soldier and his inner fields.
        */
        std::shared_ptr<Character> clone() const override;
        /**
        * isTargetInStrikeRange: checks if the target is closer to the Soldier from his maximum attack range.
        * @param src_coordinates : the coordinates of the Soldier.
        * @param dst_coordinates : the target to attack.
        * @return true if the target is in the Soldier strike range according to his range limitations.
        */
        bool isTargetInStrikeRange(const mtm::GridPoint& src_coordinates,
                                   const mtm::GridPoint& dst_coordinates) const override;
        /**
        * isStrikeLegal: checks if strike can be performed by the soldier.
        * more specifically checks the target is in the same row or column as the the soldier himself.
        * @param src_coordinates : the coordinates of the soldier.
        * @param dst_coordinates : the coordinates of the target.
        * @param target : the character at the target.
        * @return true if the strike can be performed by the soldier.
        */
        bool isStrikeLegal(const mtm::GridPoint& src_coordinates, const mtm::GridPoint& dst_coordinates,
                           std::shared_ptr<Character> target) const override;
        /**
        * performStrike: performs the soldier strike.
        * the soldier strike is divided into 2 parts, main strike and secondary strike.
        * the soldier is able to attack every kind of cell in the board (teammate, empty cell, himself, enemy)
        * but the damage will be done only to enemies.
        * the secondary strike is being made over characters that are not in the soldier team and located in a cell
        * that is closer to the main target cell than the soldier secondary attack range factor.
        * the damage in the secondary attack is lower than in the main attack and sets according to him.
        * teammates and soldier himself wont get hit in the attack.
        * @param src_coordinates : the coordinates of the soldier.
        * @param main_target_coordinates  : the soldier main attack target coordinates.
        * @param current_target_coordinates : current attacked coordinates which can be any coordinates in the board.
        * @param target : the character that is being attacked.
        * @return health points to reduce.
        */
        units_t performStrike(const mtm::GridPoint& src_coordinates, const mtm::GridPoint& main_target_coordinates,
                          const mtm::GridPoint& current_target_coordinates, std::shared_ptr<Character> target)
                          override;
    };
}

#endif //GAME_PROJECT_SOLDIER_H
