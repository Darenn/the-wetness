#include "ASCIITest.hpp"

void TestAscii()
{
	Window w;
	w.Open("A", 200, 200);

	w.Clear();

	w.Draw('H', 0x0E, 5, 0);
	w.Draw('i', 0x0E, 5, 1);
	w.Draw('!', 0x0E, 5, 2);
	w.Display();

	w.Draw('H', 0x0E, 8, 0);
	w.Draw('i', 0x0E, 8, 1);
	w.Draw('!', 0x0E, 8, 2);
	w.Display();

	system("pause");
}