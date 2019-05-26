Programming 4 - Engine - DigDug - Maris Arne 2DAE07

----------------------------------------------
Git Link:

----------------------------------------------
----------------------------------------------
Design choises, patterns and extra info:

- GameObject and Components: 
	~ Make gameObjects (barely any functionallity except it holds components)
	~ These components hold the functionallity, you can add as many components as you want (Some may not be twice on a gameObjects (automatic check + warning log)
	~ Build you game using different gameObjects
	~ Handy extra: Prefabs (premade gameObjects in a way), Prefabs have a GameObject pointer where you add all your components on, these prefabs can more easily be added and duplicated in your scenes

- Scenes:
	~ The game exist out of multiple (or a single) scene, These scene are added and made by the user
	~ The SceneManager has 1 GlobalScene, a scene that starts when the game starts and ends when the game closes (handy to put managers, menu, etc in it)
	~ Other scenes get initialized when they are loaded (needed) and cleaned when exiting (Eliminates super long startup times when you have a lot of scenes)

- FlyWeight pattern:
	~ Most resources (textures, fonts, svg files) are held in suitable containers outside the gameObjects, the gameObjects just acces these textures etc
 	~ This elimates duplicate resources (massive memory footprint) and makes sure the renderer has all its resources easily available

- Command pattern:
	~ Used for input-, Collision-Responses
	~ Input: `User adds inputActions to the InputComponent, these actions have a Response class and an inputaction (key, controllerButton, controllerStick)
		 `These inputActions will automatically call overriden methods inside your Response class (OnPress, OnRelease, OnHold)
	~ Collision: `Same principle as input but uses the ColliderComponent where you add CollisionResponse classes, calls methods OnCollisionEnter and OnCollisionExit

- State pattern:
	~ StateMachineComponent holds different states and stateTransitions:
	~ Add your derived State classes to the StateMachineComponent
	~ The Statemachine will now call overriden methods OnStateEnter, OnStateExit and InState
	~ States can be switched manually using the SetState and TryTransitionToState methods on the StateMachineComponent
	~ States can also be switched with stateTransitions, these transitions use a Input-, Collision- or Animation-Response
	~ StateTranstions need to be added in the stateMachine and can be a SetState (no condition) or a TryTranstitionToState (must be in certain state before you can go to the other one)

- Observer pattern:
	~ Used to couple the StateTranstions (Observers) to the Responses (Subjects)
	~ If there is a StateMachineComponent all the responses add the stateTransitions as their observers
	~ When the input, collision or animationResponse is triggered they notify their observers (the stateTransitions)
	~ These stateTranstions than check the notify and change the state accordingly

- Gridlevel:
	~ Easy to use GridLevel class with own save file structure (also easily editable)
	~ GridLevel builds your level using tiles you have configured
	~ Tiles can have a Texture, rotation, sizeOffset, and even the Option to directly spawn Prefabs on them
	~ Tiles can change texture and or rotate based on the amount of connections they have (Usefull for tunnels, roads etc)
	~ GridLevels are added to your scene and will be loaded and unloaded with the scene

- Multi-threaded Pathfinding:
	~ When adding an AiComponent to a gameObject you enable it to use pathfinding
	~ This pathfinding can be any grid pathfinding algorithm (only A* in engine atm)
	~ The pathfinding algorithm runs in a seperate thread and updates the path once its calculations are done
	~ This ensures your game doesnt run slower when you have a lot of enemies that use pathfinding

- Component explenation:
	~ TransformComponent: MoveToPos(pos, speed), Run smoothly to this position with a certain speed
	~ PhysicsBodyComponent: Component that enables your gameObject to work with Box2D physics API, easy to use interface for the b2Body
	~ ColliderCompononent: Component that enables collision on your gameObject, Also works with the Box2D physics API, easy to use interface to add b2Shapes (collisionShapes)
	~ AnimatedSpriteComponent: Component that holds your spritesheet, can play different parts, add animationClips (row, column limits, speed etc) to easily play different parts of the sheet

- Other:
	~ Box2D and Imgui are implemented in the engine and can be used by the user
	~ Currently only a logger with Imgui but the user can freely use all the functionality ImGui offers
	~ Currently only the physicsBody and Collision from Box2D used but there is the option for the user to work with the Box2D-API (Whole box2D is added)
	~ Everything is build so the engine can be easily expanded and with the proper knowledge Box2D can be used to make interesting physics games
	
---------------------------------------