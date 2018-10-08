#ifndef COMPONENTS_H
#define COMPONENTS_H
#include "ECS.h"
#include <string>

class MouseEventComponent {
public:
	static int x, y;
	static bool primaryButton, secondaryButton;
	static bool doubleClicks;
};

#endif // !COMPONENTS_H

