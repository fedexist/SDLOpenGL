#include "stdafx.h"
#include "PathFinder.h"

std::vector<GLint*> PathFinder::map = std::vector<GLint*>();
unsigned int PathFinder::height, PathFinder::width = 0;

PathFinder::PathFinder()
{
	//Fuoco = 0
	objectToCost.put(0,8);
	//Spawner = 1
	objectToCost.put(1,1);
	//Chest = 3
	objectToCost.put(3,1);
}


PathFinder::~PathFinder()
{
}

vector< NodeDirection > PathFinder::findPath(glm::vec2 start, glm::vec2 goal)
{
	AStarSearch<MapSearchNode> astarsearch;

	unsigned int SearchCount = 0;

	const unsigned int NumSearches = 2;

		while(SearchCount < NumSearches)
	{

			//SDL_LogDebug(0, "Start from: %f, %f", start.x, start.y);
			//SDL_LogDebug(0, "Goal is: %f, %f", goal.x, goal.y);
		// Create a start state
		MapSearchNode nodeStart;
		nodeStart.x = start.x;
		nodeStart.y = start.y; 

		// Define the goal state
		MapSearchNode nodeEnd;
		nodeEnd.x = goal.x;						
		nodeEnd.y = goal.y; 
		
		// Set Start and goal states
		
		astarsearch.SetStartAndGoalStates( nodeStart, nodeEnd );

		unsigned int SearchState;
		unsigned int SearchSteps = 0;

		do
		{
			SearchState = astarsearch.SearchStep();

			SearchSteps++;

	#if DEBUG_LISTS

			cout << "Steps:" << SearchSteps << "\n";

			int len = 0;

			cout << "Open:\n";
			MapSearchNode *p = astarsearch.GetOpenListStart();
			while( p )
			{
				len++;
	#if !DEBUG_LIST_LENGTHS_ONLY			
				((MapSearchNode *)p)->PrintNodeInfo();
	#endif
				p = astarsearch.GetOpenListNext();
				
			}

			cout << "Open list has " << len << " nodes\n";

			len = 0;

			cout << "Closed:\n";
			p = astarsearch.GetClosedListStart();
			while( p )
			{
				len++;
	#if !DEBUG_LIST_LENGTHS_ONLY			
				p->PrintNodeInfo();
	#endif			
				p = astarsearch.GetClosedListNext();
			}

			cout << "Closed list has " << len << " nodes\n";
	#endif

		}
		while( SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SEARCHING );

		//SDL_LogDebug(0, "Searchsteps: %d", SearchSteps);

		if( SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SUCCEEDED )
		{
			//SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Search found goal state" ) ;

			vector<NodeDirection> solution;
			MapSearchNode *node = astarsearch.GetSolutionStart();

			#if DISPLAY_SOLUTION
				SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION,  "Displaying solution");
				node->PrintNodeInfo();
			#endif
			int steps = 0;

			NodeDirection firstNode;
			firstNode.first = glm::vec2(node->x, node->y);
			firstNode.second = glm::vec2(-1, -1);

			solution.push_back(firstNode);
			
			for( ;; )
			{
				node = astarsearch.GetSolutionNext();

				if( !node )
					break;
				
				NodeDirection previousNode = solution.back();


				glm::vec2 direction = glm::vec2(-1.0, -1.0);

				if (static_cast<int>(previousNode.first.x) > node->x)
					direction.x = LEFT;
				else if (static_cast<int>(previousNode.first.x) < node->x)
					direction.x = RIGHT;

				if (static_cast<int>(previousNode.first.y) > node->y)
					direction.y = DOWN;
				else if (static_cast<int>(previousNode.first.y) < node->y)
					direction.y = UP;


				NodeDirection node_direction;
				node_direction.first = glm::vec2(node->x, node->y);
				node_direction.second = direction;
				solution.push_back(node_direction);

				#if DISPLAY_SOLUTION
					node->PrintNodeInfo();
					SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION,"Direction: %f %f",direction.x, direction.y);
				#endif

				
				steps ++;
				
			};
			#if DISPLAY_SOLUTION
				SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Solution steps %d ", steps);
			#endif
			// Once you're done with the solution you can free the nodes up
			astarsearch.FreeSolutionNodes();
			return solution;

		}
		else if( SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_FAILED ) 
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Search terminated. Did not find goal state" ) ;
		
		}

		// Display the number of loops the search went through
		//SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "SearchSteps: %d ", SearchSteps);

		SearchCount ++;

		astarsearch.EnsureMemoryFreed();
	}

	return {};
}

