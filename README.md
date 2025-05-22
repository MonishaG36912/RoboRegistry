# RoboRegistry

## Table of Contents
1. [Project Overview](#project-overview)
2. [Features](#features)
3. [System Architecture](#system-architecture)
4. [Class Documentation](#class-documentation)
5. [Usage Guide](#usage-guide)
6. [File Formats](#file-formats)
7. [Build Instructions](#build-instructions)
8. [Design Patterns](#design-patterns)
9. [Future Enhancements](#future-enhancements)
10. [License](#license)

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