#pragma once
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include<boost/foreach.hpp>
#include <string>
#include <set>
#include <exception>
#include <iostream>
#include"Level.h"
#include "CJeu.h"
#include"bulletStorage.h"
namespace pt = boost::property_tree;
/// <summary>
/// Parser XML qui transforme un niveau (fichier xml ou .piou en niveau)
/// </summary>
class CParserXML
{
private:
    CAssetManager* asset;
    /// Arbre qui repr�sente le fichier XML
    pt::ptree tree;
    std::string filePath;
    bulletStorage* bStorage;
    /// Le parser est orient� pour le jeu parce que flemme, donc on ressort forc�ment un niveau 
    Level level;//M�thode priv�
    /// <summary>
    /// Explore les attributs du noeud en cours
    /// </summary>
    /// <param name="value"></param>
    /// <param name="flags">Diff�rents attributs pris par le noeud en cours</param>
    /// <param name="defaultValues">Valeur par d�faut pour �viter que �a plante, le pioumaker renvoie toujours une valeur de toute fa�on</param>
    /// <returns>Les valeurs associ� aux attributs</returns>
    std::vector<std::string> explore_attribute(pt::ptree::const_iterator& value, std::vector<std::string> flags, std::vector<std::string> defaultValues);
    /// <summary>
    /// M�thode qui prend le nom du noeud en cours et applique la m�thode explore_attribute avec les bons flags/valeurs par d�faut
    /// </summary>
    /// <param name="name"></param>
    /// <param name="value"></param>
    /// <returns></returns>
    bool flag(std::string name, pt::ptree::const_iterator& value);
    /// <summary>
    /// m�thode r�cursive qui prend l'arbre en cours le noeud) et la cl� qui correspond � l'endroit o� l'on est dans l'arbre /level/pattern/ennemy par exemple
    /// </summary>
    /// <param name="pt"></param>
    /// <param name="key"></param>
    void parse_tree(const pt::ptree& pt, std::string key);
    /// <summary>
    /// Ajoute un ennemi selon son nom et les valeurs trouv�es par explore_attribute
    /// </summary>
    /// <param name="enemyName"></param>
    /// <param name="values"></param>
    void addEnemy(std::string enemyName, std::vector<std::string> values);
public:
    /// <summary>
    /// Constructeur de confort, on passe le nom du niveau et tous les �lements associ�s n�cessaire � l'instantiation d'un niveau(asset pour les ennemis la target c'est obsolete dcp)
    /// </summary>
    /// <param name="filePath_"></param>
    /// <param name="a"></param>
    /// <param name="target_"></param>
    /// <param name="bs"></param>
    CParserXML(std::string filePath_, CAssetManager* a, bulletStorage* bs);
    /// <summary>
    /// M�thode que l'on appelle pour ex�cuter le parsing, on l'appelle apr�s qu'on ait utilis� 
    /// </summary>
    void coreFunction();

    /// <summary>
    /// Permet de chercher les donn�es suivantes du niveau souhait�e :
    /// - Infinit� du niveau
    /// - description
    /// - nom du cr�ateur
    /// </summary>
    /// <param name="levelName">: Le nom du niveau � analyser</param>
    /// <returns>Un vector de string avec :<ul><li> 0 : isInfinite;</li><li> 1 : description;</li><li> 2 : nom du cr�ateur</li></ul></returns>
    std::vector<std::string> searchLevelDatas(std::string levelName);
    Level getLevel() { return level; }

};