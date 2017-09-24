#include "entity.h"

Entity::Entity(Graphics *graphics, const std::string &filePath,
               int srcX, int srcY, int width, int height,
               float posX, float posY, Vec2f speed)
    : GameObject(graphics, filePath, srcX, srcY, width, height, posX, posY),
      m_Velocity(speed),
      m_Acceleration(Vec2f::zero()),
      m_Alive(true)
{

}
