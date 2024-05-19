#include "CMenuInterfaceState.h"

void CMenuInterfaceState::init(CAssetManager* asset_)
{
	asset = asset_;
	boutonRetour = CButton(asset);
	boutonRetour.setString("Retour");


}
