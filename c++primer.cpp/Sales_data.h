#ifndef SALES_DATA_H
#define SALES_DATA_H

class Sales_data {
friend Sales_data add(const Sales_data&, const Sales_data&);
friend std::ostream &print(std::ostream&, const Sales_data&);
friend std::istream &read(std::istream&, Sales_data&); 
public:
	//construct function
	Sales_data() : bookNo(), units_sold(0), revenue(0.0) {}
	Sales_data(const std::string &s) : bookNo(s) {}
	Sales_data(const std::string &s, unsigned n, double p) :
		bookNo(s), units_sold(n), revenue(p * n) {}
	Sales_data(std::istream &);

	// function
	std::string isbn() const {
		return bookNo;
	}
	Sales_data& combine(const Sales_data&);
	double avg_price() const;
private:
	// class's member
	std::string bookNo;
	unsigned int units_sold;
	double revenue;

};

// Sales_data's interface
Sales_data add(const Sales_data&, const Sales_data&);
std::ostream &print(std::ostream&, const Sales_data&);
std::istream &read(std::istream&, Sales_data&); 

// Sales_data's function
inline Sales_data::Sales_data(std::istream &is) {
	read(is, *this);
}
#endif