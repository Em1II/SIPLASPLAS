#include <iostream>
#include <iomanip>

int FrostyDays(const int *temperatures, int amount_of_days){
  int below_zero{0};
  for (int i = 0; i < amount_of_days; ++i){
    if (temperatures[i] < 0){
        below_zero++;
    }
  }
  return below_zero;
}
int *MinMax(const int *temperatures, int amount_of_days){
  int maximum{temperatures[0]};
  int minimum{temperatures[0]};
  int *answer = new int[2];
  for (int i = 0; i < amount_of_days; ++i){
    if (maximum < temperatures[i]){
        maximum = temperatures[i];
    }
    if (minimum > temperatures[i]){
        minimum = temperatures[i];
    }
  }
  answer[0] = minimum;
  answer[1] = maximum;
  return answer;
}

double ArithmeticMean(const int *temperatures, int amount_of_days){
  double sum{0};
  for (int i = 0; i < amount_of_days; ++i){
    sum += temperatures[i];
  }
  return sum / amount_of_days;
}
int main(){
  int amount_of_days;
  std::cin >> amount_of_days;
  int *temperatures = new int[amount_of_days];
  for (int i = 0; i < amount_of_days; ++i){
    std::cin >> temperatures[i];
  }
  
  
  std::cout << std::fixed << std::setprecision(1);
  std::cout << ArithmeticMean(temperatures, amount_of_days) << std::endl;
  int *minimum_and_maximum = MinMax(temperatures, amount_of_days);
  std::cout << minimum_and_maximum[0] << " "
            << minimum_and_maximum[1] << std::endl;
  std::cout << FrostyDays(temperatures, amount_of_days);
  delete [] temperatures;
  delete [] minimum_and_maximum;
  return 0;
}