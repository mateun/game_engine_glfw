#include <string>
#include <map>
#include <vector>
#include <string>
#include "component.h"


/**
 * Represents an object within the game. 
 * 
 * They can have different components in addition: 
 *		- Mesh
 *		- BoundingBox 
 *		- LogicComponents
 *		- etc.
 */
class GameObject {
	
public:
	GameObject(const std::string& name);

private:
	std::string _name;
	std::vector<Component> _components;

};

