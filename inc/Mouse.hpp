#ifndef MOUSE_HPP_
# define MOUSE_HPP_

# include <vector>

# include <SFML/Window.hpp>

# include "EventType.hpp"

namespace mysf
{
  class Mouse
  {
		typedef void (Mouse::*updateFct)(const sf::Event & event);

	public:
		enum WheelDir
		{
			Up,
			Down,
			Right,
			Left
		};

  public:
    Mouse();
    Mouse(const Mouse & o);
    Mouse & operator=(const Mouse & o);
    virtual ~Mouse();

    void			update(const sf::Event & event);
    void			reset();

		void 							setEventType(const EventType & eventType);
		const EventType &	getEventType() const;

    bool			isDown(sf::Mouse::Button button) const;
    bool			isInside() const;
    bool			isMoved() const;
    bool			isScrolled() const;
    bool			isScrolled(WheelDir dir) const;

    const sf::Vector2i &	getPos() const;
    const sf::Vector2i &	getWheelTick() const;

	private:
		void _updatePressed(const sf::Event & event);
		void _updateReleased(const sf::Event & event);
		void _updateOnPressed(const sf::Event & event);
		void _updateOnReleased(const sf::Event & event);

		std::vector<updateFct> _update;

  protected:
		EventType							_eventType;

		std::vector<bool> 		_down;
    bool	           			_inside;
    bool          				_moved;
    bool	           			_scrolled;
    sf::Vector2i					_pos;
    sf::Vector2i       		_wheelTick;
  };
}

#endif // !MOUSE_HPP_
