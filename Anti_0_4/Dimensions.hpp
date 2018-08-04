#ifndef DIMENSIONS_HPP
#define DIMENSIONS_HPP

class Dimensions { //Abstract class penyimpan ukuran dimensi
	private:
		static double width, height;
	public:
		Dimensions(); //ctor (unused)
		Dimensions(double w, double h); //ctor inisialisasi width dan depth
		virtual ~Dimensions();
		double getWidth() const; //mengembalikan max lebar (min = 0)
		double getHeight() const; //mengembalikan max kedalaman (min = 0)
};

#endif
