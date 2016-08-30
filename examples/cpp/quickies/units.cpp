
#include <iostream>

/**
 * Measure
 *
 * Generic class for anything that has a quantity and units.
 *
 */
class Measure
{
public:
  explicit Measure(double _v = 0) : v(_v) {}
  virtual ~Measure() {}

  void set(double _v) { v = _v; }
  double get() const { return v; }

  virtual const char * abbr() const = 0;

protected:
  virtual double getRatioToReference() const = 0;

private:
  double v;

};

/**
 * Length
 *
 * Measure for units of length.
 *
 * Subclass Meter is the reference unit for Length
 */
class Length : public Measure
{
public:
  explicit Length(double _v = 0) : Measure(_v) {}

  using Measure::set;
  void set(const Length & l)
  {
    l.get(*this);
  }
  
  using Measure::get;
  void get(Length & l) const
  {
    double scale = l.getRatioToReference() / this->getRatioToReference();
    l.set(this->get() * scale);
  }
};

/**
 * Conversions
 *
 * Helper class for converting between two conformable units.
 *
 * Each type of unit has a reference unit.  The Conversions class
 * should be specialized for each unit type.  The content of the
 * class should include a static function of signature
 *
 * <code>
 * static double getRatioToReference();
 * </code>
 *
 * This function returns the multiple of the unit to the reference
 * unit.
 */
template <typename T>
struct Conversions
{
};

class Meter;
class Foot;

template <>
struct Conversions<Meter>
{
  static double getRatioToReference() { return 1.0; }
};

template <>
struct Conversions<Foot>
{
  static double getRatioToReference() { return 3.2808399; }
};

class Meter : public Length
{
public:
  explicit Meter(double _v = 0) : Length(_v) {}
  Meter(const Length & _l) : Length(0.0) { this->set(_l); }

  const char * abbr() const
  {
    static const char * text = "m";
    return text;
  }

protected:
  double getRatioToReference() const { return Conversions<Meter>::getRatioToReference(); }
};

class Foot : public Length
{
public:
  Foot(double _v = 0) : Length(_v) {}
  Foot(const Length & _l) : Length(0.0) { this->set(_l); }

  const char * abbr() const
  {
    static const char * text = "ft";
    return text;
  }

protected:
  double getRatioToReference() const { return Conversions<Foot>::getRatioToReference(); }
};

class Inch : public Length
{
public:
  Inch(double _v = 0) : Length(_v) {}
  Inch(const Length & _l) : Length(0.0) { this->set(_l); }

  const char * abbr() const
  {
    static const char * text = "in";
    return text;
  }

protected:
  double getRatioToReference() const { return 12.0 * Conversions<Foot>::getRatioToReference(); }
};

template <typename OS>
OS & operator<<(OS & os, const Measure & m)
{
  os << m.get() << " " << m.abbr();
  return os;
}

int main(int argc, char ** argv)
{
  Meter h(1.9);
  Foot f(h);
  Inch i(h);
  std::cout << h << std::endl;
  std::cout << f << std::endl;
  std::cout << i << std::endl;

  Foot mile(5280.00);
  Meter mile_m(mile);
  mile.get(mile_m);
  std::cout << mile << std::endl;
  std::cout << mile_m << std::endl;

  Inch me(72.0);
  Meter me_m(me);
  std::cout << me_m << std::endl;
}
