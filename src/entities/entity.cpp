#include "entities/entity.h"

Entity::Entity(Graphics *graphics, const std::string &filePath,
               int srcX, int srcY, int width, int height,
               float posX, float posY, Vector2 speed)
    : GameObject(graphics, filePath, srcX, srcY, width, height, posX, posY),
      m_Velocity(speed),
      m_Acceleration(Vector2::Zero()),
      m_Alive(true)
{

}

Entity::Entity()
    : GameObject(),
      m_Velocity(Vector2::Zero()),
      m_Acceleration(Vector2::Zero()),
      m_Alive(true)
{

}
