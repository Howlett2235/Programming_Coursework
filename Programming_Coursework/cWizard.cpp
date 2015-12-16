/*
=================
cWizard.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cWizard.h"

void cWizard::render()
{
	glPushMatrix();

	glTranslatef(spritePos2D.x, spritePos2D.y, 0.0f);
	glRotatef(spriteRotation, 0.0f, 0.0f, 0.0f);
	glScalef(spriteScaling.x, spriteScaling.y, 1.0f);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, GLTextureID); // Binding of GLtexture name 

	glBegin(GL_QUADS);
	glColor3f(255.0f, 255.0f, 255.0f);
	glTexCoord2f(spriteTexCoordData[0].x, spriteTexCoordData[0].y);
	glVertex2f(-(textureWidth / 2), -(textureHeight / 2));
	glTexCoord2f(spriteTexCoordData[1].x, spriteTexCoordData[1].y);
	glVertex2f((textureWidth / 2), -(textureHeight / 2));
	glTexCoord2f(spriteTexCoordData[2].x, spriteTexCoordData[2].y);
	glVertex2f((textureWidth / 2), (textureHeight / 2));
	glTexCoord2f(spriteTexCoordData[3].x, spriteTexCoordData[3].y);
	glVertex2f(-(textureWidth / 2), (textureHeight / 2));

	glEnd();
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}
/*
=================================================================
Update the sprite position
=================================================================
*/

void cWizard::update(float deltaTime)
{
	if (m_InputMgr->isKeyDown(VK_RIGHT))
	{
		spritePos2D.x += 30.0f;
	}
	if (m_InputMgr->isKeyDown(VK_LEFT))
	{
		spritePos2D.x -= 30.0f;
	}
	if (m_InputMgr->isKeyDown(VK_UP))
	{
		spritePos2D.y -= 30.0f;
	}
	if (m_InputMgr->isKeyDown(VK_DOWN))
	{
		spritePos2D.y += 30.0f;
	}
	

	if (m_InputMgr->isKeyDown(VK_SPACE))
	{
		// Add new Bolt sprite to the vector array
		theWizardBolts.push_back(new cBolt);
		int numBolts = theWizardBolts.size() - 1;
		theWizardBolts[numBolts]->setSpritePos(glm::vec2(spritePos2D.x , spritePos2D.y));
		theWizardBolts[numBolts]->setSpriteTranslation(glm::vec2(2.0f, 2.0f));
		theWizardBolts[numBolts]->setTexture(theGameTextures[4]->getTexture());
		theWizardBolts[numBolts]->setTextureDimensions(theGameTextures[4]->getTWidth(), theGameTextures[4]->getTHeight());
		theWizardBolts[numBolts]->setSpriteCentre();
		theWizardBolts[numBolts]->setBoltVelocity(glm::vec2(0.0f, 0.0f));
		theWizardBolts[numBolts]->setSpriteRotation(getSpriteRotation());
		theWizardBolts[numBolts]->setActive(true);
		theWizardBolts[numBolts]->setMdlRadius();
		// play the firing sound
		m_SoundMgr->getSnd("Shot")->playAudio(AL_TRUE);
	}

	if (spriteRotation > 360)
	{
		spriteRotation -= 360.0f;
	}

	glm::vec2 spriteVelocityAdd = glm::vec2(0.0f, 0.0f);
	spriteVelocityAdd.x = (glm::sin(glm::radians(spriteRotation)));
	spriteVelocityAdd.y = -(glm::cos(glm::radians(spriteRotation)));

	spriteVelocityAdd *= spriteTranslation;

	WizardVelocity += spriteVelocityAdd;

	spritePos2D += WizardVelocity * deltaTime;

	WizardVelocity *= 0.0;

	/*
	==============================================================
	| Check for collisions
	==============================================================
	*/
	for (vector<cBolt*>::iterator BoltIterartor = theWizardBolts.begin(); BoltIterartor != theWizardBolts.end(); ++BoltIterartor)
	{
		(*BoltIterartor)->update(deltaTime);
		for (vector<cOrc*>::iterator OrcIterator = theOrcs.begin(); OrcIterator != theOrcs.end(); ++OrcIterator)
		{
			if ((*OrcIterator)->collidedWith((*OrcIterator)->getBoundingRect(), (*BoltIterartor)->getBoundingRect()))
			{
				// if a collision set the Bolt and Orc to false
				(*OrcIterator)->setActive(false);
				(*BoltIterartor)->setActive(false);
			}
		}
	}

	vector<cBolt*>::iterator BoltIterartor = theWizardBolts.begin();
	while (BoltIterartor != theWizardBolts.end())
	{
		if ((*BoltIterartor)->isActive() == false)
		{
			BoltIterartor = theWizardBolts.erase(BoltIterartor);
			// play the explosion sound.
			m_SoundMgr->getSnd("Explosion")->playAudio(AL_TRUE);
		}
		else
		{
			//(*BoltIterartor)->update(deltaTime);
			(*BoltIterartor)->render();
			++BoltIterartor;
		}
	}
	setBoundingRect(&boundingRect);
}
/*
=================================================================
  Sets the velocity for the Wizard
=================================================================
*/
void cWizard::setWizardVelocity(glm::vec2 WizardVel)
{
	WizardVelocity = WizardVel;
}
/*
=================================================================
  Gets the Wizard velocity
=================================================================
*/
glm::vec2 cWizard::getWizardVelocity()
{
	return WizardVelocity;
}
