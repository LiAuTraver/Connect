// Precompiled header for standard template library.
#pragma once

#include <array>
#include <deque>
#include <forward_list>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// concepts
#include <iterator>
#if __cplusplus >= 202002L
#include <concepts>
#include <span>
#endif // __cplusplus >= 202002L

#if __cplusplus >= 202203L
#include <flat_map>
#include <flat_set>
#include <mdspan>
#endif // __cplusplus >= 202203L