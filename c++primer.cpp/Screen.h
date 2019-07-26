#ifndef SCREEN_H
#define SCREEN_H

class Screen {
	friend class WindowMgr;
public:
	using pos = std::string::size_type;
	Screen() : Screen(0, 0) {}
	Screen(pos ht, pos wd, char c = ' ') : cursor(0), height(ht), width(wd), contents(ht * wd, c) {}
	char get(pos ht, pos wd) const;
	char get() const;
	Screen &move(pos r, pos c);
	void some_member() const;
	Screen &set(char);
	Screen &set(pos, pos, char);
	Screen &display(std::ostream &);
	const Screen &display(std::ostream &) const;
private:
	pos cursor;
	pos height, width;
	std::string contents;
	mutable size_t access_ctr;
	void do_display(std::ostream &) const;
};

inline
void Screen::do_display(std::ostream &os) const {
	os << contents;
}

inline
Screen &Screen::move(pos r, pos c) {
	pos row = r * width;
	cursor = row + c;
	return *this;
}

inline
char Screen::get(pos r, pos c) const {
	pos row = r * width;
	return contents[row + c];
}

inline
char Screen::get() const {
	return contents[cursor];
}

inline
void Screen::some_member() const {
	++access_ctr;
}

inline
Screen &Screen::set(char c) {
	contents[cursor] = c;
	return *this;
}

inline
Screen &Screen::set(pos r, pos col, char ch) {
	contents[r * width + col] = ch;
	return *this;
}

inline
Screen &Screen::display(std::ostream &os) {
	do_display(os);
	return *this;
}

inline
const Screen &Screen::display(std::ostream &os) const {
	do_display(os);
	return *this;
}
#endif