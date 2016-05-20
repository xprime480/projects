
#include <iostream>
#include <memory>
#include <vector>

#include "treenode.h"
#include "range.h"

using std::shared_ptr;
using std::cout;
using std::endl;
using std::vector;

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

void treetest(int argc, char ** argv)
{
  test<int>(Range<int>(0,10,2));
  test<double>(Range<double>(1,10,0.25));
}
