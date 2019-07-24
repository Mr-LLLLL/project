#ifndef SALES_DATA_H
#define SALES_DATA_H

struct Sales_data {
	// class's member
	std::string bookNo;
	unsigned int units_sold = 0;
	double revenue = 0.0;

	// function
	std::string isbn() const {
		return bookNo;
	}

	Sales_data& combine(const Sales_data&);
	double avg_price() const;

};

// Sales_data's interface
Sales_data add(const Sales_data&, const Sales_data&);
std::ostream &print(std::ostream&, const Sales_data&);
std::istream &read(std::istream&, const Sales_data&); 
#endif