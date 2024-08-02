#include "MenuInterfaceState.h"

void CMenuInterfaceState::init(AssetManager* asset_)
{
	asset = asset_;
	boutonRetour = Button(asset);
	boutonRetour.setString("Retour");


}
