#pragma once

class Door {
	int width;
	int used;

	int activeGroup;
	int bias;

public:
	Door(int);

	bool canMove(int);
	void move(int);

	void reset();
};
