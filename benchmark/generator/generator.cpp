#include <errno.h>
#include <fstream>
#include <getopt.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

#define COUNT_OF_NUBMERS 30 //((sizeMB * 1024 * 1024) / sizeof(int))
#define A 0
#define B 1000

void usage() {
  cout << "Usage: \"--help\" for help; \"--path <path>\" data file location, "
          "required; \"--count <int>\" count of strings, required\n";
}

int main(int argc, char *argv[]) {
  string fname;
  int sizeMB = 0;

  if (argc < 3) {
    usage();

    return EXIT_FAILURE;
  }

  int option_symbol, count = 0;

  struct option options[] = {{"help", no_argument, NULL, 'h'},
                             {"path", required_argument, NULL, 'p'},
                             {"count", required_argument, NULL, 'c'},
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
    case 'c': {
      count = stoi(optarg);
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
  for (size_t i = 0; i < count; i++) {
    for (size_t j = 0; j < 1 + rand() % 10; j++)
    {
      dataFile << (char)(48 + rand() % (122 - 48));  //A + rand() % (B - A + 1) << " ";
    }
    dataFile << endl;
  }

  return EXIT_SUCCESS;
}