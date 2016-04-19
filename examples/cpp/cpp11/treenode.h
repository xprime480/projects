#if ! defined(TREENODE_H)
#define TREENODE_H 1

#include <memory>

template <typename T>
class TreeNode
{
public:
  using value_type = T;
  using node_type  = std::shared_ptr<TreeNode<value_type> >;

  TreeNode()
    : value(0)
    , left()
    , right()
  {
  }

  explicit TreeNode(T const & v)
    : value(v)
    , left()
    , right()
  {
  }

  ~TreeNode()
  {
  }

  void set_left(node_type & n)
  {
    left = n;
  }

  void set_right(node_type & n)
  {
    right = n;
  }

  template<typename U>
  void preorder(U f) const
  {
    f(value);
    if ( left.get() ) {
      left->preorder(f);
    }
    if ( right.get() ) {
      right->preorder(f);
    }
  }

  template<typename U>
  void inorder(U f) const
  {
    if ( left.get() ) {
      left->inorder(f);
    }
    f(value);
    if ( right.get() ) {
      right->inorder(f);
    }
  }

  template<typename U>
  node_type transform(U f) const
  {
    node_type newnode(new TreeNode(f(value)));
    if ( left.get() ) {
      node_type t = left->transform(f);
      newnode->set_left(t);
    }
    if ( right.get() ) {
      node_type t = right->transform(f);
      newnode->set_right(t);
    }
    return newnode;
  }

private:
  value_type value;
  node_type left;
  node_type right;
};

#endif /* TREENODE_H */
