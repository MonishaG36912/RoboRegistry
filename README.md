# RoboRegistry
---

## Project Overview

A comprehensive C++ application for managing a registry of humanoid robots using object-oriented principles including polymorphism, composition, and memory-safe practices.

**Key Capabilities:**
- Register and manage multiple types of robots
- Attach components with weight specs
- Perform price analysis
- Demonstrate polymorphic behavior
- Support file input/output

---

## Features

### Core Functionality
- Register new robots interactively
- Load robots from formatted files
- Display all robots in a formatted table
- Compute price statistics (min, max, mean)
- Filter robots by a price threshold

### Advanced Capabilities
- **Polymorphic Robot Types**:
  - Military: Weapons, stealth, mission tracking
  - Industrial: Factory location, production units
  - Domestic: Home use, task specialization
- **Composition**:
  - Attach optional main components with weights
- **Memory Management**:
  - Dynamic array expansion
  - Move semantics for optimization
  - RAII for safe resource handling

---

## System Architecture

```plaintext
Main Program (main.cpp)
│
├── Robot Registry (RobotRegistry.h/.cpp)
│
├── HumanoidRobot (with optional RobotComponent)
│
└── Robot Types (Polymorphic)
    ├── MilitaryRobot
    ├── IndustrialRobot
    └── DomesticRobot
### System Architecture
The Robot Registry System is built around three core components:

1. **Main Program (main.cpp)**
   - Interactive menu-driven interface
   - Handles user input with robust validation
   - Coordinates all system operations
   - Implements price analysis utilities

2. **RobotRegistry Class**
   - Central management system for all robots
   - Manages two parallel collections:
     - Concrete `HumanoidRobot` objects
     - Polymorphic `Robot` pointers
   - Implements dynamic array with automatic expansion

3. **Robot Class Hierarchy**
   - Base abstract `Robot` class
   - Three specialized implementations:
     - `MilitaryRobot`
     - `IndustrialRobot` 
     - `DomesticRobot`

### Key Technical Features

**Memory Management**
- Dynamic array with automatic resizing (`growArray()`)
- RAII principles for resource safety
- Move semantics for efficient transfers
- Proper cleanup in destructors

**User Interaction**
- Comprehensive menu system (8 options)
- Input validation via functors:
  - `PriceValidator` (positive values)
  - `StringValidator` (alphanumeric)
- Error handling for invalid inputs

**Data Management**
- File I/O operations:
  - Load robots from formatted text files
  - Output redirection capability
- Two storage systems:
  - Concrete objects (for basic operations)
  - Polymorphic pointers (for demonstrations)

**Analysis Tools**
- Price statistics (min/max/mean)
- Filter by price threshold (lambda-based)
- Formatted table display with auto-sizing
- Polymorphic behavior demonstration

### Robot Class Implementations

**HumanoidRobot**
- Composition-based design
- Contains:
  - Company, name, version identifiers
  - Validated price field
  - Optional `RobotComponent`
- Implements:
  - Move semantics
  - String conversion
  - Formatted output

**Polymorphic Robots**
1. **MilitaryRobot**
   - Mission tracking
   - Weapon power system
   - Stealth mode toggle
   - Special `fireWeapon()` method

2. **IndustrialRobot**  
   - Factory location tracking
   - Work capacity metrics
   - CSV parsing constructor

3. **DomesticRobot**
   - Home location
   - Task specialization
   - Dual-version input operator

### Advanced C++ Techniques
- Polymorphism through virtual functions
- Move semantics for optimization
- Functors for validation
- Lambda expressions for filters
- Operator overloading (<<, string conversion)
- Dynamic memory management
- STL containers (multimap for price analysis)
