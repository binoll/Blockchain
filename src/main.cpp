#include <iostream>

#include "block/block.hpp"

int main() {
  Block first_block = create_first_block();

  std::cout << "First Block:" << std::endl;
  std::cout << "Index: " << first_block.getIndex() << std::endl;
  std::cout << "Hash: " << first_block.getHash() << std::endl;
  std::cout << "Data: " << first_block.getData() << std::endl;

  std::unordered_map<std::string, std::string> block2_data;
  block2_data["index"] = "1";
  block2_data["data"] = "Second block data";
  block2_data["prev_hash"] = first_block.getHash();

  Block second_block(block2_data);

  std::cout << "\nSecond Block:" << std::endl;
  std::cout << "Index: " << second_block.getIndex() << std::endl;
  std::cout << "Prev Hash: " << second_block.getPrevHash() << std::endl;
  std::cout << "Hash: " << second_block.getHash() << std::endl;
  std::cout << "Data: " << second_block.getData() << std::endl;

  return 0;
}