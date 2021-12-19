# -*- coding: utf-8 -*-
import os
import sys
import subprocess

from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext


class CMakeExtension(Extension):
    def __init__(self, name, sourcedir=""):
        Extension.__init__(self, name, sources=[])
        self.sourcedir = os.path.abspath(sourcedir)


class CMakeBuild(build_ext):

    def build_extension(self, ext):
        extdir = os.path.abspath(os.path.dirname(
            self.get_ext_fullpath(ext.name)))

        # required for auto-detection of auxiliary "native" libs
        if not extdir.endswith(os.path.sep):
            extdir += os.path.sep

        cfg = "Debug" if self.debug else "Release"

        # CMake lets you override the generator - we need to check this.
        # Can be set with Conda-Build, for example.
        cmake_generator = os.environ.get("CMAKE_GENERATOR", "")

        cmake_args = [
            "-DCMAKE_LIBRARY_OUTPUT_DIRECTORY={}".format(extdir),
            "-DPYTHON_EXECUTABLE={}".format(sys.executable),
            "-DCMAKE_BUILD_TYPE={}".format(cfg)
        ]

        if "CMAKE_ARGS" in os.environ:
            cmake_args += [item for item in os.environ["CMAKE_ARGS"].split(" ") if item]

        build_args = []

        if self.compiler.compiler_type != "msvc":
            if not cmake_generator:
                cmake_args += ["-GNinja"]
        else:
            cmake_args += [
                "-DCMAKE_LIBRARY_OUTPUT_DIRECTORY_{}={}".format(cfg.upper(), extdir)
            ]
            build_args += ["--config", cfg]

        # Set CMAKE_BUILD_PARALLEL_LEVEL to control the parallel build level
        # across all generators.
        if "CMAKE_BUILD_PARALLEL_LEVEL" not in os.environ:
            # self.parallel is a Python 3 only way to set parallel jobs by hand
            # using -j in the build_ext call, not supported by pip or PyPA-build.
            if hasattr(self, "parallel") and self.parallel:
                # CMake 3.12+ only.
                build_args += ["-j{}".format(self.parallel)]

        if not os.path.exists(self.build_temp):
            os.makedirs(self.build_temp)

        subprocess.check_call(
            ["cmake", ext.sourcedir] + cmake_args, cwd=self.build_temp
        )
        subprocess.check_call(
            ["cmake", "--build", "."] + build_args, cwd=self.build_temp
        )

        # Automatically generate stubs
        subprocess.check_call(
            [sys.executable, "doc/generate_stubs.py", ext.name,
                os.path.realpath(self.get_ext_fullpath(ext.name))],
            cwd=os.path.dirname(os.path.abspath(__file__))
        )


with open("README.md", "r") as readme:
    long_desc = readme.read()

# Amalgamate 3rd party licenses
with open("pybind11/LICENSE", "r") as license_file:
    licenses = license_file.read()

if os.path.isfile('EXTRA_LICENSES'):
    with open("EXTRA_LICENSES", "r") as license_file:
        licenses += "\n\n\n" + license_file.read()

with open("LICENSE-3RD-PARTY", "w") as license_file:
    license_file.write(licenses)

setup(
    name="geant4_pybind",
    version="0.1.0b6",
    author="Benjamin H.",
    author_email="haarigerharald@gmx.at",
    description="Alternative python bindings for Geant4 via pybind11",
    long_description=long_desc,
    long_description_content_type="text/markdown",
    url="https://github.com/HaarigerHarald/geant4_pybind",
    license="Public Domain",
    python_requires=">=3.5, <4",
    ext_modules=[CMakeExtension("geant4_pybind")],
    cmdclass={"build_ext": CMakeBuild},
    zip_safe=False
)
