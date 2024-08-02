#include "ParserXML.h"
#include"../Game/Enemy/RoamingEnemy.h"
#include"../Game/Enemy/Boss.h"
#include"../Game/Enemy/RusherEnemy.h"
#include"../Game/Enemy/BomberEnemy.h"
#include"../Game/Enemy/ShootingEnemy.h"
#include"../Game/Enemy/testEnemy.h"


std::vector<std::string> ParserXML::explore_attribute(pt::ptree::const_iterator& value, std::vector<std::string> flags, std::vector<std::string> defaultValues)
{
    std::vector<std::string> res;
    if (flags.size() == defaultValues.size() && flags.size() != 0) {
        for (int i = 0; i < flags.size(); i++)
        {
                res.push_back(value->second.get<std::string>(flags[i], defaultValues[i]));
        }
    }
    return res;
}

ParserXML::ParserXML(std::string filePath_, AssetManager* a, bulletStorage* bs)
{
    filePath = filePath_;
    asset = a;
    bStorage = bs;

}

void ParserXML::coreFunction()
{
    pt::read_xml(filePath, tree);
    parse_tree(tree, "level");
    // On récupère les infos sur la difficulté
    int maxDifficulty = 1;
    for (Pattern pattern : level.getPatternStock()) {
        // Difficulté max du niveau
        if (pattern.getDifficulty() > maxDifficulty) {
            maxDifficulty = pattern.getDifficulty();
        }
        // ajouter dans la map des difficultés
        level.patternsPerDifficulty[pattern.getDifficulty()].push_back(pattern);

        // On ajoute au nombre de patterns
        level.totalPatternNumber += 1;
    }
    level.maxDifficultyPattern = maxDifficulty;
    std::cout << "Fini" << std::endl;
}

std::vector<std::string> ParserXML::searchLevelDatas(std::string levelName)
{
    pt::read_xml("res/level/"+levelName, tree);

    std::vector<std::string> flag = { "isInfinite","description","creator" };
    std::vector<std::string> defaultValue = { "0","Un niveau créé rien que pour vous :D","la PiouTeam" };

    pt::ptree::const_iterator it = tree.begin();
    return explore_attribute(it, flag, defaultValue);
}

