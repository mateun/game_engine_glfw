

// Some reflection macros

#define GAMEOBJECT_DEF(className) \
	className##* instantiate##className () { \
		return new className##();
	} \