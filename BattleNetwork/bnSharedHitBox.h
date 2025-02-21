
/*! \brief External hit boxes that delegate hits to their owners
 * 
 * Some spells and characters drop lagging hit boxes @see Wave 
 * and contact with these hitboxes need to behave the same as if
 * they hit the original source.
 * 
 * Shared hit boxes are classified as Obstacles because they can 
 * hit other characters and be hit themselves.
 * 
 * e.g. Boss hitbox can be hit and boss hitbox can deal damage to
 * player
 */

#pragma once
#include "bnObstacle.h"
#include "bnComponent.h"

class SharedHitbox : public Obstacle {
public:
	
  /**
   * @brief Disables tile highlighting and enables tile sharing
   * @param owner the original spell source
   * @param duration how long the hitbox should linger in seconds
   */
  SharedHitbox(Spell* owner, float duration);
  virtual ~SharedHitbox();

  /**
   * @brief Removes itself if time is up or the original source is deleted
   * @param _elapsed in seconds
   */
  virtual void OnUpdate(float _elapsed);
  
  /**
   * @brief Does not move
   * @param _direction ignored
   * @return false
   */
  virtual bool Move(Direction _direction);
  
  /**
   * @brief owner->Attack(_entity) is called 
   * @param _entity the character to attack that is not the same as the owner
   */
  virtual void Attack(Character* _entity);
  
  /**
   * @brief If the owner is also an obstacle, calls owner->Attack(_entity)
   * @param props the hit properties of the aggressor
   * @return true if the owner was hit, false otherwise
   */
  virtual const bool OnHit(const Hit::Properties props);
  virtual void OnDelete() { ; }

  virtual const float GetHeight() const;
  
private:
  float cooldown; /*< When cooldown reaches zero, this hitbox removes */
  Spell* owner; /*!< When this hitbox is hit, the owner is hit */
};
