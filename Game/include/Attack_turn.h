#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <algorithm>
#include <memory>
#include <iomanip>
#include <sstream>

// Voir si cela affiche, faire les dégats à chacun
// Afficher les pv actuels/pv totaux et le type de chacun avec leurs niveaux (si il y a)



class Attack {
public:
    Attack(const std::string& name, const std::string& type, int damage, int precision, int use)
        : name(name), type(type), damage(damage), precision(precision), use(use) {}

    const std::string& getName() const { return name; }
    const std::string& getType() const { return type; }
    int getDamage() const { return damage; }
    int getPrecision() const { return precision; }
    int getUse() const { return use; }
    void Used() { use -= 1; }

private:
    std::string name;
    std::string type;
    int damage;
    int precision;
    int use;
};

class Character {
public:
    Character(const std::string& name, int hp, int defense, int attack, int capa1, int capa2, int capa3, int capa4, const std::string& type)
        : name(name), hp(hp), defense(defense), attack(attack), capa1(capa1), capa2(capa2), capa3(capa3), capa4(capa4), type(type) {}

    const std::string& getName() const { return name; }
    const std::string& getType() const { return type; }
    int getHp() const { return hp; }
    int getDefense() const { return defense; }
    int getAttack() const { return attack; }
    bool IsAlive() const { return hp > 0; }

    void takeDamage(int damage_all) {
        hp -= damage_all;
        if (hp <= 0) {
            hp = 0;
            std::cout << name << " is dead!" << std::endl;
        }
    }
    /*
        void applyEffect() {

        }
    */


    int getCapa1() const { return capa1; }
    int getCapa2() const { return capa2; }
    int getCapa3() const { return capa3; }
    int getCapa4() const { return capa4; }


    int capa(int number) const {
        if (number >= 1 && number <= 4) {
            switch (number) {
            case 1:
                return capa1;
            case 2:
                return capa2;
            case 3:
                return capa3;
            case 4:
                return capa4;
            }
        }

        return 0;
    }

    void ShowMoves(const std::vector <std::shared_ptr<Attack>> attack, const Character& character) {
        capacitePrint(attack, character);
    }

    void capacitePrint(const std::vector <std::shared_ptr<Attack>> attack, const Character& character);

private:
    std::string name;
    std::string type;
    int hp;
    int defense;
    int attack;
    int capa1;
    int capa2;
    int capa3;
    int capa4;
};
sf::Font font;
std::vector<sf::Text> options;

// A mettre en graphique
void Character::capacitePrint(const std::vector <std::shared_ptr<Attack>> attack, const Character& character) {


    //std::shared_ptr<Attack> attack1 = attack[character.capa(1)];
    /*
    std::cout << "Name: " << attack1->getName() << attack[character.capa(1)]->getName()
        << ", Damage: " << attack.getDamage()
        << ", Type: " << attack.getType()
        << ", Remaining Uses: " << attack.getUse() << std::endl;
    */


    std::string strOptions[] = { "","","","" };
    for (int i = 0; i < 4; i++) {
        strOptions[i] = attack[character.capa(i)]->getName();
    }
    // Affiche juste le nom de la capacité, affiche le use, type
    for (int i = 0; i < 4; i++) {
        sf::Text text;
        text.setFont(font);
        text.setString(strOptions[i]);
        text.setCharacterSize(40);  // Définit la taille du caractère à 40
        text.setPosition(WINDOW_WIDTH / 4 - 50, 10 + i * 10); // Ajustez la position selon vos préférences
        options.push_back(text);
    }
}

//Lire le fichier characters.txt pour les ennemies
void ReadCharacterDataFromFile(std::vector<std::shared_ptr<Character>>& character_list) {
    std::ifstream file("characters.txt");

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open the character file." << std::endl;
        return;
    }
    /*
    std::string name, type;
    int hp, defense, attack, capa1, capa2, capa3, capa4;
    if (file >> std::quoted(name) >> hp >> comma >> defense >> comma >> attack >> comma >> capa1 >> comma >> capa2 >> comma >> capa3 >> comma >> capa4 >> comma >>std::quoted(type)) {
        Character newCharacter(name, hp, defense, attack, capa1, capa2, capa3, capa4, type);
        character = newCharacter;
    }

    file.close();
    */
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string name, type;
        int hp, defense, attack, capa1, capa2, capa3, capa4;
        char comma;

        if (iss >> std::quoted(name) >> comma >> defense >> comma >> attack >> comma >> capa1 >> comma >> capa2 >> comma >> capa3 >> comma >> capa4 >> comma >> std::quoted(type)) {
            auto character = std::make_shared<Character>(name, hp, defense, attack, capa1, capa2, capa3, capa4, type);
            character_list.push_back(character);
        }
        else {
            std::cerr << "Error reading line: " << line << std::endl;
        }
    }
}

