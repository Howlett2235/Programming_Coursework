/*
=================
cBolt.h
- Header file for class definition - SPECIFICATION
- Header file for the Bolt class which is a child of cSprite class
=================
*/
#ifndef _CBolt_H
#define _CBolt_H
#include "cSprite.h"


class cBolt : public cSprite
{
private:
	glm::vec2 BoltVelocity = glm::vec2(0.0f, 0.0f);

public:
	//cBolt(vector<cTexture*> tileTextList)

	void render();		// Default render function
	void update(float deltaTime);		// Bolt update method
	void setBoltVelocity(glm::vec2 BoltVel);   // Sets the velocity for the Bolt
	glm::vec2 getBoltVelocity();				 // Gets the Bolt velocity
	void renderCollisionBox();				// Use this function to show the collision box
};
#endif