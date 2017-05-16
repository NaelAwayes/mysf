#include "SpriteNode.hpp"

namespace mysf
{
  SpriteNode::SpriteNode()
    : SceneNode()
    , _sprite()
  {

  }

  SpriteNode::SpriteNode(const sf::Texture & texture)
    : SceneNode()
    , _sprite(texture)
  {

  }

  SpriteNode::SpriteNode(const sf::Texture & texture, const sf::IntRect & rectanlge)
    : SceneNode()
    , _sprite(texture, rectanlge)
  {

  }

  SpriteNode::~SpriteNode()
  {

  }

  void SpriteNode::setTexture(const sf::Texture & texture, bool resetRect)
	{
    _sprite.setTexture(texture, resetRect);
	}

  void SpriteNode::setTextureRect(const sf::IntRect & rectangle)
	{
    _sprite.setTextureRect(rectangle);
	}

  void SpriteNode::setColor(const sf::Color & color)
	{
    _sprite.setColor(color);
	}

  const sf::Texture * SpriteNode::getTexture() const
	{
    return _sprite.getTexture();
	}

  const sf::IntRect & SpriteNode::getTextureRect() const
	{
    return _sprite.getTextureRect();
	}

  const sf::Color & SpriteNode::getColor() const
	{
    return _sprite.getColor();
	}

  sf::FloatRect SpriteNode::getLocalBounds() const
	{
    return _sprite.getLocalBounds();
	}

  sf::FloatRect SpriteNode::getGlobalBounds() const
	{
    return _sprite.getGlobalBounds();
	}

  void SpriteNode::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
  {
    target.draw(_sprite, states);
  }
}