//Lire les attaques dans le fichier attacks.txt et les met dans le vector
void ReadAttackDataFromFile(std::vector<std::shared_ptr<Attack>>& attack_list) {
    std::ifstream file("attacks.txt");

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open the attack file." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string name, type;
        int damage, precision, use;
        char comma;

        if (iss >> std::quoted(name) >> comma >> std::quoted(type) >> comma >> damage >> comma >> precision >> comma >> use) {
            auto attack = std::make_shared<Attack>(name, type, damage, precision, use);
            attack_list.push_back(attack);
        }
        else {
            std::cerr << "Error reading line: " << line << std::endl;
        }
    }

    file.close();
}
//Liste tous les types de Pokemon possibles
enum class PokemonType { Normal, Fire, Water, Grass, Electric, Ice, Fighting, Poison, Ground, Flying, Psychic, Bug, Rock, Ghost, Steel, Dark, Fairy, Dragon, Unknown };

float typeChart[19][19] = {
    //            Normal  Fire  Water  Grass  Electric  Ice  Fighting  Poison  Ground  Flying  Psychic  Bug  Rock  Ghost  Steel  Dark  Fairy  Dragon Unknown
    /* Normal */    {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.5, 1.0, 1.0, 1.0},
    /* Fire */      { 1.0,   0.5,  0.5,   2.0,   1.0,     2.0, 1.0,     1.0,   1.0,    1.0,   1.0,    2.0, 0.5,   1.0,  2.0,  1.0,  1.0,   0.5, 0.0 },
    /* Water */     { 1.0,   2.0,  0.5,   0.5,   1.0,     1.0, 1.0,     1.0,   2.0,    1.0,   1.0,    1.0, 2.0,   1.0,  1.0,  1.0,  1.0,   1.0, 0.0 },
    /* Grass */     { 1.0,   0.5,  2.0,   0.5,   1.0,     1.0, 1.0,     0.5,   2.0,    0.5,   1.0,    2.0, 0.5,   1.0,  0.5,  1.0,  1.0,   0.5, 0.0 },
    /* Electric */  { 1.0,  1.0,  2.0,   0.5,   0.5,     1.0, 1.0,     1.0,   0.0,    2.0,   1.0,    1.0, 1.0,   1.0,  1.0,  1.0,  1.0,   0.5, 0.0 },
    /* Ice */       { 1.0,   0.5,  0.5,   2.0,   1.0,     0.5, 1.0,     1.0,   2.0,    2.0,   1.0,    1.0, 2.0,   1.0,  0.5,  1.0,  1.0,   2.0, 0.0 },
    /* Fighting */  { 2.0,  1.0,  1.0,   1.0,   1.0,     2.0, 1.0,     0.5,   1.0,    0.5,   0.5,    0.5, 2.0,   0.0,  1.0,  2.0,  2.0,   0.5, 0.0 },
    /* Poison */    { 1.0,   1.0,  1.0,   2.0,   1.0,     1.0, 1.0,     0.5,   0.5,    1.0,   1.0,    1.0, 0.5,   0.5,  1.0,  1.0,  2.0,   1.0, 0.0 },
    /* Ground */    { 1.0,   2.0,  1.0,   0.5,   2.0,     1.0, 1.0,     2.0,   1.0,    0.0,   1.0,    0.5, 2.0,   1.0,  1.0,  1.0,  1.0,   1.0, 0.0 },
    /* Flying */    { 1.0,   1.0,  1.0,   2.0,   0.5,     2.0, 2.0,     1.0,   1.0,    1.0,   1.0,    0.5, 1.0,   1.0,  1.0,  1.0,  1.0,   1.0, 0.0 },
    /* Psychic */   { 1.0,   1.0,  1.0,   1.0,   1.0,     1.0, 2.0,     2.0,   1.0,    1.0,   0.5,    1.0, 1.0,   1.0,  1.0,  0.0,  1.0,   1.0, 0.0 },
    /* Bug */       { 1.0,   2.0,  1.0,   0.5,   1.0,     1.0, 0.5,     1.0,   0.5,    0.5,   2.0,    1.0, 1.0,   0.5,  1.0,  2.0,  0.5,   1.0, 0.0 },
    /* Rock */      { 1.0,   0.5,  2.0,   2.0,   1.0,     2.0, 0.5,     0.5,   2.0,    0.5,   1.0,    2.0, 1.0,   1.0,  2.0,  1.0,  1.0,   1.0, 0.0 },
    /* Ghost */     { 0.0,   1.0,  1.0,   1.0,   1.0,     1.0, 1.0,     1.0,   1.0,    1.0,   2.0,    1.0, 1.0,   1.0,  1.0,  1.0,  0.5,   1.0, 0.0 },
    /* Steel */     { 0.5,   2.0,  1.0,   0.5,   0.5,     2.0, 1.0,     1.0,   2.0,    0.5,   0.5,    0.5, 2.0,   1.0,  0.5,  1.0,  0.5,   0.5, 0.0 },
    /* Dark */      { 1.0,   1.0,  1.0,   1.0,   1.0,     1.0, 2.0,     1.0,   1.0,    1.0,   2.0,    1.0, 1.0,   1.0,  1.0,  1.0,  0.5,   1.0, 0.0 },
    /* Fairy */     { 1.0,   1.0,  1.0,   1.0,   1.0,     1.0, 0.5,     2.0,   1.0,    1.0,   1.0,    0.5, 1.0,   1.0,  2.0,  1.0,  2.0,   2.0, 0.0 },
    /* Dragon */    { 1.0,   1.0,  1.0,   1.0,   0.5,     2.0, 1.0,     1.0,   1.0,    1.0,   1.0,    1.0, 1.0,   1.0,  1.0,  1.0,  2.0,   2.0, 0.0 }
};

