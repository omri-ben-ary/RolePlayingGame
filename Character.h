#ifndef GAME_PROJECT_CHARACTER_H
#define GAME_PROJECT_CHARACTER_H
#include "Auxiliaries.h"
#include <memory>

namespace mtm
{
    /**
    * class Character:
    *      describes the general characteristics of a character in our game.
    */
    class Character{
    private:
        units_t health_points;
        units_t ammo_points;
        units_t range;
        units_t power;
        mtm::Team team;
        units_t movement_range;
        units_t reload_ammo_addition;
        units_t attack_ammo_cost;
        char identifier_char_powerlifters;
        char identifier_char_crossfitters;

        /**
        * getCharacterHealthPoints: returns the number of health points of the character.
        * @return:character's health points field.
        */
        units_t getCharacterHealthPoints() const;

    protected:
        /**
        * getCharacterAmmo: returns the ammo points of the character.
        * @return character's ammo field.
        */
        units_t getCharacterAmmo() const;
        /**
        * getCharacterRange : returns the range of the character.
        * @return character's range field.
        */
        units_t getCharacterRange() const;
        /**
        * getCharacterPower: returns the power of the character.
        * @return character's power field.
        */
        units_t getCharacterPower() const;
        /**
        * getCharacterAttackAmmoCost :returns the ammo cost of performing attack by the character
        * @return : character's attack ammo cost field.
        */
        units_t getCharacterAttackAmmoCost() const;
        /**
        * isTargetOnSameTeam: checks if the character is on the same team as the character at his target.
        * @param target : the target we want to compare his team to the class's character.
        * @return : true if the entered character is in the same time as the current character
        */
        bool isTargetOnSameTeam(const std::shared_ptr<Character>& target) const;
        /**
        * isTargetEmpty: checks if a given target is an active player in the game.
        * @param target : the target we want to check if it's contains any active character.
        * @return true if the given target is not an active character in the game
        */
        static bool isTargetEmpty(const std::shared_ptr<Character>& target);

    public:
        /**
        * constructor of the character class that receives 10 parameters.
        * @param health_points : represents the life of the character - when it gets to 0 the character is dead.
        * @param ammo : the character need ammo in order to perform an attack.
        * @param range : represents which coordinates can be attacked by the character from it current place.
        * @param power : the damage that the character do to the target when it attacks the target.
        * @param team : the team that the character is being part of, might be Crossfitters or powerlifters.
        * @param movement_range : the character maximal movement range limitation.
        * @param reload_ammo_addition: amount of ammo that is being added to the character's ammo in reload action.
        * @param attack_ammo_cost : amount of ammo that is being reduced from the character's ammo in attack action.
        * @param identifier_char_powerlifters : the identifier char of the character as a powerlifter.
        * @param identifier_char_crossfitters : the identifier char of the character as a crossfitter.
        */
        Character(units_t health_points, units_t ammo, units_t range, units_t power, mtm::Team team,
                  units_t movement_range, units_t reload_ammo_addition, units_t attack_ammo_cost,
                  char identifier_char_powerlifters, char identifier_char_crossfitters) ;
        //
        /**
        * ~Character: default constructor of the character.
        * Pure virtual method - being implemented by the children of the class.
        */
        virtual ~Character() = default;
        /**
        * getCharacterTeam : returns the team the character is being part of - crossfitter or powerlifters..
        * @return character's team field.
        */
        mtm::Team getCharacterTeam() const;
        /**
        * getCharacterMovementRange: returns the character maximal movement range according to his inner field.
        * @return character's movement range field.
        */
        units_t getCharacterMovementRange() const ;
        /**
        * getCharacterReloadAmmoAddition: returns the amount of ammo that is added to the
        * character's total ammo in a reloading action.
        * @return character's reload ammo addition field.
        */
        units_t getCharacterReloadAmmoAddition() const;
        /**
        * returns the char that symbolizes the character according to his team.
        * @return character's identifier_char_powerlifters field if it's team is Powerlifters.
        * character's identifier_char_crossfitters field if it's team is Crossfitters.
        */
        char getCharacterIdentifierChar() const;
        /**
        * isCharacterAlive: checks if the character is alive (his health points are bigger than 0)
        * @return true if the health points field is bigger than 0.
        */
        bool isCharacterAlive() const;
        /**
        * setCharacterHealthPoints: changes the health points of the character according to the given input
        * @param points : the parameter to edit the current health points field with.
        */
        void setCharacterHealthPoints(units_t points);
        /**
        * setCharacterAmmo : changes the ammo points of the character according to the given input
        * @param ammo : the parameter to edit the current ammo points field with.
        */
        void setCharacterAmmo(units_t ammo);
        /**
        * isCharacterHasEnoughAmmo : checks if character has enough ammo to perform attack.
        * @param target_ptr : the target of the attack in order to check if it's on the same team as the character.
        * @return true if the character can perform the attack.
        */
        virtual bool isCharacterHasEnoughAmmo(const std::shared_ptr<Character>& target_ptr) const;
        /**
        * clone: creates a copy of the character instance.
        * @return absolute copy of the character and his inner fields.
        */
        virtual std::shared_ptr<Character> clone() const = 0;
        /**
        * isTargetInStrikeRange: checks if the target is in the character strike's range.
        * @param src_coordinates : the coordinates of the character (attacker).
        * @param dst_coordinates : the coordinates of the target.
        * @return true if the character can perform the attack. else - false.
        */
        virtual bool isTargetInStrikeRange(const mtm::GridPoint& src_coordinates,
                                           const mtm::GridPoint& dst_coordinates)
        const = 0;
        /**
        * isStrikeLegal: checks if the strike is legal according to the character limitations;
        * @param src_coordinates : the coordinates of the character (attacker).
        * @param dst_coordinates : the coordinates of the target.
        * @param target : the character which is the target of the attack.
        * @return true if the attack is legal and can be performed.
        */
        virtual bool isStrikeLegal(const mtm::GridPoint& src_coordinates,
                                   const mtm::GridPoint& dst_coordinates,
                                   std::shared_ptr<Character> target) const = 0;
        /**
        * performStrike: performs the strike.
        * @param src_coordinates : the coordinates of the character (attacker).
        * @param main_target_coordinates : the coordinates of the main target.
        * @param current_target_coordinates  the coordinates of the current target - might be any coordinates
        * over the game board.
        * @param target : the current target of the attack - might be any character over the board.
        * @return amount of health points to add/reduce from the target's health points
        */
        virtual units_t performStrike(const mtm::GridPoint& src_coordinates,
                                      const mtm::GridPoint& main_target_coordinates,
                                      const mtm::GridPoint& current_target_coordinates,
                                      std::shared_ptr<Character> target) = 0;
    };
}

#endif //GAME_PROJECT_CHARACTER_H
