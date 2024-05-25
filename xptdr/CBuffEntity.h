#pragma once
#include "effetspecial.h"
#include"CMob.h"

struct buff {
	effetspecial* effet;
	bool isActive;
};
/// <summary>
/// Classe qu'on fait h�riter pour pouvoir appliquer des buffs sur une unit� 
/// </summary>
class CBuffEntity
{
protected:
	std::vector<buff> buffs;
public:
	//Pour les balles, la r�f�rences des balles ne doit pas �tre d�truite
	bool isReference = false;
	virtual ~CBuffEntity() {
		if(!isReference)//Si ce n'est pas une r�ference on peut d�truire les buffs associ�s, sinon il faudra bien faire attention � copier les buffs dans les nouvelles entit�s pour �viter les erreurs m�moires
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
	/// Fonction qui ajoute un buff, on passe en param�tre si le buff est active ou non
	/// </summary>
	/// <param name="r"></param>
	/// <param name="isActive"></param>
	void addBuff(effetspecial* r, bool isActive);
	/// <summary>
	/// Cette m�thode utilise les m�thodes "globalMethod" des effets stock�s dans globalsBuffs
	/// </summary>
	/// <param name="entityList"></param>
	static void useGlobal(std::vector<CMob*>& entityList);
	void renderBuffs(sf::RenderTarget& target);
	/// <summary>
	/// Regarde les types pr�sents dans buffs et les comparent avec celui pass� en param�tre
	/// </summary>
	/// <param name="typeEffet">type de l'effet,</param>
	/// <returns>true si existe dans buffs, false sinon</returns>
	bool checkForType(int typeEffet);
	/// <summary>
	/// M�thode qui delete tous les buffs de l'entit�, check �galement si certains sont globaux
	/// </summary>
	void deleteBuffs();
};

