#!/usr/bin/env python

from distutils.core import setup, Extension

tigersources = ['sboxes.c', 'tiger.c', 'tigermodule.c']

tiger = Extension("tiger", sources=tigersources, extra_compile_args=['-g3'])

setup(name = "tiger",
    version = "0.3",
    description = "Tiger hash module",
    long_description=open("README.rst").read(),
    author="Corbin Simpson",
    author_email="MostAwesomeDude@gmail.com",
    url="http://github.com/MostAwesomeDude/tiger",
	ext_modules = [tiger]
)
