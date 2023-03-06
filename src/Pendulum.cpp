#include "Pendulum.hpp"


Pendulum::Pendulum(int x, int y, int mass, float a0, int radius){

	this->x = x;
	this->y = y;
	this->mass = mass;
	this->acceleration = a0 * PI / 180;
	 
	this->angular_acceleration = 0;
	this->radius = radius;
	this->angular_velocity = 0;

	this->weight = new sf::CircleShape(25);
	this->weight->setOrigin(sf::Vector2f(this->weight->getRadius(), this->weight->getRadius()));
	this->weight->setPosition(sf::Vector2f(getXPoint(), getYPoint()));
	this->weight->setFillColor(sf::Color(10, 199, 13));

	this->string = new sf::RectangleShape(sf::Vector2f(3, radius));
	this->string->setOrigin(this->string->getSize().x / 2, 0);
	this->string->setPosition(sf::Vector2f(this->x, this->y));
	this->string->setFillColor(sf::Color::White);
	this->string->setRotation(acceleration * 180 / PI);


}

Pendulum::Pendulum(Pendulum *upperPendulum, int mass, float a0, int radius){
	this->upperPendulum = upperPendulum;
	upperPendulum->lowerPendulum = this;
	this->x = upperPendulum->getXPoint();
	this->y = upperPendulum->getXPoint();
	
	this->mass = mass;
	this->radius = radius;
	this->angular_acceleration = 0;

	this->acceleration = a0 * PI / 180;
	this->angular_velocity = 0;

	this->weight = new sf::CircleShape(25);
	this->weight->setOrigin(sf::Vector2f(this->weight->getRadius(), this->weight->getRadius()));
	this->weight->setPosition(sf::Vector2f(getXPoint(), getYPoint()));
	this->weight->setFillColor(sf::Color(199, 63, 10));

	this->string = new sf::RectangleShape(sf::Vector2f(3, radius));
	this->string->setOrigin(this->string->getSize().x / 2, 0);
	this->string->setPosition(sf::Vector2f(this->x, this->y));
	this->string->setFillColor(sf::Color::White);
	this->string->setRotation(acceleration * 180 / PI);
}



int Pendulum::getXPoint(){
	return string->getPosition().x - radius * sin(acceleration);
}

int Pendulum::getYPoint(){
	return string->getPosition().y + radius * cos(acceleration);
}

void Pendulum::draw(sf::RenderWindow &window){
	window.draw(sf::RectangleShape(*this->string));
	window.draw(sf::CircleShape(*this->weight));
}

sf::Vector2f Pendulum::updatePosition(float dt){
	
	this->angular_velocity += this->angular_acceleration * dt;
	this->acceleration += this->angular_velocity * dt;

	if (upperPendulum != nullptr)
	{
		this->x = upperPendulum->getXPoint();
		this->y = upperPendulum->getYPoint();
	}

	this->string->setPosition(x, y);
	this->string->setRotation(this->acceleration * 180 / PI);
	this->weight->setPosition(this->getXPoint(), this->getYPoint());
	return sf::Vector2f(this->getXPoint(), this->getYPoint());
}

void Pendulum::update() {
	float r1 = upperPendulum->radius;
	float r2 = this->radius;
	float v1 = upperPendulum->angular_velocity;
	float v2 = this->angular_velocity;
	float m1 = upperPendulum->mass;
	float m2 = this->mass;
	float a1 = upperPendulum->acceleration;
	float a2 = this->acceleration;

	float num1 = -GRAVITY * (2 * m1 + m2) * sin(a1);
	float num2 = -m2 * GRAVITY * sin(a1 - 2 * a2);
	float num3 = -2 * sin(a1 - a2) * m2 * (v2 * v2 * r2 + v1 * v1 * r1 * cos(a1 - a2));
	float den = r1 * (2 * m1 + m2 - m2 * cos(2 * a1 - 2 * a2));

	upperPendulum->angular_acceleration = (num1 + num2 + num3) / den;

	num1 = 2 * sin(a1 - a2);
	num2 = v1 * v1 * r1 * (m1 + m2);
	num3 = GRAVITY * (m1 + m2) * cos(a1) + v2 * v2 * r2 * m2 * cos(a1 - a2);
	den = r2 * (2 * m1 + m2 - m2 * cos(2 * a1 - 2 * a2));
	this->angular_acceleration = (num1 * (num2 + num3)) / den;
}

Pendulum::~Pendulum() {
	delete this->string;
	delete this->weight;
	
}