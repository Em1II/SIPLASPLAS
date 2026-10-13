#include <iostream>
// У нас есть здание, поделённое на 27 комнат (3 * 3 * 3).
// В каждой комнате лежит определённое количество бананов. Их нужно съесть. 
// Для этого мы отправляем туда агентов (миньонов).
// У каждого агента есть свои характеристики: Имя, скорость поедания и максимальное количество, которое они могут съесть.
// Считается, что если агент есть бананы на протяжении более 12-ти часов, то он больше не может выполнять задание и уходит.
// Если Агент съедает больше бананов, чем может, то мы его теряем.
// Требуется написать симуляцию объедания здания. По итогам нужно собрать массив результатов.
// В массиве или лежит сколько бананов агент съел (для награды) или сообщение о причине провала.
// Очев, что вмество сообщения писать -1 -2 и другие невозможные значения плохо.
struct Agent {
    const char* name;
    int speed;
    int capacity;
};
bool StringCompare(const char* a, const char* b){
  while (*a != '\0'){
    if (*a == *b){
      a++;
      b++;
    } else {
      return false;
    }
  }
  return *a == *b;
}
int main() {
    const int x = 3;
    const int y = 3;
    const int z = 3;
    int total = x * y * z;

 
    Agent agents[] = {
        {"Stuart", 4, 300},
        {"Phil", 3, 40},
        {"Kevin", 5, 234},
        {"Tim", 3, 33},
        {"Dave", 4, 456},
        {"Carl", 2, 656},
        {"Lance", 6, 15},
        {"Jerry", 3, 345},
        {"Landa", 7, 228},
        {"Joker", 6, 312},
        {"Cowboy", 12, 432},
        {"Pyle", 40, 6332},
        {"Animal Mother", 91, 22},
        {"Rafterman", 52, 300},
        {"Eightball", 4, 4},
        {"Snowball", 6, 3},
        {"Crazy Earl", 8, 1},
        {"Doc Jay", 3, 5},
        {"Payback", 5, 4},
        {"Touchdown", 7, 3},
        {"Hartman", 9, 5},
        {"Jules", 7, 4},
        {"Vincent", 6, 3},
        {"Mia", 5, 2},
        {"Butch", 8, 4},
        {"Marsellus", 4, 6},
        {"Vito", 3, 5},
        {"Honey Bunny", 6, 2},
        {"Wolf", 9, 4},
        {"Fabienne", 3, 2},
        {"Zed", 5, 3},
        {"Maynard", 4, 4},
        {"Jimmie", 2, 6}
    };
    int ***cube = new int**[z];
    for (int zi = 0; zi < z; ++zi) {
        cube[zi] = new int*[x];
        for (int xi = 0; xi < x; ++xi) {
            cube[zi][xi] = new int[y];
            for (int yi = 0; yi < y; ++yi) {
                std::cin >> cube[zi][xi][yi];
            }
        }
    }

    const void ***results = new const void**[total * 2];

    for (int zi = 0; zi < z; ++zi) {
        for (int xi = 0; xi < x; ++xi) {
            for (int yi = 0; yi < y; ++yi) {
                int idx = zi * x * y + xi * y + yi;
                Agent current = agents[idx];
                results[idx] = new const void*[2];
                if (current.capacity < cube[zi][xi][yi] && current.speed * 12 > current.capacity) {
                    results[idx][0] = new const char[]{"Overated"};
                    results[idx][1] = new const char[]{"const char*"};
                }
                else if (cube[zi][xi][yi] / current.speed > 12) {
                    results[idx][0] = new const char[]{"Cant Eat Anymore"};
                    results[idx][1] = new const char[]{"const char*"};
                }
                else {
                    results[idx][0] = new const int{cube[zi][xi][yi]};
                    results[idx][1] = new const char[] {"int"};
                }
            }
        }
    }
    //Вывод. Если закончил - пишем сколько съел. Нет - причину провала.
    for (int i = 0; i < total; ++i) {
        std::cout << agents[i].name << " - ";
        if (StringCompare(static_cast<const char*>(results[i][1]), "const char*")) {
            std::cout << static_cast<const char*>(results[i][0]);
        }
        else if (StringCompare(static_cast<const char*>(results[i][1]), "int")) {
            std::cout << *static_cast<const int*>(results[i][0]);
        }
        std::cout << "\n";
    }
    // Удаляемся
    for (int i = 0; i < total; ++i) {
        if (StringCompare(static_cast<const char*>(results[i][1]), "const char*")) {
            delete [] static_cast<const char*>(results[i][0]);
        }
        else if (StringCompare(static_cast<const char*>(results[i][1]), "int")) {
            delete static_cast<const int*>(results[i][0]);
        }
        delete [] static_cast<const char*>(results[i][1]);
        delete [] results[i];
    }
    delete[] results;

    for (int zi = 0; zi < z; ++zi) {
        for (int xi = 0; xi < x; ++xi) {
            delete[] cube[zi][xi];
        }
        delete[] cube[zi];
    }
    delete[] cube;
    return 0;
}