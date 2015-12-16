#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#define GLX_GLXEXT_LEGACY //Must be declared so that our local glxext.h is picked up, rather than the system one


#include <windows.h>
#include "windowOGL.h"
#include "GameConstants.h"
#include "cWNDManager.h"
#include "cInputMgr.h"
#include "cSoundMgr.h"
#include "cFontMgr.h"
#include "cSprite.h"
#include "OrcsGame.h"
#include "cButton.h"

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR cmdLine,
	int cmdShow)
{

	//Set our window settings
	const int windowWidth = 1024;
	const int windowHeight = 768;
	const int windowBPP = 16;
	int increment = 0;
	int timer = 0;
	int score = 0;
	bool player_dead = false;





	//This is our window
	static cWNDManager* pgmWNDMgr = cWNDManager::getInstance();

	// This is the input manager
	static cInputMgr* theInputMgr = cInputMgr::getInstance();

	// This is the sound manager
	static cSoundMgr* theSoundMgr = cSoundMgr::getInstance();

	// This is the Font manager
	static cFontMgr* theFontMgr = cFontMgr::getInstance();

	//The example OpenGL code
	windowOGL theOGLWnd;

	//Attach our the OpenGL window
	pgmWNDMgr->attachOGLWnd(&theOGLWnd);

	// Attach the keyboard manager
	pgmWNDMgr->attachInputMgr(theInputMgr);

	//Attempt to create the window
	if (!pgmWNDMgr->createWND(windowWidth, windowHeight, windowBPP))
	{
		//If it fails

		MessageBox(NULL, "Unable to create the OpenGL Window", "An error occurred", MB_ICONERROR | MB_OK);
		pgmWNDMgr->destroyWND(); //Reset the display and exit
		return 1;
	}

	if (!theOGLWnd.initOGL(windowWidth, windowHeight)) //Initialize our example
	{
		MessageBox(NULL, "Could not initialize the application", "An error occurred", MB_ICONERROR | MB_OK);
		pgmWNDMgr->destroyWND(); //Reset the display and exit
		return 1;
	}

	//Clear key buffers
	theInputMgr->clearBuffers(theInputMgr->KEYS_DOWN_BUFFER | theInputMgr->KEYS_PRESSED_BUFFER);

	/* initialize random seed: */
	srand((unsigned int)time(NULL));

	// Create vector array of textures
	LPCSTR texturesToUse[] = { "Images\\Orc Baddy.png", "Images\\Orc Baddy.png", "Images\\Orc Baddy.png", "Images\\Orc Baddy.png", "Images\\Magic Bolt.png" };
	for (int tCount = 0; tCount < 5; tCount++)
	{
		theGameTextures.push_back(new cTexture());
		theGameTextures[tCount]->createTexture(texturesToUse[tCount]);
	}

	// Create vector array of textures
	vector<cTexture*> textureBkgList;
	LPCSTR bkgTexturesToUse[] = { "Images/Background.png", "Images/Introduction_Screen.png", "Images/Game_Over_Screen.png" };
	for (int tCount = 0; tCount < 3; tCount++)
	{
		textureBkgList.push_back(new cTexture());
		textureBkgList[tCount]->createTexture(bkgTexturesToUse[tCount]);
	}

	cTexture transSprite;
	transSprite.createTexture("Images/blank.png");

	cBkGround spriteBkgd;
	spriteBkgd.setSpritePos(glm::vec2(0.0f, 0.0f));
	spriteBkgd.setTexture(textureBkgList[0]->getTexture());
	spriteBkgd.setTextureDimensions(textureBkgList[0]->getTWidth(), textureBkgList[0]->getTHeight());

	cBkGround spriteStartBkgd;
	spriteStartBkgd.setSpritePos(glm::vec2(0.0f, 0.0f));
	spriteStartBkgd.setTexture(textureBkgList[1]->getTexture());
	spriteStartBkgd.setTextureDimensions(textureBkgList[1]->getTWidth(), textureBkgList[1]->getTHeight());

	cBkGround spriteEndBkgd;
	spriteEndBkgd.setSpritePos(glm::vec2(0.0f, 0.0f));
	spriteEndBkgd.setTexture(textureBkgList[2]->getTexture());
	spriteEndBkgd.setTextureDimensions(textureBkgList[2]->getTWidth(), textureBkgList[2]->getTHeight());



	// load game sounds
	// Load Sound
	LPCSTR gameSounds[3] = { "Audio/Background_Music.mp3", "Audio/Magic_Bolt.flac", "Audio/Orc_Death.mp3" };

	theSoundMgr->add("Theme", gameSounds[0]);
	theSoundMgr->add("Shot", gameSounds[1]);
	theSoundMgr->add("Explosion", gameSounds[2]);

	// load game fontss
	// Load Fonts
	LPCSTR gameFonts[2] = { "Fonts/digital-7.ttf", "Fonts/space age.ttf" };

	theFontMgr->addFont("SevenSeg", gameFonts[0], 24);
	theFontMgr->addFont("Space", gameFonts[1], 24);

	// Create vector array of button textures
	vector<cTexture*> btnTextureList;
	LPCSTR btnTexturesToUse[] = { "Images/Main_Quit_Button.png","Images/Main_Play_Button.png", "Images/Game_Over_Quit.png", "Images/Game_Over_Replay.png" };
	for (int tCount = 0; tCount < 4; tCount++)
	{
		btnTextureList.push_back(new cTexture());
		btnTextureList[tCount]->createTexture(btnTexturesToUse[tCount]);
	}

	cButton exitButton;
	exitButton.attachInputMgr(theInputMgr);
	exitButton.setTexture(btnTextureList[0]->getTexture());
	exitButton.setTextureDimensions(btnTextureList[0]->getTWidth(), btnTextureList[0]->getTHeight());

	cButton playButton;
	playButton.attachInputMgr(theInputMgr);
	playButton.setTexture(btnTextureList[1]->getTexture());
	playButton.setTextureDimensions(btnTextureList[1]->getTWidth(), btnTextureList[1]->getTHeight());

	cButton quitButton;
	quitButton.attachInputMgr(theInputMgr);
	quitButton.setTexture(btnTextureList[2]->getTexture());
	quitButton.setTextureDimensions(btnTextureList[2]->getTWidth(), btnTextureList[2]->getTHeight());

	cButton replayButton;
	replayButton.attachInputMgr(theInputMgr);
	replayButton.setTexture(btnTextureList[3]->getTexture());
	replayButton.setTextureDimensions(btnTextureList[3]->getTWidth(), btnTextureList[3]->getTHeight());



	cTexture WizardTxt;
	WizardTxt.createTexture("Images\\Wizard Dude.png");
	cWizard WizardSprite;
	WizardSprite.attachInputMgr(theInputMgr); // Attach the input manager to the sprite
	WizardSprite.setSpritePos(glm::vec2(100.0f, 380.0f));
	WizardSprite.setTexture(WizardTxt.getTexture());
	WizardSprite.setTextureDimensions(WizardTxt.getTWidth(), WizardTxt.getTHeight());
	WizardSprite.setSpriteCentre();
	WizardSprite.setWizardVelocity(glm::vec2(0.0f, 0.0f));

	// Attach sound manager to Wizard sprite
	WizardSprite.attachSoundMgr(theSoundMgr);
	gameState theGameState = MENU;
	btnTypes theBtnType = EXIT;
	string strScore = "";

	//This is the mainloop, we render frames until isRunning returns false
	while (pgmWNDMgr->isWNDRunning())
	{
		pgmWNDMgr->processWNDEvents(); //Process any window events

		//We get the time that passed since the last frame
		float elapsedTime = pgmWNDMgr->getElapsedSeconds();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		switch (theGameState)
		{
		case MENU:
			spriteStartBkgd.render();

			playButton.setSpritePos(glm::vec2(400.0f, 300.0f));
			exitButton.setSpritePos(glm::vec2(400.0f, 500.0f));
			playButton.render();
			exitButton.render();

			theGameState = playButton.update(theGameState, PLAYING);
			exitButton.update();


			if (exitButton.getClicked())
			{
				SendMessage(pgmWNDMgr->getWNDHandle(), WM_CLOSE, NULL, NULL);
			}
			break;
		case PLAYING:

			spriteBkgd.render();
			

			WizardSprite.update(elapsedTime);
			{
				vector<cOrc*>::iterator OrcIterator = theOrcs.begin();
				while (OrcIterator != theOrcs.end())
				{
					if ((*OrcIterator)->isActive() == false)
					{
						OrcIterator = theOrcs.erase(OrcIterator);
						increment--;
						score++;

					}
					else if (WizardSprite.collidedWith(WizardSprite.getBoundingRect(), (*OrcIterator)->getBoundingRect()))
		
						{
							theGameState = END;
							break;

						}


					else
					{
						(*OrcIterator)->update(elapsedTime);
						(*OrcIterator)->render();
						++OrcIterator;
					}
				}
			}

			



			timer++;

			if (timer > 40)

			{


				theOrcs.push_back(new cOrc);
				theOrcs[increment]->setSpritePos(glm::vec2(1024, rand() % windowHeight));
				theOrcs[increment]->setSpriteTranslation(glm::vec2((rand() % 4 + 1), (rand() % 4 + 1)));
				int randOrc = rand() % 4;
				theOrcs[increment]->setTexture(theGameTextures[randOrc]->getTexture());
				theOrcs[increment]->setTextureDimensions(theGameTextures[randOrc]->getTWidth(), theGameTextures[randOrc]->getTHeight());
				theOrcs[increment]->setSpriteCentre();
				theOrcs[increment]->setOrcVelocity(glm::vec2(glm::vec2(0.0f, 0.0f)));
				theOrcs[increment]->setActive(true);
				theOrcs[increment]->setMdlRadius();

				increment++;

				timer = 0;
			}

			WizardSprite.render();
			strScore = "Score:  " + std::to_string(score);

			theFontMgr->getFont("Space")->printText(strScore.c_str(), FTPoint(25.0f, 25.0f, 0.0f));

			break;
		case END:
			
			spriteEndBkgd.render();

			replayButton.setClicked(false);
			quitButton.setClicked(false);

			replayButton.setSpritePos(glm::vec2(50.0f, 600.0f));
			quitButton.setSpritePos(glm::vec2(700.0f, 600.0f));
			replayButton.render();
			quitButton.render();

			theFontMgr->getFont("Space")->printText(strScore.c_str(), FTPoint(25.0f, 25.0f, 0.0f));

			theGameState = replayButton.update(theGameState, PLAYING);

			theOrcs.clear();
			WizardSprite.setSpritePos(glm::vec2(100.0f, 380.0f));
			WizardSprite.update(elapsedTime);
			increment = 0;

			theOrcs.push_back(new cOrc);
			theOrcs[increment]->setSpritePos(glm::vec2(1024, rand() % windowHeight));
			theOrcs[increment]->setSpriteTranslation(glm::vec2((rand() % 4 + 1), (rand() % 4 + 1)));
			int randOrc = rand() % 4;
			theOrcs[increment]->setTexture(theGameTextures[randOrc]->getTexture());
			theOrcs[increment]->setTextureDimensions(theGameTextures[randOrc]->getTWidth(), theGameTextures[randOrc]->getTHeight());
			theOrcs[increment]->setSpriteCentre();
			theOrcs[increment]->setOrcVelocity(glm::vec2(glm::vec2(0.0f, 0.0f)));
			theOrcs[increment]->setActive(true);
			theOrcs[increment]->setMdlRadius();


			exitButton.update();

			if (quitButton.getClicked())
			{
				SendMessage(pgmWNDMgr->getWNDHandle(), WM_CLOSE, NULL, NULL);
			}


			

		}
			pgmWNDMgr->swapBuffers();
			theInputMgr->clearBuffers(theInputMgr->KEYS_DOWN_BUFFER | theInputMgr->KEYS_PRESSED_BUFFER);

		}

		theOGLWnd.shutdown(); //Free any resources
		pgmWNDMgr->destroyWND(); //Destroy the program window

		return 0; //Return success
	}

