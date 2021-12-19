#include <header.hpp>

#include "functions.hpp"
#include "picosha2.h"

void signalHandler(int signum) {
  std::cout << "Interrupt signal (" << signum << ") received.\n";

  exit(signum);
}

int main(int argc, char* argv[]) {
  uint count_threads;
  if (argc > 1) {
    count_threads = *(argv[1]) - '0';
  } else {
    count_threads = std::thread::hardware_concurrency();
  }
  std::vector<std::thread> threads(count_threads);
  std::ofstream log_file("file_05.log");

  init();
  BOOST_LOG_TRIVIAL(trace) << "A trace severity message";
  BOOST_LOG_TRIVIAL(info) << "An informational severity message";
  std::mutex mx1;
  std::signal(SIGTERM, signalHandler);

  time_t t0 = time(nullptr);
  while (true) {
    // for (int h = 0; h <30000; ++h) {

    for (auto& i : threads) {
      mx1.lock();
      i = std::thread(sha_calculation, t0);
      mx1.unlock();
    }
    for (auto& thread : threads) {
      thread.join();
    }
  }
  return EXIT_SUCCESS;
}