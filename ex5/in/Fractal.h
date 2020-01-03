#include <iostream>
#include <vector>




typedef class BitMap BitMap;

class Point {
public :
  long x , y;
  char chart;
  Point() {};
  Point(long x, long y, char chart) : x(x), y(y), chart(chart) {};
  Point operator + ( Point const &other );
  Point relaitve(Point & other, BitMap & bitmap, int deep);
};

class BitMap {
public:
  long width, height;
  Point * points = nullptr;
  BitMap(long width, long height, Point * points) :
    width(width), height(height), points(points) {

    };

    ~BitMap() {
        if (this->points != nullptr  )
        {
            delete [] this->points;
        }
        this->points = nullptr;
    }

  Point * begin();
  Point * end();
};

static BitMap SierpinskiCarpet = BitMap(3, 3,
  new Point[9]{
    Point(0,0,'#'),Point(1,0,'#'),Point(2,0,'#'),
    Point(0,1,'#'),Point(1,1,' '),Point(2,1,'#'),
    Point(0,2,'#'),Point(1,2,'#'),Point(2,2,'#')
  }
);
static BitMap SierpinskiSieve = BitMap(2, 2,
  new Point[4]{
    Point(0,0,'#'),Point(1,0,'#'),
    Point(0,1,'#'),Point(1,1,' ')
  }
);
static BitMap CantorDust = BitMap(3, 3,
  new Point[9]{
    Point(0,0,'#'),Point(1,0,' '),Point(2,0,'#'),
    Point(0,1,' '),Point(1,1,'#'),Point(2,1,' '),
    Point(0,2,'#'),Point(1,2,' '),Point(2,2,'#')
  }
);

static BitMap * fractals = new BitMap[3] {
  SierpinskiCarpet,
  SierpinskiSieve,
  CantorDust
};

typedef std::vector<std::vector<char>> outVec;


class Fractal {
private:
  static void draw(Point & p, Point & p_prime, outVec & out);
  static void draw(Point & p, BitMap & bitmap, BitMap & empty, int deep, outVec & out);

public:
  static void draw(BitMap & bitmap ,int deep);
};
