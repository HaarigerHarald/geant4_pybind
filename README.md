# Python bindings for Geant4

[![Tests](https://github.com/HaarigerHarald/geant4_pybind/actions/workflows/tests.yml/badge.svg)](https://github.com/HaarigerHarald/geant4_pybind/actions/workflows/tests.yml)
[![Wheel](https://img.shields.io/pypi/wheel/geant4-pybind)](https://pypi.org/project/geant4-pybind)
[![PyPI](https://img.shields.io/pypi/v/geant4-pybind)](https://pypi.org/project/geant4-pybind)

Alternative Python bindings for [Geant4](https://geant4.web.cern.ch/) via [pybind11](https://github.com/pybind/pybind11). It is loosely based on g4py, but retains an API closer to the standard C++ API and does not depend on Boost.Python.

It currently includes all g4py bindings plus a large portion of very commonly used classes and functions that aren't currently present in g4py. However, it is still off from replicating the full Geant4 API and is thus (currently) only applicable for simple simulations.

## Installation

It's available on PyPI for all major platforms as a fully self-contained (i.e. statically linked) wheel.

    pip3 install geant4-pybind

## Building

**Unix (Linux, OS X) prerequisits**

* A Geant4 installation version 11.0+, compiled with CMake option `GEANT4_BUILD_TLS_MODEL=global-dynamic` ([make sure it is also added to the path](https://geant4-userdoc.web.cern.ch/UsersGuides/InstallationGuide/html/postinstall.html#required-environment-settings-on-unix))
* A C++17 compiler (preferably the one Geant4 was compiled with)
* Python3
* pip
* git

**Windows prerequisits**

  * A Geant4 installation version 11.0+, compiled with CMake option `GEANT4_BUILD_TLS_MODEL=global-dynamic` ([make sure it is also added to the PATH](https://geant4-userdoc.web.cern.ch/UsersGuides/InstallationGuide/html/postinstall.html#required-environment-settings-on-windows))
  * [Visual Studio 2019](https://visualstudio.microsoft.com/en/vs) for C++ development
  * Python3
  * pip
  * [git](https://git-scm.com/download/win)

*Note*: If you haven't downloaded the required datasets yet you can let geant4_pybind handle them.

**Installation**

```bash
git clone --recursive https://github.com/HaarigerHarald/geant4_pybind
pip3 install ./geant4_pybind
```

**Windows notes**

The above commands have to be executed in a "Developer Command Prompt for VS 2019" and require that Python3, pip and git are added to the PATH environment variable.

**General notes**

If the repository was cloned non-recursively you can check out the submodule with:

```bash
git -C ./geant4_pybind submodule update --init
```

## Usage

**Minimal**

A minimal example that just starts a Geant4 shell:

```python
from geant4_pybind import *
import sys

ui = G4UIExecutive(len(sys.argv), sys.argv)
ui.SessionStart()
```

**Simulation examples**

Check out the [examples](https://github.com/HaarigerHarald/geant4_pybind/tree/main/examples) directory, which contains the Geant4 basic examples ported to Python. However, writing simulations in Python should be pretty straight forward as the API is almost identical to the C++ one. One notable exception are template classes, which have been renamed such that their type replaces the `T` (i.e. `G4TScoreNtupleWriter<G4GenericAnalysisManager>` becomes `G4GenericScoreNtupleWriter`).

## Bugs?

Yes! Please create an issue if you encounter one.

## License

This builds upon Geant4 and g4py and thus the [Geant4 license](https://geant4.web.cern.ch/license/LICENSE.html) applies. The binding code uses [pybind11](https://github.com/pybind/pybind11/blob/master/LICENSE). All my contributions are [public domain](https://github.com/HaarigerHarald/geant4_pybind/blob/main/LICENSE).
