Tiger for Python
----------------

This is a simple implementation of the Tiger cryptographic hash for Python. It
uses the same API as all other hashing modules, with new(), update(), and
digest()/hexdigest().

It's written in C, and uses the standard Python/C bindings and the reference C
implementation for Tiger. It has been tested on i386 and amd64, and correctly
reports the reference hashes in standard order.

Requirements
============

 * Python 2.4 (if it works on 2.3, tell me, please!)
 * Python developement packages and a working toolchain

Changelog
=========
 * v0.3
    * PyPI compatibility; Tiger is now available on PyPI.
 * v0.2
    * Unbreak the entire module, particularly hexdigest().
    * Add tests.
 * v0.1
    * Initial release.
