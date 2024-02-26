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
class CParserXML
{
private:
    CAssetManager* asset;
    /// <summary>
    /// Arbre qui représente le fichier XML
    /// </summary>
    pt::ptree tree;
    std::string filePath;
    CMob* target;
    bulletStorage* bStorage;
    /// <summary>
    /// Le parser est orienté pour le jeu parce que flemme, donc on ressort forcément un niveau 
    /// </summary>
    Level level;
public:
    CParserXML(std::string filePath_, CAssetManager* a, CMob* target_, bulletStorage* bs) {
        filePath = filePath_;
        asset = a;
        target = target_;
        bStorage = bs;
    }
    std::vector<std::string> explore_children(pt::ptree::const_iterator& value, std::vector<std::string> flags, std::vector<std::string> defaultValues);
    void coreFunction();
    bool flag(std::string name, pt::ptree::const_iterator& value);
    void parse_tree(const pt::ptree& pt, std::string key);
    Level getLevel() { return level; }

    void addEnemy(std::string enemyName, std::vector<std::string> values);
};