#ifndef PARALLEL_H
#define PARALLEL_H

#include <algorithm>
#include <thread>
#include <vector>

namespace parallel {

const auto thread_count = std::thread::hardware_concurrency();

template <typename Iterator, typename Functor>
void for_each(Iterator begin, Iterator end, Functor func) {

  const auto total_elements = std::distance(begin, end);
  const unsigned long elements_per_thread =
      std::ceil(1.0 * total_elements / thread_count);

  // Partition data for each thread
  thread_local std::vector<std::thread> threads;
  for (unsigned int i = 0; i < thread_count; ++i) {

    // Initialise iterators
    thread_local auto front = begin;
    thread_local auto back =
        std::min(std::next(front, elements_per_thread), end);

    // Process each partition
    threads.push_back(std::thread(
        [&func](auto f, auto b) { std::for_each(f, b, func); }, front, back));

    front = back;
    back = std::min(std::next(front, elements_per_thread), end);
  }

  for (auto &thr : threads)
    if (thr.joinable())
      thr.join();
}
} // namespace parallel

#endif
