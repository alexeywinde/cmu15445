//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// buffer_pool_manager_instance.cpp
//
// Identification: src/buffer/buffer_pool_manager.cpp
//
// Copyright (c) 2015-2021, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include "buffer/buffer_pool_manager_instance.h"

#include "common/exception.h"
#include "common/macros.h"

namespace bustub {

BufferPoolManagerInstance::BufferPoolManagerInstance(size_t pool_size, DiskManager *disk_manager, size_t replacer_k,
                                                     LogManager *log_manager)
    : pool_size_(pool_size), disk_manager_(disk_manager), log_manager_(log_manager) {
  // we allocate a consecutive memory space for the buffer pool
  pages_ = new Page[pool_size_];
  page_table_ = new ExtendibleHashTable<page_id_t, frame_id_t>(bucket_size_);
  replacer_ = new LRUKReplacer(pool_size, replacer_k);

  // Initially, every page is in the free list.
  for (size_t i = 0; i < pool_size_; ++i) {
    free_list_.emplace_back(static_cast<int>(i));
  }

  // TODO(students): remove this line after you have implemented the buffer pool manager
/*  throw NotImplementedException(
      "BufferPoolManager is not implemented yet. If you have finished implementing BPM, please remove the throw "
      "exception line in `buffer_pool_manager_instance.cpp`.");*/
}

BufferPoolManagerInstance::~BufferPoolManagerInstance() {
  delete[] pages_;
  delete page_table_;
  delete replacer_;
}

auto BufferPoolManagerInstance::NewPgImp(page_id_t *page_id) -> Page * {
       std::scoped_lock<std::mutex> lock(latch_);

	frame_id_t frame_id;

	if(!free_list_.empty()){
		frame_id=free_list_.back();
		free_list_.pop_back();
		*page_id=AllocatePage();
	}	
	else if(replacer_->Evict(&frame_id)){
		*page_id=AllocatePage();
	}
	else{
		return nullptr;
	}
	
	if(pages_[frame_id].is_dirty_)
              disk_manager_->WritePage(*page_id,pages_[frame_id].GetData());

	replacer_->SetEvictable(frame_id, false);
	pages_[frame_id].ResetMemory();
	pages_[frame_id].page_id_=*page_id;
	pages_[frame_id].pin_count_++;
	replacer_->RecordAccess(frame_id);
	page_table_->Insert(*page_id,frame_id);
	return &pages_[frame_id]; 
}

auto BufferPoolManagerInstance::FetchPgImp(page_id_t page_id) -> Page * {
	std::scoped_lock<std::mutex> lock(latch_);

	frame_id_t frame_id;
       	if(!page_table_->Find(page_id,frame_id)){
      		frame_id_t frame_id;

   	        if(!free_list_.empty()){
                	frame_id=free_list_.back();
               	        free_list_.pop_back();
               	        page_id=AllocatePage();
       		 }
       		 else if(replacer_->Evict(&frame_id)){
                	page_id=AllocatePage();
       		 }
		else{
		 	return nullptr;
		 }

       		 if(pages_[frame_id].is_dirty_)
             		 disk_manager_->WritePage(page_id,pages_[frame_id].GetData());

   		 replacer_->SetEvictable(frame_id, false);
       		 pages_[frame_id].ResetMemory();
		 pages_[frame_id].page_id_=page_id;
       		 pages_[frame_id].pin_count_++;
     		 replacer_->RecordAccess(frame_id);
       		 page_table_->Insert(page_id,frame_id);
		 return &pages_[frame_id];
	}
	return &pages_[page_id];
}
auto BufferPoolManagerInstance::UnpinPgImp(page_id_t page_id, bool is_dirty) -> bool { 
	std::scoped_lock<std::mutex> lock(latch_);

	frame_id_t frame_id;
	if(page_table_->Find(page_id,frame_id))
		return false;
	if(pages_[frame_id].pin_count_<=0)
		return false;

	if(!(--pages_[frame_id].pin_count_))
		replacer_->SetEvictable(frame_id,true);

	pages_[frame_id].is_dirty_=is_dirty;
	return true;
}

auto BufferPoolManagerInstance::FlushPgImp(page_id_t page_id) -> bool { 
	std::scoped_lock<std::mutex> lock(latch_);

	if(page_id==INVALID_PAGE_ID)
		return false;
	frame_id_t frame_id;
	if(page_table_->Find(page_id,frame_id)){
		disk_manager_->WritePage(page_id,pages_[frame_id].data_);
		return true;
	}
	else{
		return false;
	}
}

void BufferPoolManagerInstance::FlushAllPgsImp() {
	std::scoped_lock<std::mutex> lock(latch_);

	frame_id_t frame_id;
	for(size_t i=0;i<pool_size_;i++){
		page_table_->Find(pages_[i].page_id_,frame_id);
		disk_manager_->WritePage(pages_[i].page_id_,pages_[i].data_);
	}
	
}

auto BufferPoolManagerInstance::DeletePgImp(page_id_t page_id) -> bool { 
	std::scoped_lock<std::mutex> lock(latch_);

	if(pages_[page_id].pin_count_>0)
		return false;
	frame_id_t frame_id;
	if(!page_table_->Find(page_id,frame_id)){
		return true;	
	}
	page_table_->Remove(frame_id);
	free_list_.emplace_back(frame_id);
	return true;
}

auto BufferPoolManagerInstance::AllocatePage() -> page_id_t { return next_page_id_++; }

}  // namespace bustub
