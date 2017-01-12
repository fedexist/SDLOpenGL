#pragma once
#include "astar-algorithm/stlastar.h"


#define DEBUG_LISTS 0;
#define DEBUG_LIST_LENGTHS_ONLY 0;
#define DISPLAY_SOLUTION 0;

typedef std::pair<glm::vec2, glm::vec2 > NodeDirection;

class PathFinder
{
	friend class AI;

	class MapSearchNode
	{
		public:
			int x;	 // the (x,y) positions of the node
			int y;	
	
			MapSearchNode() { x = y = 0; }
			MapSearchNode( int px, int py ) { x=px; y=py; }

			float GoalDistanceEstimate( MapSearchNode &nodeGoal );
			bool IsGoal( MapSearchNode &nodeGoal );
			bool GetSuccessors( AStarSearch<MapSearchNode> *astarsearch, MapSearchNode *parent_node );
			float GetCost( MapSearchNode &successor );
			bool IsSameState( MapSearchNode &rhs );

			void PrintNodeInfo() const; 
	};

public:
	PathFinder();
	~PathFinder();
	unsigned int width, height;
	static std::vector<GLint*> map;
	std::vector< NodeDirection > findPath(glm::vec2 start, glm::vec2 goal);
	void updateWorld(std::vector<GLint*> logicLevelMap, std::vector<GLint*> objectLevelMap, GLint H, GLint W);
	Hashtable<unsigned int, unsigned int> objectToCost;
	static int GetMap(int x, int y);
};

