#include "Character.h"
namespace mtm
{
    Character::Character(units_t health_points, units_t ammo, units_t range, units_t power, mtm::Team team,
                         units_t movement_range, units_t reload_ammo_addition, units_t attack_ammo_cost,
                         char identifier_char_powerlifters, char identifier_char_crossfitters) :
            health_points(health_points), ammo_points(ammo), range(range), power(power), team(team),
            movement_range(movement_range), reload_ammo_addition(reload_ammo_addition),
            attack_ammo_cost(attack_ammo_cost), identifier_char_powerlifters(identifier_char_powerlifters),
            identifier_char_crossfitters(identifier_char_crossfitters){
    }

    units_t Character::getCharacterHealthPoints() const {
        return this->health_points;
    }

    units_t Character::getCharacterAmmo() const {
        return this->ammo_points;
    }

    units_t Character::getCharacterRange() const {
        return this->range;
    }

    units_t Character::getCharacterPower() const {
        return this->power;
    }

    mtm::Team Character::getCharacterTeam() const {
        return this->team;
    }

    units_t Character::getCharacterMovementRange() const {
        return movement_range;
    }

    units_t Character::getCharacterReloadAmmoAddition() const {
        return reload_ammo_addition;
    }

    units_t Character::getCharacterAttackAmmoCost() const {
        return attack_ammo_cost;
    }

    char Character::getCharacterIdentifierChar() const{
        if (team == mtm::POWERLIFTERS)
        {
            return identifier_char_powerlifters;
        }
        return identifier_char_crossfitters;
    }

    bool Character::isCharacterAlive() const {
        return (getCharacterHealthPoints() > 0);
    }

    bool Character::isCharacterHasEnoughAmmo(const std::shared_ptr<Character>& target_ptr) const {
        return (this->getCharacterAmmo() >= this->getCharacterAttackAmmoCost());
    }

    bool Character::isTargetOnSameTeam(const std::shared_ptr<Character>& target) const {
        return (this->getCharacterTeam() == (*target).getCharacterTeam());
    }

    bool Character::isTargetEmpty(const std::shared_ptr<Character>& target) {
        return (target == nullptr);
    }

    void Character::setCharacterHealthPoints(units_t points) {
        this->health_points += points;
    }

    void Character::setCharacterAmmo(units_t ammo) {
        this->ammo_points += ammo;
    }
}
















