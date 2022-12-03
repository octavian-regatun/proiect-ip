namespace my
{
enum ScreenType
{
	Start,
	FirstImage,
	SecondImage,
	Morphing,
	End
};

class Screen
{
public:
	static ScreenType currentScreen;
	static void nextScreen();
	static void previousScreen();
	static void goToScreen(ScreenType screen);
};
}
