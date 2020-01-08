#include <functional>
#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <vector>
#include "Fractal.h"

const int ONEDEGREE = 1;
const int ZERO      = 0;
//const char SPACE    = ' ';

/*
 *  relaitve - scaling the coordinates of the point, relative to
 *  the recursion deep.
 *  @return the scaling the coordinates.
 */
Point Point::relaitve(Point & other, BitMap & bitmap, int deep)
{
        return Point(
                this->x + other.x*std::pow(bitmap.width, deep-ONEDEGREE),
                this->y + other.y*std::pow(bitmap.height, deep-ONEDEGREE),
                other.chart);
}
/**
 * Point::operator+ , return the vectors addition of the point with
 * other given point.
 * @param other the given point which will determinate the hist.
 * @return new point which it's coordinates are the summing of the
 * pair of the points.
 */
Point Point::operator+( Point const &other )
{
        return Point(this->x + other.x, this->y + other.y, other.chart);
}
/**
 * BitMap::begin() return a pointer to the points segment.
 * @return return a pointer to the points segment.
 */
Point * BitMap::begin()
{
        return this->points;
}
/**
 * BitMap::end() return a pointer to the ends of the points segment.
 * @return a pointer to the ends of the points segment.
 */
Point * BitMap::end() {
        return &this->points[this->width * this->height - ONEDEGREE];
}
/**
 * Fractal::draw, assigment a value to specific location in the
 * the output vector.
 * @param p point which holds the coordinate of the location, which will be
 *  setted.
 * @param p_prime the original point in the bitmap when deep equals zero.
 * @param out the output vector which in the end will printed.
 */
void Fractal::draw(Point & p, Point & p_prime, outVec & out)
{
        out[ p.y ][ p.x ] = p_prime.chart;
}
/**
 * Fractal::draw - the core method, getting dawn in recursion, and print the
 * given bitmap in the finally stage.
 * @param p - the hist which we start to draw from, used to determinate the global
 * location of the cursor.
 * @param bitmap - the given bitmap to print.
 * @param empty - passing an empty bitmap, which will be used to draw spaces in the
 * output vector.
 * @param deep the depth of the recursion.
 * @param out - a vector which will holds the the values that will be printed to the screen.
 */
void Fractal::draw(Point & p, BitMap & bitmap, BitMap & empty, int deep, outVec & out)
{
        Point * p_prime = bitmap.begin();
        if (!deep)
        {
                Point temp = p.relaitve(*p_prime, bitmap, deep);
                Fractal::draw(temp, *p_prime, out);
        }
        else
        {
                for (; p_prime <= bitmap.end(); p_prime++ )
                {
                        Point temp = p.relaitve(*p_prime, bitmap, deep);
                        if ( temp.chart != SPACE)
                        {
                                Fractal::draw(temp, bitmap, empty, deep - ONEDEGREE, out);
                        }
                        else
                        {
                                Fractal::draw(temp, empty, empty, deep - ONEDEGREE, out);
                        }
                }
        }
}
/**
 * createEmptyBitMap returns an empty bitmap filled with only spaces.
 * @param bitmap - an reference to other bitmap with willed shape.
 * @return the empty bitmap.
 */
BitMap createEmptyBitMap(BitMap & bitmap) {
        Point * empty_points = new Point[ bitmap.height * bitmap.width ];
        for (int i = 0; i < bitmap.height; i++)
        {
                for (int j = 0; j < bitmap.width; j++)
                {
                        empty_points[i * bitmap.height + j] = Point(i, j, SPACE);
                }
        }
        return BitMap(bitmap.width, bitmap.height, empty_points);
}
/**
 * PrintFractal - printing the output vector.
 * @param out - the vector which will be printed.
 */
void PrintFractal(outVec out)
{
        for ( auto i = out.begin(); i !=  out.end();)
        {
                for ( auto j = (*i).begin(); j !=  (*i).end(); j++)
                {
                        std::cout << (*j);
                }
                i++;
                if ( i != out.end() )
                {
                        std::cout << std::endl;
                }
        }
}
/**
 * Fractal::draw manging the flow, first initializing the output vector,
 * the filling him by calling to the recursive draw function, then printing
 * the fractal by calling to printFractal method.
 * @param bitmap the given fractal to print.
 * @param deep the depth of the recursion.
 */
void Fractal::draw(BitMap & bitmap,int deep)
{
        BitMap empty = createEmptyBitMap(bitmap);
        outVec out;
        out.resize(std::pow(bitmap.height, deep));

        for (auto i = out.begin(); i != out.end(); i++)
        {
                (*i).resize(std::pow(bitmap.width, deep));
        }
        Point begin_point (ZERO,ZERO, SPACE);
        Fractal::draw(begin_point, bitmap, empty, deep, out);

        PrintFractal(out);
}
