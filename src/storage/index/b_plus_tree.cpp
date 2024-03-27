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
	if (IsEmpty()) return false;
	auto bptp = reinterpret_cast<BPlusTreePage *>(buffer_pool_manager_->FetchPage(root_page_id_)->GetData());
	int l, r, mid;  // the key of array_[0] is invalid
	while ( !bptp->IsLeafPage() ) {
		auto internal = reinterpret_cast< InternalPage* >(bptp);
		l = 1;
		r = internal->GetSize();
		mid = 0;
		while (l <= r) {
    		mid = l + (r + 1 - l) / 2;  // the root of (l+r)/2
    		if (comparator(key, interna->KeyAt(mid)) < 0) {
        		r = mid - 1;
    		} else if (comparator(internal->KeyAt(mid), key) < 0) {
        		l = mid + 1;
    		} else {
    			r = mid;
        		break;
    		}
    	}  // r
    	//cur_id = internal->GetPageId();
    	buffer_pool_manager_->UnpinPgImp(internal->GetPageId(), false);
    	bptp = reinterpret_cast< BPlusTreePage* >(buffer_pool_manager_->FetchPage(internal->ValueAt(r))->GetData());
	}
	auto leaf = reinterpret_cast< LeafPage* >(bptp);
	l = 0;
	l = leaf->GetSize() - 1;
	mid = 0;
	while (l <= r) {
    	mid = l + (r + 1 - l) / 2;
    	if (comparator(key, leaf->KeyAt(mid)) < 0) {
    		r = mid - 1;
    	} else if (comparator(leaf->KeyAt(mid), key) < 0) {
    		l = mid + 1;
    	} else {
    		break;
    	}
  	}
	if (l > r) {
    	return false;
	}
	(*result).emplace_back(leaf->ValueAt(mid));
	buffer_pool_manager_->UnpinPgImp(leaf->GetPageId(), false);
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
	BPlusTree *bptp; InternalPage *internal; LeafPage *leaf;
	if (root_page_id_ == INVALID_PAGE_ID) {
		internal = reinterpret_cast< InternalPage* >(buffer_pool_manager_->NewPgImp(&root_Page_id_)->GetData());
    	internal->Init(root_page_id_, INVALID_PAGE_ID, internal_max_size_);
		page_id_t leafId;
		leaf = reinterpret_cast< LeafPage* >(buffer_pool_manager_->NewPgImp(&leafId)->GetData());
		leaf->Init(leafId, root_Page_id_, leaf_max_size_);
    	leaf->SetNextPageId(INVALID_PAGE_ID);
    	MappingType *ptr = reinterpret_cast<MappingType*>(internal) + 24;
		*ptr = std::make_pair(key, leafId);
		internal->IncreaseSize(1);
		ptr = reinterpret_cast<MappingType*>(leaf) + 28;
		*ptr = std::make_pair(key, value);
    	leaf->IncreaseSize(1);
		buffer_pool_manager_->UnpinPgImp(root_page_id_, true);
    	buffer_pool_manager_->UnpinPgImp(leafId, true);
    	return true;
	}
	std::vector<std::pair<int, page_id_t>> path;
	bptp = reinterpret_cast< BPlusTreePage* >(buffer_pool_manager_->FetchPage(root_page_id_)->GetData());
	int l, r, mid;  // array_[0].first is invalid
	while ( !bptp->IsLeafPage() ) {
    	internal = reinterpret_cast< InternalPage* >(bptp);
    	l = 1;
    	r = internal->GetSize() - 1;
    	mid = 0;
    	while (l <= r) {
    		mid = l + (r + 1 - l) / 2;                             // the root of (l+r)/2
    		if (comparator(key, internal->KeyAt(mid)) < 0) {  // key<KeyAt(mid)
    			r = mid - 1;
    		} else if (comparator(internal->KeyAt(mid), key) < 0) {
        		l = mid + 1;
    		} else {
        		r = mid;
        		break;
    		}
    	}
    	path.emplace_back(r, internal->GetPageId());
		bptp = reinterpret_cast< BPlusTreePage* >(buffer_pool_manager_->FetchPage(internal->ValueAt(r))->GetData());
	}
	leaf = reinterpret_cast< LeafPage* >(bptp);
	l = 0; r = leaf->GetSize() - 1; mid = 0;
	while (l <= r) {
    	mid = l + (r + 1 - l) / 2;
    	if (comparator(key, leaf->KeyAt(mid)) < 0) {
    		r = mid - 1;
    	} else if (comparator(leaf->KeyAt(mid), key) < 0) {
      		l = mid + 1;
    	} else {
      		break;
    	}
  	}  // l;
  	if (l <= r) {
    	return false;
  	}  // duplicate
	MappingType* ptr_leaf = reinterpret_cast<MappingType*>(leaf) + 28;
	for (int i = leaf.GetSize() - 1; i >= l; --i) {
    	ptr_leaf[i + 1] = ptr_leaf[i];
	}
	ptr_leaf[l] = std::make_pair(key, value);
	leaf->IncreaseSize(1);
	
	buffer_pool_manager_->UnpinPgImp(leaf->GetPageId(), false);
	if (leaf->GetSize() < leaf->GetMaxSize()) {
		for(int i = path.size() - 1; i >= 0; --i){
			buffer_pool_manager_->UnpinPgImp(path[i], false);
		}
    	return true;
	}
