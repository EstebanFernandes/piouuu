#include "File.h"


File::File(std::string filename) : fileName(filename)
{
	uicurrentLine = 0;
}
//basic separator is , ex : "number,right,left,up"
void File::addKeyWords(std::string kw)
{
	addKeyWords(kw, ',');
}
//surcharge où l'on choisit le separateur
void File::addKeyWords(std::string kw, char separator)
{
	int substr = 0;
	std::string temp = kw;
	while (substr!=std::string::npos)
	{
		 substr = kw.find(separator);
		keyWords.push_back(kw.substr(0, substr));
		kw = kw.substr(substr+1);
	}
	keyWords.push_back(kw);
}

void File::FileAnalysis()
{
	std::ifstream file(fileName);
	if (!file.is_open()) {
		std::cout << "Can't open file\n";
	}
	std::string ligne;
	while (std::getline(file, ligne)) {
		setCurrentLine(ligne);
			struct object F = Value();
			if (F.index != -1)
				valueList.push_back(F);
	}
}

object File::Value()
{
	for (int i = 0; i < keyWords.size(); i++)
	{
		size_t temp = currentLine.find(keyWords[i]);
		//si on est ici c'est que un mot clé est présent
			if(temp != std::string::npos)
			{
				object returnValue;
				returnValue.numeroligne = uicurrentLine;
				returnValue.valeur = currentLine.substr(currentLine.find('=') + 2);
				returnValue.index = i;
				return returnValue;
			}
	}
	object temp;
	temp.index = -1;
	return temp;
}
