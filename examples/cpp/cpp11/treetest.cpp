
#include <iostream>
#include <memory>
#include <vector>

using std::shared_ptr;
using std::cout;
using std::endl;
using std::vector;

/**
 * Class to hold a node of a binary tree
 */
template <typename T>
class TreeNode
{
public:
  using value_type = T;
  using node_type  = shared_ptr<TreeNode<value_type> >;

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

template<typename T>
struct Sequence
{
  Sequence(T l, T h, T s)
    : lo(l)
    , hi(h)
    , step(s)
  {
  }

  T operator()()
  {
    if ( lo >= hi ) 
      throw "Out of bounds";
    T rv = lo;
    lo += step;
    return rv;
  }

private:
  T lo,hi,step;
};

template<typename T, typename G>
typename TreeNode<T>::node_type make_tree(G gen)
{
  using value_type = T;
  using tree_type = TreeNode<T>;
  using node_type = typename TreeNode<T>::node_type;

  vector<node_type> nodes;
  try { 
    nodes.push_back(node_type(new tree_type(gen())));
    for ( int i = 0 ; /**/ ; ++i ) {
      node_type n(new tree_type(gen()));
      int idx = i >> 1;
      if ( 0 == i % 2 ) {
	nodes[idx]->set_left(n);
      }
      else {
	nodes[idx]->set_right(n);
      }
      nodes.push_back(n);
    }
  }
  catch ( ... ) {
  }

  node_type tree;
  if ( ! nodes.empty() ) {
    tree = nodes.front();
  }
  return tree;
}

template <typename T>
T sumtree(shared_ptr<TreeNode<T> > tree)
{
  using value_type = T;

  value_type sum(0);
  auto g = [&sum] (value_type v) { sum += v; };
  tree->preorder(g);
  return sum;
}

template<typename T, typename G>
void test(G gen)
{
  using value_type = T;
  using tree_type = TreeNode<T>;
  using node_type = typename TreeNode<T>::node_type;

  auto tree = make_tree<T, G>(gen);
  if ( ! tree.get() ) {
    return;
  }
  auto t = [] (value_type v) { return v+v; };
  auto newtree = tree->transform(t);

  auto f = [] (value_type v) { cout << v << " "; };
  tree->inorder(f);
  cout << endl;

  tree->preorder(f);
  cout << endl;

  newtree->preorder(f);
  cout << endl;
 
  cout << "            total = " << sumtree(tree)    << endl;
  cout << "transformed total = " << sumtree(newtree) << endl;
}

int main(int argc, char ** argv)
{
  test<int>(Sequence<int>(0,10,2));
  test<double>(Sequence<double>(1,10,0.25));

  return 0;
}