void ParserXML::parse_tree(const pt::ptree& pt, std::string key)
{
    std::string nkey;
    if (!key.empty())
    {
        // The full-key/value pair for this node is
        // key / pt.data()
        // So do with it what you need
        nkey = key + ".";  // More work is involved if you use a different path separator
    }
    pt::ptree::const_iterator end = pt.end();
    pt::ptree::const_iterator it = pt.begin();
    size_t r = key.find_last_of('.');
    if (r != std::string::npos)
    {
        if (flag(key.substr(r + 1), it))
        {
            std::cout << key << std::endl;
        }
    }
    else {
        flag(key, it);
    }
    for (it; it != end; ++it)
    {
        parse_tree(it->second, nkey + it->first);
    }
}
void ParserXML::addEnemy(std::string enemyName,std::vector<std::string> values)
{
    int screenheight = Engine::SCREEN_HEIGHT;
    int screenwidth = Engine::SCREEN_WIDTH;
    //Ennemi
    enemy enemyToAdd;
    enemyToAdd.enemy = NULL;
    enemyToAdd.spawnerTiming = std::stof(values[1]);
    //Info sur l'ennemi direction/Position et spawn side
    enemyInfo infoE;
    // mustSetDirection
    infoE.mustSetDirection = std::stoi(values[15]);
    //Spawn side
    infoE.spawnSide = values[13];
    infoE.isAim= std::stoi(values[11]);
    infoE.scoreGived = std::stoi(values[12]);
    infoE.xpGived = std::stoi(values[14]);
    //Position (soit en absolu, soit en pourcentage selon l'écran
    size_t fade = values[3].find(';');
    std::string posString = values[3];
    if (posString.find('%')!=std::string::npos)
    {
        infoE.pos.x = screenwidth*(std::stof(posString.substr(0, fade-1)) / 100.f);
        infoE.pos.y = screenheight * (std::stof(posString.substr(fade+1, posString.size()-1)) / 100.f);
    }
    else
        infoE.pos = sf::Vector2f(std::stof(values[3].substr(0, fade)), std::stof(values[3].substr(fade+1)));

    // Direction
    //fade ??
    fade = values[4].find(';');
    sf::Vector2f direct = sf::Vector2f(std::stof(values[4].substr(0, fade)), std::stof(values[4].substr(fade + 1)));
    direct.x = direct.x / 100.f * screenwidth;
    direct.y = direct.y / 100.f * screenheight;
    // On vérifie que l'ennemi est un roaming ou un rusher ET que sa direction doit être saisie
    if ((enemyName == "roamingEnemy" || enemyName == "rusher") && infoE.mustSetDirection) {
        infoE.direction = utilities::dirAtoB(infoE.pos, direct);
    }


    Character CS;
    CS.setMaxHealth(std::stof(values[2]));
    CS.setMoveSpeed(std::stof(values[6]));
    //Damage quand on touche
    CS.setDamagePerBullet(std::stoi(values[7]));
    CS.setXp(std::stoi(values[14]));
    //VS Quand on touuche avec une balle
    WeaponStat W;

    // Direction des tirs
    if (enemyName == "shootingEnemy" && infoE.mustSetDirection) {
        W.dir = utilities::dirAtoB(infoE.pos, direct);
    }
    else if (enemyName == "bomber") {
        W.dir = sf::Vector2f(0, 1.f);
    }

    W.bulletDamage = std::stof(values[8]);
    W.bulletSpeed = std::stof(values[9]);
    W.attackSpeed = std::stof(values[10]);
    if (enemyName == "roamingEnemy") {
        RoamingEnemy* temp;
             temp = new RoamingEnemy(asset,CS,infoE);
             enemyToAdd.enemy = temp;
    }
    else if (enemyName == "shootingEnemy") {
        ShootingEnemy* temp = new ShootingEnemy(asset, CS, W, infoE);
        temp->setBulletStorage(bStorage);
        enemyToAdd.enemy = temp;
        
        
    }
    else if (enemyName == "bomber") {
        BomberEnemy* temp = new BomberEnemy(asset,CS,W,infoE);
        temp->setBulletStorage(bStorage);
        enemyToAdd.enemy = temp;
    }
    else if (enemyName == "pantin") {
        //testEnemy* temp = new testEnemy(asset,pos, (int)CS.getMaxHealth());
        //enemyToAdd.enemy = temp;
    }
    else if (enemyName == "rusher") {
        RusherEnemy* temp = new RusherEnemy(asset,CS,infoE);
        enemyToAdd.enemy = temp;
    }
    else {
        std::cout << "tentative d'invocation d'un ennemi qui n'existe pas";
    }
    if(enemyToAdd.enemy!=NULL)
        level.addEnemy(enemyToAdd);
}
bool ParserXML::flag(std::string name, pt::ptree::const_iterator& value)
{

    //Valeur prise en compte dans le parser
    std::vector<std::string> switchCase{ "level", "assets", "asset","pattern","wave","enemy" };
    std::vector<std::string> test;
    std::vector<std::string> flag;
    std::vector<std::string> defaultValue{ "-1", "0","-1" };
    auto it = std::find(switchCase.begin(), switchCase.end(), name);
    if (it != switchCase.end())
    {
        switch (it - switchCase.begin())
        {
        case 0://Level
            flag = { "isRandom","isInfinite","description","creator"};
            defaultValue = { "0","0","Un niveau créé rien que pour vous :D","la PiouTeam"};
            break;
        case 1://assets 

            break;
        case 2://asset
            flag = { "name", "filePath" };
            defaultValue = { "", "" };
            break;
        case 3://Pattern

            flag = { "duration", "order","name","random", "difficulty"};
            defaultValue = { "-1", "-1","undefined","0", "1"};
            break;
        case 4://Wave
            flag = { "duration" };
            defaultValue = { "-1" };
            break;
        case 5://Enemy
            flag = { "type","spawnTime","health", "pos","direction","moveTo","moveSpeed",
                "damage","damageonPerBullet","bulletSpeed","attackSpeed","autoAim","scoreGived","apparitionDirection","xpGived", "mustSetDirection"};
            defaultValue = { "undefined","0","20", "-1;-1","-2;-2", "-1;-1" , "2",
                "3","3","1","0.5","0","0","droite","3", "0"};
            break;
        }
        test = explore_attribute(value, flag, defaultValue);
        for (int i = 0; i < test.size(); i++)
        {
            std::cout << flag[i] << "  " << test[i] << std::endl;
        }
        //Deuxième partie, on remplit chaque truc
        switch (it - switchCase.begin())
        {
        case 0://Level
            level.setRandom(std::stoi(test[0]));
            level.isInfinite = std::stoi(test[1]);
            break;
        case 1://assetS 

            break;
        case 2://asset
        {
            std::string temp = test[0] + "-" + test[1];
            level.addAsset(temp);
            break;
        }
        case 3://Pattern
        {
            Pattern temp = Pattern(std::stof(test[0]), std::stoi(test[1]), test[2], std::stoi(test[3]));
            temp.setDifficulty(std::stoi(test[4]));
            level.addPattern(temp);
            break;
        }
        case 4://Wave
        {
            Wave temp = Wave(std::stof(test[0]));
            level.addWave(temp);
            break;
        }
        case 5://Enemy
        {
            addEnemy(test[0], test);
            break;
        }
        }
    }
    if (test.size() == 0)
        return false;
    return true;
}

