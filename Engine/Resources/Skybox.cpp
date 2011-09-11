#include "Skybox.h"
#include "../Core/Kernel.h"

Skybox::Skybox()
{

}

void Skybox::Update()
{
	this->SetPosition( Kernel::Instance()->GetRenderer()->GetCamera()->GetPosition() );
	EntityModel::Update();
}

Skybox::~Skybox()
{

}