void PathFinder::updateWorld(std::vector<GLint*> logicLevelMap, std::vector<GLint*> objectLevelMap, GLint H, GLint W)
{

	if (map.empty())
	{
		for (int i = 0; i < H; ++i)
		{
			PathFinder::map.push_back(new GLint[W]);
		}
		
	}

	//map.clear();
	map = logicLevelMap;
	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < W; j++)
		{
			//map[i][j] = logicLevelMap[i][j];
			if (logicLevelMap[i][j] > -1)
			{
				map[i][j] = 1;
				if (objectLevelMap[i][j]>-1)
				{
					map[i][j] = objectToCost.get(objectLevelMap[i][j]);
				}
			}
			else
			{
				map[i][j] = -1; 
			}
		}
	}

	width = W;
	height = H;
	/*
	string s = "";
	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < W; j++)
		{
			s += " " + std::to_string(map[i][j]);
		}
		s += "\n";
	}*/
	//SDL_LogDebug(1, s.c_str()); 

	//SDL_LogDebug(0, "width: %d, height: %d, %d", width, height, height - 1 - 1);

	//SDL_LogDebug(0, "(3, 1) cost is: %d", GetMap(3, 1));

	//SDL_LogDebug(0, "wrong (3, 1) cost is: %d", map[3][1]);
}

bool PathFinder::MapSearchNode::IsSameState( MapSearchNode &rhs )
{
	// same state in a maze search is simply when (x,y) are the same
	return x == rhs.x && y == rhs.y;
}

void PathFinder::MapSearchNode::PrintNodeInfo() const
{
	SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Node position : (%d,%d)\n", x,y );
}

// Here's the heuristic function that estimates the distance from a Node
// to the Goal. 

float PathFinder::MapSearchNode::GoalDistanceEstimate( MapSearchNode &nodeGoal )
{
	//Manhattan
	//return fabsf(x - nodeGoal.x) + fabsf(y - nodeGoal.y);	

	//Norma euclidea
	return SDL_sqrtf( powf(fabsf(x - nodeGoal.x), 2) + powf(fabsf(y - nodeGoal.y), 2));
}

bool PathFinder::MapSearchNode::IsGoal( MapSearchNode &nodeGoal )
{

	return x == nodeGoal.x && y == nodeGoal.y;

}

int PathFinder::GetMap(int x, int y)
{
	if (x < 0 || y < 0 || x > width || y > height)
		return -2;

	return map[height - y - 1][x];
}

// This generates the successors to the given Node. It uses a helper function called
// AddSuccessor to give the successors to the AStar class. The A* specific initialisation
// is done for each node internally, so here you just set the state information that
// is specific to the application
bool PathFinder::MapSearchNode::GetSuccessors( AStarSearch<MapSearchNode> *astarsearch, MapSearchNode *parent_node )
{

	int parent_x = -1; 
	int parent_y = -1; 

	if( parent_node )
	{
		parent_x = parent_node->x;
		parent_y = parent_node->y;
	}
	

	MapSearchNode NewNode;

	// push each possible move except allowing the search to go backwards

	if( (GetMap( x-1, y ) != -1) 
		&& !((parent_x == x-1) && (parent_y == y))
	  ) 
	{
		NewNode = MapSearchNode( x-1, y );
		astarsearch->AddSuccessor( NewNode );
	}	

	if( (GetMap( x, y-1 ) != -1) 
		&& !((parent_x == x) && (parent_y == y-1))
	  ) 
	{
		NewNode = MapSearchNode( x, y-1 );
		astarsearch->AddSuccessor( NewNode );
	}	

	if( (GetMap( x+1, y ) != -1)
		&& !((parent_x == x+1) && (parent_y == y))
	  ) 
	{
		NewNode = MapSearchNode( x+1, y );
		astarsearch->AddSuccessor( NewNode );
	}	

		
	if( (GetMap( x, y+1 ) != -1) 
		&& !((parent_x == x) && (parent_y == y+1))
		)
	{
		NewNode = MapSearchNode( x, y+1 );
		astarsearch->AddSuccessor( NewNode );
	}

	//Successori diagonali


	if( (GetMap( x+1, y+1 ) != -1) 
		&& !((parent_x == x+1) && (parent_y == y+1))
		)
	{
		NewNode = MapSearchNode( x+1, y+1 );
		astarsearch->AddSuccessor( NewNode );
	}

	if( (GetMap( x-1, y-1 ) != -1) 
		&& !((parent_x == x-1) && (parent_y == y-1))
		)
	{
		NewNode = MapSearchNode( x-1, y-1 );
		astarsearch->AddSuccessor( NewNode );
	}

	if( (GetMap( x-1, y+1 ) != -1) 
		&& !((parent_x == x-1) && (parent_y == y+1))
		)
	{
		NewNode = MapSearchNode( x-1, y+1 );
		astarsearch->AddSuccessor( NewNode );
	}

	if( (GetMap( x+1, y-1 ) != -1) 
		&& !((parent_x == x+1) && (parent_y == y-1))
		)
	{
		NewNode = MapSearchNode( x+1, y-1 );
		astarsearch->AddSuccessor( NewNode );
	}

	return true;
}

// given this node, what does it cost to move to successor. In the case
// of our map the answer is the map terrain value at this node since that is 
// conceptually where we're moving

float PathFinder::MapSearchNode::GetCost( MapSearchNode &successor )
{
	//SDL_LogDebug(0, "Cost is: %f", static_cast<float>(GetMap(x, y)));
	return static_cast<float>(GetMap(x, y));

}
