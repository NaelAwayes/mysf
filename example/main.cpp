#include <iostream>

#include "../inc/Mysf.hpp"

// Creating node where inputs are handle and sprite is display
class Node : public mysf::SpriteNode
{
	enum Action
	{
		Up,
		Left,
		Down,
		Right,
		ActionCount
	};

public:
  explicit Node()
		: mysf::SpriteNode()
		, _bind(ActionCount)
		, _speed(1)
	{
		std::map<std::string, unsigned int> bind;

		bind["Up"] = Up;
		bind["Left"] = Left;
		bind["Down"] = Down;
		bind["Right"] = Right;
		_bind.load("key.conf", bind);
	}

protected:
  virtual void updateCurrent(const sf::Time & /* deltaTime */, const mysf::Event & event)
  {
    sf::Vector2f pos(getPosition());
		// const float move = deltaTime.asSeconds() * _speed;
		const unsigned int move = _speed;

    if (_bind.getInput(Up, event))
      pos.y -= move;
    if (_bind.getInput(Left, event))
      pos.x -= move;
    if (_bind.getInput(Down, event))
      pos.y += move;
    if (_bind.getInput(Right, event))
      pos.x += move;
    setPosition(pos);
  }

private:
	mysf::Binding _bind;
  unsigned int _speed;
};

// Creating a GraphicRender to be run by the engine
class Render : public mysf::GraphicRender
{
public:
  explicit Render(mysf::Context & ctx) : mysf::GraphicRender(ctx) {}

  virtual bool init()
  {
    _ctx.gls.resize(1);
    _ctx.gls.clear();

    _def.setTexture(_ctx.thl.getDefault());
		_def.setColor(sf::Color::Green);
		// _def.setTextureRect(sf::IntRect(0, 0, 100, 100));
    _ctx.gls[0].add(&_def);
    return true;
  }

private:
  Node _def;
};

// Creating the engine that will handle your differents GraphicRenders
class Main : public mysf::Engine
{
public:
  virtual bool init(int /* ac */, char ** /* av */)
  {
    _grender = new Render(_ctx);

		// _event.key().setEventType(mysf::OnPressed);
    _ctx.win.create(sf::VideoMode(800, 450), "Test");
    if (_ctx.thl.setDefault("../rsc/default.png") == false)
      return false;
    return _grender->init();
  }
};

// Instantiate Engine, initialize it and run it
int main(int ac, char ** av)
{
  Main test;

  if (test.init(ac, av) == false)
    return 1;
  return test.run();
}
