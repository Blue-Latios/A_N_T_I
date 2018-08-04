#include <iostream>
#include <fstream>

const char E = 'E';

template <class Type>
List<Type>::List() { //ctor List kosong
}

template <class Type>
List<Type>::List(Type* a, int size) { //ctor Masukan array dan konversi ke list
	for (int i = 0; i < size; i++)
		L.push_front(a[i]);
}

template <class Type>
List<Type>::List(const List<Type>& Li) { //cctor
	L = Li.L;
}

template <class Type>
List<Type>::~List() { //dtor
	L.clear();
}

template <class Type>
List<Type>& List<Type>::operator=(const List<Type>& Li) { //operator assignment
	this->L = Li.L;
	return *this;
}

template <class Type>
int List<Type>::size() const {
	return L.size();
}

template <class Type>
void List<Type>::add(Type t) { //menambah di belakang
	L.push_front(t);
}

template <class Type>
template <class Type2>
void List<Type>::add(Type2 t) { //menambah di belakang suatu type berbeda (possible error)
	L.push_front(t);
}

template <class Type>
void List<Type>::remove(Type t) { //menghilangkan elemen t yang pertama muncul
	unsigned int i = 0;
	typename list<Type>::iterator I = L.begin();
	while ((!(*I == t)) && (i < L.size())) {
		i++;
		I++;
	}
	if (*I == t)
		I = L.erase(I);
}

template <class Type>
void List<Type>::removeAt(unsigned int idx) { //menghilangkan elemen t yang pertama muncul
	try {
		if (idx >= L.size()) {
			throw E;
		} else {
			typename list<Type>::iterator I = L.begin();
			for (unsigned int i = 0; i < idx; i++)
				I++;
			I = L.erase(I);
		}
	} catch (const char E) {
		std::ofstream ErrFile;
		ErrFile.open("errlog.txt");
		ErrFile << "You are requesting an index outside list capacity (removeAt). Terminating..." << endl;
		ErrFile.close();
		exit(1);
	}
}

template <class Type>
void List<Type>::removeAll() {
	L.clear();
}

template <class Type>
int List<Type>::find(Type t) { //Mencari list seolah-olah indeks array
	unsigned int i = 0;
	typename list<Type>::iterator I = L.begin();
	while ((!(*I == t)) && (i < L.size())) {
		i++;
		I++;
	}
	if (*I == t)
		return i;
	else
		return -1; //return -1 apabila tidak ditemukan
}

template <class Type>
bool List<Type>::isEmpty() const {
	return L.empty();
}

template <class Type>
Type& List<Type>::operator [](unsigned int idx) { //MinIdx = 0
	try {
		if (idx >= L.size()) {
			throw E;
		} else {
			typename list<Type>::iterator I = L.begin();
			for (unsigned int i = 0; i < idx; i++)
				I++;
			return *I;
		}
	} catch (const char E) {
		std::ofstream ErrFile;
		ErrFile.open("errlog.txt");
		ErrFile << "You are requesting an index outside list capacity (get). Terminating..." << endl;
		ErrFile.close();
		exit(2);
	}
}
template <class Type>
void List<Type>::setBegin() { //Dipanggil apabila list tidak kosong
	I = L.begin();
}
template <class Type>
void List<Type>::setBeginAt(unsigned int idx) { //Dipanggil apabila list tidak kosong
	try {
		I = L.begin();
		advance(I, idx);
	 } catch (const char E) {
		std::ofstream ErrFile;
		ErrFile.open("errlog.txt");
		ErrFile << "You are requesting an index outside list capacity (setBeginAt). Terminating..." << endl;
		ErrFile.close();
		exit(3);
	}
}
template <class Type>
Type& List<Type>::getIValue() { //ambil data pada iterator
	return *I;
}
template <class Type>
void List<Type>::next(){
	I++;
}
template <class Type>
void List<Type>::removeIValue() { //remove elemen iterator
	I = L.erase(I);
}
template <class Type>
bool List<Type>::atEnd() const { //mengecek keadaan akhir
	return I == L.end();
}
