/*
=================
cOrc.h
- Header file for class definition - SPECIFICATION
- Header file for the Wizard class which is a child of cSprite class
=================
*/
#ifndef _COrc_H
#define _COrc_H
#include "cSprite.h"

class cOrc : public cSprite
{
private:
	glm::vec2 OrcVelocity = glm::vec2(0.0f, 0.0f);

public:
	void render();		// Default render function
	void update(float deltaTime);		// Wizard update method
	void setOrcVelocity(glm::vec2 OrcVel);   // Sets the velocity for the Wizard
	glm::vec2 getOrcVelocity();				 // Gets the Wizard velocity
	void renderCollisionBox();				// Use this function to show the collision box
};
#endif