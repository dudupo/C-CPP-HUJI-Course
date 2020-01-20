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


  listT * ptrlistT = new listT();
  const iteratorT null_iterator =  ptrlistT->end();  //end();


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
    listT * new_table = new listT[new_size + 1];

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

  void fill ( HashMap const & const_ref)
  {
      for ( const auto& it : const_ref )
      {
          this->insert( it.first , it.second  );
      }
  }

  class Shell {
  private:
      keyT& key;
      valueT& val;
      HashMap& hashtable;
  public:
    Shell( keyT key ,  HashMap& hashtable, valueT val = valueT() ) : val(val),  key(key), hashtable(hashtable) {}
    //Shell( keyT key,  HashMap& hashtable  ) : val(  default )  , key(key), hashtable(hashtable) {}
    operator valueT()
    {
      return this->val;
    }

    Shell& operator=(valueT val )
    {
      this->val = val;
      this->hashtable.insert(this->key, this->val);
      return *this;
    }

  };

public:
    HashMap( HashMap const & const_ref ) {

      this->cells = const_ref.cells;
      this->items  = 0;
      this->lower_load_factor = const_ref.lower_load_factor;
      this->upper_load_factor = const_ref.upper_load_factor;

      this->table =  new listT [this->cells + 1];

       this->fill( const_ref );



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
      table = new listT[cells +  1];
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
      delete this->ptrlistT;
  };
  int size() const {
      return this->items;
  }
  int capacity() const {
    return this->cells;
  }
  double getLoadFactor() const {
     return (double) this->items / this->cells;
  }
  bool empty() const {
    return this->items == 0;
  }
  bool insert(keyT key, valueT value) {

    iteratorT position = this->getPoisition(key);
    if (position != this->null_iterator) {
        // override
        position->second = value;
        return false;
    }
    else
    {
        this->table[this->hash(key)].push_front(pairT(key, value));

    }
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
      //this->cells= DEFAULTSIZE;
      table = new listT[cells + 1];
      this->items = 0;

  }

//    HashMap & operator=(HashMap && hashtable) {
//        this->cells = hashtable.cells;
//        this->items = hashtable.items;
//        this->lower_load_factor = hashtable.lower_load_factor;
//        this->upper_load_factor = hashtable.upper_load_factor;
//        this->table = &hashtable.table[0];
//        return *this;
//    }
    HashMap & operator=(HashMap const & hashtable) {

        if ( this->table != hashtable.table )
        {
          this->clear();
          this->lower_load_factor = hashtable.lower_load_factor;
          this->upper_load_factor = hashtable.upper_load_factor;
          this->fill(  hashtable  );
        }
        return *this;
  }

    Shell operator[] (keyT key) {

      iteratorT it = this->getPoisition(key);

      if ( it != null_iterator )
      {
          return Shell(key, *this, it->second);
      }
      else
      {
        return Shell(key, *this);
      }

    }
    class iterator
    {
    public:
        typedef iterator self_type;
        typedef pairT value_type;
        typedef pairT& reference;
        typedef iteratorT pointer;
        typedef std::forward_iterator_tag iterator_category;
        typedef int difference_type;

        iterator(listT * ptr, listT * ptr_end) : list_pos(ptr), cell_pos(ptr->begin()), end_cell(ptr_end)
        {
            nextOccupy();
        }
        self_type operator++()
        {
            cell_pos++;

            while (  (list_pos != end_cell) && (cell_pos == list_pos->end())  )
            {
                list_pos++;
                cell_pos = list_pos->begin();
            }

            return *this;

        }
        self_type operator++(int junk)
        {
            return this->operator++();
        }
        reference operator*()
        {
            return cell_pos.operator*();
        }
        pointer operator->()
        {
            return cell_pos.operator->();
        }
        bool operator==(const self_type& rhs)
        {
            return cell_pos == rhs.cell_pos;
        }
        bool operator!=(const self_type& rhs)
        {
            return cell_pos != rhs.cell_pos;
        }
    private:

        void nextOccupy()
        {
          while (  (list_pos != end_cell) && (cell_pos == list_pos->end())  )
          {
              list_pos++;
              cell_pos = list_pos->begin();
          }
        }

        listT * list_pos;
        pointer cell_pos;
        listT * end_cell;
    };

    class const_iterator
    {
    public:
        typedef const_iterator self_type;
        typedef pairT value_type;
        typedef pairT& reference;
        typedef iteratorT pointer;
        typedef std::forward_iterator_tag iterator_category;
        typedef int difference_type;
        const_iterator(listT * ptr, listT * ptr_end) : list_pos(ptr), cell_pos(ptr->begin()), end_cell(ptr_end)
        {
            nextOccupy();
        }
        self_type operator++()
        {
          cell_pos++;

          while (  (list_pos != end_cell) && (cell_pos == list_pos->end())  )
          {
              list_pos++;
              cell_pos = list_pos->begin();
          }

          return *this;
        }
        self_type operator++(int junk)
        {
          return this->operator++();
        }
        const reference operator*()
        {
          return cell_pos.operator*();
        }
        const pointer operator->()
        {
          return cell_pos.operator->();
      }
      bool operator==(const self_type& rhs)
      {
          return cell_pos == rhs.cell_pos;
      }
      bool operator!=(const self_type& rhs)
      {
          return cell_pos != rhs.cell_pos;
      }
    private:
        void nextOccupy()
        {
            while (  (list_pos != end_cell) && (cell_pos == list_pos->end())  )
            {
                list_pos++;
                cell_pos = list_pos->begin();
            }
        }


      listT * list_pos;
      pointer cell_pos;
      listT * end_cell;
    };


    iterator begin()
    {
        return iterator(this->table, this->table + this->cells);
    }

    iterator end()
    {
        return iterator(this->table + this->cells, this->table + this->cells);
    }

    const_iterator begin() const
    {
        return const_iterator(this->table , this->table + this->cells);
    }

    const_iterator end() const
    {
        return const_iterator(this->table + this->cells, this->table + this->cells);
    }


    const_iterator cbegin() const
    {
        return const_iterator(this->table , this->table + this->cells);
    }

    const_iterator cend() const
    {
        return const_iterator(this->table + this->cells, this->table + this->cells);
    }


     bool operator==(const HashMap<keyT, valueT>& hashtable) const {
        for ( const auto& it : hashtable )
        {
            if ( !this->containsKey( it.first ) )
            {
                return false;
            }
            if ( this->at( it.first ) != it.second )
            {
                return false;
            }
        }

         for ( const auto& it : *this )
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

        for ( const auto& it : hashtable )
        {
            if ( !this->containsKey( it.first ) )
            {
                return true;
            }

            if ( this->at( it.first ) != it.second )
            {
                return true;
            }
        }

         for ( const auto& it : *this )
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

};
