/*************************************************************************
  > File Name: _bst.h
  > Author: anthony
  > Mail: w826581298@163.com
  > Created Time: Fri 06 Dec 2019 05:34:23 PM CST
 ************************************************************************/
#ifndef _BST_H
#define _BST_H
#include <vector>
#include <iostream>
#include <stack>
#include <utility>
enum E_BOOL_VALUE { FALSE, TRUE };
enum E_CMP_VALUE { SMALLER, EQUAL, BIGGER };
typedef int BOOL;

template <typename T>
struct treeNode {
  T value;
  treeNode<T>* p = nullptr;
  treeNode<T>* l = nullptr;
  treeNode<T>* r = nullptr;
};

template <typename T>
class BST {
private:
  E_CMP_VALUE(*cmp)(const T& v1, const T& v2); /* The function init how to compare two elements */
  void freeNode(treeNode<T>* node);
  treeNode<T>* getSuccessor(treeNode<T>* node);
  void handleSuccessor(treeNode<T>* successor);
  BOOL isLeft(treeNode<T>* node);
  int size; /* The size(the number of the nodes) of the bst */
  treeNode<T>* head; /* The head node of the bst */
public:
  BST() :size(0), head(nullptr), cmp(nullptr) {}
  ~BST();
  void destory();
  void init(E_CMP_VALUE(*cmp)(const T& v1, const T& v2));
  treeNode<T>* getHead() { return head; };

  void get(const T& element, std::vector<T>& v);
  BOOL put(const T& element);
  int remove(const T& element);

  T* inOrder();
  T* preOrder();
  T* postOrder();
  BOOL isEmpty() { return head == nullptr; }
  int getSize() { return size; }
};

/*************************************************************************
 * Function name	:~BST
 * Description		:The destructor of the BST
 * Parameter		:void
 * Return			:void
*************************************************************************/
template <typename T>
BST<T>::~BST() {
  destory();
}
/*************************************************************************
 * Function name	:freeNode
 * Description		:Travese the bst with inOrder and delete all the nodes,
 *					free the memories
 * Parameter		:
 *		node	:Pointer of the node to delete
 * Return			:void
*************************************************************************/
template <typename T>
void BST<T>::freeNode(treeNode<T>* node) {
  if (node == nullptr) {
    return;
  }
  treeNode<T>* l, * r;
  l = node->l;
  r = node->r;
  delete node;
  node = nullptr;
  if (l != nullptr) {
    freeNode(l);
  }
  if (r != nullptr) {
    freeNode(r);
  }
}

/*************************************************************************
 * Function name	:getSuccessor
 * Description		:We always delete the leaf node or the node without left child,
 *					Here we use the successor of the node to be deleted to replace
 *					itself and delete the successor. This function is used to get
 *					the successor.
 * Parameter		:
 *	node		:The node to be deleted.
 * Return		    :
 *	treeNode<T>*:The pointer of the successor node.If there is no successor node,
 *				return nullptr.
*************************************************************************/
template <typename T>
treeNode<T>* BST<T>::getSuccessor(treeNode<T>* node) {
  treeNode<T>* tmp = node->r;
  if (tmp == nullptr) {
    return nullptr;
  }
  while (tmp->l != nullptr) {
    tmp = tmp->l;
  }
  return tmp;
}

/*************************************************************************
 * Function name	:handleSuccessor
 * Description		:After replace the node to be deleted with its successor
 *					node, we should delete the sucessor node and adjust its
 *					parent's child domain with this function.
 * Parameter		:
 *	successor	:The successor node.
 * Return			:void
*************************************************************************/
template <typename T>
void BST<T>::handleSuccessor(treeNode<T>* successor) {
  treeNode<T>* par = successor->p;
  if (par == successor) {
    par->r = successor->r;
    return;
  }

  //The successor id the left child of its parent
  if (isLeft(successor)) {
    //Modify the parent domain of the successor's child 
    //Modify the child domain of the successor's parent
    if (successor->r != nullptr) {
      successor->r->p = par;
      par->l = successor->r;
    }
    else {
      par->l = nullptr;
    }
  }
  //The successor id the left child of its parent
  else {
    if (successor->r != nullptr) {
      successor->r->p = par;
      par->r = successor->r;
    }
    else {
      par->r = nullptr;
    }
  }
}

