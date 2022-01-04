// Copyright 2021 Nikita Pushkin

#include <functions.hpp>

mutex mx;
mutex mx1;

void init() {
  BOOST_LOG_TRIVIAL(trace) << "A trace severity message";
  BOOST_LOG_TRIVIAL(info) << "An informational severity message";
  srand(time(nullptr));
  boost::log::add_common_attributes();
}

void print(const string& hash, int random, time_t t0) {
  time_t t1 = time(nullptr);
  double time = difftime(t1, t0);

  json a;
  a["hash"] = hash;
  a["random"] = random;
  a["time_stamp"] = time;

  std::ofstream log_file("../file_05.log");
  if (log_file.is_open()) {
    log_file << a << "\n";
  }
}

void calc(time_t t0) {
  int random = rand();

  string data{std::to_string(random)};
  string hash = picosha2::hash256_hex_string(data);

  if (hash.substr(60, 4) == "0000") {
    mx.lock();
    print(hash, random, t0);
    mx.unlock();
  }
  mx1.lock();
  BOOST_LOG_TRIVIAL(trace) << random << "\twith hash:\t" << hash << "\n";
  hash.clear();
  mx1.unlock();
}
