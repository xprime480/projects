
#include <iostream>
#include <set>
#include <map>
#include <memory>

using namespace std;

class TrieVisitor
{
public:
  virtual ~TrieVisitor()
  {
  }

  virtual bool visit(char const * key, int value) = 0;
};

class Trie
{
public:
    Trie()
        : terminal(false)
    {
    }

    void insert(char const * key, int item)
    {
        if ( NULL == key || '\0' == *key ) {
            value = item;
            terminal = true;
            return;
        }

        map<char, unique_ptr<Trie>>::iterator iter = children.find(*key);
        if ( iter == children.end() ) {
            children[*key] = std::move(unique_ptr<Trie>(new Trie));
        }
        auto & child = children[*key];
        child->insert(key+1, item);
    }

    void visit(TrieVisitor & visitor)
    {
        static string rootKey = string("");
        visit(rootKey, visitor);
    }

    int get(char const * key)
    {
        if ( NULL == key || '\0' == *key ) {
            return terminal ? value : -1;
        }

        auto iter = children.find(key[0]);
        if ( children.end() == iter ) {
            return -1;
        }

        return iter->second->get(key+1);
    }

private:

    bool terminal;
    int value;
    map<char, unique_ptr<Trie>> children;

    bool visit(string const & key, TrieVisitor & visitor)
    {
        if ( terminal ) {
            if ( ! visitor.visit(key.c_str(), value) ) {
                return false;
            }
        }

	for ( const auto & value : children ) {
            string xkey = key + value.first;
	    if ( ! value.second->visit(xkey, visitor) ) {
		return false;
	    }
	}

	return true;
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

    virtual bool visit(char const * key, int value)
    {
        ++count;
        return true;
    }

    size_t getCount()
    {
        return count;
    }

private:
    size_t count;
};

class LexicalVisitor : public TrieVisitor
{
public:
    LexicalVisitor()
        : TrieVisitor()
    {
    }

    virtual bool visit(char const * key, int value)
    {
	cout << key << "\n";
        return true;
    }
};

int main(int argc, char ** argv)
{
    Trie t;
    t.insert("once", 1);
    t.insert("two",  2);
    t.insert("one",  3);
    t.insert("on",   4);

    CountVisitor visitor;
    t.visit(visitor);
    cout << visitor.getCount() << " items\n";
    cout << "================\n";

    LexicalVisitor lexical;
    t.visit(lexical);
    cout << "================\n";

    const char * keys[] = { "on", "two", "only" };
    for ( auto key : keys ) {
        cout << key << " = " << t.get(key) << "\n";
    }

    return 0;
}
