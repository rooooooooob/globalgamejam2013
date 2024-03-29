#ifndef TRIG_HPP
#define TRIG_HPP

#include <cmath>
#include <SFML/System/Vector2.hpp>

namespace ggj
{

const float pi = 3.14159265;

float lengthdirX(float length, float dir);

float lengthdirY(float length, float dir);

sf::Vector2f lengthdir(float length, float dir);


float pointDistance(const sf::Vector2f& a, const sf::Vector2f& b);

float pointDistance(float x1, float y1, float x2, float y2);


float pointDirection(const sf::Vector2f& a, const sf::Vector2f& b);

float pointDirection(float x1, float y1, float x2, float y2);

}

#endif

