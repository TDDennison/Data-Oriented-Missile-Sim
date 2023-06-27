# DOMSim
Data-Oriented Missile Simulation

# Description
DOMSim is a two-stage, ballistic missile simulation that has been built primarily following data-oriented software design techniques. The core functionality utilizes a data-oriented Entity Component System, component based objects, and the idea of existential processing in order to limit the number and size of data objects in memory. Limiting these allows for more efficient use of CPU cache memory which ultimately improves software performance.

# Execution 
The simulation is managed by the Simulation class. This class handles the interactions between Systems and Component Managers, it is the executive data manager of a simulation run. The Simulation object handles the execution of algorithms, as well as registration of entities and components with Systems and Component Managers.
The order of algorithm execution is user-defined (using configuration files) and sequential; all algorithms run in the order they are defined, and one at a time. Doing so allows for efficient use of the instruction cache, as well as ensuring that each simulation run is deterministic and repeatable.

# Physics Engine
The physics engine is built using a summation of forces and moments exerted on a body which are integrated into their derived properties over the lifetime of a simulation run. 

# Simulation Configuration
Simulation configuration is handled through the configuration files (TBD) prior to starting a simulation run.

# Component Management
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

struct MovementComponent {
  double velocity;
  double angularVelocity;
  double acceleration;
  double angularAcceleration;
}

struct TransformComponent {
  double position;
  Quaternion orientation;
}
```

This allows alogrithms to load less unnecessary data from main memory into RAM or cache memory, which in turn allows for faster processing of algorithms.
The component data is then managed efficiently for tightly packed, non-fragmented storage by Component Managers, further increasing runtime performance.
When data is tightly packed, the CPU can accurately pre-fetch data that is soon to be used allowing for cache lines to be more efficiently used. An example of how component management works is illustrated below.

![ComponentManager](https://github.com/TDDennison/DOMSim/assets/54010305/7fe2d458-e86a-4095-ab7b-48c777fc9b20)
