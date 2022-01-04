#include "functions.hpp"

void signalHandler(int signum) {
  std::cout << "Interrupt signal (" << signum << ") received.\n";

  exit(signum);
}

int main(int argc, char* argv[]) {
  uint count_threads;
  if (argc > 1) {
    count_threads = *(argv[1]) - '0';
  } else {
    count_threads = thread::hardware_concurrency();
  }

  vector<thread> threads(count_threads);

  init();
  mutex mx1;
  std::signal(SIGTERM, signalHandler);

  time_t t0 = time(nullptr);
  for (;;) {
    for (auto& i : threads) {
      mx1.lock();
      i = thread(calc, t0);
      mx1.unlock();
    }
    for (auto& thread : threads) {
      thread.join();
    }
  }
  return EXIT_SUCCESS;
}