/*
A) Batalha de gladiadores
    Desenvolver um sistema de batalha entre gladiadores, que opera da seguinte maneira:
        1. O jogador deve cadastrar 5 gladiadores, fornecendo os seguintes atributos para cada um: Nome
        (String), Força (int), Habilidade (int) e Idade(int). Tanto a força quanto a habilidade variam de 0 a
        10.
        2. Após cadastrar os 5 gladiadores, o jogador pode escolher quais gladiadores irão se enfrentar.
        3. As batalhas ocorrem da seguinte forma:
            a. Cada gladiador inicia com 100 pontos de vida.
            b. O primeiro gladiador selecionado ataca primeiro.
            c. O dano causado durante um ataque é calculado como "DANO = força + (2^habilidade)".
            d. Após o ataque do primeiro gladiador, é a vez do próximo gladiador, e assim por diante,
            até que um dos dois seja derrotado (quando sua vida atinge 0).
        4. Para sair do jogo, o jogador deve digitar '-1'.
        5. Ao final do código, forneça comentários indicando a complexidade assintótica do seu código e a
        complexidade, no modelo RAM, das funções do seu código (Coloque como comentários no
        próprio código).
*/

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

/*
    - Inicialização do loop (i = 0) -> 1 atribuição = 1
    - Condição do loop (i < 5) -> (2 consultas + 1 comparação) * (5 + 1) = 18
    - Incremento do loop (i++) -> 5 incrementos * 3 (custo da tabela) = 15
    - Corpo do loop (executado 5 vezes):
        - Leituras/Escritas (getline, cin, ignore, system) -> 4 operações * 1 = 4
        - Acessos à memória (gladiators[i].atributo) -> 4 acessos * 1 = 4
        - Validação (while de forca/habilidade) -> Custo variável, mas tratado como constante
        - Subtotal do corpo por iteração: ~10 (incluindo acessos e chamadas)

    Custo RAM Total aproximado = 1 + 18 + 15 + (5 * 10) = 84

    Como o numero de gladiadores e fixo (5), o custo total e um valor
    inteiro constante, resultando em complexidade O(1).
*/

void registerGladiators(Gladiators gladiators[]) {
    for (int i = 0; i < 5; i++) {
        getline(cin, gladiators[i].name);

        cin >> gladiators[i].strength;
        while (gladiators[i].strength < 0 || gladiators[i].strength > 10) {
            cin >> gladiators[i].strength;
        }

        cin >> gladiators[i].skill;
        while (gladiators[i].skill < 0 || gladiators[i].skill > 10) {
            cin >> gladiators[i].skill;
        }

        cin >> gladiators[i].age;

        cin.ignore();
        system("cls");
    }
}

/*
    - 2 acessos à memória (gladiator.strength e gladiator.skill) -> 1 + 1 = 2
    - 2 Operações aritiméticas (+ e *) -> 1 + 1 = 2
    - 1 Atribuição (implícita) utilizando return -> 1
    Custo RAM Total = 5 = O(1) (constante, pois o cálculo do dano é independente do número de gladiadores ou rodadas).
*/
int demage(Gladiators gladiator) {
    return gladiator.strength + (gladiator.skill * gladiator.skill);
}

/*
    - 2 Atribuições iniciais (life = 100) -> 1 + 1 = 2
    - Controle do loop while (considerando N rodadas):
        - O teste da condição ocorre N vezes (no caso de while(1), custo de execução direta) -> N
    - Dentro do loop (executado N vezes):
        - 2 Chamadas da função demage -> 2 * (Custo de demage) = 2 * 5 = 10
        - 2 Operações de subtração e atribuição (-=) -> 2 * (1 + 1) = 4
        - 2 Comparações de seguranca (if <= 0) -> 1 + 1 = 2

    Custo RAM Total = 2 + N * (10 + 4 + 2) = 16N + 2 = O(N) (onde N é o número de rodadas até a vitória de um gladiador).
*/
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

/*
    - Chamada registerGladiators() -> Custo fixo (aprox. 84)
    - Leitura inicial (cin >> gladiator1) -> 1

    - Controle do loop while (considerando X batalhas):
        - Condição (gladiator1 != -1) -> (1 consulta + 1 comparação) * (X + 1) = 2X + 2
        - Leitura interna (cin >> gladiator2) -> 1 leitura * X = 1X
        - Chamada da função battle() -> (Custo de battle) * X = 16NX + 2X (onde N é o número médio de rodadas por batalha)
        - Saída de dados (cout) -> 1 escrita * X = 1X
        - Leitura final do loop (cin >> gladiator1) -> 1 leitura * X = 1X

    Custo RAM Total = 85 + 2(X + 1) + X + (16R + 2)X + 2X = 87 + (16R + 7)X,
    onde R é o número médio de rodadas por batalha e X é o número de batalhas.

    Complexidade Assintotica Total:
    - Seguindo a regra de manter o termo de maior importancia e descartar coeficientes:
    - O termo dominante e N (numero de batalhas).
    - Resultado: O(n).
*/
int main()
{
    Gladiators gladiators[5];
    int gladiator1, gladiator2;

    registerGladiators(gladiators);

    cin >> gladiator1;

    while (gladiator1 != -1)
    {
        cin >> gladiator2;

        if (battle(gladiators[gladiator1], gladiators[gladiator2]) == 1)
            cout << gladiators[gladiator1].name << " ganhou a batalha contra " << gladiators[gladiator2].name << endl;
        else
            cout << gladiators[gladiator2].name << " ganhou a batalha contra " << gladiators[gladiator1].name << endl;

        cin >> gladiator1;
    }

    return 0;
}