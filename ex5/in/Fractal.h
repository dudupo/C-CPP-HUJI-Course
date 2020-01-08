#include <iostream>
#include <vector>

const char SHARP = '#';
const char SPACE = ' ';
/**
 *  declering the bitmap, which will be defined later.
 */
typedef class BitMap BitMap;

/**
 * the point class, responsible to holds coordinate,
 * and scaling them relative to recursive depth.
 */
class Point
{
public:
long x, y;
char chart;
/**
 * basic constructor.
 */
Point()
{

};
/**
 * constructor.
 * @param x - the x coordinate.
 * @param y - the y coordinate.
 * @param chart the symbol of the point ( in our case sharp '#' or  space ' ' )
 */
Point(long x, long y, char chart) : x(x), y(y), chart(chart)
{

};

/**
 * Point::operator+ , return the vectors addition of the point with
 * other given point.
 * @param other the given point which will determinate the hist.
 * @return new point which it's coordinates are the summing of the
 * pair of the points.
 */
Point operator + ( Point const &other );
/*
 *  relaitve - scaling the coordinates of the point, relative to
 *  the recursion deep.
 *  @return the scaling the coordinates.
 */
Point relaitve(Point & other, BitMap & bitmap, int deep);
};


/**
 *  the Bitmap class holds the fractal in it's basic
 *  form ( depth zero )
 */
class BitMap
{
public:
long width, height;
Point * points = nullptr;

/**
 * constructor
 * @param width - the width of the bitmap.
 * @param height the height of the bitmap.
 * @param points array of points.
 */
BitMap(long width, long height, Point * points) :
        width(width), height(height), points(points)
{

};
/**
 *  destructor, responsible to relase the memmory.
 */
~BitMap()
{
        if (this->points != nullptr  )
        {
                delete [] this->points;
        }
        this->points = nullptr;
}

/**
 * BitMap::begin() return a pointer to the points segment.
 * @return return a pointer to the points segment.
 */
Point * begin();

/**
 * BitMap::end() return a pointer to the ends of the points segment.
 * @return a pointer to the ends of the points segment.
 */
Point * end();
};

static BitMap SierpinskiCarpet = BitMap(3, 3,
                                        new Point[9]{
        Point(0,0,SHARP),Point(1,0,SHARP),Point(2,0,SHARP),
        Point(0,1,SHARP),Point(1,1,SPACE),Point(2,1,SHARP),
        Point(0,2,SHARP),Point(1,2,SHARP),Point(2,2,SHARP)
}
                                        );
static BitMap SierpinskiSieve = BitMap(2, 2,
                                       new Point[4]{
        Point(0,0,SHARP),Point(1,0,SHARP),
        Point(0,1,SHARP),Point(1,1,SPACE)
}
                                       );
static BitMap CantorDust = BitMap(3, 3,
                                  new Point[9]{
        Point(0,0,SHARP),Point(1,0,SPACE),Point(2,0,SHARP),
        Point(0,1,SPACE),Point(1,1,SHARP),Point(2,1,SPACE),
        Point(0,2,SHARP),Point(1,2,SPACE),Point(2,2,SHARP)
}
                                  );

static BitMap * fractals = new BitMap[3] {
        SierpinskiCarpet,
        SierpinskiSieve,
        CantorDust
};

typedef std::vector<std::vector<char> > outVec;


class Fractal
{
private:
/**
 * Fractal::draw, assigment a value to specific location in the
 * the output vector.
 * @param p point which holds the coordinate of the location, which will be
 *  setted.
 * @param p_prime the original point in the bitmap when deep equals zero.
 * @param out the output vector which in the end will printed.
 */
static void draw(Point & p, Point & p_prime, outVec & out);
/**
 * Fractal::draw - the core method, getting dawn in recursion, and print the
 * given bitmap in the finally stage.
 * @param p - the hist which we start to draw from, used to determinate the
 *  global location of the cursor.
 * @param bitmap - the given bitmap to print.
 * @param empty - passing an empty bitmap, which will be used to draw spaces
 *  in the output vector.
 * @param deep the depth of the recursion.
 * @param out - a vector which will holds the the values that will be printed
 *  to the screen.
 */
static void draw(Point & p, BitMap & bitmap, BitMap & empty, int deep,
                 outVec & out);

public:
/**
 * Fractal::draw manging the flow, first initializing the output vector,
 * the filling him by calling to the recursive draw function, then printing
 * the fractal by calling to printFractal method.
 * @param bitmap the given fractal to print.
 * @param deep the depth of the recursion.
 */
static void draw(BitMap & bitmap,int deep);
};
