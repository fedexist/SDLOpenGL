#pragma once
#include <stlastar.h>
#include <fsa.h>

#define DEBUG_LISTS false;
#define DEBUG_LIST_LENGTHS_ONLY false;
#define DISPLAY_SOLUTION true;

typedef std::pair<glm::vec2, glm::vec2 > NodeDirection;

class PathFinder
{
	friend class AI;

	class MapSearchNode
	{
		public:
			static int x;	 // the (x,y) positions of the node
			static int y;	
	
			MapSearchNode() { x = y = 0; }
			MapSearchNode( int px, int py ) { x=px; y=py; }

			static float GoalDistanceEstimate( MapSearchNode &nodeGoal );
			static bool IsGoal( MapSearchNode &nodeGoal );
			static bool GetSuccessors( AStarSearch<MapSearchNode> *astarsearch, MapSearchNode *parent_node );
			static float GetCost( MapSearchNode &successor );
			bool IsSameState( MapSearchNode &rhs );

			void PrintNodeInfo() const; 
	};

public:
	PathFinder();
	~PathFinder();
	unsigned int width, height;
	std::vector<GLint*> map;
	static std::vector< NodeDirection > findPath(glm::vec2 start, glm::vec2 goal);
	static void updateWorld();
};