// Function to convert type name to an index
PokemonType TypeToIndex(const std::string& typeName) {
    if (typeName == "Water")            return PokemonType::Water;
    else if (typeName == "Fire")        return PokemonType::Fire;
    else if (typeName == "Grass")       return PokemonType::Grass;
    else if (typeName == "Electric")    return PokemonType::Electric;
    else if (typeName == "Normal")      return PokemonType::Normal;
    else if (typeName == "Ice")         return PokemonType::Ice;
    else if (typeName == "Fighting")    return PokemonType::Fighting;
    else if (typeName == "Poison")      return PokemonType::Poison;
    else if (typeName == "Flying")      return PokemonType::Flying;
    else if (typeName == "Psychic")     return PokemonType::Psychic;
    else if (typeName == "Bug")         return PokemonType::Bug;
    else if (typeName == "Rock")        return PokemonType::Rock;
    else if (typeName == "Ghost")       return PokemonType::Ghost;
    else if (typeName == "Steel")       return PokemonType::Steel;
    else if (typeName == "Dark")        return PokemonType::Dark;
    else if (typeName == "Fairy")       return PokemonType::Fairy;
    else if (typeName == "Dragon")      return PokemonType::Dragon;
    else {
        std::cerr << "Unknown type: " << typeName << std::endl;
        return PokemonType::Unknown; // Return an invalid type
    }
}

int CalculDamage(const Attack& attack, const Character& attacker, const Character& defenser) {
    int damage = 0;
    int damage_attack = attack.getDamage();
    int attacker_attack = attacker.getAttack();
    int defenser_defense = defenser.getDefense();
    const std::string& type_attack = attack.getType();
    const std::string& type_defenser = defenser.getType();

    PokemonType attack_type = TypeToIndex(type_attack);
    PokemonType defender_type = TypeToIndex(type_defenser);


    float damageMultiplier = typeChart[static_cast<int>(attack_type)][static_cast<int>(defender_type)];

    damage = (0.5 * attacker_attack * (damage_attack / defenser_defense) * damageMultiplier) + 1;
    return damage;
}

