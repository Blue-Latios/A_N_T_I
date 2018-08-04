#ifndef LISTS_HPP
#define LISTS_HPP

#include <list>
using namespace std;

template <class Type>
class List { //Setiap elemennya unik
	private:
		list<Type> L; //List
		typename list<Type>::iterator I; //iterator
	public:
		List(); //ctor List kosong
		List(Type*, int); //ctor Masukan array dan konversi ke list
		List(const List<Type>&); //cctor
		virtual ~List(); //dtor
		List<Type>& operator=(const List<Type>&); //operator assignment
		
		//Methods
		int size() const; //Ukuran list
		void add(Type); //menambah ke belakang
		template <class Type2>
		void add(Type2); //menambah ke belakang (demi polymorphism)
		void remove(Type); //menghilangkan elemen t yang pertama muncul
		void removeAt(unsigned int); //menghilangkan elemen pada indeks
		void removeAll(); //menghilangkan semua elemen
		int find(Type); //Mencari list seolah-olah indeks array
		bool isEmpty() const; //Cek kekosongan list
		Type& operator[](unsigned int); //MinIdx = 0
		void setBegin(); //set iterator di awal
		void setBeginAt(unsigned int); //set iterator di suatu indeks
		Type& getIValue(); //ambil data pada iterator
		void next(); //inkremen iterator
};

#include "Lists.cpp"

#endif
