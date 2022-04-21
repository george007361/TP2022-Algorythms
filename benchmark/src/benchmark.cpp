#include <array>
#include <errno.h>
#include <getopt.h>
#include <iostream>
#include <time.h>

#define MILLISEC_IN_SEC 1000
#define MILLISEC_IN_NANOSEC 1 / 1000000

using namespace std;

void usage() {
  cout << "Usage: \"--help\" for help; \"--count <int>\" count of test, "
          "required; \"--lines\" count of lines for each test, required\n";
}

string execCommand(const string cmd, int &out_exitStatus) {
  out_exitStatus = 0;
  auto pPipe = ::popen(cmd.c_str(), "r");
  if (pPipe == nullptr) {
    throw runtime_error("Cannot open pipe");
  }

  array<char, 256> buffer;

  std::string result;

  while (!feof(pPipe)) {
    auto bytes = fread(buffer.data(), 1, buffer.size(), pPipe);
    result.append(buffer.data(), bytes);
  }

  auto rc = ::pclose(pPipe);

  if (WIFEXITED(rc)) {
    out_exitStatus = WEXITSTATUS(rc);
  }

  return result;
}

int runTest(string pathToExe, double &timePassed) {
  int exitCode = 0;
  struct timespec startTime, endTime;
  clock_gettime(CLOCK_REALTIME, &startTime);
  cout << "Output:\n" << execCommand(pathToExe, exitCode); // << endl;
  clock_gettime(CLOCK_REALTIME, &endTime);
  if (exitCode == EXIT_FAILURE) {

    return EXIT_FAILURE;
  }
  timePassed = (MILLISEC_IN_SEC * (endTime.tv_sec - startTime.tv_sec) +
                (endTime.tv_nsec - startTime.tv_nsec) * MILLISEC_IN_NANOSEC);

  return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
  if (argc < 3) {
    usage();

    return EXIT_FAILURE;
  }

  int option_symbol, count = 0, lines = 0;

  struct option options[] = {{"help", no_argument, NULL, 'h'},
                             {"count", required_argument, NULL, 'c'},
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
    case 'c': {
      count = stoi(optarg);
      break;
    }
    case 'l': {
      lines = stoi(optarg);
      break;
    }
    }
  }

  int exitCode = 0;

  double medTime = 0;


cout << "Count of tests: " << count << "; Lines count: " << lines << endl;
  for (int i = 0; i < count; i++) {
    // generate
    execCommand(string("./generator/generator --path ./data/data.txt --lines " +
                       to_string(lines)),
                exitCode);
    if (exitCode == EXIT_FAILURE) {

      return EXIT_FAILURE;
    }

    double time;

    // run
    if (runTest("./task <./data/data.txt", time) ==
        EXIT_FAILURE) {
      return EXIT_FAILURE;
    }
    cout << "Test #" << i + 1 << ". Time passed:" << time
         << " millisec (10^-3 sec)" << endl;
    medTime += time;

  }

  // Crear dirs
  cout << execCommand("sh ./scripts/clear.sh", exitCode);
  if (exitCode == EXIT_FAILURE) {

    return EXIT_FAILURE;
  }

  cout << "->Median time: " << medTime / count << " ms" << endl;

  cout << "Done!" << endl;
  return EXIT_SUCCESS;
}
