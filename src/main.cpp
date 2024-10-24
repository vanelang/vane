#include <iostream>
#include "config.h"

static int usage(const char* arg0) {
  std::cerr 
    << "Usage: " << arg0 << " [OPTIONS] -o <file> <source>\n\n"
    << "Options: \n"
    << " -v           : Prints the Vane version number.\n"
    << " -o <file>    : Specify the output file.\n";

  return EXIT_FAILURE;
}

int main(int argc, char** argv) {
  std::string outfile;
  std::string sourcefile;

  if (argc < 2) {
    return usage(argv[0]);
  }

  for (int i = 1; i < argc; i++) {
    std::string arg = argv[i];

    if (arg == "-v") {
      std::cout << VANE_VERSION_STRING << std::endl;
    }

    else if (arg == "-o" && argc > (i + 1)) {
      i++;
      outfile = argv[i];
    }

    else if (sourcefile.empty()) {
      sourcefile = argv[i];
    }

    else {
      return usage(argv[0]);
    }
  }

  if (sourcefile.empty()) {
    return usage(argv[0]);
  }

  return EXIT_SUCCESS;
}