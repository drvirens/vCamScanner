#ifndef VALUESTORAGE_H
#define VALUESTORAGE_H

class ValueStorage
{
public:
    typedef int Key;
    //viren: todo; put them in different cpp file
  
  int get(const int key);
  void set(const int key, const int value);
  
private:
  friend class System;
  
  int mKey;
  int mValue;
};

#if 0
class ValueStorage
{
public:
    //typedef int Key;
//viren: todo; put them in different cpp file

  static int get(const int key) {
    if (key == mKey) {
      return mValue;
    }
    return 0;
  }
  static void set(const int key, const int value) {
    mKey = key;
    mValue = value;
  }

private:
    friend class System;
  
  static int mKey;
  static int mValue;
};
#endif

#endif // VALUESTORAGE_H
