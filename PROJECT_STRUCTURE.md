# **ATLAS Project Structure**

*A multi-language, institutional-grade quant research platform.*

This document outlines the core directory layout for ATLAS and describes the role of each major component. The structure is designed for long-term scalability, multi-language interoperability, and professional quant research workflows.

---

# **📁 Top-Level Directory Layout**

```
atlas/
│
├── cpp/                       # C++ core engine (backtester, simulator, portfolio)
│   ├── include/               # Public C++ headers
│   ├── src/                   # Engine source code
│   ├── bindings/              # pybind11 + CxxWrap bindings
│   ├── tests/                 # C++ unit tests
│   ├── CMakeLists.txt         
│   └── README.md
│
├── julia/                     # Julia mathematical research lab
│   ├── AtlasJL/               # Julia package (module)
│   │   ├── src/               # Factor & model implementations
│   │   ├── test/              # Julia tests
│   │   └── Project.toml
│   └── notebooks/             # Research notebooks (Julia)
│
├── python/                    # Python orchestration & ML layer
│   ├── atlas_py/              # Python package
│   │   ├── experiments/       # Experiment manager system
│   │   ├── data/              # Data loader and schema definitions
│   │   ├── models/            # ML models (PyTorch/JAX)
│   │   ├── viz/               # Dashboards and visualization tools
│   │   └── utils/             # Shared utilities
│   │
│   ├── scripts/               # Command-line utilities (CLI)
│   ├── notebooks/             # Python research notebooks
│   └── tests/                 # Python unit tests
│
├── data/                      # Unified dataset storage (gitignored)
│   ├── raw/                   # Raw datasets
│   ├── processed/             # Cleaned Parquet data
│   └── metadata/              # Dataset versioning + schema definitions
│
├── configs/                   # Experiment and engine configuration YAMLs
│
├── docs/                      # Documentation + architecture diagrams
│   ├── architecture/          # PNG/SVG system diagrams
│   ├── whitepapers/           # Research writeups
│   └── api/                   # API docs (auto-generated)
│
├── docker/                    # Dockerfiles for each environment
│   ├── cpp.Dockerfile
│   ├── python.Dockerfile
│   └── julia.Dockerfile
│
├── tests/                     # Cross-language integration tests
│
├── scripts/                   # Setup utilities, installers, data fetchers
│
├── environment.yml            # Conda environment config (Python)
├── docker-compose.yml         
├── ROADMAP.md
├── PROJECT_STRUCTURE.md
└── README.md
```

---

# **📦 Component Breakdown**

---

## **🔧 C++ Core Engine (`cpp/`)**

**Purpose:**
Ultra-fast backtesting, simulation, portfolio optimization, execution logic, and factor evaluation.

**Contents:**

* Event-driven architecture
* Multi-asset portfolio accounting
* Optimizers (mean-variance, convex, RL-based optional)
* High-performance data structures
* Parallel computing (OpenMP/TBB)

**Interop:**

* `pybind11` → expose engine to Python
* `CxxWrap.jl` → interface with Julia
* Shared Arrow memory buffers

---

## **📐 Julia Mathematical Layer (`julia/`)**

**Purpose:**
A research-focused, mathematically expressive environment for factor creation, modeling, and advanced statistics.

**Features:**

* Statistical factor library
* State-space models / Kalman filtering
* PDEs, SDE solvers
* Probabilistic programming (Turing.jl)
* Dimensionality reduction
* Time-series transformations

**Interop:**

* Calls C++ core via wrappers
* Called from Python via PyJulia
* Direct Arrow table support

---

## **🐍 Python Orchestration & ML Layer (`python/`)**

**Purpose:**
High-level control system for experiments, machine learning, visualization, research automation.

**Features:**

* Experiment configuration + tracking
* ML models (PyTorch/JAX)
* Visualization dashboards
* Automated hyperparameter searches
* Factor analytics and IC computation
* Research notebooks (Python)

**Interop:**

* Loads Julia functions through PyJulia
* Calls C++ through pybind11
* Arrow/DuckDB for shared data

---

## **🗄 Unified Data Layer (`data/`)**

**Architecture:**

```
raw/         → unmodified vendor data  
processed/   → cleaned Parquet tables  
metadata/    → version logs + schema definitions  
```

**Technologies:**

* Apache Arrow (in-memory)
* Parquet (storage)
* DuckDB (analytics)

**Guarantees:**

* Zero-copy exchange across C++/Python/Julia
* Deterministic datasets
* Full schema versioning

---

## **⚙ Configuration System (`configs/`)**

Contains:

* Backtest configurations
* Portfolio optimization configs
* Experiment settings
* Pipeline composition definitions

Format:
**YAML** + **JSON**

All fully reproducible.

---

## **📘 Documentation (`docs/`)**

Includes:

* Architecture diagrams
* Module-level docs
* System design docs
* Research whitepapers
* Auto-generated API docs

---

## **🐳 Docker (`docker/`)**

Separate container builds for each language:

```
cpp.Dockerfile
python.Dockerfile
julia.Dockerfile
```

Plus a combined `docker-compose.yml` to launch the entire environment.

---

## **🧪 Testing (`tests/`)**

Three levels:

1. **Unit tests** (per language)
2. **Integration tests** (multi-language interactions)
3. **Cross-sectional strategy tests** (final validation)

Testing is **CI-enforced via GitHub Actions**.

---

# **🏗 Suggested Final Repository Structure (Condensed)**

```
atlas/
├── cpp/
├── julia/
├── python/
├── data/
├── configs/
├── docs/
├── docker/
├── tests/
├── scripts/
├── README.md
├── ROADMAP.md
└── PROJECT_STRUCTURE.md
```
