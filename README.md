# DOMSim
Data-Oriented Missile Simulation

# Description
DOMSim is a two-stage, ballistic missile simulation that has been built primarily following data-oriented software design techniques. The core functionality utilizes a data-oriented Entity Component System, component based objects, and the idea of existential processing in order to limit the number and size of data objects in memory. Limiting these allows for more efficient use of CPU cache memory which ultimately improves software performance.

# Execution 
The simulation is managed by the Simulation class. This class handles the interactions between Systems and Component Managers, it is the executive data manager of a simulation run. The Simulation object handles the execution of algorithms, as well as registration of entities and components with Systems and Component Managers.
The order of algorithm execution is user-defined (using configuration files) and sequential; all algorithms run in the order they are defined, and one at a time. Doing so allows for efficient use of the instruction cache, as well as ensuring that each simulation run is deterministic and repeatable.

# Simulation Configuration
Simulation configuration is handled through the configuration files (TBD) prior to starting a simulation run.

# Components
Components are intended to be small groups of plain-old-data (POD) structures limited to only the data necesary to comprise a component.

For example:
```
class PhysicalObject {
  double mass;
  Matrix inertiaTensor;
  double position;
  Quaternion orientation;
  double velocity;
  double angularVelocity;
  double acceleration;
  double angularAcceleration;
}
```

Might be broken down into components in the following way.
```
struct MassComponent {
  double mass;
  Matrix inertiaTensor;
}

struct TransformComponent {
  double position;
  Quaternion orientation;
}

struct MovementComponent {
  double velocity;
  double angularVelocity;
  double acceleration;
  double angularAcceleration;
}
```

This allows alogrithms to load less unnecessary data from main memory into RAM or cache memory, which in turn allows for faster processing of algorithms.
The component data is then managed efficiently for tightly packed, non-fragmented storage by Component Managers, further increasing runtime performance.

<b>NOTE: For each component type (MassComponent, MovementComponent, etc.) there should be an associated component manager type (MassManager, MovementManager, etc.).</b>

# Component Management
Component Managers keep the component data tightly stored in memory. When data is tightly packed, the CPU can accurately pre-fetch data that is soon to be used allowing for cache lines to be more efficiently used. An example of how component management works is illustrated below.

![ComponentManager](https://github.com/TDDennison/Data-Oriented-Missile-Sim/assets/54010305/f59f2432-76ab-476d-b295-ff21c74c18df)


# Entities
The core functionality of DOMSim is built using an Entity Component System (ECS). An entity is merely a unique number identifier that can represent any object (physical or non-physical) in the simulation. An entity is comprised of any number of components describing its properties. For example, an entity can be created representing a full-stack missile. The entity would have a unique identifier and be comprised of the components that describe a physical object; MassComponent, MovementComponet, TransformComponent etc. Entities can be created or destroyed at any appropriate time during the course of a simulation run. This means that if modeling an impact, where debris fields are created, each piece of debris would likely become its own unique entitiy with components to describe its physical properties.

# Systems
Systems can be any algorithms (or groups of related algorithms) that act on entity component data in desired ways. 

For example a BoosterSystem would compute thrust from burned mass, decrement the total propellant mass left, and the thrust force to the total accumulation of forces for the given entity.

Another example might be a NavigationGuidanceControlSystem. This system would take inputs of entity component data that represent an IMU sensor measurement, and give outputs of control commands to actuators component data. The actuator component datawould then be ingested by the desired actuator system (potentially a ThrustVectorControllerSystem) to steer the missile.

Entities can be registered and unregistered from systems at any appropriate time during a simulation run. This should be done by utilizing the appropriate function calls in the Simulation object. All systems have a reference to the single Simulation object inorder to use this functionality. 

Registering and unregistering an entity from a system is how the simulation emulates turning a model on or off. For example, if a missile is in a first stage boost mode, the entity representing that missile will be registered with the first stage booster system only. It will not be registered with the second stage booster system until it is time for the second stage booster system algorithms to act on the given entity (likely after first stage burnout and stage separation has occured), at which point the entity would beunregistered from the first stage booster system also.

# Physics Engine
The physics engine is built using a summation of forces and moments exerted on a body which are integrated into their derived properties over the lifetime of a simulation run.

Systems will act on entity component data, and any forces that are produced are added to the entity's AccumulatorComponent data. This data is ingested by the IntegrationSystem to produce linear and rotational accelerations. These accelerations are then integrated into their respective velocities and positions to complete a Six Degrees Of Freedom simulation of physical objects.
