#include "ship.h"

ship::ship(std::vector<sf::Texture> &tex, Vector2 pos, std::vector<sf::Drawable*>& vect) : _textures(tex), _pos(pos)
{
	_sprite.setTexture(_textures[0]);
	_speed = Vector2(0, 0);
	_sprite.setPosition(_pos);
	vect.push_back(&_sprite);
	_it = _textures.begin();
}

void ship::render(bool a)
{
	_sprite.setColor(sf::Color(255, 255, 255, a ? 255 : 0));
}

void ship::update()
{
	sf::FloatRect rect = _sprite.getGlobalBounds();
	_pos += _speed;
	if (_pos.x + rect.width >= 800)
		_pos.x = 800 - rect.width;
	if (_pos.x <= 0)
		_pos.x = 0;
	if (_pos.y + rect.height >= 600)
		_pos.y = 600 - rect.height;
	if (_pos.y <= 0)
		_pos.y = 0;
	_speed = Vector2(0, 0);
	_sprite.setTexture(*_it);
	if (++_it == _textures.end())
		_it = _textures.begin();
	_sprite.setPosition(_pos);
}

void ship::changeSpeed(Vector2 s)
{
	_speed.x += s.x;
	_speed.y += s.y;
}

player::player(std::vector<sf::Texture> &tex, Vector2 pos, std::vector<sf::Drawable*>& vect) : ship(tex, pos, vect)
{

}

enemy::enemy(std::vector<sf::Texture> &tex, Vector2 pos, std::vector<sf::Drawable*>& vect) : ship(tex, pos, vect)
{

}