#include <iostream>

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
void Deposit(int &sum, int k = 0) {
  if (k <= 0) {
    std::cout << "error";
  } else {
    sum += k;
  }
}
void Withdraw(int &sum, int k = 0) {
  if (k <= 0 || sum < k) {
    std::cout << "error";
  } else {
    sum -= k;
  }
}
void Balance(int &sum, int k = 0) {
  std::cout << sum << std::endl;
}
void Reset(int &sum, int k = 0) {
  sum = 0;
}
void IntoTheDebt(int &sum, int k = 0) {
  sum = -k;
}

struct Execute {
  const char *command;
  void (*func)(int&, int);
  bool need_argument;
};

int main(){
  int sum{0};
  Execute table[] = {
    {"deposit", Deposit, true},
    {"withdraw", Withdraw, true},
    {"balance", Balance, false},
    {"reset", Reset, false},
    {"debt", IntoTheDebt, true},
  };
  int n = sizeof(table) / sizeof(table[0]);
  char command[256];
  int k{0};
  while (std::cin >> command) {
    if (StringCompare(command, "stop")){
        break;
    }
    for (int i = 0; i < n; ++i){
        if (StringCompare(table[i].command, command)){
            if (table[i].need_argument){
                std::cin >> k;
            }
            table[i].func(sum, k);
            break;
        }
    }
  }
  return 0;
}