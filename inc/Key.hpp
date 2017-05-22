#ifndef KEY_HPP_
# define KEY_HPP_

# include <vector>

# include <SFML/Window.hpp>

# include "EventType.hpp"

namespace mysf
{
  class Key
  {
		typedef void (Key::*updateFct)(const sf::Event & event);

  public:
    Key();
    Key(const Key & o);
    Key & operator=(const Key & o);
    virtual ~Key();

    void	update(const sf::Event & event);
    void	reset();

		void 							setEventType(const EventType & eventType);
		const EventType &	getEventType() const;

    bool	isDown(sf::Keyboard::Key key) const;

	private:
		void _updatePressed(const sf::Event & event);
		void _updateReleased(const sf::Event & event);
		void _updateOnPressed(const sf::Event & event);
		void _updateOnReleased(const sf::Event & event);

		std::vector<updateFct> _update;

  protected:
		EventType					_eventType;
    std::vector<bool>	_down;
  };
}

#endif // !KEY_HPP_
