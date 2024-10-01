#include "Message.hpp"

#include <cstdlib>
#include <iostream>

int main() {
  Message say_hello("Hello, CMake World from C++!");

  std::cout << say_hello << std::endl;

  Message say_goodbye("Goodbye, CMake World from C++!");

  std::cout << say_goodbye << std::endl;

  return EXIT_SUCCESS;
}
