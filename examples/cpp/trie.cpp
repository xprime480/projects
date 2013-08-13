
#include <iostream>
#include <set>
#include <map>

using namespace std;

class TrieVisitor
{
public:
  virtual ~TrieVisitor()
  {
  }

  virtual bool visit(char const * key, void * item) = 0;
};

class Trie 
{
public:
  Trie()
  {
  }

  ~Trie()
  {
    map<char, Trie *>::iterator iter;
    for ( iter = children.begin() ; iter != children.end() ; ++iter ) {
      delete iter->second;
    }
    children.clear();
  }

  void add(char const * key, void * item)
  {
    if ( NULL == key || '\0' == *key ) {
      items.insert(item);
      return;
    }

    map<char, Trie *>::iterator iter = children.find(*key);
    if ( iter == children.end() ) {
      children[*key] = new Trie();
    }
    children[*key]->add(key+1, item);
  }

  void visit(TrieVisitor & visitor) 
  {
    static string rootKey = string("");
    visit(rootKey, visitor);
  }

private:

  set<void *> items;

  map<char, Trie *> children;

  void visit(string const & key, TrieVisitor & visitor)
  {
    if ( ! visitor.visit(key.c_str(), (void *) 0) ) {
      return;
    }

    set<void *>::iterator iiter;
    for ( iiter = items.begin() ; iiter != items.end() ; ++iiter ) {
      if ( ! visitor.visit(key.c_str(), *iiter) ) {
	return;
      }
    }

    map<char, Trie*>::iterator citer;
    for ( citer = children.begin() ; citer != children.end() ; ++citer ) {
      string xkey = key + citer->first;
      citer->second->visit(xkey, visitor);
    }
  }

};

class CountVisitor : public TrieVisitor
{
public:
  CountVisitor()
    : TrieVisitor()
    , count(0)
  {
  }

  virtual bool visit(char const * key, void * item)
  {
    if ( item ) {
      ++count;
    }
    return true;
  }

  size_t getCount()
  {
    return count;
  }

private:
  size_t count;
  
};

int main(int argc, char ** argv)
{
  Trie t;
  t.add("once", (void *) 1);
  t.add("two",  (void *) 2);
  t.add("one",  (void *) 3);

  CountVisitor visitor;
  t.visit(visitor);
  cout << visitor.getCount() << " items" << endl;
}
