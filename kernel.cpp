//
// kernel.cpp
//
#include "kernel.h"
#include "utils/SimpleGamePadDefs.h"

#include "snake/SnakeGame.h"
#include "tetris/TetrisGame.h"
#include "pong/PongGame.h"
#include "invaders/InvadersGame.h"


#include <assert.h>

#define DRIVE		"SD:"
#define DEVICE_INDEX	1		// "upad1"

CKernel *CKernel ::s_pThis = 0;



CKernel::CKernel (void) : 
  m_2DGraphics(m_Options.GetWidth(), m_Options.GetHeight()),
  m_Timer(&m_Interrupt),
  m_USBHCI(&m_Interrupt, &m_Timer,TRUE),
  m_EMMC(&m_Interrupt, &m_Timer, &m_ActLED),
  m_SoundDevice (&m_Interrupt),
  m_pGamePad(0)
{
	s_pThis = this;
	m_ActLED.Blink (5);
}

CKernel::~CKernel (void)
{
	s_pThis = 0;
	delete background;
	delete btnInvaders;
	delete btnPong;
	delete btnSnake;
	delete btnTetris;
	delete activeGame;
	delete writer;
}

boolean CKernel::Initialize (void)
{
	boolean success = TRUE;

	if(success)
	{
		success = m_2DGraphics.Initialize ();
	}
	if(success)
	{
		success = m_Interrupt.Initialize();
	}
	if(success)
	{
		success = m_Timer.Initialize();
	}
	if(success)
	{
		success = m_USBHCI.Initialize();
	}
	if(success)
	{
		success = m_EMMC.Initialize();
	}

	return success;
}

TShutdownMode CKernel::Run (void)
{
	// Mount file system (fail check omitted)
	f_mount(&m_FileSystem, DRIVE, 1);

	//Load images 	
	background = new Image("/gfx/menu.lmi");
	btnPong = new Image("/gfx/pong.lmi");
	btnTetris = new Image("/gfx/tetris.lmi");
	btnSnake = new Image("/gfx/snake.lmi");
	btnInvaders = new Image("/gfx/invaders.lmi");
	sndMenu = new Sound("/audio/menu_loop.raw", 2, 16);

	writer = new FontWriter("/gfx/fonts/font_I-pixel-u_20x20_anti.lmi", {20,20});
	screenHeight = m_Options.GetHeight();
	screenWidth = m_Options.GetWidth();
	


	for (unsigned int cycle = 0; 1; cycle++)
	{	
		boolean bUpdated = m_USBHCI.UpdatePlugAndPlay ();

		if(m_pGamePad == 0)
		{
			if (!bUpdated) {
				continue;
			}
					
			m_pGamePad = (CUSBGamePadDevice *) m_DeviceNameService.GetDevice ("upad", DEVICE_INDEX, FALSE);
			
			if (m_pGamePad == 0) {
				m_2DGraphics.ClearScreen(BLACK_COLOR);
				writer->Write(screenWidth / 2, (screenHeight / 2) - writer->GetFontHeight(), "NO GAMEPAD DETECTED", &m_2DGraphics,C2DGraphics::AlignCenter );
//				m_2DGraphics.DrawText(screenWidth / 2, (screenHeight / 2) - 10, BLACK_COLOR, "NO GAMEPAD DETECTED", C2DGraphics::AlignCenter);
				writer->Write(screenWidth / 2, (screenHeight / 2) + 10, "PLEASE ATTACH ONE", &m_2DGraphics,C2DGraphics::AlignCenter );
//				m_2DGraphics.DrawText(screenWidth/ 2, (screenHeight / 2) + 10, BLACK_COLOR, "PLEASE ATTACH ONE", C2DGraphics::AlignCenter);
				m_2DGraphics.UpdateDisplay();
				continue;
			}
			
			m_pGamePad->RegisterRemovedHandler(GamePadRemovedHandler);
			
			// get initial state from gamepad and register status handler
			const TGamePadState *pState = m_pGamePad->GetInitialState();			
			assert (pState != 0);
			GamePadStatusHandler (DEVICE_INDEX-1, pState);
			
			m_pGamePad->RegisterStatusHandler (GamePadStatusHandler);
		}

		if(activeGame == nullptr || !activeGame->isActive())
		{
			MenuUpdate();
			continue;;
		}


		//Handle input
        activeGame->HandleInput(m_GamePadState);

		//Update
        activeGame->Update(&m_Timer);

        // Drawing        
        activeGame->Draw(&m_2DGraphics);

		//Update display
		m_2DGraphics.UpdateDisplay();
	}
		
	// Unmount file system (fail check omitted)
	f_mount (0, DRIVE, 0);

	return ShutdownHalt;

}

