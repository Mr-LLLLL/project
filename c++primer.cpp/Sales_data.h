#ifndef SALES_DATA_H
#define SALES_DATA_H
class Sales_data {
	friend Sales_data add(const Sales_data&, const Sales_data&);
	friend std::ostream &print(std::ostream&, const Sales_data&);
	friend std::istream &read(std::istream&, Sales_data&);
	friend std::ostream &operator<<(std::ostream &os, const Sales_data &item);
	friend std::istream &operator >> (std::istream &is, Sales_data &item);
	friend Sales_data operator+(const Sales_data &lhs, const Sales_data &rhs);
	friend bool operator==(const Sales_data &lhs, const Sales_data &rhs);
	friend bool operator!=(const Sales_data &lhs, const Sales_data &rhs);
public:
	//constructot
	Sales_data();
	explicit Sales_data(const std::string &s);
	Sales_data(const std::string &s, unsigned n, double p);
	explicit Sales_data(std::istream &);
	// copy constructor
	Sales_data(const Sales_data &orig);
	// move constructor
	Sales_data(Sales_data &&rhs) noexcept;
	// copy assignment operator
	Sales_data& operator=(const Sales_data &rhs) &;
	// move assignment operator
	Sales_data& operator=(Sales_data &&rhs) & noexcept ;
	Sales_data& operator=(const std::string &s);
	// destructor
	~Sales_data() { }
	// function
	std::string isbn() const;
	Sales_data& combine(const Sales_data&);
	double avg_price() const;
	Sales_data& operator+=(const Sales_data &rhs);
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

// constructor
inline
Sales_data::Sales_data(std::istream &is) {
	read(is, *this);
}

inline
Sales_data::Sales_data() : bookNo(), units_sold(0), revenue(0.0) {}

inline
Sales_data::Sales_data(const std::string &s) : bookNo(s) {}

inline
Sales_data::Sales_data(const std::string &s, unsigned n, double p) : bookNo(s), units_sold(n), revenue(p * n) {}

// copy constructor
inline
Sales_data::Sales_data(const Sales_data &orig) : bookNo(orig.bookNo), units_sold(orig.units_sold), revenue(orig.revenue) {}

//move constructor
inline
Sales_data::Sales_data(Sales_data &&rhs) noexcept : bookNo(std::move(rhs.bookNo)), units_sold(rhs.units_sold), revenue(rhs.revenue) {}

//move assignment operator
inline
Sales_data &Sales_data::operator=(Sales_data &&rhs) & noexcept {
	if (this != &rhs) {
		bookNo = std::move(rhs.bookNo);
		units_sold = rhs.units_sold;
		revenue = rhs.revenue;
	}
	return *this;
}

// copy assignment operator
inline
Sales_data &Sales_data::operator=(const Sales_data &rhs) & {
	bookNo = rhs.bookNo;
	units_sold = rhs.units_sold;
	revenue = rhs.revenue;
	return *this;
}

inline
Sales_data& Sales_data::operator=(const std::string &isbn) {
	bookNo = isbn;
	return *this;
}

// function
inline
std::string Sales_data::isbn() const {
	return bookNo;
}

#endif