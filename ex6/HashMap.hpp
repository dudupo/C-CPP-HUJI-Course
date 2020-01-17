#include <iostream>
#include <functional>
#include <utility>
#include <stdexcept>
#include <list>
#include <vector>
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


  int hash(keyT key, int parameter) const {
     return std::hash<keyT>{}( key ) & (parameter - 1);
  }

  int hash(keyT key) const {
      return this->hash(key, this->cells);
  }
  iteratorT getPoisition(keyT key) const {
    listT & cell = this->table[this->hash(key)];
    iteratorT it = cell.begin();
    for (; it != cell.end(); ++it)
      if ( it->first == key)
        return it;

    return this->null_iterator;
  }

  void throwException (keyT key) const
  {
      if ( !this->containsKey(key))
      {
          std::cout << " excption " << '\n';
          throw std::invalid_argument( "excption" );
      }
  }

  bool rehash(int new_size) {
    listT * new_table = new listT[new_size];

    for (auto it = this->begin(); it != this->end(); it++)
    {
        new_table[this->hash( (*it).first, new_size )].push_front(  pairT((*it).first, (*it).second)  );
    }


    delete [] this->table;

    this->table = new_table;
    this->cells = new_size;

    return true;
  }

  //TableIterator begin() const;

  bool balance() {

    if ( this->cells > DEFAULTSIZE &&
       (this->getLoadFactor() < this->lower_load_factor) )
      return this->rehash(this->cells >> 1);

    if ( this->getLoadFactor() > this->upper_load_factor )
      return this->rehash(this->cells << 1);

    return true;
  }

public:
    HashMap( HashMap const & const_ref ) {
      this->table = const_ref.table;
      this->cells = const_ref.cells;
      this->items  = const_ref.items;
      this->lower_load_factor = const_ref.lower_load_factor;
      this->upper_load_factor = const_ref.upper_load_factor;

  }