bool CalculPrecision(Attack& attack, bool player_turn) {
    int random = std::rand() % 10 + 1; // Random number between 1 and 10
    attack.Used();
    if (random <= attack.getPrecision()) {
        return true;
    }
    else {
        return false;
    }
}

int Attack_turn(const std::shared_ptr<Attack>& attack, const Character& Attacker, Character& Defenser, bool player_turn) {
    if (CalculPrecision(*attack, player_turn)) {
        int damage = CalculDamage(*attack, Attacker, Defenser);
        Defenser.takeDamage(damage);
        if (Defenser.IsAlive()) {
            std::cout << "L'attaque a blesse de " << damage << " hp" << std::endl;
        }
    }
    else {
        std::cout << "L'attaque a rate" << std::endl;
    }
    return 0;
}

/*
class StatusEffect {
public:
    StatusEffect(const std::string& name, int damage, int duration)
        : name(name), damage(damage), duration(duration) {}

    const std::string& getName() const { return name; }
    int getDamage() const { return damage; }
    int getDuration() const { return duration; }

    void reduceDuration() {
        if (duration > 0) {
            duration--;
        }
    }

    bool isActive() const {
        return duration > 0;
    }

private:
    std::string name;
    int damage;
    int duration;
};
*/

/*

int CalculDamage(const Attack& attack, const Character& attacker, const Character& defender) {
    int damage = 0;
    int damage_attack = attack.getDamage();
    int attacker_type_index = static_cast<int>(TypeToIndex(attacker.getType()));
    int defender_type_index = static_cast<int>(TypeToIndex(defender.getType()));

    // Check if the attacker and defender types are valid indices
    if (attacker_type_index >= 0 && defender_type_index >= 0) {
        float effectiveness = typeChart[attacker_type_index][defender_type_index];
        damage = static_cast<int>(damage_attack * effectiveness);
    }
    else {
        std::cerr << "Invalid attacker or defender type" << std::endl;
    }

    return damage;
};
*/

class AttackMenu {
private:
    sf::Font font;
    int selectedIndex = 0;
    std::vector<std::shared_ptr<Attack>> attackOptions;
    std::vector<std::shared_ptr<Attack>> attacks_player;
    std::vector<std::shared_ptr<Attack>> attacks_enemy;

public:
    AttackMenu() {
        if (!font.loadFromFile("assets/fonts/monogram.ttf")) {  // Chargez votre propre police ici
            std::cerr << "Erreur lors du chargement de la police!" << std::endl;
        }
    }

    int run(sf::RenderWindow& window) {
        ReadAttackDataFromFile(attackOptions);

        Character P1("Jaja", 500, 9999, 20, 2, 4, 5, 20, "Grass"); //Faire read le file pour mettre les données du player
        Character P2("L'ane Trotro", 100, 10, 50, 1, 2, 3, 4, "Water");//Faire read le file pour mettre les données d'un ennemi

        for (int i = 0; i < 4; i++) {
            attacks_player.push_back(attackOptions[P1.capa(i)]);
        }

        for (int i = 0; i < 4; i++) {
            attacks_enemy.push_back(attackOptions[P2.capa(i)]);
        }


        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Up) {
                        selectedIndex = (selectedIndex - 1 + attacks_player.size()) % attacks_player.size();
                    }
                    else if (event.key.code == sf::Keyboard::Down) {
                        selectedIndex = (selectedIndex + 1) % attacks_player.size();
                    }
                    else if (event.key.code == sf::Keyboard::Enter) {
                        return selectedIndex; //Faire que ça fait les dégats etc pour ensuite revenir ici et tout afficher
                    }
                }
            }

            window.clear();

            for (int i = 0; i < attacks_player.size(); i++) {
                sf::Text text;
                text.setFont(font);
                text.setString(attacks_player[i]->getName());
                text.setCharacterSize(30);
                text.setPosition(WINDOW_WIDTH / 2 - 50, 200 + i * 60);

                if (i == selectedIndex) {
                    text.setFillColor(sf::Color::Red);
                }
                else {
                    text.setFillColor(sf::Color::White);
                }

                window.draw(text);
            }

            window.display();
        }
        return -1;
    }
};