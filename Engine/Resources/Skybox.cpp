#include "Skybox.h"
#include "../Core/Kernel.h"

Skybox::Skybox()
{

}

void Skybox::Update()
{
	EntityModel::Update();
	this->SetPosition( Kernel::Instance()->GetRenderer()->GetCamera()->GetPosition() );	
}

Skybox::~Skybox()
{

}