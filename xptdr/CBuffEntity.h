#pragma once
#include "effetspecial.h"
#include"CMob.h"

struct buff {
	effetspecial* effet;
	bool isActive;
};
/// <summary>
/// Classe qu'on fait hériter pour pouvoir appliquer des buffs sur une unité 
/// </summary>
class CBuffEntity
{
protected:
	std::vector<buff> buffs;
public:
	//Pour les balles, la références des balles ne doit pas être détruite
	bool isReference = false;
	virtual ~CBuffEntity() {
		if(!isReference)//Si ce n'est pas une réference on peut détruire les buffs associés, sinon il faudra bien faire attention à copier les buffs dans les nouvelles entités pour éviter les erreurs mémoires
		{
			deleteBuffs();
		}

	}

	/// <summary>
	/// Vector qu'on utilise pour les buffs globaux (le feu par exemple)
	/// </summary>
	static std::vector<effetspecial*> globalBuffs;
	void onHit(CMob& b);
	std::vector<buff>& getBuffs() { return buffs; }
	void updateBuff(float delta);
	/// <summary>
	/// Fonction qui ajoute un buff, on passe en paramètre si le buff est active ou non
	/// </summary>
	/// <param name="r"></param>
	/// <param name="isActive"></param>
	void addBuff(effetspecial* r, bool isActive);
	/// <summary>
	/// Cette méthode utilise les méthodes "globalMethod" des effets stockés dans globalsBuffs
	/// </summary>
	/// <param name="entityList"></param>
	static void useGlobal(std::vector<CMob*>& entityList);
	void renderBuffs(sf::RenderTarget& target);
	/// <summary>
	/// Regarde les types présents dans buffs et les comparent avec celui passé en paramètre
	/// </summary>
	/// <param name="typeEffet">type de l'effet,</param>
	/// <returns>true si existe dans buffs, false sinon</returns>
	bool checkForType(int typeEffet);
	/// <summary>
	/// Méthode qui delete tous les buffs de l'entité, check également si certains sont globaux
	/// </summary>
	void deleteBuffs();
};

