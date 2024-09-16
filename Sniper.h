#ifndef GAME_PROJECT_SNIPER_H
#define GAME_PROJECT_SNIPER_H
#include "Character.h"

namespace mtm
{
    /**
    * class Sniper:
    *      represents the character of type Sniper.
    */
    class Sniper : public Character{
    private:

        int successful_strikes_counter;
        static const units_t SNIPER_MOVEMENT_RANGE;
        static const units_t SNIPER_RELOAD_AMMO_ADDITION;
        static const units_t SNIPER_ATTACK_AMMO_COST;
        static const int SNIPER_STRIKE_RANGE_FACTOR;
        static const int CEILING_FACTOR;
        static const int STRIKE_FACTOR;
        static const int NO_STRIKE_FACTOR;
        static const int NUM_OF_SUCCESSFUL_STRIKE_FOR_FACTOR;
        static const char IDENTIFIER_CHAR_POWERLIFTERS;
        static const char IDENTIFIER_CHAR_CROSSFITTERS;

    public:
        /**
        * constructor to Sniper that receives 5 parameters.
        * @param health_points : represents the life of the Sniper - when it gets to 0 the Sniper is dead.
        * @param ammo : the Sniper need ammo in order to perform an attack.
        * @param range : represents which coordinates can be attacked by the Sniper from it current place.
        * @param power : the damage that the Sniper do to the target when it attacks the target.
        * @param team : the team that the Sniper is being part of, might be Crossfitters or powerlifters.
        */
        Sniper(units_t health_points, units_t ammo_points, units_t range, units_t power, mtm::Team team);
        /**
        * Sniper's copy constructor.
        * initializes new Sniper with the fields of given Sniper.
        */
        Sniper(const Sniper&) = default;
        /**
        * operator= sets class's Sniper fields to the entered Sniper fields.
        * @return reference to the class's Sniper.
        */
        Sniper& operator=(const Sniper&) = default;
        /**
        * ~Sniper: default constructor of the Sniper.
        * destroys the class and all of his inner fields.
        */
        ~Sniper() override = default;
        /**
        * clone: creates a copy of the Sniper instance.
        * @return absolute copy of the Sniper and his inner fields.
        */
        std::shared_ptr<Character> clone() const override;
        /**
        * isTargetInStrikeRange: checks if the target is closer to the sniper from his maximum attack range but
        * further then his minimum attack range.
        * @param src_coordinates : the coordinates of the Sniper.
        * @param dst_coordinates : the target to attack.
        * @return true if the target is in the Sniper strike range according to his range limitations.
        */
        bool isTargetInStrikeRange(const mtm::GridPoint& src_coordinates,
                                   const mtm::GridPoint& dst_coordinates)const override;
        /**
        * isStrikeLegal: checks if strike can be performed by the Sniper.
        * more specifically checks the target is not empty and that the Sniper doesn't try to attack one of his
        * teammates.
        * @param src_coordinates : the coordinates of the sniper.
        * @param dst_coordinates : the coordinates of the target.
        * @param target : the character at the target.
        * @return true if the strike can be performed by the sniper.
        */
        bool isStrikeLegal(const mtm::GridPoint& src_coordinates, const mtm::GridPoint& dst_coordinates,
                           std::shared_ptr<Character> target) const override;
        /**
        * performStrike: performs the sniper strike. the sniper attacks only one time in one place.
        * if the target is an enemy the attack cost the normal sniper attack cost and he hits him according to his
        * power field. the sniper has an attack factor that every time that he reached to a multiple of this factor
        * he doubles his power.
        * @param src_coordinates : the coordinates of the sniper.
        * @param main_target_coordinates  : the sniper main attack target coordinates.
        * @param current_target_coordinates : current attacked coordinates which can be any coordinates in the board.
        * @param target : the character that is being attacked.
        * @return health points to reduce.
        */
        units_t performStrike(const mtm::GridPoint& src_coordinates, const mtm::GridPoint& main_target_coordinates,
                          const mtm::GridPoint& current_target_coordinates, std::shared_ptr<Character> target)
                          override;
    };
}

#endif //GAME_PROJECT_SNIPER_H
