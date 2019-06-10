#ifndef __PATTERN_H__
#define __PATTERN_H__

class Singleton {
private:
	Singleton();
	Singleton(const Singleton&);
	Singleton& operator=(const Singleton&);

	static Singleton instance;

public:
	Singleton* Instance()
	{
		return &instance;
	}
};
Singleton Singleton::instance;

// Factory Method
class Factory {

};

class Product {

};

// Abstract Factory method



#endif