/*
=================
cWizard.h
- Header file for class definition - SPECIFICATION
- Header file for the Wizard class which is a child of cSprite class
=================
*/
#ifndef _CWizard_H
#define _CWizard_H
#include "cSprite.h"
#include "OrcsGame.h"

class cWizard : public cSprite
{
private:
	glm::vec2 WizardVelocity = glm::vec2(0.0f, 0.0f);

public:
	void render();		// Default render function
	void update(float deltaTime);		// Wizard update method
	void setWizardVelocity(glm::vec2 WizardVel);   // Sets the velocity for the Wizard
	glm::vec2 getWizardVelocity();				 // Gets the Wizard velocity

};
#endif