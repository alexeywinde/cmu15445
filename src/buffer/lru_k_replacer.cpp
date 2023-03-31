//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// lru_k_replacer.cpp
//
// Identification: src/buffer/lru_k_replacer.cpp
//
// Copyright (c) 2015-2022, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include "buffer/lru_k_replacer.h"

namespace bustub {

LRUKReplacer::LRUKReplacer(size_t num_frames, size_t k) : replacer_size_(num_frames), k_(k){
		max_size=num_frames;
}

auto LRUKReplacer::Evict(frame_id_t *frame_id) -> bool{
	 std::scoped_lock<std::mutex> lock(latch_);
        size_t min_ts=current_timestamp_+1;//earliest timestamp
	std::list<k_distance>::iterator max_k_iter;
	frame_id_t max_k_id;
        for(auto [k,v]:cache_le_k_){
                if(frame_evict_[k]==true&&hist_timestamp_[k].front()<min_ts){
                        min_ts=hist_timestamp_[k].front();
                        max_k_iter=v;
			max_k_id=k;
                }
        }

        if(min_ts<(current_timestamp_+1)){
                *frame_id=max_k_id;
                hist_timestamp_.erase(max_k_id);
                cache_frame_.erase(max_k_iter);
                cache_le_k_.erase(max_k_id);
               // replacer_size_--;
              //  return true;
        }else{
        	size_t max_k=0;
   	     for(auto [k,v]:cache_k_){
                if(frame_evict_[k]==true&&cache_k_[k]->second>max_k){
                        max_k=cache_k_[k]->second;
			max_k_id=k;
                        max_k_iter=v;
                }
       	     }

       	     if(max_k){
                *frame_id=max_k_id;
                hist_timestamp_.erase(max_k_id);
                cache_frame_.erase(max_k_iter);
                cache_k_.erase(max_k_id);
              //replacer_size_--;
               // return true;
             }else{
	     	return false;
	     }
	}
	return true;
}

void LRUKReplacer::RecordAccess(frame_id_t frame_id) {
	 std::scoped_lock<std::mutex> lock(latch_);
        current_timestamp_++;
	replacer_size_--;
        BUSTUB_ASSERT((long unsigned)frame_id>=replacer_size_,"The frame id is invlaid!\n");

        if(hist_timestamp_.find(frame_id)==hist_timestamp_.end()){
                std::list<timestamp> *ptr=new std::list<timestamp>;
                ptr->emplace_back(current_timestamp_);
                hist_timestamp_.emplace(frame_id,*ptr);
                cache_frame_.emplace_back(std::make_pair(frame_id,INT_MAX));
                cache_le_k_.emplace(frame_id,--(cache_frame_.end()));
        }
        else{
		auto iter=hist_timestamp_.find(frame_id);
                if(iter->second.size()==(k_-1)){
                        iter->second.emplace_back(current_timestamp_);
			auto iter_id=cache_le_k_.find(frame_id);
                        cache_k_.emplace(frame_id,iter_id->second);
			cache_le_k_.erase(iter_id);
                }
                else if(iter->second.size()==k_){
                        iter->second.emplace_back(current_timestamp_);
                        iter->second.pop_front();
                }
                else{
                        iter->second.emplace_back(current_timestamp_);
                }
        }

        for(auto [frame_id,k_iter]:cache_k_){
   k_iter->second=hist_timestamp_[frame_id].back()-hist_timestamp_[frame_id].front();
        }
}

void LRUKReplacer::SetEvictable(frame_id_t frame_id, bool set_evictable){
	 std::scoped_lock<std::mutex> lock(latch_);
        BUSTUB_ASSERT((unsigned long)frame_id>=replacer_size_,"The frame id is invlaid!\n");

        if(frame_evict_.at(frame_id)==true&&set_evictable==false)
                replacer_size_--;
        if(frame_evict_.at(frame_id)==false&&set_evictable==true)
                replacer_size_++;
}

void LRUKReplacer::Remove(frame_id_t frame_id){
	 std::scoped_lock<std::mutex> lock(latch_);

        auto iter=frame_evict_.find(frame_id);
    	if(iter==frame_evict_.end())
		return;

	BUSTUB_ASSERT(frame_evict_.at(frame_id)==false,"The frame is non-evictable!\n");

	auto iter_rm=cache_k_.find(frame_id);
	//std::unordered_map<frame_id_t,std::list<k_distance>::iterator> iter_rm=cache_k_.find(frame_id);
	if(iter_rm!=cache_k_.end()){
        	iter_rm=cache_k_.find(frame_id);
		cache_k_.erase(frame_id);
	}else{
		iter_rm=cache_le_k_.find(frame_id);
		cache_le_k_.erase(frame_id);
	}

        hist_timestamp_.erase(frame_id);
        cache_frame_.erase(iter_rm->second);
               // replacer_size_--;
 }

auto LRUKReplacer::Size() -> size_t{
	 std::scoped_lock<std::mutex> lock(latch_);

        return max_size-replacer_size_;
}

}  // namespace bustub
