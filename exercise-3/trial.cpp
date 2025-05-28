#include <optional>
#include <iostream>

int main()
{
  std::optional<int> x;
  int y = 2;
  x = 5;
  std::cout<<x.value()<<"\n";
}