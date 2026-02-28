#include <iostream>
#include <string>
#include <cmath>

using namespace std;

struct Gladiators {
    string name;
    int strength = 0;
    int skill = 0;
    int age = 0;
    int life = 100;
};

void registerGladiators(Gladiators gladiators[], int gladiatorCount) {

    cin.ignore();

    getline(cin, gladiators[gladiatorCount].name);
    cin >> gladiators[gladiatorCount].strength;
    cin >> gladiators[gladiatorCount].skill;
    cin >> gladiators[gladiatorCount].age;

    system("cls");
}

int demage(Gladiators gladiator) {
    return gladiator.strength + (gladiator.skill * gladiator.skill);
}

int battle(Gladiators gladiator1, Gladiators gladiator2) {
    gladiator1.life = 100;
    gladiator2.life = 100;

    while (1) {
        gladiator2.life -= demage(gladiator1);
        if (gladiator2.life <= 0) return 1;
        gladiator1.life -= demage(gladiator2);
        if (gladiator1.life <= 0) return 2;
    }
}

int main()
{
    Gladiators gladiators[1000];
    int gladiator1, gladiator2;
    int choice;
	int gladiatorCount = 0;

    while (1) {

        cin >> choice;

        if(choice == 1) {
            registerGladiators(gladiators, gladiatorCount);
            gladiatorCount++;
        }

        else if (choice == 2) {

            if (gladiatorCount < 2) break;

            else {
                cin >> gladiator1 >> gladiator2;
                if (battle(gladiators[gladiator1], gladiators[gladiator2]) == 1)
                    cout << gladiators[gladiator1].name << " ganhou a batalha contra " << gladiators[gladiator2].name << endl;
                else
                    cout << gladiators[gladiator2].name << " ganhou a batalha contra " << gladiators[gladiator1].name << endl;
            }
        }

		else if (choice == 3) break;
    }

	return 0;
}