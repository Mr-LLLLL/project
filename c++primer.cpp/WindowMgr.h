#ifndef WINDOWMGR_H
#define WINDOWMGR_H
	
class WindowMgr {
public:
	using ScreenIndex = std::vector<Screen>::size_type;
	ScreenIndex addScreen(const Screen&);
	void clear(ScreenIndex);
private:
	std::vector<Screen> screens{ Screen(24, 80, ' ') };
};

inline
WindowMgr::ScreenIndex WindowMgr::addScreen(const Screen &s) {
	screens.push_back(s);
	return screens.size() - 1;
}
inline
void WindowMgr::clear(ScreenIndex i) {
	Screen &s = screens[i];
	s.contents = std::string(s.height * s.width, ' ');
}
#endif