/*************************************************************************
 * Function name	:isLeft
 * Description		:To judge if the present is its parent's left child.
 * Parameter		:
 *	node		:The node to be judged.
 * Return		    :BOOL
 *	TRUE		:If the node is its parent's left child.
 *	FALSE		:If the node is its parent's right child or it has no parent.
*************************************************************************/
template <typename T>
BOOL BST<T>::isLeft(treeNode<T>* node) {
  treeNode<T>* par = node->p;
  if (par == nullptr) {
    return FALSE;
  }
  return par->l == node;
}
/*************************************************************************
 * Function name	:destory
 * Description		:To destory the bst and free all the memories.
 * Parameter		:void
 * Return			:void
*************************************************************************/
template <typename T>
void BST<T>::destory() {
  freeNode(head);
  head = nullptr;
}
/************************************************************************
 * Function name	:init
 * Description		:To init the cmp function.
 * Parameter		:
 *	_cmp		:The cmp function of the bst.
 * Return			:void
*************************************************************************/
template <typename T>
void BST<T>::init(E_CMP_VALUE(*_cmp)(const T& v1, const T& v2)) {
  cmp = _cmp;
}

/*************************************************************************
 * Function name	:get
 * Description		:To get the element equals(according to the cmp function)
 *					to the given value
 * Parameter		:
 *	element		:The given value.
 *	v			:The vector of T to contain the results.Because ther might be
 *				not only on elements equals to the given value.
 * Return			:void
*************************************************************************/
template <typename T>
void BST<T>::get(const T& element, std::vector<T>& v) {
  treeNode<T>* h = head;
  E_CMP_VALUE CMP;
  while (h != nullptr) {
    CMP = cmp(h->value, element);
    if (CMP == EQUAL) {
      v.push_back(h->value);
      h = h->l;
    }
    else if (CMP == SMALLER) {
      h = h->l;
    }
    else {
      h = h->r;
    }
  }
}

/*************************************************************************
 * Function name	:put
 * Description		:Add a new element to the bst.
 * Parameter		:
 *	element		:The element to be added.
 * Return			:BOOL
 *	TRUE		:Add the element successfully.
 *	FALSE		:Fail to add it because of some exceptions.
*************************************************************************/
template <typename T>
BOOL BST<T>::put(const T& element) {
  size++;
  treeNode<T>* node = new treeNode<T>;
  node->value = element;
  if (head == nullptr) {
    head = node;
    return TRUE;
  }
  treeNode<T>* h = head;
  while (1) {
    node->p = h;
    //If the element to be inserted is BIGGER than the present node.The node change to its left child
    if (cmp(h->value, element) == BIGGER) {
      if (h->r == nullptr) {
        h->r = node;
        return TRUE;
      }
      h = h->r;
    }
    //If the element to be inserted is SMALLER than the present node or EQUAL.The node change to its left child
    else {
      if (h->l == nullptr) {
        h->l = node;
        return TRUE;
      }
      h = h->l;
    }
  }
}

/*************************************************************************
 * Function name	:remove
 * Description		:To remove the node that equals to the given value.
 * Parameter		:
 *	element		:The given element to be removed.
 * Return			:The number of the nodes have been removed.
*************************************************************************/
template <typename T>
int BST<T>::remove(const T& element) {
  treeNode<T>* h = head;
  treeNode<T>* successor;
  treeNode<T>* par;
  int num = 0;
  E_CMP_VALUE CMP;
  while (h != nullptr) {
    successor = nullptr;
    CMP = cmp(h->value, element);
    if (CMP == EQUAL) {
      num++;
      par = h->p;
      successor = getSuccessor(h);
      //The successor node exists.
      if (successor != nullptr) {
        h->value = successor->value;
        handleSuccessor(successor);
        h = h->l;
      }
      //Its right child is nullptr but left child exists.
      else if (h->l != nullptr) {
        //Not the head node and it's the left child of its parent
        if (par != nullptr && isLeft(h)) {
          par->l = h->l;
          h->l->p = par;
          delete h;
          h = par->l;
        }
        //Not the head node and it's the right child of its parent
        else if (par != nullptr && !isLeft(h)) {
          par->r = h->l;
          h->l->p = par;
          delete h;
          h = par->r;
        }
        //This the head node.
        else {
          head = h->l;
          head->p = nullptr;
          h = head;
        }
      }
      //Its right child is nullptr and left child is nullptr too.
      else {
        //Not the head node and it's the left child of its parent
        if (par != nullptr && isLeft(h)) {
          par->l = nullptr;
          delete h;
          break;
        }
        //Not the head node and it's the right child of its parent
        else if (par != nullptr && !isLeft(h)) {
          par->r = nullptr;
          delete h;
          break;
        }
        //It's the head node.
        else {
          head = nullptr;
          break;
        }
      }
    }
    else if (CMP == SMALLER) {
      h = h->l;
    }
    else {
      h = h->r;
    }
  }
  size -= num;
  return num;
}

