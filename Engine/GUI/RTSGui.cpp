#include "RTSGui.h"


RTSGui::RTSGui(CEGUI::Window* newRoot)
{
	this->SetRoot(newRoot);
	this->mainGui = CEGUI::WindowManager::getSingleton().getWindow("MainGUI");
	this->buildScreen = CEGUI::WindowManager::getSingleton().getWindow("MainGUI/CommandMenu/BuildMenu");
	this->buildButton = this->buildScreen->getChild("MainGUI/CommandMenu/BuildMenu/BuildButton");
	this->buildScreen_Basic = CEGUI::WindowManager::getSingleton().getWindow("MainGUI/CommandMenu/BuildMenuBasic");

	this->mainGui->setVisible(true);
	this->buildScreen->setVisible(true);
	this->buildScreen_Basic->setVisible(false);

	this->RegisterEvents();

	int children = this->buildScreen_Basic->getChildCount();
	CEGUI::Window* child0 = this->buildScreen_Basic->getChildAtIdx(1);
	std::string childName = child0->getName().c_str();

	//CEGUI::System::getSingleton().executeScriptFile("../datafiles/lua_scripts/rtsgui.lua");
	//(*this->mainGui.*setVisible)(true);

}

double RTSGui::One( long inVal )
{
	return 0;
}

void RTSGui::SetRoot(CEGUI::Window* newRoot)
{
	this->root = newRoot;
}

bool RTSGui::EnableBuildBasic(const CEGUI::EventArgs& e)
{
	this->buildScreen->setVisible(false);
	this->buildScreen_Basic->setVisible(true);
	return true;
}

bool RTSGui::DisableBuildBasic(const CEGUI::EventArgs& e)
{
	this->buildScreen->setVisible(true);
	this->buildScreen_Basic->setVisible(false);
	return true;
}

bool RTSGui::BuildBasicKeyPress(const CEGUI::EventArgs& e)
{
	//Cast it to a key event
	const CEGUI::KeyEventArgs& key = static_cast<const CEGUI::KeyEventArgs&>(e);
	if(key.scancode == CEGUI::Key::Escape)
	{
		this->buildScreen->setVisible(true);
		this->buildScreen_Basic->setVisible(false);
	}
	return true;
}

void RTSGui::RegisterEvents()
{
	CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
	this->buildScreen->getChild("MainGUI/CommandMenu/BuildMenu/BuildButton")->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&RTSGui::EnableBuildBasic,this));
	this->buildScreen_Basic->getChild("MainGUI/CommandMenu/BuildMenuBasic/Cancel")->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&RTSGui::DisableBuildBasic,this));
	this->buildScreen_Basic->subscribeEvent(CEGUI::PushButton::EventKeyDown,CEGUI::Event::Subscriber(&RTSGui::BuildBasicKeyPress,this));
}

RTSGui::~RTSGui()
{

}