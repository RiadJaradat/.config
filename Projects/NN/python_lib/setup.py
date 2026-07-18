from setuptools import setup
from pybind11.setup_helpers import Pybind11Extension, build_ext

ext_modules = [
    Pybind11Extension(
        "NN",
        ["src/binding.cpp"],
        include_dirs=["include"],
        language="c++",
    ),
]

setup(
    name="NN",
    version="0.1.0",
    ext_modules=ext_modules,
    cmdclass={"build_ext": build_ext},
)