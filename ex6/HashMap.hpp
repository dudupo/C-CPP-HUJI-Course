
#include <functional>
#include <utility>
#include <stdexcept>
#include <list>
#include <iterator>

// ------------------------------
  const unsigned int DEFAULTSIZE = 16;
  const double DEFAULT_LOWER_LOAD_FACTOR = 0.25;
  const double DEFAULT_UPPER_LOAD_FACTOR = 0.75;
// ------------------------------

template <typename keyT, typename valueT>
class HashMap {
    typedef class std::list<std::pair<keyT, valueT>> listT;
    typedef class listT::iterator iteratorT;
    typedef class std::pair<keyT, valueT> pairT;
    friend class TableIterator;

private:
  /* data */

  listT * table;
  double lower_load_factor;
  double upper_load_factor;
  int cells, items;

  const iteratorT null_iterator = (new listT())->end();


  int hash(keyT key, int parameter) {
     return std::hash<keyT>{}( key ) & (parameter - 1);
  }

  int hash(keyT key) {
      return this->hash(key, this->cells);
  }
  iteratorT getPoisition(keyT key) {
    listT & cell = this->table[this->hash(key)];
    iteratorT it = cell.begin();
    for (; it != cell.end(); ++it)
      if ( it->first == key)
        return it;

    return this->null_iterator;
  }

  bool rehash(int new_size) {
    listT * new_table = new listT[new_size];

    std::cout << "  -- rehash --  " << '\n';
    std::cout << "current_size : " << this->cells << "\t\tnew_size : " << new_size << '\n';
    std::cout << "current_factor : " << this->getLoadFactor() << "\t\tmin_factor : " << this->lower_load_factor << "\t\tmax_factor : " << this->upper_load_factor << '\n';
    for (auto it = this->begin(); it != this->end(); it++) {
        std::cout << "key : " << (*it).first << "\t\tvalue : " << (*it).second << '\n';
        new_table[this->hash( (*it).first, new_size )].push_front(  pairT((*it).first, (*it).second)  ); // pairT((*it).first, (*it).second)
        //std::cout << new_table[this->hash( (*it).first, new_size )].begin()->first << '\n';
    }

    std::cout << "  -- finish rehash --  " << '\n';

    this->table = new_table;
    this->cells = new_size;
    std::cout << "current_factor : " << this->getLoadFactor() << "\t\tmin_factor : " << this->lower_load_factor << "\t\tmax_factor : " << this->upper_load_factor << '\n';

    return true;
  }

  bool balance() {

    if ( this->cells > DEFAULTSIZE &&
       (this->getLoadFactor() < this->lower_load_factor) )
      return this->rehash(this->cells >> 1);

    if ( this->getLoadFactor() > this->upper_load_factor )
      return this->rehash(this->cells << 1);

    return true;
  }

public:
  HashMap (double lower_load_factor, double upper_load_factor) :
    lower_load_factor(lower_load_factor),
    upper_load_factor(upper_load_factor) {

      this->cells= DEFAULTSIZE;
      table = new listT[cells];
      this->items = 0;

  }

  HashMap ( ) : HashMap( DEFAULT_LOWER_LOAD_FACTOR,
     DEFAULT_UPPER_LOAD_FACTOR ) {};

  // HashMap( HashMap&& );
  // HashMap( const HashMap&);
  virtual ~HashMap () {};
  int size() {
      return this->items;
  }
  int capacity() {
    return this->cells * this->upper_load_factor;
  }
  double getLoadFactor() {
     return (double) this->items / this->cells;
  }
  bool empty() {
    return this->items == 0;
  }
  bool insert(keyT key, valueT value) {

    iteratorT position = this->getPoisition(key);
    if (position != this->null_iterator)
      position->second = value;
    else
      this->table[this->hash(key)].push_front( pairT(key, value) );

    this->items++;
    return this->balance();
  }

  valueT at(keyT key) {
    iteratorT position = this->getPoisition(key);

    if ( position == this->null_iterator ) {
      std::cout << " excption " << '\n';
      throw std::invalid_argument( "excption" );
    }
    return position->second;
  }
  bool containsKey(keyT key) {
    return this->getPoisition(key) != this->null_iterator;
  }
  bool erase(keyT key) {

    iteratorT position = this->getPoisition(key);

    if ( position != this->null_iterator)
      (this->table[this->hash(key)]).erase( position );

    else
      return false;

    this->items--;
    return this->balance();
  }
  int bucketSize(keyT key) {
    return table[this->hash(key)].size();
  }
  void clear() {

  }
  void operator=(HashMap & hashtable) {
    this->cells = hashtable.cells;
    this->items = hashtable.items;
    this->lower_load_factor = hashtable.lower_load_factor;
    this->upper_load_factor = hashtable.upper_load_factor;
    this->table = &hashtable.table[0];
  }

  class TableIterator
  {

  private:
    HashMap & hashtable;
    iteratorT pos;
    int list = 0;

    bool endofcell(){
      return this->pos == this->hashtable.table[this->list].end();
    }
    bool endoftable() {
      return this->endofcell() && this->list == (this->hashtable.cells-1);
    }
    void assignment_position() {
      this->pos = this->hashtable.table[this->list].begin();
    }
    void advance_to_next() {
      while (endofcell() && !endoftable()) {
          this->list++;
          this->assignment_position();
      }
    }

  public:
      TableIterator(HashMap & hashtable) : hashtable(hashtable) {
        this->assignment_position();
        this->advance_to_next();
      }
      ~TableIterator() { }

      TableIterator & end() {
        this->list = (this->hashtable.cells-1);
        this->pos = this->hashtable.table[this->list].end();
        return *this;
      }
      TableIterator & operator++(int) {
        this->pos++;
        this->advance_to_next();
        return *this;
      }
      TableIterator & operator++() {
        return this->operator++(1);
      }
      pairT  operator* () const {
         return *(this->pos);
      }
      pairT & operator->() const {
         return *(this->pos);
      }
      bool operator==( TableIterator other ) const {
          return this->pos == other.pos;
      }
      bool operator!=( TableIterator other ) const {
          return this->pos != other.pos;
      }
  };

  HashMap<keyT,valueT>::TableIterator begin() {
    return TableIterator(*this);
  }
  HashMap<keyT,valueT>::TableIterator end() {
    return TableIterator(*this).end();
  }

};
