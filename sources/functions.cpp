// Copyright 2021 Nikita Pushkin

#include "functions.hpp"

#include <header.hpp>
std::mutex mx;
std::mutex mx1;

void init() {
  /// указатель на ядро
  // boost::shared_ptr<bl::core> core = bl::core::get();
  // auto sinkFile=bl::add_console_log(
  // bl::keywords::file_name = "file_%5N.log",
  // bl::keywords::rotation_size = 5 * 1024 * 1024,
  // bl::keywords::format = "[TimeStamp]: hash");
  /// register in the core.
  // typedef bl::sinks::synchronous_sink< sinks::text_file_backend > sink_t;
  // boost::shared_ptr< sink_t > sink(new sink_t(backend));
  // sink ->set_filter(logging::trivial::severity >= logging::trivial::info);
  // core->add_sink(sink);

  // auto sinkConsole = bl::add_console_log(
  // std::cout,
  // bl::keywords::format =
  // ( bl::keywords::format = "[TimeStamp]: hash));
  // sinkConsole->set_filter(bl::trivial::severity >= bl::trivial::trace);

  ///Обычно используемые атрибуты
  bl::add_common_attributes();
}

void print(const std::string& hash, int random, time_t t0) {
  time_t t1 = time(nullptr);
  double time = difftime(t1, t0);
  std::ofstream log_file("file_05.log", std::ios::app);
  json a;
  a["hash"] = hash;
  a["random"] = random;
  a["time_stamp"] = time;
  if (log_file.is_open()) {
    log_file << a << "\n";
  }
}

void sha_calculation(time_t t0) {
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist6(
      0, std::numeric_limits<int>::max());

  int random = dist6(rng);

  const std::vector<unsigned char> data_vector{
      static_cast<unsigned char>(random)};  // вектор

  std::string hash = picosha2::hash256_hex_string(data_vector);

  if (hash.substr(62, 2) == "f0") {
    mx.lock();
    print(hash, random, t0);
    hash.clear();
    mx.unlock();
  } else {
    mx1.lock();
    BOOST_LOG_TRIVIAL(trace) << random << "\twith hash:\t" << hash << "\n";
    hash.clear();
    mx1.unlock();
  }
  mx.unlock();
}
