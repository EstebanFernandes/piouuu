#include "CBuffEntity.h"

std::vector<effetspecial*> CBuffEntity::globalBuffs;
void CBuffEntity::onHit(CMob& b)
{
	for (std::vector<buff>::iterator it = buffs.begin();
		it != buffs.end();)
	{
		if (CBuffEntity* buffMob = dynamic_cast<CBuffEntity*>(&b)) {
			// Si le cast réussi, vous pouvez utiliser les méthodes de ExtraFeatures
			it->effet->changeTarget(&b);
			buffMob->addBuff(it->effet, true);
				it = buffs.erase(it);

		}
	}
}

void CBuffEntity::updateBuff(float delta)
{
	for (int index = 0; index < buffs.size(); index++)
	{

		effetspecial* temp = buffs[index].effet;
		temp->update(delta);
		if (temp->needDelete)
		{
			if (temp->hasGlobal)
			{
				auto it = std::find(globalBuffs.begin(), globalBuffs.end(), temp);
				if (it != globalBuffs.end())
					globalBuffs.erase(it);
			}
			delete(temp);
			buffs.erase(buffs.begin() + index);
			if (index != 0)
				index--;
		}
	}
}

void CBuffEntity::addBuff(effetspecial* r, bool isActive) {
	buff temp;
	temp.effet = r;
	temp.isActive = isActive;
	if (isActive)
	{
		r->resetClock();
		r->action();
	if (r->hasGlobal)
		globalBuffs.push_back(r);
	}
	buffs.push_back(temp);
}

void CBuffEntity::useGlobal(std::vector<CMob*>& entityList)
{
	for (int index = 0; index < globalBuffs.size(); index++)
	{
		if(globalBuffs[index]->hasGlobal)
			globalBuffs[index]->globalMethod(entityList);
	}
}

void CBuffEntity::renderBuffs(sf::RenderTarget& target)
{
	for (int index = 0; index < buffs.size(); index++)
	{
		if(buffs[index].isActive)
			buffs[index].effet->renderBuff(target);
	}
}

bool CBuffEntity::checkForType(int typeEffet)
{
	for (int i = 0; i < buffs.size(); i++)
	{
		if (buffs[i].effet->type == typeEffet)
			return false;
	}
	return true;
}

void CBuffEntity::deleteBuffs()
{
	for (auto it = buffs.begin(); it != buffs.end();)
	{
		if (it->effet->hasGlobal)
		{
			auto itt = std::find(globalBuffs.begin(), globalBuffs.end(), it->effet);
			if (itt != globalBuffs.end())
				globalBuffs.erase(itt);
		}
		delete it->effet;
		it = buffs.erase(it);
	}
}
