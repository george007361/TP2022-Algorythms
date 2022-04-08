#include <errno.h>
#include <fstream>
#include <getopt.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

#define COUNT_OF_NUBMERS 100//((sizeMB * 1024 * 1024) / sizeof(int))
#define A 0
#define B 10000

void usage() {
  cout << "Usage: \"--help\" for help; \"--path <path>\" data file location, "
          "required; \"--size <int>\" file size MB, required\n";
}

int main(int argc, char *argv[]) {
  string fname;
  int sizeMB = 0;

  if (argc < 3) {
    usage();

    return EXIT_FAILURE;
  }

  int option_symbol, count = 0, size = 0;

  struct option options[] = {{"help", no_argument, NULL, 'h'},
                             {"path", required_argument, NULL, 'p'},
                             {"size", required_argument, NULL, 's'},
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
    case 's': {
      sizeMB = stoi(optarg);
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
  dataFile << COUNT_OF_NUBMERS << endl;
  for (size_t i = 0; i < COUNT_OF_NUBMERS; i++) {
    dataFile << A + rand() % (B - A + 1) << " ";
  }

  return EXIT_SUCCESS;
}