//***************************************************************
//******                     overflow                       *****
//***************************************************************
  	LeafPage *sptLeaf; page_id_t sptLeafId;
	page_id_t cur_id, parent_id;
  	cur_id = leaf->GetPageId(); 
	parent_id = leaf->GetParentId();
	sptLeaf = reinterpret_cast< LeafPage* >(buffer_pool_manager_->NewPgImp(&sptLeafId)->GetData());
  	sptLeaf->Init(sptLeafId, parent_id, leaf_max_size_);
	sptLeaf->SetNextPageId(leaf->GetNextPageId);
  	leaf->SetNextPageId(sptLeafId);

  	KeyType of_key = leaf->KeyAt((leaf_max_size_) / 2);  // overflow
	MappingType* ptr_spt = reinterpret_cast<MappingType*>(sptLeaf) + 28;
  	memcpy(ptr_spt, ptr + (leaf_max_size_) / 2, sizeof(MappingType) * ((leaf_max_size_ + 1) / 2));
  	leaf->SetSize((leaf_max_size_) / 2);
  	sptLeaf->SetSize((leaf_max_size_ + 1) / 2);
  	memset(leaf->GetArray()+(leaf_max_size_)/2, 0, sizeof(MappingType)*(leaf_max_size_+1)/2);
  	buffer_pool_manager_->UnpinPgImp(sptLeafId, true);
  	buffer_pool_manager_->UnpinPgImp(curr_id, true);

  	cur_id = internal->GetPageId();
  	parent_id = internal->GetParentPageId();
	while (1) {  // parent_id!=INVALID_PAGE_ID){
    	int pos = path.back();
    	path.pop_back();
    	internal = reinterpret_cast<InternalPage *>(buffer_pool_manager_->FetchPgImp(pos)->GetData());
    	curr_id = internal->GetPageId();
    	parent_id = internal->GetParentPageId();
    	if (internal->GetSize() < internal_max_size_) {
      		ptr_internal = reinterpret_cast<MappingType*>(internal) + 24;
      		for (int i = internal->GetSize(); i >= pos; --i) {
        		ptr_internal[i + 1] = ptr_internal[i];
      		}
      		ptr_internal[pos + 1] = std::make_pair(of_key, sptLeafId);
      		internal->IncreaseSize(1);
      		while (parent_id != INVALID_PAGE_ID) {
        		buffer_pool_manager_->UnpinPgImp(curr_id, true);
        		curr_id = parent_id;
        		page = buffer_pool_manager_->FetchPgImp(curr_id);
        		page_internal = reinterpret_cast<InternalPage *>(page->GetData());
        		parent_id = page_internal->GetParentId();
      		}
      		buffer_pool_manager_->UnpinPgImp(curr_id, true);
      		return true;
		}else{
			InternalPage *sptInter;
    		page_id_t sptInterId;
    		sptInter = reinterpret_cast< InternalPage* >(buffer_pool_manager_->NewPgImp(&sptInterId)->GetData());
    		sptInter->Init(sptInterId, parent_id, internal_max_size_);
    		of_key = internal->KeyAt((internal_max_size_+1)/2+1);
    		memcpy(array_2, array[(internal_max_size_ / 2 + 1)], sizeof(MappingType) * ((internal_max_size_ + 1) / 2));
    		internal->SetSize(internal_max_size_ / 2);
    		sptInter->SetSize((internal_max_size_ + 1) / 2);
    // parent_id=page_internal->GetParentPageId();
    		buffer_pool_manager_->UnpinPgImp(cur_id, true);
    		buffer_pool_manager_->UnpinPgImp(sptInterId, true);	
    		if ( cur_id == root_page_id_ ) {
      // old_split_id=new_split_id;
      			page_split = buffer_pool_manager_->NewPgImp(&root_Page_id_);
      			internal_split = reinterpret_cast<InternalPage *>(page_split->GetData());
      			array = internal_split->GetArray();
      			array[0].second = curr_id;
      			array[1] = std::make_pair(key_overflow, old_split_id);
      			buffer_pool_manager_->UnpinPgImp(new_split_id, true);
			}
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
	if (root_page_id_ == INVALID_PAGE_ID) return;
	BPlusTree *bptp; InternalPage *internal; LeafPage *leaf;
    bptp = reinterpret_cast< BPlusTreePage* >(buffer_pool_manager_->FetchPage(root_page_id_)->GetData());
    int l, r, mid;
    std::vector<int> path;
    while ( !bptp->IsLeafPage() ) {
    	internal = reinterpret_cast< InternalPage* >( bptp );
      	l = 1;
      	r = internal->GetSize() - 1;
      	mid = 0;
      	while (l <= r) {
        	mid = l + (r + 1 - l) / 2;                             // the root of (l+r)/2
        	if (comparator(key, internal->KeyAt(mid)) < 0) {  // key<KeyAt(mid)
          		r = mid - 1;
        	} else if (comparator(internal->KeyAt(mid), key) < 0) {
          		l = mid + 1;
        	} else {
          		r = mid;
          		break;
        	}
      	}
      	path.emplace_back(r,);
      	bptp = bufffer_pool_manager_->FetchPgImp(internal->ValueAt(r));
    }
    leaf = reinterpret_cast< LeafPage* >( bptp );
    l = 0;
    r = leaf->GetSize() - 1;
    mid = 0;
    while (l <= r) {
      	mid = l + (r + 1 - l) / 2;
      	if (comparator(key, leaf->KeyAt(mid)) < 0) {
        	r = mid - 1;
      	} else if (comparator(leaf->KeyAt(mid), key) < 0) {
        	l = mid + 1;
      	} else {
        	// r=mid;
        	break;
      	}
    }
    if (l <= r) {
      	MappingType *ptrLeaf = reinterpret_cast< LeafPage* >(leaf) + 28;
      	for (int i = r; i < leaf->GetSize() - 1; ++i) {
        	ptrLeaf[i] = ptrLeaf[ i + 1 ];
      	}
      	leaf->IncreaseSize(-1);
    }
    if (leaf->GetSize() >= leaf->GetMinSize() ) {
      	return;
    }
    int pos = path.back();
    index_pos.pop_back();
    // 1
    Page *page_bro, *page_par;
    InternalPage *internal_par, *internal_bro;
    LeafPage *leaf_bro;
    MappingType *array_bro, *array_curr;
    page_id_t curr_id = page_leaf->GetPageId(), par_id = page_leaf->GetParentId(), bro_id;
    // if(0<pos)
    page_par = buffer_pool_manager_->FetchPgImp(par_id);
    internal_par = page_par->GetData();
    if (0 < pos) {
      page_bro = buffer_pool_manager_->FetchPgImp(internal_par->ValueAt(pos - 1));
      leaf_bro = page_bro->GetData();
      // bro_page_id=leaf_bro->GetPageId();
      if (leaf_bro->GetSize() > leaf_bro->GetMinSize()) {
        array_curr = page_leaf->GetArray();
        array_bro = leaf_bro->GetArray();
        for (int k = page_leaf->GetSize() - 1; k > 1; k--) {
          array_curr[k + 1] = array_curr[k];
        }
        array_curr[1] = array_bro[leaf_bro->GetSize() - 1];
        leaf_bro->IncreaseSize(-1);
        page_leaf->IncreaseSize(1);
        return;
        // leaf_bro->GetArray()[]=leaf_bro->GetArray()[leaf_bro->Getsize()-1];
      }
    }
    // if(0<pos){
    // 2
    if (pos < page_leaf->GetMaxSize() - 1) {
      page_bro = buffer_pool_manager_->FetchPgImp(internal_par->ValueAt(pos + 1));
      leaf_pro = page_bro->GetData();
      if (leaf_bro->GetSize() > leaf_bro->GetMinSize()) {
        array_curr = page_leaf->GetArray();
        array_bro = leaf_bro->GetArray();
        // for(int k=page_leaf->GetSize()-1 ; k>1 ; k--){
        //	array_curr[k+1]=array_curr[k];
        //}
        array_curr[page_leaf->GetSize()] = array_bro[1];
        for (int k = 1; k < leaf_bro->GetSize() - 1; k++) {
          array_bro[k] = array_bro[k + 1];
        }
        leaf_bro->IncreaseSize(-1);
        page_leaf->IncreaseSize(1);
        return;
      }
    }
    // 3 merge
    if (0 < r) {
      page_bro = buffer_pool_manager_->FetchPgImp(internal_par->ValueAt(pos - 1));
      leaf_pro = page_bro->GetData();
      array_curr = page_leaf->GetArray();
      array_bro = leaf_bro->GetArray();
      memcpy(array_bro[page_bro->Getsize()], array_curr, sizeof(MappingType) * (page_leaf->GetSize()));
      array_curr = internal_par->GetArray();
      for (int k = pos; k < internal_par->GetSize(); k++) {
        array_curr[k] = array_curr[k + 1];
      }
    } else {
      page_bro = buffer_pool_manager_->FetchPgImp(internal_par->ValueAt(pos - 1));
      leaf_pro = page_bro->GetData();
      array_curr = page_leaf->GetArray();
      array_bro = leaf_bro->GetArray();
      memcpy(array_bro[page_bro->Getsize()], array_curr, sizeof(MappingType) * (page_leaf->GetSize()));
      array_curr = internal_par->GetArray();
      for (int k = pos; k < internal_par->GetSize(); k++) {
        array_curr[k] = array_curr[k + 1];
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
  auto BPLUSTREE_TYPE::Begin()->INDEXITERATOR_TYPE {
    if (root_page_id_ == INVALID_PAGE_ID)
      return INDEXITERATOR_TYPE(buffer_pool_manager_, nullptr, INVALID_PAGE_ID, 0, 0);

    Pages *page = buffer_pool_manager_->FetchPgImp(root_page_id_);
    page_id_t curr_id;
    InternalPage *internal;
    LeafPage *leaf;
    IndexPageType page_type;
    memcpy(page_type, page->GetData(), sizeof(IndexPageType));
    while (page_type == INTERNAL_PAGE) {
      internal = reinterpret_cast<InternalPage *>(page->GetData());
      curr_id = internal->GetPageId();
      page = buffer_Pool_manager_->FetchPgImp(internal->ValueAt(0));
      buffer_pool_manager_->UnpinPgImp(curr_id, false);
      memcpy(page_type, page->GetData(), sizeof(IndexPageType));
    }
    leaf = reinterpret_cast<LeafPage *>(page->GetData());
    curr_id = leaf->GetPageId();
    MappingType *KeyValue = &leaf->ValueAt(1);
    page_id_t next_page_id = leaf->GetNextPageId();
    int curr_max_index = page_leaf->GetSize() - 1;

    buffer_pool_manager_->UnpinPgImp(curr_id, false);
    return INDEXITERATOR_TYPE(buffer_pool_manager_, KeyValue, next_page_id, 0, curr_max_index);
  }

  /*
   * Input parameter is low key, find the leaf page that contains the input key
   * first, then construct index iterator
   * @return : index iterator
   */
  INDEX_TEMPLATE_ARGUMENTS
  auto BPLUSTREE_TYPE::Begin(const KeyType &key)->INDEXITERATOR_TYPE {
    if (root_page_id_ == INVALID_PAGE_ID)
      return INDEXITERATOR_TYPE(buffer_pool_manager_, nullptr, INVALID_PAGE_ID, 0, 0);

    Pages *index_page = buffer_pool_manager_->FetchPgImp(root_page_id_);
    page_id_t page_id;
    IndexPageType page_type;
    memset(page_type, 0, sizeof(IndexPageType));
    memcpy(page_type, page_data, sizeof(IndexPageType));
    InternalPage page_internal;
    memcpy(page_internal, page_data, BUSTUB_PAGE_SIZE);
    while (page_type == INTERNAL_PAGE) {
      memcpy(page_internal, page_data, BUSTUB_PAGE_SIZE);
      buffer_pool_manager_->UnpinPgImp();
      buffer_Pool_manager_->FetchPgImp();
      page_data = index_page->GetData();
      memcpy(page_type, page_data, sizeof(IndexPageType));
    }
    LeafPage &page_leaf;
    page_leaf = reinterpret_cast<LeafPage *>(page_data);
    MappingType KeyValue = &page_leaf->array_[1];
    page_id_t next_page_id = page_leaf->GetNextPageId();
    int curr_max_size = page_leaf->GetSize();
    return INDEXITERATOR_TYPE(buffer_pool_manager_, KeyValue, next_page_id, 1, curr_max_size);
  }

  /*
   * Input parameter is void, construct an index iterator representing the end
   * of the key/value pair in the leaf node
   * @return : index iterator
   */
  INDEX_TEMPLATE_ARGUMENTS
  auto BPLUSTREE_TYPE::End()->INDEXITERATOR_TYPE {
    if (root_page_id_ == INVALID_PAGE_ID)
      return INDEXITERATOR_TYPE(buffer_pool_manager_, nullptr, INVALID_PAGE_ID, 0, 0);

    // Pages *page=buffer_pool_manager_->FetchPgImp(root_page_id_);
    Pages *page = buffer_pool_manager_->FetchPgImp(root_page_id_);
    page_id_t curr_id, next_id;
    InternalPage *internal;
    LeafPage *leaf;
    IndexPageType page_type;
    memcpy(page_type, page->GetData(), sizeof(IndexPageType));
    while (page_type == INTERNAL_PAGE) {
      internal = reinterpret_cast<InternalPage *>(page->GetData());
      curr_id = internal->GetPageId();
      next_id = internal->ValueAt(internal->GetMaxSize());

      page = buffer_Pool_manager_->FetchPgImp(next_id);
      buffer_pool_manager_->UnpinPgImp(curr_id, false);
      memcpy(page_type, page->GetData(), sizeof(IndexPageType));
    }
    leaf = reinterpret_cast<LeafPage *>(page->GetData());
    curr_id = leaf->GetPageId();
    max_index = leaf->GetMaxSize() - 1;
    MappingType *KeyValue = &leaf->ValueAt(max_index);
    page_id_t next_page_id = leaf->GetNextPageId();
    int curr_max_index = page_leaf->GetSize() - 1;
    return INDEXITERATOR_TYPE(buffer_pool_manager_, KeyValue, next_page_id, curr_max_index + 1, curr_max_index);
  }

  /**
   * @return Page id of the root of this tree
   */
  INDEX_TEMPLATE_ARGUMENTS
  auto BPLUSTREE_TYPE::GetRootPageId()->page_id_t { return root_page_id_; }

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
  void BPLUSTREE_TYPE::Draw(BufferPoolManager * bpm, const std::string &outf) {
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
  void BPLUSTREE_TYPE::Print(BufferPoolManager * bpm) {
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
  void BPLUSTREE_TYPE::ToGraph(BPlusTreePage * page, BufferPoolManager * bpm, std::ofstream & out) const {
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
        out << "{rank=same " << leaf_prefix << leaf->GetPageId() << " " << leaf_prefix << leaf->GetNextPageId()
            << "};\n";
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
  void BPLUSTREE_TYPE::ToString(BPlusTreePage * page, BufferPoolManager * bpm) const {
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
      std::cout << "Internal Page: " << internal->GetPageId() << " parent: " << internal->GetParentPageId()
                << std::endl;
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
