#ifndef GAME_HPP_
# define GAME_HPP_

# include <SFML/Graphics.hpp>

# include "Engine.hpp"
# include "GraphicRender.hpp"
# include "ResourceHolder.hpp"
# include "Binding.hpp"
# include "SpriteNode.hpp"
# include "TextNode.hpp"

# include "Resource.hpp"
# include "Map.hpp"
# include "Action.hpp"
# include "Helicopter.hpp"

class Game : public mysf::GraphicRender
{
public:
	explicit Game(mysf::Engine<sf::RenderWindow> & engine, sf::RenderWindow & window);
	Game(const Game &) = delete;
	Game & operator=(const Game &) = delete;
	virtual ~Game();

	virtual bool init() override;
	virtual mysf::GraphicRender * onUpdate(const sf::Time & deltaTime, const mysf::Event & event) override;

private:
	bool initBinding();
	void gameover(const mysf::Event & event);

private:
	static const sf::Vector2u WindowSize;

	mysf::Engine<sf::RenderWindow> & _engine;
	sf::RenderWindow & _window;
	mysf::TextureHolder _thl;
	mysf::FontHolder _fhl;
	mysf::Binding _bind;

	mysf::SpriteNode _background;
	Map _map;
	Score _score;
	Helicopter _helicopter;
};

#endif // !GAME_HPP_
