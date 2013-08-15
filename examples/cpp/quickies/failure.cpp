#include <fstream>

// Does not produce the output *I* expected.

int main(int argc, char ** argv)
{
  std::ifstream  IN ("input_file");
  std::ofstream  OUT ("output_file"); 
  
  OUT << IN;
}
