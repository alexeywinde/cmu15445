//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// extendible_hash_table.cpp
//
// Identification: src/container/hash/extendible_hash_table.cpp
//
// Copyright (c) 2022, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include <cassert>
#include <cstdlib>
#include <functional>
#include <list>
#include <utility>

#include "container/hash/extendible_hash_table.h"
#include "storage/page/page.h"

namespace bustub {

template <typename K, typename V>
ExtendibleHashTable<K, V>::ExtendibleHashTable(size_t bucket_size)
    : global_depth_(0), bucket_size_(bucket_size), num_buckets_(1) {
  auto ptr = std::make_shared<Bucket>(bucket_size, 0);
  dir_.emplace_back(ptr);
  dir_.reserve(1);
}

template <typename K, typename V>
auto ExtendibleHashTable<K, V>::IndexOf(const K &key) -> size_t {
  int mask = (1 << global_depth_) - 1;
  return std::hash<K>()(key) & mask;
}

template <typename K, typename V>
auto ExtendibleHashTable<K, V>::GetGlobalDepth() const -> int {
  std::scoped_lock<std::mutex> lock(latch_);
  return GetGlobalDepthInternal();
}

template <typename K, typename V>
auto ExtendibleHashTable<K, V>::GetGlobalDepthInternal() const -> int {
  return global_depth_;
}

template <typename K, typename V>
auto ExtendibleHashTable<K, V>::GetLocalDepth(int dir_index) const -> int {
  std::scoped_lock<std::mutex> lock(latch_);
  return GetLocalDepthInternal(dir_index);
}

template <typename K, typename V>
auto ExtendibleHashTable<K, V>::GetLocalDepthInternal(int dir_index) const -> int {
  return dir_[dir_index]->GetDepth();
}

template <typename K, typename V>
auto ExtendibleHashTable<K, V>::GetNumBuckets() const -> int {
  std::scoped_lock<std::mutex> lock(latch_);
  return GetNumBucketsInternal();
}

template <typename K, typename V>
auto ExtendibleHashTable<K, V>::GetNumBucketsInternal() const -> int {
  return num_buckets_;
}

//===--------------------------------------------------------------------===//
// ExtendibleHashTable
//===--------------------------------------------------------------------===//

template <typename K, typename V>
auto ExtendibleHashTable<K, V>::Find(const K &key, V &value) -> bool {
  std::scoped_lock<std::mutex> lock(latch_);
  return dir_[IndexOf(key)]->Find(key, value);
}

template <typename K, typename V>
auto ExtendibleHashTable<K, V>::Remove(const K &key) -> bool {
  std::scoped_lock<std::mutex> lock(latch_);
  return dir_[IndexOf(key)]->Remove(key);
}

template <typename K, typename V>
void ExtendibleHashTable<K, V>::Insert(const K &key, const V &value) {
  std::scoped_lock<std::mutex> lock(latch_);
  std::shared_ptr<Bucket> ptr = dir_[IndexOf(key)];
  if (ptr->Insert(key, value)) return;

  // std::shared_ptr<Bucket> ptr=dir_[IndexOf(key)];
  while (!ptr->Insert(key, value)) {
    if (global_depth_ == ptr->GetDepth()) {
      dir_.reserve(dir_.capacity() * 2);
      int i = 1 << global_depth_;  // index of the end,corner case:1<<0=1
      int up_step;
      while (i > 0) {
        i = i - 1;
        up_step = (1 << (global_depth_ - dir_[i]->GetDepth())) - 1;
        // corner case:1<<0-1=0
        i = i - up_step;
        for (int j = 0; j < 2 * (up_step + 1); j++) {
          dir_[2 * i + j] = dir_[i];
        }
      }
      ptr->IncrementDepth();
      ++global_depth_;
      dir_[IndexOf(key)] = std::make_shared<Bucket>(bucket_size_, ptr->GetDepth());
    } else {
      ptr->IncrementDepth();
      auto ptr_new = std::make_shared<Bucket>(bucket_size_, ptr->GetDepth());
      int mask = ~((1 << (global_depth_ - ptr->GetDepth())) - 1);
      // gloabl_depth_ - ptr->GetDepth()>0,corner case:~(1<<(2-1-1)-1)=0xffffffff
      for (int k = 0; k < mask; k++) {
        dir_[(IndexOf(key) & mask) + k] = ptr_new;
      }
    }

    for (auto iter = ptr->GetItems().begin(); iter != ptr->GetItems().end(); iter++) {
      if (reinterpret_cast<int *>(iter->first) == reinterpret_cast<int *>(IndexOf(key))) {
        dir_[IndexOf(key)]->GetItems().emplace_back(*iter);
        iter = ptr->GetItems().erase(iter);
      }
    }
  }
}

//===--------------------------------------------------------------------===//
// Bucket
//===--------------------------------------------------------------------===//
template <typename K, typename V>
ExtendibleHashTable<K, V>::Bucket::Bucket(size_t array_size, int depth) : size_(array_size), depth_(depth) {}

template <typename K, typename V>
auto ExtendibleHashTable<K, V>::Bucket::Find(const K &key, V &value) -> bool {
  typename std::list<std::pair<K, V>>::iterator iter;
  for (iter = GetItems().begin(); iter != GetItems().end(); iter++) {
    if (iter->first == key) break;
  }
  if (iter == list_.end()) return false;

  value = iter->second;
  return true;
}

template <typename K, typename V>
auto ExtendibleHashTable<K, V>::Bucket::Remove(const K &key) -> bool {
  typename std::list<std::pair<K, V>>::iterator iter;
  for (iter = GetItems().begin(); iter != GetItems().end(); iter++) {
    if (iter->first == key) break;
  }
  if (iter == list_.end()) return false;

  list_.erase(iter);
  size_--;
  return true;
}

template <typename K, typename V>
auto ExtendibleHashTable<K, V>::Bucket::Insert(const K &key, const V &value) -> bool {
  if (IsFull()) return false;

  typename std::list<std::pair<K, V>>::iterator iter;
  for (iter = GetItems().begin(); iter != GetItems().end(); iter++) {
    if (iter->first == key) break;
  }
  if (iter == list_.end()) {
    list_.emplace_back(std::make_pair(key, value));
  } else {
    iter->second = value;
  }
  size_++;
  return true;
}

template class ExtendibleHashTable<page_id_t, Page *>;
template class ExtendibleHashTable<Page *, std::list<Page *>::iterator>;
template class ExtendibleHashTable<int, int>;
// test purpose
template class ExtendibleHashTable<int, std::string>;
template class ExtendibleHashTable<int, std::list<int>::iterator>;

}  // namespace bustub
