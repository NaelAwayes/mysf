#ifndef MYSF_SPRITE_NODE_HPP_
# define MYSF_SPRITE_NODE_HPP_

# include <SFML/Graphics.hpp>

# include "SceneNode.hpp"

namespace mysf
{
  class SpriteNode : public SceneNode
  {
  public:
    SpriteNode();
    explicit SpriteNode(const sf::Texture & texture);
    SpriteNode(const sf::Texture & texture, const sf::IntRect & rectangle);
    SpriteNode(const SpriteNode & o) = delete;
    SpriteNode & operator=(const SpriteNode & o) = delete;
    virtual ~SpriteNode();

    void setTexture(const sf::Texture & texture, bool resetRect = false);
    void setTextureRect(const sf::IntRect & rectangle);
    void setColor(const sf::Color & color);
    const sf::Texture * getTexture() const;
    const sf::IntRect & getTextureRect() const;
    const sf::Color & getColor() const;
    sf::FloatRect getLocalBounds() const;
    sf::FloatRect getGlobalBounds() const;

  protected:
    // virtual void	updateCurrent(const sf::Time & deltaTime, const Input & input) = 0;
    virtual void	drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const;

	private:
		void _updatePositions();
		void _updateTexCoords();

	private:
		sf::Vertex				 	_vertices[4];
		const sf::Texture *	_texture;
		sf::IntRect 				_textureRect;
  };
}

#endif // !SMYSF_PRITE_NODE_HPP_
