#pragma once
namespace DarennPathfinding {
	struct Vector2uc
	{
		unsigned char x;
		unsigned char y;

		bool operator==(const Vector2uc& rhs) const {
			return x == rhs.x && y == rhs.y;
		}
	};

	class Node
	{
	public:
		Vector2uc position;
		unsigned short g_cost;
		unsigned short h_cost;
		unsigned short f_cost;
		bool isTraversable;
		Node* parent;
	};
}