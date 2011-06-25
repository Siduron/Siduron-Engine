
wmgr = CEGUI.WindowManager:getSingleton();
mainGui = wmgr:getWindow("MainGUI");
buildScreen = wmgr:getWindow("BuildMenu");
buildScreen_Basic = wmgr:getWindow("BuildMenuBasic");
buildScreen_Advanced = wmgr:getWindow("BuildMenuAdvanced");

mainGui:setVisible(true);
buildScreen:setVisible(true);
buildScreen_Basic:setVisible(false);
buildScreen_Advanced:setVisible(false);

--Register events for layout
buildScreen:getChild("Build"):subscribeEvent("Clicked","BuildBasic");
buildScreen:getChild("Advanced"):subscribeEvent("Clicked","BuildAdvanced");
buildScreen_Basic:getChild("BuildBasic_Cancel"):subscribeEvent("Clicked","BuildBasic_Cancel");
buildScreen_Advanced:getChild("BuildAdvanced_Cancel"):subscribeEvent("Clicked","BuildAdvanced_Cancel");

function BuildBasic()
	buildScreen:setVisible(false);
	buildScreen_Basic:setVisible(true);
	local logger = Logger:Instance();
	logger:Progress();
end

function BuildBasic_Cancel()
	buildScreen:setVisible(true);
	buildScreen_Basic:setVisible(false);
end

function BuildAdvanced()
	buildScreen:setVisible(false);
	buildScreen_Advanced:setVisible(true);
end

function BuildAdvanced_Cancel()
	buildScreen:setVisible(true);
	buildScreen_Advanced:setVisible(false);
end