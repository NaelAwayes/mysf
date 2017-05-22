#include "Joysticks.hpp"

namespace mysf
{
  Joysticks::Joystick::Joystick()
    : _isConnected(false)
    , _down(sf::Joystick::ButtonCount, false)
    , _axis(sf::Joystick::AxisCount, 0.f)
	{

	}

  Joysticks::Joystick::Joystick(const Joystick & o)
    : _isConnected(o._isConnected)
    , _down(o._down)
    , _axis(o._axis)
	{

	}

  Joysticks::Joystick & Joysticks::Joystick::operator=(const Joystick & o)
	{
    if (this == &o)
      return *this;
    _isConnected = o._isConnected;
    _down = o._down;
    _axis = o._axis;
    return *this;
	}

  Joysticks::Joystick::~Joystick()
	{

	}

  void Joysticks::Joystick::connect()
	{
    reset();
    _isConnected = true;
	}

  void Joysticks::Joystick::disconnect()
	{
    _isConnected = false;
	}

  bool Joysticks::Joystick::isConnected() const
	{
    return _isConnected;
	}

  void Joysticks::Joystick::reset()
	{
    for (unsigned int i = 0; i < _down.size(); ++i)
      _down[i] = false;
    for (unsigned int i = 0; i < _axis.size(); ++i)
      _axis[i] = 0.f;
	}

  bool Joysticks::Joystick::isDown(unsigned int button) const
	{
    return _down[button];
	}

  float Joysticks::Joystick::getAxis(sf::Joystick::Axis axis) const
	{
    return _axis[axis];
	}

  Joysticks::Joysticks()
    : _update(EventType::EventTypeCount)
		, _eventType(EventType::Pressed)
		, _joysticks()
    , _nbConnected(0)
  {
    for (unsigned int i = 0; i < sf::Joystick::Count; ++i)
      if (sf::Joystick::isConnected(i))
        connect(i);
		_update[EventType::Pressed] = &Joysticks::_updatePressed;
		_update[EventType::Released] = &Joysticks::_updateReleased;
		_update[EventType::OnPressed] = &Joysticks::_updateOnPressed;
		_update[EventType::OnReleased] = &Joysticks::_updateOnReleased;
  }

  Joysticks::Joysticks(const Joysticks & o)
    : _update(EventType::EventTypeCount)
		, _eventType(o._eventType)
		, _joysticks(o._joysticks)
    , _nbConnected(o._nbConnected)
  {
		_update[EventType::Pressed] = &Joysticks::_updatePressed;
		_update[EventType::Released] = &Joysticks::_updateReleased;
		_update[EventType::OnPressed] = &Joysticks::_updateOnPressed;
		_update[EventType::OnReleased] = &Joysticks::_updateOnReleased;
}

  Joysticks & Joysticks::operator=(const Joysticks & o)
  {
    if (&o == this)
      return *this;
		_eventType = o._eventType;
    _joysticks = o._joysticks;
    _nbConnected = o._nbConnected;
    return *this;
  }

  Joysticks::~Joysticks()
  {

  }

  void Joysticks::update(const sf::Event & event)
  {
		(this->*_update[_eventType])(event);
    switch (event.type)
      {
      case sf::Event::JoystickMoved:
        _joysticks[event.joystickMove.joystickId]._axis[event.joystickMove.axis] = event.joystickMove.position;
        break;
      case sf::Event::JoystickConnected:
        connect(event.joystickConnect.joystickId);
      	break;
      case sf::Event::JoystickDisconnected:
        disconnect(event.joystickConnect.joystickId);
      	break;
      default:
	      break;
      }
  }

  void Joysticks::reset()
  {
    for (unsigned int i = 0; i < _joysticks.size(); ++i)
      _joysticks[i].reset();
  }

	void Joysticks::setEventType(const EventType & eventType)
	{
		_eventType = eventType;
		reset();
	}

	const EventType & Joysticks::getEventType() const
	{
		return _eventType;
	}

  const Joysticks::Joystick & Joysticks::operator[](unsigned int joystick) const
  {
    return _joysticks[joystick];
  }

  unsigned int Joysticks::size() const
  {
    return _joysticks.size();
  }

  unsigned int Joysticks::nbConnected() const
  {
    return _nbConnected;
  }

	bool Joysticks::isConnected(unsigned int joystick) const
	{
		if (joystick >= _joysticks.size())
			return false;
		return _joysticks[joystick].isConnected();
	}

  void Joysticks::connect(unsigned int joystick)
  {
    if (_joysticks.size() == 0)
      _joysticks.resize(sf::Joystick::Count);
    _joysticks[joystick].connect();
    ++_nbConnected;
  }

  void Joysticks::disconnect(unsigned int joystick)
  {
    _joysticks[joystick].disconnect();
    --_nbConnected;
    if (!_nbConnected)
      _joysticks.clear();
  }

	void Joysticks::_updatePressed(const sf::Event & event)
	{
		switch (event.type)
			{
			case sf::Event::JoystickButtonPressed:
				_joysticks[event.joystickButton.joystickId]._down[event.joystickButton.button] = true;
				break;
			case sf::Event::JoystickButtonReleased:
				_joysticks[event.joystickButton.joystickId]._down[event.joystickButton.button] = false;
				break;
			default:
				break;
			}
	}

	void Joysticks::_updateReleased(const sf::Event & event)
	{
		switch (event.type)
			{
			case sf::Event::JoystickButtonPressed:
				_joysticks[event.joystickButton.joystickId]._down[event.joystickButton.button] = false;
				break;
			case sf::Event::JoystickButtonReleased:
				_joysticks[event.joystickButton.joystickId]._down[event.joystickButton.button] = true;
				break;
			default:
				break;
			}
	}

	void Joysticks::_updateOnPressed(const sf::Event & event)
	{
		static std::vector<int> key(sf::Joystick::Count, -1);
		static int joystickId = -1;

		if (joystickId != -1 && key[joystickId] != -1)
			{
				_joysticks[joystickId]._down[key[joystickId]] = false;
				key[joystickId] = -1;
				joystickId = -1;
			}
		switch (event.type)
			{
			case sf::Event::JoystickButtonPressed:
				key[joystickId] = static_cast<int>(event.mouseButton.button);
				joystickId = event.joystickButton.joystickId;
				_joysticks[joystickId]._down[key[joystickId]] = true;
				break;
			default:
				break;
			}
	}

	void Joysticks::_updateOnReleased(const sf::Event & event)
	{
		static std::vector<int> key(sf::Joystick::Count, -1);
		static int joystickId = -1;

		if (joystickId != -1 && key[joystickId] != -1)
			{
				_joysticks[joystickId]._down[key[joystickId]] = false;
				key[joystickId] = -1;
				joystickId = -1;
			}
		switch (event.type)
			{
			case sf::Event::JoystickButtonReleased:
				key[joystickId] = static_cast<int>(event.mouseButton.button);
				joystickId = event.joystickButton.joystickId;
				_joysticks[joystickId]._down[key[joystickId]] = true;
				break;
			default:
				break;
			}
	}
}
