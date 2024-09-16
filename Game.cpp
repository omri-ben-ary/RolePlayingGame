#include "Game.h"
#include "Soldier.h"
#include "Medic.h"
#include "Sniper.h"
#include <cstring>

namespace mtm
{
    using std::vector;
    using std::shared_ptr;
    using std::string;

    Game::Game(int height, int width) : height(height), width(width)
    {
        if ((height <= 0 ) || (width <= 0))
        {
            throw IllegalArgument();
        }
        this->board = vector<vector<shared_ptr<Character>>>(
                height,vector<shared_ptr<Character>>(width, nullptr));
    }

    Game::Game(const Game &other) :height(other.height), width(other.width),
    board(other.height,vector<shared_ptr<Character>>(other.width,nullptr))
    {
        for (int r = 0; r < height ; r++)
        {
            for (int c = 0; c < width; c++)
            {
                if (other.board[r][c] == nullptr)
                {
                    continue;
                }
                board[r][c] = other.board[r][c].get()->clone();
            }
        }
    }

    bool Game::isCellEmpty(const GridPoint &coordinates) const {
        return (getCharacterAtCoordinates(coordinates) == nullptr);
    }

    Game& Game::operator=(const Game &other){
        vector<vector<shared_ptr<Character>>>
                tmp_board(other.height,vector<shared_ptr<Character>>(other.width, nullptr));
        for (int r = 0; r < other.height ; r++)
        {
            for (int c = 0; c < other.width; c++)
            {
                GridPoint current_coordinates(r,c);
                if (other.isCellEmpty(current_coordinates))
                {
                    continue;
                }
                tmp_board[r][c] = other.board[r][c].get()->clone();
            }
        }
        this->board = tmp_board;
        this->height = other.height;
        this->width = other.width;
        return *this;
    }

    void Game::addCharacter(const GridPoint &coordinates, shared_ptr<Character> character) {
        if (areCoordinatesIllegal(coordinates))
        {
            throw IllegalCell();
        }
        if (!isCellEmpty(coordinates))
        {
            throw CellOccupied();
        }
        board[coordinates.row][coordinates.col] = character;
    }

    shared_ptr<Character> Game::makeCharacter(CharacterType type, Team team, units_t health,
                                                   units_t ammo, units_t range, units_t power) {
        if (health <= 0 || ammo < 0 || range < 0 || power < 0)
        {
            throw IllegalArgument();
        }
        shared_ptr<Character> character;
        switch(type) {
            case SOLDIER :
                character = std::make_shared<Soldier>(health, ammo, range, power, team);
                break;
            case MEDIC  :
                character = std::make_shared<Medic>(health, ammo, range, power, team);
                break;
            case SNIPER :
                character = std::make_shared<Sniper>(health, ammo, range, power, team);
                break;
        }
        return character;
    }

    shared_ptr<Character>Game::getCharacterAtCoordinates(const GridPoint& coordinates) {
        return board.at(coordinates.row).at(coordinates.col);
    }

    shared_ptr<Character>Game::getCharacterAtCoordinates(const GridPoint &coordinates) const {
        return board.at(coordinates.row).at(coordinates.col);
    }

    bool Game::areCoordinatesIllegal(const GridPoint& coordinates) const {
        return (coordinates.row >= height || coordinates.col >= width || coordinates.row < 0 || coordinates.col < 0);
    }

    void Game::move(const GridPoint &src_coordinates, const GridPoint &dst_coordinates) {
        if (areCoordinatesIllegal(src_coordinates) || areCoordinatesIllegal(dst_coordinates))
        {
            throw IllegalCell();
        }
        if (isCellEmpty(src_coordinates))
        {
            throw CellEmpty();
        }
        shared_ptr<Character> character = getCharacterAtCoordinates(src_coordinates);
        if (GridPoint::distance(src_coordinates, dst_coordinates) > character->getCharacterMovementRange())
        {
            throw MoveTooFar();
        }
        if (!isCellEmpty(dst_coordinates))
        {
            throw CellOccupied();
        }
        swap(board[src_coordinates.row][src_coordinates.col], board[dst_coordinates.row][dst_coordinates.col]);
    }