void CKernel::MenuUpdate()
{
	if(!muted)
		sndMenu->Play(&m_SoundDevice);
	
	//Background
	m_2DGraphics.ClearScreen(COLOR16(0,0,2));
	
	background->DrawAt(screenWidth/2, screenHeight/2, &m_2DGraphics, Center);		
	//List o' games
	
	btnSnake->DrawAt(screenWidth/2, screenHeight/2, &m_2DGraphics, TopCenter, 0x00, (selectedIndex == 0 ? COLOR16(0,0,31): 0x00));
	btnTetris->DrawAt(screenWidth/2, screenHeight/2+30, &m_2DGraphics, TopCenter, 0x00, (selectedIndex == 1 ? COLOR16(0,0,31): 0x00));
	btnPong->DrawAt(screenWidth/2, screenHeight/2+60, &m_2DGraphics, TopCenter, 0x00, (selectedIndex == 2 ? COLOR16(0,0,31): 0x00));
	btnInvaders->DrawAt(screenWidth/2, screenHeight/2+90, &m_2DGraphics, TopCenter, 0x00, (selectedIndex == 3 ? COLOR16(0,0,31): 0x00));

	//Selection dot
//	m_2DGraphics.DrawRect((screenWidth - 250 - 20) /2, (screenHeight/2) + (selectedIndex * 30)+ 5, 20, 20, BLUE_COLOR);
//	m_2DGraphics.DrawRect((screenWidth - 250)/2, (screenHeight/2) + (selectedIndex * 30) + 25, 250, 5, BLUE_COLOR);
		
//	m_2DGraphics.DrawText(10,10,WHITE_COLOR, debugText);


	m_2DGraphics.UpdateDisplay();

	if(keyDelay > 0)
	{
		keyDelay--;
		return;
	}


	
	if(code.GetSize() == 8) //Never going to happen for now
	{
		if(
			code[7] == GamePadButtonUp && 
			code[6] == GamePadButtonUp && 
			code[5] == GamePadButtonDown && 
			code[4] == GamePadButtonDown && 
			code[5] == GamePadButtonLeft && 
			code[4] == GamePadButtonRight && 
			code[3] == GamePadButtonLeft && 
			code[2] == GamePadButtonB && 
			code[1] == GamePadButtonA && 
			code[0] == GamePadButtonStart 
		)
		{
			writer->Write(screenWidth/2, screenHeight/2, "KONAMI STYLE!!!", &m_2DGraphics, C2DGraphics::AlignCenter );
		}
	}
	
	if(code.GetSize() == 3)
	{
		if(
			(code[2] & GamePadButtonLeft && code[1] & GamePadButtonLeft && code[0] & GamePadButtonTriangle )
			|| (code[2] & SimpleGamePadButtonA && code[1] & SimpleGamePadButtonA && code[0] & SimpleGamePadButtonSelect /*Same as GamePadButtonCircle*/)
		)
		{
			CString path;
			path.Format("/x/%02i.lmi", rnd.GetNumber() % 6);
			delete background;
        	background = new Image(path);
			code.clear();
		}
	}

	if( (m_GamePadState.buttons & GamePadButtonLeft) ||
	    (m_GamePadState.buttons & GamePadButtonRight) || 
		(m_GamePadState.buttons & GamePadButtonUp) || 
		(m_GamePadState.buttons & GamePadButtonDown) || 
		(m_GamePadState.buttons & GamePadButtonCross /*also equals SimpleGamePadStart*/) || 
		(m_GamePadState.buttons & GamePadButtonSquare) || 
		(m_GamePadState.buttons & GamePadButtonTriangle) ||
		(m_GamePadState.buttons & GamePadButtonCircle /*also equals SimpleGamePadSelect*/)   ||
		(m_GamePadState.buttons & SimpleGamePadButtonB)   ||
		(m_GamePadState.buttons & SimpleGamePadButtonA) )
	{
		keyDelay = 10;
		code.push(m_GamePadState.buttons);
	}

	
	
	//Up
	if (((m_GamePadState.buttons & GamePadButtonUp) || (m_GamePadState.axes[1].value == 0))) {
        if(selectedIndex > 0)
			selectedIndex--;
		keyDelay = 10;
//		code.push(m_GamePadState.buttons);
    }
	//Down
    if (((m_GamePadState.buttons & GamePadButtonDown) || (m_GamePadState.axes[1].value == 255))) {
        if(selectedIndex < 3)
            selectedIndex++;
		keyDelay = 10;
//		code.push(m_GamePadState.buttons);
    }

	//Mute
	if((m_GamePadState.buttons & GamePadButtonCircle) || (m_GamePadState.buttons & SimpleGamePadButtonSelect))
	{		
		if(m_SoundDevice.PlaybackActive()) 
			sndMenu->Stop(&m_SoundDevice);
		muted = !muted;
	}
	//Select
    if ((m_GamePadState.buttons & GamePadButtonCross /*same as SimpleGamePadButtonStart*/) || (m_GamePadState.buttons & SimpleGamePadButtonB)) {

		sndMenu->Stop(&m_SoundDevice);
		
		while(m_SoundDevice.PlaybackActive())
		{
			//Just wat for the audio sample to finish
		}

		switch (selectedIndex)
		{
		case 0:
			if(activeGame != nullptr) delete activeGame;					
			activeGame = new SnakeGame(m_Options.GetWidth(), m_Options.GetHeight());			
			break;
		case 1:
			if(activeGame != nullptr) delete activeGame;
			activeGame = new TetrisGame(m_Options.GetWidth(), m_Options.GetHeight());			
			break;
		case 2:
			if(activeGame != nullptr) delete activeGame;
			activeGame = new PongGame(m_Options.GetWidth(), m_Options.GetHeight());
			break;
		case 3:	
			if(activeGame != nullptr) delete activeGame;
			activeGame = new InvadersGame(m_Options.GetWidth(), m_Options.GetHeight());
			break;
		default:
			break;
		}

		if(activeGame != nullptr)
		{
			
			//m_SoundDevice = CPWMSoundDevice(&m_Interrupt);
			activeGame->setSoundDevice(&m_SoundDevice);
		}
		
		keyDelay = 10;
    }
}

void CKernel::GamePadStatusHandler (unsigned nDeviceIndex, const TGamePadState *pState)
{
	if (nDeviceIndex != DEVICE_INDEX-1) {
		return;
	}

	assert (s_pThis != 0);
	assert (pState != 0);
	memcpy (&s_pThis->m_GamePadState, pState, sizeof *pState);
}

void CKernel::GamePadRemovedHandler (CDevice *pDevice, void *pContext)
{
	assert (s_pThis != 0);
	s_pThis->m_pGamePad = 0;
}

