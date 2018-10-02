#ifndef PARALLEL_H
#define PARALLEL_H

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <thread>
#include <vector>

template <typename Iterator, typename Functor>
void for_each_par(Iterator begin, Iterator end, Functor func) {

  const auto thread_count = std::thread::hardware_concurrency();
  const auto total_elements = std::distance(begin, end);
  const unsigned long elements_per_thread =
      std::ceil(1.0 * total_elements / thread_count);

  // Partition data for each thread
  std::cerr << thread_count << " threads\n";
  std::cerr << total_elements << " size\n";
  std::cerr << elements_per_thread << " elements per thread\n";

  thread_local std::vector<std::thread> threads;
  for (unsigned int i = 0; i < thread_count; ++i) {

    // Initialise iterators
    thread_local auto front = begin;
    thread_local auto back =
        std::min(std::next(front, elements_per_thread), end);

    // Process each partition
    threads.push_back(std::thread(
        [&func](auto f, auto b) {
          std::cerr << "start\n";
          for_each(f, b, func);
          std::cerr << "done\n";
        },
        front, back));

    front = back;
    back = std::min(std::next(front, elements_per_thread), end);
  }

  for (auto &thr : threads)
    if (thr.joinable())
      thr.join();
}

#endif
