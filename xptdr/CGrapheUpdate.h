#pragma once
#include"CGraphe.h"
class CGrapheUpdate : public CGraphe
{
public:
	std::vector<std::string> ListeType;
	std::string Name;


	CGrapheUpdate& operator=(const CGrapheUpdate& GRAParam)
	{
		bGRAType = GRAParam.bGRAType;
		lisGRAListeSommet = GRAParam.lisGRAListeSommet;
		ListeType = GRAParam.ListeType;
		return *this;
	}
	CGrapheUpdate(const CGrapheUpdate& GRAParam)
	{
		this->operator=(GRAParam);
	}
	CGrapheUpdate() {
		bGRAType = Oriente;
	}
};

