enum MyScreenEnum
{
	Start,
	FirstImage,
	SecondImage,
	Morphing,
	End
};

class MyScreen
{
public:
	static MyScreenEnum currentScreen;
	static void nextScreen();
	static void previousScreen();
	static void goToScreen(MyScreenEnum screen);
};
