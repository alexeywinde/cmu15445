/**
 * index_iterator.cpp
 */
#include <cassert>

#include "storage/index/index_iterator.h"

namespace bustub {

/*
 * NOTE: you can change the destructor/constructor method here
 * set your own input parameters
 */
INDEX_TEMPLATE_ARGUMENTS
INDEXITERATOR_TYPE::IndexIterator() = default;

INDEX_TEMPLATE_ARGUMENTS
INDEXITERATOR_TYPE::IndexIterator(const IndexIterator& iter) = default{
	buffer_pool_manager_=iter.buffer_pool_manager_;
	KeyValue=iter.KeyValue;
	NextPageId=iter.NextPageId;
	CurrentIndex=iter.CurrentIndex;
	MaxIndex=iter.MaxIndex;
}

INDEX_TEMPLATE_ARGUMENTS
INDEXITERATOR_TYPE::~IndexIterator() = default;  // NOLINT

INDEX_TEMPLATE_ARGUMENTS
auto INDEXITERATOR_TYPE::IsEnd() -> bool {
	if(NextPageId==nullptr&&CurrentIndex==MaxIndex){ return true; }
	
	return false;	
	//throw std::runtime_error("unimplemented");
 }

INDEX_TEMPLATE_ARGUMENTS
auto INDEXITERATOR_TYPE::operator*() -> const MappingType & {
       	return *KeyValue;
	//throw std::runtime_error("unimplemented"); 
}

INDEX_TEMPLATE_ARGUMENTS
auto INDEXITERATOR_TYPE::operator++() -> INDEXITERATOR_TYPE & {
       //throw std::runtime_error("unimplemented");
       if(CurrentIndex<MaxIndex){
	       CurrentIndex++;
       		return *this;
       }
       Pages *next_page=buffer_pool_manager_->FetchPgimp(NextPageId);
       LeafPage next_leaf;
       char *leaf_data=next_page->GetData();
       memcpy(next_leaf,leaf_data,BUSTUB_PAGE_SIZE);
       //CurrentPageId=next_leaf.GetPageId();
       NextPageId=next_leaf.GetNextPageId();
       CurrentIndex=0;
       MaxIndex=leaf.GetMaxSize();
       buffer_pool_manager_->UnpinPgimp(NextPageId);
       return *this;
}

INDEX_TEMPLATE_ARGUMENTS
auto INDEXITERATOR_TYPE::operator!=(const IndexIterator &itr) const -> bool {
       //throw std::runtime_error("unimplemented"); 
	return KeyValue!=itr.KeyValue;
}

INDEX_TEMPLATE_ARGUMENTS
auto INDEXITERATOR_TYPE::operator==(const IndexIterator &itr) const -> bool {
       //throw std::runtime_error("unimplemented"); }
	return KeyValue==itr.KeyValue;
}

template class IndexIterator<GenericKey<4>, RID, GenericComparator<4>>;

template class IndexIterator<GenericKey<8>, RID, GenericComparator<8>>;

template class IndexIterator<GenericKey<16>, RID, GenericComparator<16>>;

template class IndexIterator<GenericKey<32>, RID, GenericComparator<32>>;

template class IndexIterator<GenericKey<64>, RID, GenericComparator<64>>;

}  // namespace bustub
