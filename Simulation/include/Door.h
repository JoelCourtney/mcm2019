#pragma once

class Door {
	int width;
	int used;

public:
	Door(int);

	bool canMove();
	void move();

	void reset();
};
