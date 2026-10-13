#include <iostream>

int StringLength(char* string) {
  int length{0};
  while (*string != '\0') {
    length++;
    string++;
  }
  return length;
}
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
struct Execute{
    const char *command;
    bool(*func)(int, int, char[5][10], char*);
    bool need_arguments;
};
bool Clear(int x, int y, char table[5][10], char* text) {
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 10; ++j) {
        table[i][j] = ' ';
    }
  }
  return true;
}
bool Put(int x, int y, char table[5][10], char* text) {
  if (0 <= y && y <= 4 && 0 <= x && x <= 9) {
    table[y][x] = *text;
    return true;
  }
  std::cout << "error" << std::endl;
  return false;
}

bool Text(int x, int y, char table[5][10], char* text) {
  if (0 <= y && y <= 4 && 0 <= x + StringLength(text) - 1 && x + StringLength(text) - 1 < 10) {
    while (*text != '\0') {
        Put(x, y, table, text);
        x++;
        text++;
    }
    return true;
  }
  std::cout << "error" << std::endl;
  return false;
}
bool Print(int x, int y, char table[5][10], char* text) {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 10; ++j) {
            std::cout << table[i][j];
        }
        std::cout << std::endl;
    }
    return 0;
}
void SpaceInit(char table[5][10]) {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 10; ++j) {
            table[i][j] = ' ';
        }
    }
}
int main() {
    char table[5][10];
    SpaceInit(table);
    int x{0};
    int y{0};
    char txt[256];
    char command[256];
    Execute operations[] = {
        {"clear", Clear, false},
        {"put", Put, true},
        {"text", Text, true},
        {"print", Print, false},
    };
    int amount_of_operations = sizeof(operations) / sizeof(operations[0]);
    
    while (std::cin >> command) {
        if (StringCompare(command, "quit")) {
            break;
        }
        for (int i = 0; i < amount_of_operations; ++i) {
            if (StringCompare(operations[i].command, command)) {
                if (operations[i].need_arguments) {
                    std::cin >> x;
                    std::cin >> y;
                    std:: cin >> txt;
                }
                operations[i].func(x, y, table, txt);
            }
        }
    }
    return 0;
}