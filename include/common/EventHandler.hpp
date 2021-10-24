#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <functional>

namespace sfev
{
using EventCallback = std::function<void(const sf::Event& event)>;

template<typename T>
using EventCallbackMap = std::unordered_map<T, EventCallback>;

using CstEv = const sf::Event&;

template<typename T>
class SubTypeManager
{
public:
	SubTypeManager(std::function<T(const sf::Event&)> unpack) :
		m_unpack(unpack)
	{}

	~SubTypeManager() = default;

	void processEvent(const sf::Event& event) const
	{
		T sub_value = m_unpack(event);
		auto it(m_callmap.find(sub_value));
		if (it != m_callmap.end()) {
			(it->second)(event);
		}
	}

	void addCallback(const T& sub_value, EventCallback callback)
	{
		m_callmap[sub_value] = callback;
	}

private:
	EventCallbackMap<T> m_callmap;
	std::function<T(const sf::Event&)> m_unpack;
};


class EventMap
{
public:
	EventMap(bool use_builtin_helpers = true)
		: m_key_pressed_manager([](const sf::Event& event) {return event.key.code; })
		, m_key_released_manager([](const sf::Event& event) {return event.key.code; })
		, m_mouse_pressed_manager([](const sf::Event& event) {return event.mouseButton.button; })
		, m_mouse_released_manager([](const sf::Event& event) {return event.mouseButton.button; })
	{
		if (use_builtin_helpers) {
			this->addEventCallback(sf::Event::EventType::KeyPressed, [&](const sf::Event& event) {m_key_pressed_manager.processEvent(event); });
			this->addEventCallback(sf::Event::EventType::KeyReleased, [&](const sf::Event& event) {m_key_released_manager.processEvent(event); });
			this->addEventCallback(sf::Event::EventType::MouseButtonPressed, [&](const sf::Event& event) {m_mouse_pressed_manager.processEvent(event); });
			this->addEventCallback(sf::Event::EventType::MouseButtonReleased, [&](const sf::Event& event) {m_mouse_released_manager.processEvent(event); });
		}
	}

	void addEventCallback(sf::Event::EventType type, EventCallback callback)
	{
		m_events_callmap[type] = callback;
	}

	void addKeyPressedCallback(sf::Keyboard::Key key_code, EventCallback callback)
	{
		m_key_pressed_manager.addCallback(key_code, callback);
	}

	void addKeyReleasedCallback(sf::Keyboard::Key key_code, EventCallback callback)
	{
		m_key_released_manager.addCallback(key_code, callback);
	}

	void addMousePressedCallback(sf::Mouse::Button button, EventCallback callback)
	{
		m_mouse_pressed_manager.addCallback(button, callback);
	}

	void addMouseReleasedCallback(sf::Mouse::Button button, EventCallback callback)
	{
		m_mouse_released_manager.addCallback(button, callback);
	}

	void executeCallback(const sf::Event& e, EventCallback fallback = nullptr) const
	{
		auto it(m_events_callmap.find(e.type));
		if (it != m_events_callmap.end()) {
			(it->second)(e);
		} else if (fallback) {
			fallback(e);
		}
	}

	void removeCallback(sf::Event::EventType type)
	{
		auto it(m_events_callmap.find(type));
		if (it != m_events_callmap.end()) {
			m_events_callmap.erase(it);
		}
	}

private:
	SubTypeManager<sf::Keyboard::Key> m_key_pressed_manager;
	SubTypeManager<sf::Keyboard::Key> m_key_released_manager;
	SubTypeManager<sf::Mouse::Button> m_mouse_pressed_manager;
	SubTypeManager<sf::Mouse::Button> m_mouse_released_manager;
	EventCallbackMap<sf::Event::EventType> m_events_callmap;
};

class EventManager
{
public:
	EventManager(sf::Window& window, bool use_builtin_helpers) :
		m_window(window),
		m_event_map(use_builtin_helpers)
	{
	}

	void processEvents(EventCallback fallback = nullptr) const
	{
		sf::Event event;
		while (m_window.pollEvent(event)) {
			m_event_map.executeCallback(event, fallback);
		}
	}

	void addEventCallback(sf::Event::EventType type, EventCallback callback)
	{
		m_event_map.addEventCallback(type, callback);
	}

	void removeCallback(sf::Event::EventType type)
	{
		m_event_map.removeCallback(type);
	}

	void addKeyPressedCallback(sf::Keyboard::Key key, EventCallback callback)
	{
		m_event_map.addKeyPressedCallback(key, callback);
	}

	void addKeyReleasedCallback(sf::Keyboard::Key key, EventCallback callback)
	{
		m_event_map.addKeyReleasedCallback(key, callback);
	}

	void addMousePressedCallback(sf::Mouse::Button button, EventCallback callback)
	{
		m_event_map.addMousePressedCallback(button, callback);
	}

	void addMouseReleasedCallback(sf::Mouse::Button button, EventCallback callback)
	{
		m_event_map.addMouseReleasedCallback(button, callback);
	}

	sf::Window& getWindow()
	{
		return m_window;
	}

	sf::Vector2f getFloatMousePosition() const
	{
		const sf::Vector2i mouse_position = sf::Mouse::getPosition(m_window);
		return { static_cast<float>(mouse_position.x), static_cast<float>(mouse_position.y) };
	}

	sf::Vector2i getMousePosition() const
	{
		return sf::Mouse::getPosition(m_window);
	}

private:
	sf::Window& m_window;
	EventMap    m_event_map;
};

}

#endif // EVENT_HANDLER_H
