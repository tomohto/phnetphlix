#ifndef TREEMULTIMAP_INCLUDED
#define TREEMULTIMAP_INCLUDED
#include <vector>
template <typename KeyType, typename ValueType>
class TreeMultimap
{
  public:
    class Iterator
    {
      public:
        Iterator()
        {
            // Replace this line with correct code.
            isValid = false;
            index = -1;
            ptr = nullptr;
        }
        Iterator(std::vector<ValueType>* point,int dex){
            isValid = true;
            index = dex;
            ptr = point;
            
        }

        ValueType& get_value() const
        {
            return ptr->at(index);
        }

        bool is_valid() const
        {
            return isValid;
        }

        void advance()
        {
            // Replace this line with correct code.
            index++;
            if (index >= ptr->size()){
                isValid = false;
            }
        }

      private:
        bool isValid;
        int index;
        std::vector<ValueType>* ptr;
        
    };

    TreeMultimap()
    {
        root = nullptr;
    }

    ~TreeMultimap() //find correct destructor code
    {
        freeTheTree(root);
    }

    void insert(const KeyType& key, const ValueType& value)
    {
        // Replace this line with correct code.
        if(root == nullptr){
            root = new Node(value);
            root->m_key = key;
            return;
        }
        
        Node* curr = root;
        Node* parent = nullptr;
        while(curr != nullptr){ //check if the key exists
            if(key < curr->m_key){ //is the key smaller
                parent = curr;
                curr = curr->left;
            }else if(key > curr->m_key){ //is the key greater
                parent = curr;
                curr = curr->right;
            }else{ //is it at the correct key
                curr->data.push_back(value);
                return;
            }
        }
        
        //create a new node
        Node* insertion = new Node(value);
        insertion->parent = parent;
        insertion->m_key = key;
        //insert the node as a child of the parents
        if(key<parent->m_key) {
            parent->left = insertion;
        }else{
            parent->right = insertion;
        }
    }

    Iterator find(const KeyType& key) const
    {
        Node* curr = root;
        while(curr != nullptr){
            if(key > curr->m_key){
                curr = curr->right;
            }else if(key < curr->m_key){
                curr = curr->left;
            }else{
                return Iterator(&curr->data,0);
            }
        }
        return Iterator();
    }

  private:
    struct Node {
        std::vector<ValueType> data;
        KeyType m_key;
        Node* parent;
        Node* left;
        Node* right;
        
        Node(const ValueType& val) {
            data.push_back(val);
            left = nullptr;
            right = nullptr;
            parent = nullptr;
        }
    };
    void freeTheTree(Node* node){
        if (node == nullptr)
            return;
        freeTheTree(node->left);
        freeTheTree(node->right);
        delete node;
    }
    Node* root;
    
};

#endif // TREEMULTIMAP_INCLUDED
