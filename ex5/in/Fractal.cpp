#include <functional>
#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <vector>
#include "Fractal.h"


Point Point::relaitve(Point & other, BitMap & bitmap, int deep){
    return Point(
      this->x + other.x*std::pow(bitmap.width, deep-1),
      this->y + other.y*std::pow(bitmap.height, deep-1),
       other.chart);
}

Point Point::operator+( Point const &other ) {
  return Point(this->x + other.x, this->y + other.y, other.chart);
}
Point * BitMap::begin() {
  return this->points;
}
Point * BitMap::end() {
  return &this->points[this->width * this->height - 1];
}

void Fractal::draw(Point & p, Point & p_prime, outVec & out) {
  out[ p.y ][ p.x ] = p_prime.chart;
}

void Fractal::draw(Point & p, BitMap & bitmap, BitMap & empty, int deep, outVec & out) {
  Point * p_prime = bitmap.begin();
  if (!deep) {

    Point temp = p.relaitve(*p_prime, bitmap, deep);
     Fractal::draw(temp, *p_prime, out);
  }
  else {
    for ( ;
     p_prime <= bitmap.end(); p_prime++ ) {
       Point temp = p.relaitve(*p_prime, bitmap, deep);
       if ( temp.chart != ' ')
        Fractal::draw(temp, bitmap, empty, deep - 1, out);
      else
        Fractal::draw(temp, empty, empty, deep - 1, out);
     }
  }
}

BitMap createEmptyBitMap(BitMap & bitmap) {
  Point * empty_points = new Point[ bitmap.height * bitmap.width ];
  for (int i = 0 ; i < bitmap.height; i++)
    for (int j = 0 ; j < bitmap.width; j++)
      empty_points[i*bitmap.height + j] = Point(i,j, ' ');
  return BitMap(bitmap.width, bitmap.height, empty_points);
}

void PrintFractal(outVec out) {
  for ( auto i = out.begin(); i !=  out.end();) {
    for ( auto j = (*i).begin(); j !=  (*i).end() ; j++) {
        std::cout << (*j);
    }
    i++;
    if ( i != out.end() ) {
        std::cout << '\n';
    }
  }
}

void Fractal::draw(BitMap & bitmap ,int deep){
    BitMap empty = createEmptyBitMap(bitmap);
    outVec out;
    out.resize(std::pow(bitmap.height, deep));

    for ( auto i = out.begin(); i !=  out.end() ; i++)
      (*i).resize(std::pow(bitmap.width, deep));

    Point begin_point (0,0, ' ');
    Fractal::draw(begin_point, bitmap, empty, deep, out);

    PrintFractal(out);
}
