#include "GUI.h"
#include "../Core/Kernel.h"
#include "CEGui.h"
#include "RendererModules\Direct3D9\CEGUIDirect3D9Renderer.h"
#include "CEGUIRenderer.h"
#include "ScriptingModules\LuaScriptModule\CEGUILua.h"
#include "ScriptingModules\LuaScriptModule\support\tolua++\tolua++.h"
#include "CEGUI_Window.h"

#include "../LUA Interfaces/LuaInterface.h"

GUI::GUI(Renderer* r)
{
	this->renderer = r;
	this->lastUpdate = 0;
}

GUI::~GUI()
{

}

void GUI::Init()
{
	CEGUI::Direct3D9Renderer& myRenderer =
		CEGUI::Direct3D9Renderer::create( Kernel::Instance()->GetRenderer()->GetDevice() );

	/*CEGUI::LuaScriptModule& script_module = 
		CEGUI::LuaScriptModule::create();*/
	//CEGUI::Direct3D9Renderer& myRenderer =
	//CEGUI::Direct3D9Renderer::create( this->renderer->GetDevice() );

	//CEGUI::System::create( myRenderer );
	//
	try
	{
		CEGUI::System::create( myRenderer);
	}
	catch(CEGUI::GenericException except){
		std::cout << except.getMessage();
	}
	
	

	 // create a script module.
	CEGUI::LuaScriptModule& scriptmod(CEGUI::LuaScriptModule::create());
	
	// Add tolua++ bindings to your script module
	lua_State * luaState = scriptmod.getLuaState();
	tolua_LuaInterface_open(luaState);

	// tell CEGUI to use this scripting module
    CEGUI:: System::getSingleton().setScriptingModule(&scriptmod);

	CEGUI::DefaultResourceProvider* rp = static_cast<CEGUI::DefaultResourceProvider*>(
	CEGUI::System::getSingleton().getResourceProvider());

	rp->setResourceGroupDirectory("schemes", "./Content/datafiles/schemes/");
	rp->setResourceGroupDirectory("imagesets", "./Content/datafiles/imagesets/");
	rp->setResourceGroupDirectory("fonts", "./Content/datafiles/fonts/");
	rp->setResourceGroupDirectory("layouts", "./Content/datafiles/layouts/");
	rp->setResourceGroupDirectory("looknfeels", "./Content/datafiles/looknfeel/");
	rp->setResourceGroupDirectory("lua_scripts", "./Content/datafiles/lua_scripts/");

	// This is only needed if you are using Xerces and need to
	// specify the schemas location
	rp->setResourceGroupDirectory("schemas", "../../XMLRefSchema/");

	// set the default resource groups to be used
	CEGUI::Imageset::setDefaultResourceGroup("imagesets");
	CEGUI::Font::setDefaultResourceGroup("fonts");
	CEGUI::Scheme::setDefaultResourceGroup("schemes");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
	CEGUI::WindowManager::setDefaultResourceGroup("layouts");
	CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");
	// Again, you only need to this one if you are using xerces and have
	// defined a group for schemas.
	
	// load in the scheme file, which auto-loads the TaharezLook imageset
	CEGUI::SchemeManager::getSingleton().create( "VanillaSkin.scheme" );
	CEGUI::SchemeManager::getSingleton().create( "TaharezLook.scheme" );

	// load in a font.  The first font loaded automatically becomes the default font.
	//if(! CEGUI::FontManager::getSingleton().isFontPresent( "Commonwealth-10" ) )
	CEGUI::FontManager::getSingleton().create( "DejaVuSans-10.font" );
	CEGUI::FontManager::getSingleton().create( "Batang-26.font" );

	CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
	CEGUI::Window* myRoot = CEGUI::WindowManager::getSingleton().loadWindowLayout( "test.layout" );
	
	CEGUI::System::getSingleton().setGUISheet( myRoot );

    CEGUI:: System::getSingleton().executeScriptFile("rtsgui.lua");

}

void GUI::Render()
{	
	SDL_Event Event;
	while(SDL_PollEvent(&Event)) 
	{
		OnEvent(&Event);
    }
	//this->renderer->GetDevice()->SetTextureStageState(0,D3DTSS_COLOROP,D3DTOP_SELECTARG1);
	//this->renderer->GetDevice()->SetTextureStageState(0,D3DTSS_COLORARG1,D3DTA_TEXTURE);
	//this->renderer->GetDevice()->SetTextureStageState(0,D3DTSS_ALPHAOP,D3DTOP_SELECTARG1);
	//this->renderer->GetDevice()->SetTextureStageState(0,D3DTSS_ALPHAARG1,D3DTA_TEXTURE);
	//this->renderer->GetDevice()->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	//this->renderer->GetDevice()->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
	//DIMOUSESTATE mousestate = Kernel::Instance()->GetInputManager()->GetMouseInput() ;
	//long mouseX = mousestate.lX;
	//long mouseY = mousestate.lY;
	//long mouseZ = mousestate.lZ;
	

	
	//this->renderer->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE,FALSE);
	/*this->renderer->GetDevice()->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
    this->renderer->GetDevice()->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);*/
	CEGUI::System::getSingleton().injectTimePulse(time(NULL)-this->lastUpdate);
	this->lastUpdate = time(NULL);
	CEGUI::System::getSingleton().renderGUI();
	this->renderer->GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, D3DZB_TRUE);
	this->renderer->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE,FALSE);

}

void GUI::OnEvent(SDL_Event* Event)
{
    CEvent::OnEvent(Event);
}

void GUI::OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle)
{
	CEGUI::System::getSingleton().injectMousePosition(mX, mY);
	//if(Left)
	//{
	//	CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::MouseButton::LeftButton);
	//}
	//else
	//{
	//	CEGUI::System::getSingleton().injectMouseButtonUp(CEGUI::MouseButton::LeftButton);
	//}
}

void GUI::OnLButtonDown(int mX, int mY)
{
	CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::MouseButton::LeftButton);
}

void GUI::OnLButtonUp(int mX, int mY)
{
	CEGUI::System::getSingleton().injectMouseButtonUp(CEGUI::MouseButton::LeftButton);
}

void GUI::OnKeyDown(Uint8 scancode, SDLKey sym, SDLMod mod, Uint16 unicode)
{
	//Get the keystates
	Uint8 *keystates = SDL_GetKeyState( NULL );
	if(keystates[SDLK_r])
	{
		Logger::Instance()->Log("reload", Info);
	}
	CEGUI::System::getSingleton().injectKeyDown(scancode);
}