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
            :m_valid(false), m_size(0), pos(-1)     //iterator not valid when created without argument
        {
        }
        Iterator(std::vector<ValueType>& v) 
            :m_valid(true), m_size(v.size()), pos(0)
        {
            values = &v;
        }

        ValueType& get_value() const
        {  
                return (*values)[pos];
        }

        bool is_valid() const
        {
            return m_valid;
        }

        void advance()
        {
            if (m_valid) {
                pos++;     
                if (pos == m_size)  //if reached end, return false
                    m_valid = false;
            }
        }

      private:
          int m_size;
          int pos;
          bool m_valid;
          std::vector<ValueType>* values;
    };

    TreeMultimap()
    {
        m_root = nullptr;
    }

    ~TreeMultimap()
    {
        delete m_root;
    }

    void insert(const KeyType& key, const ValueType& value)
    {
        if (m_root == nullptr) {       //adding if tree empty
            m_root = new Node;
            m_root->m_key = key;
            m_root->m_values.push_back(value);
            m_root->m_left = nullptr;
            m_root->m_right = nullptr;
            return;
        }
        Node* cur = m_root;
        for (;;) {
            if (key == cur->m_key) {
                cur->m_values.push_back(value);     //if key already exists, add the value to the vector
                return;
            }
            if (key < cur->m_key) {     //lower key
                if (cur->m_left != nullptr)
                    cur = cur->m_left;
                else {
                    cur->m_left = new Node;
                    cur->m_left->m_key = key;
                    cur->m_left->m_values.push_back(value);
                    cur->m_left->m_left = nullptr;
                    cur->m_left->m_right = nullptr;
                    return;
                }
            }
            else if (key > cur->m_key) {    //higher key
                if (cur->m_right != nullptr)
                    cur = cur->m_right;
                else {
                    cur->m_right = new Node;
                    cur->m_right->m_key = key;
                    cur->m_right->m_values.push_back(value);
                    cur->m_right->m_left = nullptr;
                    cur->m_right->m_right = nullptr;
                    return;
                }
            }
        }

    }

    Iterator find(const KeyType& key) const
    {
        Node* p = m_root;
        while (p != nullptr) {
            if (key == p->m_key) {      //key found
                return Iterator(p->m_values);
            }
            else if (key < p->m_key)    //key less
                p = p->m_left;
            else                  //key greater
                p = p->m_right;         
        }
        return Iterator();
    }

  private:
      struct Node {
          KeyType m_key;
          std::vector<ValueType> m_values;
          Node* m_left;
          Node* m_right;
      };
      Node* m_root;
};

#endif // TREEMULTIMAP_INCLUDED
