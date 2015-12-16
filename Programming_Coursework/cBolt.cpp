/*
=================
cBolt.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cBolt.h"

void cBolt::render()
{
	glPushMatrix();

	glTranslatef(spritePos2D.x, spritePos2D.y, 0.0f);
	glRotatef(spriteRotation, 0.0f, 0.0f, 1.0f);
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

void cBolt::update(float deltaTime)
{

	glm::vec2 spriteVelocityAdd = glm::vec2 (0.0f, 0.0f);
	
	spriteVelocityAdd.x = (glm::cos(glm::radians(spriteRotation)));

	spriteVelocityAdd *= spriteTranslation;

	BoltVelocity += spriteVelocityAdd;

	//glm::vec2 centrePos = getSpriteCentre();
	//spritePos2D.x -= centrePos.x;
	//spritePos2D.y += centrePos.y;
	
	spritePos2D.x += 5.0f;
	 
	BoltVelocity *= 1;

	setBoundingRect(&boundingRect);

}
/*
=================================================================
  Sets the velocity for the Bolt
=================================================================
*/
void cBolt::setBoltVelocity(glm::vec2 BoltVel)
{
	BoltVelocity = BoltVel;
}
/*
=================================================================
  Gets the Bolt velocity
=================================================================
*/
glm::vec2 cBolt::getBoltVelocity()
{
	return BoltVelocity;
}
/*
==========================================================================
Use this method to show the collision box.
==========================================================================
*/
void cBolt::renderCollisionBox()
{
	glPushMatrix();

	glTranslatef(boundingRect.left, boundingRect.top, 0.0f);
	glRotatef(spriteRotation, 0.0f, 0.0f, 1.0f);
	glScalef(spriteScaling.x, spriteScaling.y, 1.0f);

	glColor3f(255.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	//glVertex2f(-(textureWidth / 2), -(textureHeight / 2));
	//glVertex2f((textureWidth / 2), -(textureHeight / 2));
	//glVertex2f((textureWidth / 2), (textureHeight / 2));
	//glVertex2f(-(textureWidth / 2), (textureHeight / 2));

	glVertex2f(-((boundingRect.right - boundingRect.left) / 2), -((boundingRect.bottom - boundingRect.top) / 2));
	glVertex2f(((boundingRect.right - boundingRect.left) / 2), -((boundingRect.bottom - boundingRect.top) / 2));
	glVertex2f(((boundingRect.right - boundingRect.left) / 2), ((boundingRect.bottom - boundingRect.top) / 2));
	glVertex2f(-((boundingRect.right - boundingRect.left) / 2), ((boundingRect.bottom - boundingRect.top) / 2));

	glEnd();

	glPopMatrix();
}