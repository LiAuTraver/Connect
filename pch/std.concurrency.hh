// Precompiled header for concurrency in std.
#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <shared_mutex>
#include <atomic>

#if __cplusplus >= 202002L
#include <coroutine> // concurrency TS
#include <stop_token>
#include <barrier>
#include <latch>
#include <semaphore>
#endif // __cplusplus >= 202002L

#if __cplusplus >= 202603L
#include <hazard_pointer>
#include <rcu>
#endif // __cplusplus >= 202603L