#pragma once

#include <iostream>

class aPolygon
{
protected:
  int n;      //number of edges
  double *l;  //length of edge
  void set_name(const char *s);
private:
  char *name; //name of class, for demo purposes
  aPolygon();   //don't want to allow a Polygon with less than 3 edges
public:
  aPolygon(const int ne); //builds a polygon with ne edges
  aPolygon(const aPolygon& rhs);
  virtual ~aPolygon();
  aPolygon& operator=(const aPolygon& rhs);

  double Edges() const;
  double operator[](int i) const;    //read_only operator[]. could be changed to read-write, but there is no possibility to check if length is <= 0

  virtual void setLength(const int edge_no, const double length);

  virtual double Perimeter() const;
  virtual double Area() const = 0;  //pure virtual area
  
  friend std::ostream& operator<<(std::ostream& out, const aPolygon& rhs);
};

class aTriangle : public aPolygon
{
public:
  aTriangle();
  aTriangle(const double a, const double b, const double c);
  
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Woverloaded-virtual"
  /* 
    disable overload-virtual warning, because here we intend to
    inherit the virtual function from aPolygon without overloading it,
    and also build another overload function for ease of use
  */
  void setLength(const double a, const double b, const double c);
  #pragma clang diagnostic pop
  
  
  double Area() const;

  bool isRight() const;       //if has right angle
  bool isIsosceles() const;
  bool isEquilateral() const;
};

class aRectangle : public aPolygon
{
public:
  aRectangle();
  aRectangle(const double side0, const double side1);

  virtual void setLength(const int edge_no, const double length); //overload so if it changes one edge, it automatically changes the other
  void setLength(const double side0, const double side1);
  
  virtual double Perimeter() const;    //a more efficient perimeter calculation
  double Area() const;    
  
  bool isSquare();
};

class aSquare : public aRectangle
{
  void setLength(const double side0, const double side1); //mask this one
public:
  aSquare();
  aSquare(const double length);

  void setLength(const int edge_no, const double length); //overload so if it changes one edge, it automatically changes every other
  void setLength(const double length);

  double Perimeter() const;    //an even more efficient perimeter calculation
};
