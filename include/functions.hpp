// Copyright 2021 by SovesT

#ifndef INCLUDE_FUNCTIONS_HPP_
#define INCLUDE_FUNCTIONS_HPP_
#include <string>

#include "header.hpp"
#include "picosha2.h"

void print(const std::string& hash, int random, time_t t0);
void init();
void sha_calculation(time_t t0);
#endif  // INCLUDE_FUNCTIONS_HPP_