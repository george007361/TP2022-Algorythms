#include <errno.h>
#include <fstream>
#include <getopt.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

#define A 0
#define B 1000000000

void usage() {
  cout << "Usage: \"--help\" for help; \"--path <path>\" data file location, "
          "required; \"--lines <int>\" count of lines, required\n";
}

int main(int argc, char *argv[]) {
  string fname;

  if (argc < 3) {
    usage();

    return EXIT_FAILURE;
  }

  int option_symbol, lines = 0;

  struct option options[] = {{"help", no_argument, NULL, 'h'},
                             {"path", required_argument, NULL, 'p'},
                             {"lines", required_argument, NULL, 'l'},
                             {NULL, 0, NULL, 0}};

  while ((option_symbol = getopt_long_only(argc, argv, "", options, NULL)) !=
         -1) {
    switch (option_symbol) {

    default:
    case 'h': {
      usage();

      return EXIT_FAILURE;
    }
    case 'p': {
      fname = string(optarg);
      break;
    }
    case 'l': {
      lines = stoi(optarg);
      break;
    }
    }
  }

  ofstream dataFile;

  dataFile.open(fname, ios::in | ios::trunc);
  if (!dataFile.is_open()) {

    return EXIT_FAILURE;
  }

  srand(time(NULL));
  dataFile << lines << endl;
  for (size_t i = 0; i < lines; i++) {
    int a = A + rand() % (B - A + 1);
    int b = A + rand() % (B - A + 1);
    dataFile << std::min(a,b) << " " << std::max(a,b) << endl;
  }

  return EXIT_SUCCESS;
}