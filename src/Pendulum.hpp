#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>

class Pendulum {

public:

	Pendulum(int x, int y, int mass, float a0, int radius);
	Pendulum(Pendulum *upperPendulum, int mass, float a0, int r);
	~Pendulum();

	void update();
	void draw(sf::RenderWindow &window);
	void attachPendulum(Pendulum *lowerPendulum);
	sf::Vector2f updatePosition(float dt);

private:
	uint32_t mass, x, y, radius;

	const float  PI = 3.14159265358979f;
	const float  GRAVITY = 9.81;
	
	int getXPoint();
	int getYPoint();
	
	float angular_acceleration, angular_velocity, acceleration;

	sf::CircleShape *weight;
	sf::RectangleShape *string;

	Pendulum *upperPendulum = nullptr;
	Pendulum *lowerPendulum = nullptr;
	
};