    void Game::preAttackCheck(const GridPoint &src_coordinates, const GridPoint &dst_coordinates,
                                   const shared_ptr<Character>& attacker_ptr, const shared_ptr<Character>& target_ptr)
                                   const
    {
        if (isCellEmpty(src_coordinates))
        {
            throw CellEmpty();
        }
        if (!(attacker_ptr->isTargetInStrikeRange(src_coordinates, dst_coordinates)))
        {
            throw OutOfRange();
        }
        if (!(attacker_ptr->isCharacterHasEnoughAmmo(target_ptr)))
        {
            throw OutOfAmmo();
        }
        if (!(attacker_ptr->isStrikeLegal(src_coordinates, dst_coordinates, target_ptr)))
        {
            throw IllegalTarget();
        }
    }

    void Game::attack(const GridPoint &src_coordinates, const GridPoint &dst_coordinates) {
        if (areCoordinatesIllegal(src_coordinates) || areCoordinatesIllegal(dst_coordinates))
        {
            throw IllegalCell();
        }
        shared_ptr<Character> attacker_ptr = getCharacterAtCoordinates(src_coordinates);
        shared_ptr<Character> target_ptr = getCharacterAtCoordinates(dst_coordinates);
        preAttackCheck(src_coordinates, dst_coordinates, attacker_ptr, target_ptr);
        for (int r = 0; r < height ; r++)
        {
            for (int c = 0; c < width; c++)
            {
                GridPoint current_coordinates = GridPoint(r, c);
                shared_ptr<Character> current_target_ptr = board[r][c];
                units_t strike_result = attacker_ptr->performStrike(src_coordinates, dst_coordinates,
                                                                current_coordinates, current_target_ptr);
                if (strike_result != 0)
                {
                    current_target_ptr->setCharacterHealthPoints(strike_result);
                    if (!(current_target_ptr->isCharacterAlive()))
                    {
                        board[r][c] = nullptr;
                    }
                }
            }
        }
    }

    void Game::reload(const GridPoint &coordinates) {
        if (areCoordinatesIllegal(coordinates))
        {
            throw IllegalCell();
        }
        if (isCellEmpty(coordinates))
        {
            throw CellEmpty();
        }
        shared_ptr<Character> character = getCharacterAtCoordinates(coordinates);
        character->setCharacterAmmo(character->getCharacterReloadAmmoAddition());
    }

    std::ostream& operator<<(std::ostream &os, const Game& game) {
        string output_str = string();
        for (int r = 0; r < game.height ; r++)
        {
            for (int c = 0; c < game.width; c++)
            {
                GridPoint coordinate(r,c);
                if (game.isCellEmpty(coordinate))
                {
                    output_str += " " ;
                }
                else
                {
                    output_str += game.board[r][c]->getCharacterIdentifierChar();
                }
            }
        }
        const char *begin = output_str.c_str();
        const char *end = begin + strlen(begin);
        printGameBoard(os, begin, end, game.width);
        return os;
    }

    bool Game::isOver(Team *winningTeam) const {
        bool no_players_alive = true;
        Team potential_winning_team;
        for (int r = 0; r < height ; r++)
        {
            for (int c = 0; c < width; c++)
            {
                GridPoint current_coordinates(r,c);
                if(!isCellEmpty(current_coordinates))
                {
                    if (no_players_alive)
                    {
                        potential_winning_team = board[r][c]->getCharacterTeam();
                        no_players_alive = false;
                    }
                    else
                    {
                        if (potential_winning_team != board[r][c]->getCharacterTeam())
                        {
                            return false;
                        }
                    }
                }
            }
        }
        return isOverReturnResult(winningTeam, no_players_alive, potential_winning_team);
    }

    bool Game::isOverReturnResult(Team *winningTeam, bool no_players_alive, Team potential_winning_team)
    {
        if (no_players_alive)
        {
            return false;
        }
        if (winningTeam != nullptr)
        {
            *winningTeam = potential_winning_team;
        }
        return true;
    }
}
