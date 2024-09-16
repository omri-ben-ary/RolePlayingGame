#ifndef GAME_PROJECT_GAME_H
#define GAME_PROJECT_GAME_H
#include <vector>
#include "Character.h"
#include "Exceptions.h"
#include "Auxiliaries.h"
#include <iostream>

namespace mtm
{
    /**
    * class Game
    * represents the whole game.
    */
    class Game {
    private:
        int height;
        int width;
        std::vector<std::vector<std::shared_ptr<Character>>> board;

        /**
        * isCellEmpty: checks if the cell in a given coordinates is empty.
        * @param coordinates : the coordinates to check.
        * @return true if the cell in a given coordinates is empty. else - otherwise.
        */
        bool isCellEmpty(const GridPoint& coordinates) const;
        /**
        * getCharacterAtCoordinates: get shared ptr to the character at the given coordinates.
        * @param coordinates : coordinates to get the character at.
        * @return shared ptr to the character.
        */
        std::shared_ptr<Character> getCharacterAtCoordinates(const GridPoint& coordinates);
        /**
        * getCharacterAtCoordinates: get shared ptr to the character at the given coordinates.
        * @param coordinates : coordinates to get the character at.
        * @return shared ptr to the character.
        */
        std::shared_ptr<Character> getCharacterAtCoordinates(const GridPoint& coordinates) const;
        /**
        * areCoordinatesIllegal : checks if the given coordinates are out of the game's board
        * @param coordinates : coordinates to check.
        * @return true if the given coordinates are out of the game's board.
        */
        bool areCoordinatesIllegal(const GridPoint& coordinates) const;
        /**
        * preAttackCheck : performs pre check attack - checks if the attack can be taken place.
        * @param src_coordinates : coordinates of the attacker.
        * @param dst_coordinates : coordinates of the target.
        * @param attacker_ptr : pointer to the attacker.
        * @param target_ptr : pointer to the target.
        */
        void preAttackCheck(const mtm::GridPoint &src_coordinates, const mtm::GridPoint &dst_coordinates,
                            const std::shared_ptr<Character>& attacker_ptr,
                            const std::shared_ptr<Character>&target_ptr) const;
        /**
        * isOverReturnResult: checks if the game is over.
        * @param winningTeam : ptr to the field of the winning team which should be edited if there is a winner and
        * it's current content different than null.
        * @param no_players_alive : indicates if the are still players who are alive and therefore the game should
        * continue.
        * @param potential_winning_team : the team which might won the game.
        * @return true if the game is over.
        */
        static bool isOverReturnResult(mtm::Team *winningTeam, bool no_players_alive, Team potential_winning_team);

    public:
        /**
        * Constructor of the game that receives 2 parameters.
        * @param height : number of rows in the game board - must be positive integer.
        * @param width : number of columns in the game board - must be positive integer.
        */
        Game(int height, int width);
        /**
        * Destructor of the game the frees all the memory that was allocated.
        */
        ~Game() = default;
        /**
        * Copy Constructor - initializes game instance with the data and fields of another game.
        * after the copy the two games are independent.
        * @param other : the game we want to copy his inner fields to the new game instance.
        */
        Game(const Game& other);
        /**
        * operator=: copies all of the fields of one game to the fields of the current game instance.
        * after the copy the two games are independent.
        * @param other : the game instance to copy his fields.
        * @return reference to the game instance which his class were updated.
        */
        Game& operator=(const Game& other);
        /**
        * addCharacter: adds character to the game board in a chosen coordinates.
        * @param coordinates: the coordinates to add the character to.
        * @param character : shared pointer to the character we want to add to the game.
        * possible errors:
        *      - IllegalCell : if the entered coordinates are out of the game's board.
        *      - CellOccupied : if there is already a character at the given coordinates.
        */
        void addCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character);
        /**
        * makeCharacter: creates new character.
        * @param type : the type of the character to create.
        * @param team : the parameter to set the team of the character to..
        * @param health : the parameter to set the character health points to.
        * @param ammo : the parameter to set the character ammo points to.
        * @param range : the parameter to set the character range to.
        * @param power : the parameter to set the character damage's to.
        * @return shared ptr to the character.
        * possible errors:
        *      - IllegalArgument : if the entered parameter health is 0 or one of health, ammo, range, power is
        *      negative.
        */
        static std::shared_ptr<Character> makeCharacter(CharacterType type, Team team,
                                                   units_t health, units_t ammo, units_t range, units_t power);
        /**
        * move: moves the character from src coordinates to dst coordinates.
        * @param src_coordinates : the coordinates to move the character from.
        * @param dst_coordinates : the coordinates to move the character to.
        * possible errors:
        *      - IllegalCell : if the entered coordinates are out of the game's board.
        *      - CellEmpty : if src coordinates are empty.
        *      - MoveTooFar: if the dst coordinates are out of the character's move range.
        *      - CellOccupied: if there is already a character at the given coordinates.
        */
        void move(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);
        /**
        * attack: performs the attack of the character at the src coordinates on the character at the dst coordinates.
        * the attack is taken place only of the character at the src coordinates can attack the dst coordinates.
        * the character at the dst coordinates (if there is one) will be affected by the attack according to the type
        * of the attacking character.
        * if as a result of the attack one of the characters on the board die, we will remove it from the board.
        * @param src_coordinates : the coordinates of the attacker.
        * @param dst_coordinates : the coordinates of the target.
        * possible errors:
        *      - IllegalCell : if the entered coordinates are out of the game's board.
        *      - CellEmpty : if src coordinates are empty.
        *      - OutOfRange : if the dst coordinates are out of the character's attack range.
        *      - OutOfAmmo: if the character at the dst coordinates does not have enough coordinates to perform the
        *      attack.
        *      - IllegalTarget: if the attack cannot be performed from different reasons than stated above.
        */
        void attack(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);
        /**
        * reload : performs ammo reloading to the ammo of the character at the given coordinates.
        * @param coordinates : the coordinates to reload ammo to the character at.
        * possible errors:
        *      - IllegalCell : if the entered coordinates are out of the game's board.
        *      - CellEmpty : if the coordinates are empty.
        */
        void reload(const GridPoint & coordinates);
        /**
        * operator<< : prints the board of the game in a specific format.
        * the game board will be in the following format:
        *      - empty cell in the board - ' '.
        *      - cell  the contains soldier - S he is Powerlifter, s if he is crossfitter.
        *      - cell  the contains medic - M he is Powerlifter, m if he is crossfitter.
        *      - cell  the contains sniper - N he is Powerlifter, n if he is crossfitter.
        * @param os : the output stream to print the data to.
        * @param game : the game to print his board.
        * @return  the output stream that we receive in order to able concatenation.
        *
        */
        friend std::ostream& operator<<(std::ostream& os, const Game& game);

        /**
         * isOver : checks if in the current game state there is a winner.
         * @param winningTeam : a variable to enter the winning team (if there is one) to, might be null and then
         * won't be changed.
         * @return true if there are character from only one team on the board.
         * if winning team is different than NULL the function update the winning team value with the winning team
         * identity.
         * if there is characters from both teams on the boards or from none of the teams the function returns false.
         */
        bool isOver(Team* winningTeam=NULL) const;
    };
    std::ostream& operator<<(std::ostream& os, const Game& game);
}

#endif //GAME_PROJECT_GAME_H
