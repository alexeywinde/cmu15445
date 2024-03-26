#include <string>

#include "common/exception.h"
#include "common/logger.h"
#include "common/rid.h"
#include "storage/index/b_plus_tree.h"
#include "storage/page/header_page.h"

namespace bustub {
INDEX_TEMPLATE_ARGUMENTS
BPLUSTREE_TYPE::BPlusTree(std::string name, BufferPoolManager *buffer_pool_manager, const KeyComparator &comparator,
                          int leaf_max_size, int internal_max_size)
    : index_name_(std::move(name)),
      root_page_id_(INVALID_PAGE_ID),
      buffer_pool_manager_(buffer_pool_manager),
      comparator_(comparator),
      leaf_max_size_(leaf_max_size),
      internal_max_size_(internal_max_size) {}

/*
 * Helper function to decide whether current b+tree is empty
 */
 //测试 : vscode下git功能提交测试。
INDEX_TEMPLATE_ARGUMENTS
auto BPLUSTREE_TYPE::IsEmpty() const -> bool { return root_page_id_ == INVALID_PAGE_ID; }
/*****************************************************************************
 * SEARCH
 *****************************************************************************/
/*
 * Return the only value that associated with input key
 * This method is used for point query
 * @return : true means key exists
 */
INDEX_TEMPLATE_ARGUMENTS
auto BPLUSTREE_TYPE::GetValue(const KeyType &key, std::vector<ValueType> *result, Transaction *transaction) -> bool {
	if(IsEmpty())	return false;

	InternalPage *internal; LeafPage *leaf;
	page_id_t cur_id;
	Page *page = buffer_pool_manager_->FetchPgImp( root_page_id_ );

	IndexPageType page_type;
	memcpy(page_type, page->GetData(), sizeof(IndexPageType));
	int l,r,mid;//the key of array_[0] is invalid
	while( page_type == INTERNAL_PAGE ){
		page_internal = reinterpret_cast< InternalPage* >( page->GetData() );
		l = 1; r = page_internal->GetSize(); mid = 0;
		while(l <= r){
			mid = l + ( r + 1 - l ) / 2;//the root of (l+r)/2
			if(comparator(key , page_interna->KeyAt(mid)) < 0){
				r = mid - 1;
			}else if(comparator(page_internal->KeyAt(mid) , key) < 0){
				l = mid + 1;
			}else{
				r = mid;
				break;
			}
		}//r
  		curr_id = page->GetPageId();
		buffer_pool_manager_->UnpinPgImp( curr_id, false );
		page = bufffer_pool_manager_->FetchPgImp( page_internal->ValueAt( r ) );
		memcpy(page_type, page->GetData(), sizeof( IndexPageType ));
	}	
	curr_id = page->GetPageId();
	page_leaf = reinterpret_cast< LeafPage* >( page->GetData() );
	l = 0; l = page_leaf->GetSize() - 1; mid = 0;
	while( l <= r){
		mid = l + ( r + 1 - l ) / 2;
		if(comparator( key , page_leaf->KeyAt(mid) ) < 0){
			r = mid - 1;
		}else if(comparator( page_leaf->KeyAt(mid) , key ) < 0){
			l = mid + 1;
		}else{
			break;
		}
	}
	if(l > r){ return false; }
	(*result).emplace_back(page_leaf->ValueAt( mid ));
	buffer_pool_manager_->UnpinPgImp(curr_id , false);
	return true;
}

/*****************************************************************************
 * INSERTION
 *****************************************************************************/
/*
 * Insert constant key & value pair into b+ tree
 * if current tree is empty, start new tree, update root page id and insert
 * entry, otherwise insert into leaf page.
 * @return: since we only support unique key, if user try to insert duplicate
 * keys return false, otherwise return true.
 */
INDEX_TEMPLATE_ARGUMENTS
auto BPLUSTREE_TYPE::Insert(const KeyType &key, const ValueType &value, Transaction *transaction) -> bool {
	if(root_page_id_==INVALID_PAGE_ID){
		Page *page_=buffer_pool_manager_->NewPgImp(&root_Page_id_);
		LeafPage *page_leaf=reinterpret_cast<LeafPage*>(page_->GetData());
		page_leaf->Init(root_page_id_,INVALID_PAGE_ID,leaf_max_size_);
		page_leaf->SetNextPageId(INVALID_PAGE_ID);
		MappingType *array=page_leaf->GetArray();
		page_leaf->array[0]=std::make_pair(key,value);
		page_leaf->IncreaseSize(1);
		buffer_pool_manager_->UnpinPgImp(root_page_id_,true);
		return true;
	}
	std::vector<int>index_pos;
	Page *page=buffer_pool_manager_->FetchPgImp(root_page_id_);
	InternalPage *page_internal ; LeafPage *page_leaf;
	Mapping *array,*array_2;//=page_leaf->GetArray();
        IndexPageType page_type;
	memcpy(page_type,page->GetData(),sizeof(IndexPageType));
     	int l,r,mid;//array_[0].first is invalid
        while(page_type==INTERNAL_PAGE){
		page_internal=reinterpret_cast<InternalPage*>(page->GetData());
                l=1; r=page_internal->GetSize(); mid=0;
                while(l<=r){
                	mid=l+(r+1-l)/2;//the root of (l+r)/2
                        if(comparator(key , page_internal->KeyAt(mid)) < 0){//key<KeyAt(mid)
                        	r=mid-1;
                        }else if(comparator(page_internal->KeyAt(mid) , key) <0){
                 		l=mid+1;
                        }else{
				r=mid;
                        	break;
              		}
                }
		index_pos.emplace_back(r);
		page=bufffer_pool_manager_->FetchPgImp(page_internal->ValueAt(r));
       		memcpy(page_type,page->GetData(),sizeof(IndexPageType));
       	}
	page_leaf=reinterpret_cast<LeafPage*>(page->GetData());
        l=0; l=page_leaf->GetSize()-1; mid=0;
        while(l<=r){
               	mid=l+(r+1-l)/2;
               	if(comparator(key , page_leaf->KeyAt(mid))<0){
                       	r=mid-1;
               	}else if(comparator(page_leaf->KeyAt(mid) , key)<0){
                       	l=mid+1;
		}else{
			break;
		}
	}//l;
	if(l<=r){ return false; }//duplicate

	array=page_leaf->GetArray();
	for(int k=page_leaf.GetSize()-1; k>=l; k--){
		array[k+1]=array[k];
	}
	array[l]=std::make_pair(key,value);
	page_leaf->IncreaseSize(1);
	page_id_t curr_id,parent_id;
	if(page_leaf->GetSize()<page_leaf->GetMaxSize()){
		curr_id=page_leaf->GetPageId() ; parent_id=page_leaf->GetParentId();
		while(parent_id!=INVALID_PAGE_ID){
			buffer_pool_manager_->unpinPgImp(curr_id,true);
			curr_id=parent_id;
			page=buffer_pool_manager_->FetchPgImp(curr_id);
			page_internal=reinterpret_cast<InternalPage*>(page->GetData());
			parent_id=page_internal->GetParentId();
		}
		return true;
	}
//--------------------------overflow--------------------------------------------------------------------
	LeafPage *leaf_split;
	Page *page_split;
	page_id_t old_split_id;
	curr_id=page_leaf->GetPageId() ; parent_id=page_leaf->GetParentId();
		
	page_split=buffer_pool_manager_->NewPgImp(&old_split_id);
	leaf_split=reinterpret_cast<LeafPage*>(page_split->GetData());
        leaf_split->Init(old_split_id,parent_id,leaf_max_size_);

        leaf_split->SetNextPageId(page_leaf->GetNextPageId);
	page_leaf->SetNextPageId(old_split_id);

	KeyType key_overflow=page_leaf->KeyAt((leaf_max_size_)/2);//overflow
	memcpy(leaf_split->GetArray(),page_leaf->GetArray()+(leaf_max_size_)/2,sizeof(MappingType)*((leaf_max_size_+1)/2));
	page_leaf->SetSize((leaf_max_size_)/2);
	leaf_split->SetSize((leaf_max_size_+1)/2);
		//Note:memset(page_leaf->GetArray()+(leaf_max_size_)/2,0,sizeof(MappingType)*(leaf_max_size_+1)/2);
		
	buffer_pool_manager_->UnpinPgImp(old_splid_id,true);
	buffer_pool_manager_->UnpinPgImp(curr_id,true);

	int pos;
	curr_id=page_leaf->GetPageId(); parent_id=page_internal->GetParentPageId();
	//std::pair(key_flow,_old_split_id);
	while(1){//parent_id!=INVALID_PAGE_ID){
		pos=index_pos.back();
		index_pos.pop_back();
		page=buffer_pool_manager_->FetchPgImp(parent_id);
		page_internal=reinterpret_cast<InternalPage*>(page->GetData());
		curr_id=page_internal->GetPageId(); parent_id=page_internal->GetParentPageId();

		if((int k=page_internal->GetSize())  <  internal_max_size_){
			array=Page_internal->GetArray();
                	for(k;k>pos;k--){
                        	array[k+1]=array[k];
                	}
                	array[pos+1]=std::make_pair(key_overflow,old_split_id);
                        page_internal->IncreaseSize(1);

			while(parent_id!=INVALID_PAGE_ID){
					buffer_pool_manager_->UnpinPgImp(curr_id,true);
					curr_id=parent_id;
					page=buffer_pool_manager_->FetchPgImp(curr_id);
					page_internal=reinterpret_cast<InternalPage*>(page->GetData());
	                		parent_id=page_internal->GetParentId();
			}
			buffer_pool_manager_->UnpinPgImp(curr_id,true);
			//break;
			return true;
		}
		
		InternalPage *internal_split;
		page_id_t new_split_id;
		page_split=buffer_pool_manager_->NewPgImp(&new_split_id);
		internal_split=reinterpret_cast<InternalPage*>(page_split->GetData());
		
		internal_split->Init(new_split_id,parent_id,internal_max_size_);
		
		//key_overflow=page_internal->KeyAt((internal_max_size_+1)/2+1);
		
		array=page_intrenal->GetArray(); array_2=internal_split->GetArray();
		
		memcpy(array_2 , array[(internal_max_size_/2+1)],sizeof(MappingType)*((internal_max_size_+1)/2));
		//key_overflow=array_2[0].first;
		page_internal->SetSize(internal_max_size_/2);
		internal_split->SetSize((internal_max_size_+1)/2);

			
		/*l=1;r=internal_insert->GetSize();
		while(l<=r){
                	mid=l+(r+1-l)/2;
                	if(comparator(key , page_leaf->KeyAt(mid))<0){
                        	r=mid-1;
                	}else if(comparator(page_leaf->KeyAt(mid) , key)<0){
                        	l=mid+1;
                	}else{
                        	break;
                	}
        	}//l;
		array=internal_insert->GetArray();
		for(int k=internal_insert->GetSize();k>=l;k--){
			array[k+1]=array[k];
		}
		array[l]=std::make_pair(Key_overflow,old_split_id);*/

		if(pos<=(internal_max_size_/2+1)){ InsertIntoInternal_pos(page_internal,key_flow,old_split_id);}
		else{ InsertIntoInternal_pos(internal_split,key_flow,old_split_id);}

		key_overflow=array_2[0].first;
		//parent_id=page_internal->GetParentPageId();
                buffer_pool_manager_->UnpinPgImp(curr_id,true);
                buffer_pool_manager_->UnpinPgImp(new_split_id,true);
                old_split_id=new_split_id;

		if(curr_id=root_page_id_){
			//old_split_id=new_split_id;
                        page_split=buffer_pool_manager_->NewPgImp(&new_split_id);
                	internal_split=reinterpret_cast<InternalPage*>(page_split->GetData());
			array=internal_split->GetArray();
			array[0].second=curr_id;
			array[1]=std::make_pair(key_overflow,old_split_id);
			buffer_pool_manager_->UnpinPgImp(new_split_id,true);

                }
	return true;
}

/*****************************************************************************
 * REMOVE
 *****************************************************************************/
/*
 * Delete key & value pair associated with input key
 * If current tree is empty, return immdiately.
 * If not, User needs to first find the right leaf page as deletion target, then
 * delete entry from leaf page. Remember to deal with redistribute or merge if
 * necessary.
 */
INDEX_TEMPLATE_ARGUMENTS
void BPLUSTREE_TYPE::Remove(const KeyType &key, Transaction *transaction) {
	if(root_page_id_==INVALID_PAGE_ID){ return; }
	Page *page;
	InternalPage *page_internal;
	LeafPage *page_leaf;
	page=buffer_pool_manager_->FetchPgImp(root_page_id_);
	IndexPageType page_type;
	memcpy(page_type,page->GetData());
	int l,r,mid;
	std::vector<int>index_pos;
	while(page_type==INTERNAL_PAGE){
		page_internal=reinterpret_cast<InternalPage*>(page->GetData());
		l=1; r=page_internal->GetSize()-1; mid=0;
                while(l<=r){
                        mid=l+(r+1-l)/2;//the root of (l+r)/2
                        if(comparator(key , page_internal->KeyAt(mid)) < 0){//key<KeyAt(mid)
                                r=mid-1;
                        }else if(comparator(page_internal->KeyAt(mid) , key) <0){
                                l=mid+1;
                        }else{
                                r=mid;
                                break;
                        }
                }
                index_pos.emplace_back(r);
                page=bufffer_pool_manager_->FetchPgImp(page_internal->ValueAt(r));
                memcpy(page_type,page->GetData(),sizeof(IndexPageType));
	}
	page_leaf=reinterpret_cast<LeafPage*>(page->GetData());
	l=0; l=page_leaf->GetSize()-1; mid=0;
        while(l<=r){
		mid=l+(r+1-l)/2;
                if(comparator(key , page_leaf->KeyAt(mid))<0){
                	r=mid-1;
                }else if(comparator(page_leaf->KeyAt(mid) , key)<0){
                        l=mid+1;
                }else{
                                //r=mid;
                        break;
		}
	}
	if(l<=r){
		MappingType *array=page_leaf->GetArray();
		for(int k=mid;k<page_leaf->GetSize()-1;k++){
			array[k]=array[k+1];
		}
		page_leaf->IncreaseSize(-1);
	}
	if(page_leaf->GetSize()>=((leaf_max_size_+0)/2)) { return; }
	int pos=index_pos.back();
	index_pos.pop_back();
		//1
	Page *page_bro,*page_par;
	InternalPage *internal_par,*internal_bro;
	LeafPage *leaf_bro;
	MappingType *array_bro,*array_curr;
	page_id_t curr_id=page_leaf->GetPageId() , par_id=page_leaf->GetParentId() , bro_id;
	//if(0<pos)
	page_par=buffer_pool_manager_->FetchPgImp(par_id); internal_par=page_par->GetData();
	if(0<pos){	
		page_bro=buffer_pool_manager_->FetchPgImp(internal_par->ValueAt(pos-1)); leaf_bro=page_bro->GetData();
	       	//bro_page_id=leaf_bro->GetPageId();
		if(leaf_bro->GetSize()>leaf_bro->GetMinSize()){
			array_curr=page_leaf->GetArray();array_bro=leaf_bro->GetArray();
			for(int k=page_leaf->GetSize()-1;k>1;k--){
				array_curr[k+1]=array_curr[k];
			}
			array_curr[1]=array_bro[leaf_bro->GetSize()-1];
			leaf_bro->IncreaseSize(-1);
			page_leaf->IncreaseSize(1);
			return;
			//leaf_bro->GetArray()[]=leaf_bro->GetArray()[leaf_bro->Getsize()-1];
		}
	}
	//if(0<pos){
	//	page_parent=
	//	page_bro=buffer_pool_manager_->FetchPgImp(page);}
	//2
	if(pos<page_leaf->GetMaxSize()-1){
		page_bro=buffer_pool_manager_->FetchPgImp(internal_par->ValueAt(pos+1));leaf_pro=page_bro->GetData();
		if(leaf_bro->GetSize()>leaf_bro->GetMinSize()){
			array_curr=page_leaf->GetArray() ; array_bro=leaf_bro->GetArray();
			//for(int k=page_leaf->GetSize()-1 ; k>1 ; k--){
			//	array_curr[k+1]=array_curr[k];
			//}
			array_curr[page_leaf->GetSize()]=array_bro[1];
			for(int k=1 ; k<leaf_bro->GetSize()-1 ; k++){
				array_bro[k]=array_bro[k+1];
			}
			leaf_bro->IncreaseSize(-1);
			page_leaf->IncreaseSize(1);
			return;
		}
	}
	//3 merge
	if(0<r){
		page_bro=buffer_pool_manager_->FetchPgImp(internal_par->ValueAt(pos-1)) ; leaf_pro=page_bro->GetData();
		array_curr=page_leaf->GetArray() ; array_bro=leaf_bro->GetArray();
		memcpy(array_bro[page_bro->Getsize()],array_curr,sizeof(MappingType)*(page_leaf->GetSize()));
		array_curr=internal_par->GetArray();
		for(int k=pos;k<internal_par->GetSize();k++){
			array_curr[k]=array_curr[k+1];
		}	
	}else{
		page_bro=buffer_pool_manager_->FetchPgImp(internal_par->ValueAt(pos-1)) ; leaf_pro=page_bro->GetData();
                array_curr=page_leaf->GetArray() ; array_bro=leaf_bro->GetArray();
                memcpy(array_bro[page_bro->Getsize()],array_curr,sizeof(MappingType)*(page_leaf->GetSize()));
                array_curr=internal_par->GetArray();
                for(int k=pos;k<internal_par->GetSize();k++){
                        array_curr[k]=array_curr[k+1];

	        }
	}
}
/*****************************************************************************
 * INDEX ITERATOR
 *****************************************************************************/
/*
 * Input parameter is void, find the leaftmost leaf page first, then construct
 * index iterator
 * @return : index iterator
 */
INDEX_TEMPLATE_ARGUMENTS
auto BPLUSTREE_TYPE::Begin() -> INDEXITERATOR_TYPE {
	if(root_page_id_==INVALID_PAGE_ID)
		return INDEXITERATOR_TYPE(buffer_pool_manager_,nullptr,INVALID_PAGE_ID,0,0);

	Pages *page=buffer_pool_manager_->FetchPgImp(root_page_id_);
	page_id_t curr_id;
	InternalPage *internal ; LeafPage *leaf ;
	IndexPageType page_type;
        memcpy(page_type,page->GetData(),sizeof(IndexPageType));
	while(page_type==INTERNAL_PAGE){
		internal=reinterpret_cast<InternalPage*>(page->GetData());
		curr_id=internal->GetPageId();
		page=buffer_Pool_manager_->FetchPgImp(internal->ValueAt(0));
		buffer_pool_manager_->UnpinPgImp(curr_id,false);
                memcpy(page_type,page->GetData(),sizeof(IndexPageType));
	}
	leaf=reinterpret_cast<LeafPage*>(page->GetData());
	curr_id=leaf->GetPageId();
	MappingType *KeyValue=&leaf->ValueAt(1);
	page_id_t next_page_id=leaf->GetNextPageId();
	int curr_max_index=page_leaf->GetSize()-1;

	buffer_pool_manager_->UnpinPgImp(curr_id,false);	
	return INDEXITERATOR_TYPE(buffer_pool_manager_,KeyValue,next_page_id,0,curr_max_index); }

/*
 * Input parameter is low key, find the leaf page that contains the input key
 * first, then construct index iterator
 * @return : index iterator
 */
INDEX_TEMPLATE_ARGUMENTS
auto BPLUSTREE_TYPE::Begin(const KeyType &key) -> INDEXITERATOR_TYPE {
	if(root_page_id_==INVALID_PAGE_ID)
                return INDEXITERATOR_TYPE(buffer_pool_manager_,nullptr,INVALID_PAGE_ID,0,0);

        Pages *index_page=buffer_pool_manager_->FetchPgImp(root_page_id_);
        page_id_t page_id;
        IndexPageType page_type;
        memset(page_type,0,sizeof(IndexPageType));
        memcpy(page_type,page_data,sizeof(IndexPageType));
        InternalPage page_internal;
        memcpy(page_internal,page_data,BUSTUB_PAGE_SIZE);
        while(page_type==INTERNAL_PAGE){
                memcpy(page_internal,page_data,BUSTUB_PAGE_SIZE);
                buffer_pool_manager_->UnpinPgImp();
                buffer_Pool_manager_->FetchPgImp();
                page_data=index_page->GetData();
                memcpy(page_type,page_data,sizeof(IndexPageType));
        }
        LeafPage &page_leaf;
        page_leaf=reinterpret_cast<LeafPage*>(page_data);
        MappingType KeyValue=&page_leaf->array_[1];
        page_id_t next_page_id=page_leaf->GetNextPageId();
        int curr_max_size=page_leaf->GetSize();
        return INDEXITERATOR_TYPE(buffer_pool_manager_,KeyValue,next_page_id,1,curr_max_size); 


}

/*
 * Input parameter is void, construct an index iterator representing the end
 * of the key/value pair in the leaf node
 * @return : index iterator
 */
INDEX_TEMPLATE_ARGUMENTS
auto BPLUSTREE_TYPE::End() -> INDEXITERATOR_TYPE {
	if(root_page_id_==INVALID_PAGE_ID)
                return INDEXITERATOR_TYPE(buffer_pool_manager_,nullptr,INVALID_PAGE_ID,0,0);

       // Pages *page=buffer_pool_manager_->FetchPgImp(root_page_id_);
        Pages *page=buffer_pool_manager_->FetchPgImp(root_page_id_);
        page_id_t curr_id,next_id;
        InternalPage *internal ; LeafPage *leaf ;
        IndexPageType page_type;
        memcpy(page_type,page->GetData(),sizeof(IndexPageType));
        while(page_type==INTERNAL_PAGE){
                internal=reinterpret_cast<InternalPage*>(page->GetData());
                curr_id=internal->GetPageId();
		next_id=internal->ValueAt(internal->GetMaxSize());

                page=buffer_Pool_manager_->FetchPgImp(next_id);
                buffer_pool_manager_->UnpinPgImp(curr_id,false);
                memcpy(page_type,page->GetData(),sizeof(IndexPageType));
        }
        leaf=reinterpret_cast<LeafPage*>(page->GetData());
	curr_id=leaf->GetPageId();
	max_index=leaf->GetMaxSize()-1;
        MappingType *KeyValue=&leaf->ValueAt(max_index);
        page_id_t next_page_id=leaf->GetNextPageId();
        int curr_max_index=page_leaf->GetSize()-1;
        return INDEXITERATOR_TYPE(buffer_pool_manager_,KeyValue,next_page_id,curr_max_index+1,curr_max_index);
}

/**
 * @return Page id of the root of this tree
 */
INDEX_TEMPLATE_ARGUMENTS
auto BPLUSTREE_TYPE::GetRootPageId() -> page_id_t { return root_page_id_; }

/*****************************************************************************
 * UTILITIES AND DEBUG
 *****************************************************************************/
/*
 * Update/Insert root page id in header page(where page_id = 0, header_page is
 * defined under include/page/header_page.h)
 * Call this method everytime root page id is changed.
 * @parameter: insert_record      defualt value is false. When set to true,
 * insert a record <index_name, root_page_id> into header page instead of
 * updating it.
 */
INDEX_TEMPLATE_ARGUMENTS
void BPLUSTREE_TYPE::UpdateRootPageId(int insert_record) {
  auto *header_page = static_cast<HeaderPage *>(buffer_pool_manager_->FetchPage(HEADER_PAGE_ID));
  if (insert_record != 0) {
    // create a new record<index_name + root_page_id> in header_page
    header_page->InsertRecord(index_name_, root_page_id_);
  } else {
    // update root_page_id in header_page
    header_page->UpdateRecord(index_name_, root_page_id_);
  }
  buffer_pool_manager_->UnpinPage(HEADER_PAGE_ID, true);
}

/*
 * This method is used for test only
 * Read data from file and insert one by one
 */
INDEX_TEMPLATE_ARGUMENTS
void BPLUSTREE_TYPE::InsertFromFile(const std::string &file_name, Transaction *transaction) {
  int64_t key;
  std::ifstream input(file_name);
  while (input) {
    input >> key;

    KeyType index_key;
    index_key.SetFromInteger(key);
    RID rid(key);
    Insert(index_key, rid, transaction);
  }
}
/*
 * This method is used for test only
 * Read data from file and remove one by one
 */
INDEX_TEMPLATE_ARGUMENTS
void BPLUSTREE_TYPE::RemoveFromFile(const std::string &file_name, Transaction *transaction) {
  int64_t key;
  std::ifstream input(file_name);
  while (input) {
    input >> key;
    KeyType index_key;
    index_key.SetFromInteger(key);
    Remove(index_key, transaction);
  }
}

/**
 * This method is used for debug only, You don't need to modify
 */
INDEX_TEMPLATE_ARGUMENTS
void BPLUSTREE_TYPE::Draw(BufferPoolManager *bpm, const std::string &outf) {
  if (IsEmpty()) {
    LOG_WARN("Draw an empty tree");
    return;
  }
  std::ofstream out(outf);
  out << "digraph G {" << std::endl;
  ToGraph(reinterpret_cast<BPlusTreePage *>(bpm->FetchPage(root_page_id_)->GetData()), bpm, out);
  out << "}" << std::endl;
  out.flush();
  out.close();
}

/**
 * This method is used for debug only, You don't need to modify
 */
INDEX_TEMPLATE_ARGUMENTS
void BPLUSTREE_TYPE::Print(BufferPoolManager *bpm) {
  if (IsEmpty()) {
    LOG_WARN("Print an empty tree");
    return;
  }
  ToString(reinterpret_cast<BPlusTreePage *>(bpm->FetchPage(root_page_id_)->GetData()), bpm);
}

/**
 * This method is used for debug only, You don't need to modify
 * @tparam KeyType
 * @tparam ValueType
 * @tparam KeyComparator
 * @param page
 * @param bpm
 * @param out
 */
INDEX_TEMPLATE_ARGUMENTS
void BPLUSTREE_TYPE::ToGraph(BPlusTreePage *page, BufferPoolManager *bpm, std::ofstream &out) const {
  std::string leaf_prefix("LEAF_");
  std::string internal_prefix("INT_");
  if (page->IsLeafPage()) {
    auto *leaf = reinterpret_cast<LeafPage *>(page);
    // Print node name
    out << leaf_prefix << leaf->GetPageId();
    // Print node properties
    out << "[shape=plain color=green ";
    // Print data of the node
    out << "label=<<TABLE BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\" CELLPADDING=\"4\">\n";
    // Print data
    out << "<TR><TD COLSPAN=\"" << leaf->GetSize() << "\">P=" << leaf->GetPageId() << "</TD></TR>\n";
    out << "<TR><TD COLSPAN=\"" << leaf->GetSize() << "\">"
        << "max_size=" << leaf->GetMaxSize() << ",min_size=" << leaf->GetMinSize() << ",size=" << leaf->GetSize()
        << "</TD></TR>\n";
    out << "<TR>";
    for (int i = 0; i < leaf->GetSize(); i++) {
      out << "<TD>" << leaf->KeyAt(i) << "</TD>\n";
    }
    out << "</TR>";
    // Print table end
    out << "</TABLE>>];\n";
    // Print Leaf node link if there is a next page
    if (leaf->GetNextPageId() != INVALID_PAGE_ID) {
      out << leaf_prefix << leaf->GetPageId() << " -> " << leaf_prefix << leaf->GetNextPageId() << ";\n";
      out << "{rank=same " << leaf_prefix << leaf->GetPageId() << " " << leaf_prefix << leaf->GetNextPageId() << "};\n";
    }

    // Print parent links if there is a parent
    if (leaf->GetParentPageId() != INVALID_PAGE_ID) {
      out << internal_prefix << leaf->GetParentPageId() << ":p" << leaf->GetPageId() << " -> " << leaf_prefix
          << leaf->GetPageId() << ";\n";
    }
  } else {
    auto *inner = reinterpret_cast<InternalPage *>(page);
    // Print node name
    out << internal_prefix << inner->GetPageId();
    // Print node properties
    out << "[shape=plain color=pink ";  // why not?
    // Print data of the node
    out << "label=<<TABLE BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\" CELLPADDING=\"4\">\n";
    // Print data
    out << "<TR><TD COLSPAN=\"" << inner->GetSize() << "\">P=" << inner->GetPageId() << "</TD></TR>\n";
    out << "<TR><TD COLSPAN=\"" << inner->GetSize() << "\">"
        << "max_size=" << inner->GetMaxSize() << ",min_size=" << inner->GetMinSize() << ",size=" << inner->GetSize()
        << "</TD></TR>\n";
    out << "<TR>";
    for (int i = 0; i < inner->GetSize(); i++) {
      out << "<TD PORT=\"p" << inner->ValueAt(i) << "\">";
      if (i > 0) {
        out << inner->KeyAt(i);
      } else {
        out << " ";
      }
      out << "</TD>\n";
    }
    out << "</TR>";
    // Print table end
    out << "</TABLE>>];\n";
    // Print Parent link
    if (inner->GetParentPageId() != INVALID_PAGE_ID) {
      out << internal_prefix << inner->GetParentPageId() << ":p" << inner->GetPageId() << " -> " << internal_prefix
          << inner->GetPageId() << ";\n";
    }
    // Print leaves
    for (int i = 0; i < inner->GetSize(); i++) {
      auto child_page = reinterpret_cast<BPlusTreePage *>(bpm->FetchPage(inner->ValueAt(i))->GetData());
      ToGraph(child_page, bpm, out);
      if (i > 0) {
        auto sibling_page = reinterpret_cast<BPlusTreePage *>(bpm->FetchPage(inner->ValueAt(i - 1))->GetData());
        if (!sibling_page->IsLeafPage() && !child_page->IsLeafPage()) {
          out << "{rank=same " << internal_prefix << sibling_page->GetPageId() << " " << internal_prefix
              << child_page->GetPageId() << "};\n";
        }
        bpm->UnpinPage(sibling_page->GetPageId(), false);
      }
    }
  }
  bpm->UnpinPage(page->GetPageId(), false);
}

/**
 * This function is for debug only, you don't need to modify
 * @tparam KeyType
 * @tparam ValueType
 * @tparam KeyComparator
 * @param page
 * @param bpm
 */
INDEX_TEMPLATE_ARGUMENTS
void BPLUSTREE_TYPE::ToString(BPlusTreePage *page, BufferPoolManager *bpm) const {
  if (page->IsLeafPage()) {
    auto *leaf = reinterpret_cast<LeafPage *>(page);
    std::cout << "Leaf Page: " << leaf->GetPageId() << " parent: " << leaf->GetParentPageId()
              << " next: " << leaf->GetNextPageId() << std::endl;
    for (int i = 0; i < leaf->GetSize(); i++) {
      std::cout << leaf->KeyAt(i) << ",";
    }
    std::cout << std::endl;
    std::cout << std::endl;
  } else {
    auto *internal = reinterpret_cast<InternalPage *>(page);
    std::cout << "Internal Page: " << internal->GetPageId() << " parent: " << internal->GetParentPageId() << std::endl;
    for (int i = 0; i < internal->GetSize(); i++) {
      std::cout << internal->KeyAt(i) << ": " << internal->ValueAt(i) << ",";
    }
    std::cout << std::endl;
    std::cout << std::endl;
    for (int i = 0; i < internal->GetSize(); i++) {
      ToString(reinterpret_cast<BPlusTreePage *>(bpm->FetchPage(internal->ValueAt(i))->GetData()), bpm);
    }
  }
  bpm->UnpinPage(page->GetPageId(), false);
}

template class BPlusTree<GenericKey<4>, RID, GenericComparator<4>>;
template class BPlusTree<GenericKey<8>, RID, GenericComparator<8>>;
template class BPlusTree<GenericKey<16>, RID, GenericComparator<16>>;
template class BPlusTree<GenericKey<32>, RID, GenericComparator<32>>;
template class BPlusTree<GenericKey<64>, RID, GenericComparator<64>>;

}  // namespace bustub