/*************************************************************************
 * Function name	:preOrder
 * Description		:To travese the bst with preOrder.Use stack instead of
 *					recursion function.
 * Parameter		:void
 * Return			:The array of the nodes.
*************************************************************************/
template <typename T>
T* BST<T>::preOrder() {
  if (size == 0) {
    return nullptr;
  }
  T* res = new T[size];
  int index = 0;
  treeNode<T>* h = head;
  treeNode<T>* tmp;
  std::stack<treeNode<T>*> s;
  s.push(h);
  while (!s.empty()) {
    tmp = s.top();
    s.pop();
    if (tmp->r != nullptr) {
      s.push(tmp->r);
    }
    if (tmp->l != nullptr) {
      s.push(tmp->l);
    }
    res[index++] = tmp->value;
  }
  return res;
}

/*************************************************************************
 * Function name	:inOrder
 * Description		:To travese the bst with inOrder.Use stack instead of recursion function.
 * Parameter		:void
 * Return			:The array of the nodes.
*************************************************************************/
template <typename T>
T* BST<T>::inOrder() {
  if (size == 0) {
    return nullptr;
  }
  enum E_CHECK { CHECK, PRINT };
  T* res = new T[size];
  int index = 0;
  treeNode<T>* h = head;
  treeNode<T>* ttmp;
  std::stack<std::pair<treeNode<T>*, E_CHECK> > s; /* Use pair to mask if the node has been visited */
  std::pair<treeNode<T>*, E_CHECK> p, tmp;
  p = std::make_pair(h, CHECK);
  s.push(p);
  while (!s.empty()) {
    tmp = s.top();
    s.pop();
    ttmp = tmp.first;
    if (tmp.second == CHECK) {
      if (ttmp->r != nullptr) {
        s.push(std::make_pair(ttmp->r, CHECK));
      }
      tmp.second = PRINT;
      s.push(tmp);
      if (ttmp->l != nullptr) {
        s.push(std::make_pair(ttmp->l, CHECK));
      }
    }
    else {
      res[index++] = ttmp->value;
    }
  }
  return res;
}

/*************************************************************************
 * Function name	:postOrder
 * Description		:To travese the bst with postOrder.Use stack instead of recursion function.
 * Parameter		:void
 * Return			:The array of the nodes.
*************************************************************************/
template <typename T>
T* BST<T>::postOrder() {
  if (size == 0) {
    return nullptr;
  }
  enum E_CHECK { CHECK, PRINT };
  T* res = new T[size];
  int index = 0;
  treeNode<T>* h = head;
  treeNode<T>* ttmp;
  std::stack<std::pair<treeNode<T>*, E_CHECK> > s;
  std::pair<treeNode<T>*, E_CHECK> p, tmp;
  p = std::make_pair(h, CHECK);
  s.push(p);
  while (!s.empty()) {
    tmp = s.top();
    s.pop();
    ttmp = tmp.first;
    if (tmp.second == CHECK) {
      //The children of the present node has been visited so change the node STATE to print
      tmp.second = PRINT;
      s.push(tmp);
      if (ttmp->r != nullptr) {
        s.push(std::make_pair(ttmp->r, CHECK));
      }
      if (ttmp->l != nullptr) {
        s.push(std::make_pair(ttmp->l, CHECK));
      }
    }
    else {
      res[index++] = ttmp->value;
    }
  }
  return res;
}
#endif
