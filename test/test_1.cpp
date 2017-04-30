#include <iostream>
#include <cppconfig.h>

int main(){
  auto conf = config::load("test_1.conf");
  std::string s = conf["abc"];
  std::cout << "abc: " << s << std::endl;
}