//    HashMap( HashMap & const_ref ) {
//        this->table = const_ref.table;
//        this->cells = const_ref.cells;
//        this->items  = const_ref.items;
//        this->lower_load_factor = const_ref.lower_load_factor;
//        this->upper_load_factor = const_ref.upper_load_factor;
//
//    }

  HashMap (double lower_load_factor, double upper_load_factor) :
    lower_load_factor(lower_load_factor),
    upper_load_factor(upper_load_factor) {

      this->cells= DEFAULTSIZE;
      table = new listT[cells];
      this->items = 0;

  }

  HashMap ( ) : HashMap( DEFAULT_LOWER_LOAD_FACTOR,
     DEFAULT_UPPER_LOAD_FACTOR ) {};


  HashMap ( const std::vector<keyT> &keys, const std::vector<valueT> &values ) :
   HashMap( DEFAULT_LOWER_LOAD_FACTOR, DEFAULT_UPPER_LOAD_FACTOR ) {

      if (  keys.size( ) != values.size() )
      {
          std::cout << " excption " << '\n';
          throw std::invalid_argument( "excption" );

      }

      typename std::vector<keyT>::const_iterator it_key = keys.begin();
      typename std::vector<valueT>::const_iterator it_val = values.begin();
      while (  it_key != keys.end() && it_val != values.end()  )
      {
        this->insert( *it_key , * it_val );
        it_key++; it_val++;
      }

  }



    // HashMap( HashMap&& );
  // HashMap( const HashMap&);
  virtual ~HashMap () {
      delete [] this->table;
  };
  int size() const {
      return this->items;
  }
  int capacity() const {
    return this->cells * this->upper_load_factor;
  }
  double getLoadFactor() const {
     return (double) this->items / this->cells;
  }
  bool empty() const {
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

  valueT& at(keyT key) const {
    iteratorT position = this->getPoisition(key);

    if ( position == this->null_iterator ) {
      std::cout << " excption " << '\n';
      throw std::invalid_argument( "excption" );
    }
    return position->second;
  }
  bool containsKey(keyT key) const {
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

  int bucketIndex(keyT key) const {
      this->throwException(key);
      return this->hash(key);
  }

  int bucketSize(keyT key) const {
    this->throwException(key);
    return table[this->hash(key)].size();
  }
  void clear() {

      delete [] this->table;
      this->cells= DEFAULTSIZE;
      table = new listT[cells];
      this->items = 0;

  }



    HashMap & operator=(HashMap && hashtable) {
        this->cells = hashtable.cells;
        this->items = hashtable.items;
        this->lower_load_factor = hashtable.lower_load_factor;
        this->upper_load_factor = hashtable.upper_load_factor;
        this->table = &hashtable.table[0];
        return *this;
    }
    HashMap & operator=(HashMap const & hashtable) {
    this->cells = hashtable.cells;
    this->items = hashtable.items;
    this->lower_load_factor = hashtable.lower_load_factor;
    this->upper_load_factor = hashtable.upper_load_factor;
    this->table = &hashtable.table[0];
    return *this;
  }
//
//    HashMap& operator=(const HashMap & const_ref){
//        this->table = const_ref.table;
//        this->cells = const_ref.cells;hashtable
//        this->items  = const_ref.items;
//        this->lower_load_factor = const_ref.lower_load_factor;
//        this->upper_load_factor = const_ref.upper_load_factor;
//        return *this;
//    }

    valueT& operator[] (keyT key) {

        return this->getPoisition(key)->second;



    }

  class TableIterator : std::iterator<std::forward_iterator_tag, HashMap<keyT,valueT>>
  {

  private:
    HashMap & hashtable;
    mutable iteratorT pos;
    mutable int list = 0;

    bool endofcell() const {
      return this->pos == this->table[this->list].end();
    }
    bool endoftable() const {
      return this->endofcell() && this->list == (this->cells-1);
    }
    void assignment_position() const {
      this->pos = this->table[this->list].begin();
    }
    void advance_to_next() const {
      while (endofcell() && !endoftable()) {
          this->list++;
          this->assignment_position();
      }
    }

  public:
        TableIterator( HashMap const & hashtable ) : hashtable(hashtable)
        {
        this->assignment_position();
        this->advance_to_next();
      }

//      ~TableIterator() { }

      TableIterator & end() const {
        this->list = (this->hashtable.cells-1);
        this->pos = this->hashtable.table[this->list].end();
        return *this;
      }
      TableIterator & operator++(int)  {
        this->pos++;
        this->advance_to_next();
        return *this;
      }
      TableIterator & operator++()   {
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
//
//      TableIterator & operator=( const TableIterator & other )  {
////            this->hashtable = other.hashtable;
//
//
//            this->list = 0;
//            this->assignment_position();
//            this->advance_to_next();
//      }
  };

  HashMap<keyT,valueT>::TableIterator& begin() const {
    return *(new TableIterator(*this));
  }
  HashMap<keyT,valueT>::TableIterator& end() const {
    return TableIterator(*this ).end();
  }

    HashMap<keyT,valueT>::TableIterator& cbegin() const {
        return  *(new TableIterator(*this));
    }
    HashMap<keyT,valueT>::TableIterator& cend() const {
        return TableIterator(  *this).end( );
    }

    bool operator==(const HashMap<keyT, valueT>& hashtable) const {
        for ( auto it : *this )
        {
            if ( !hashtable.containsKey( it.first ) )
            {
                return false;
            }
            if ( hashtable.at( it.first ) != it.second )
            {
                return false;
            }
        }
        return true;
    }


    bool operator!=(const HashMap & hashtable) const {

        for ( auto it : *this )
        {
            if ( !hashtable.containsKey( it.first ) )
            {
                return true;
            }

            if ( hashtable.at( it.first ) != it.second )
            {
                return true;
            }
        }

        return false;
    }

};HashMap( HashMap & const_ref ) {
        this->table = const_ref.table;
        this->cells = const_ref.cells;
        this->items  = const_ref.items;
        this->lower_load_factor = const_ref.lower_load_factor;
        this->upper_load_factor = const_ref.upper_load_factor;

    }
