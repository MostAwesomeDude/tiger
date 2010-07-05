#!/usr/bin/env python

import unittest

import tiger

class TigerTest(unittest.TestCase):

    def test_instance(self):
        tiger.new()
        pass

    def test_empty_hash(self):
        self.assertEqual("3293ac630c13f0245f92bbb1766e16167a4e58492dde73f3",
            tiger.new().hexdigest())

    def test_pangram(self):
        self.assertEqual("6d12a41e72e644f017b6f0e2f7b44c6285f06dd5d2c5b075",
            tiger.new("The quick brown fox jumps over the lazy dog").hexdigest())

    def test_pangram_update(self):
        t = tiger.new()
        t.update("The quick brown fox jumps over the lazy dog")
        self.assertEqual("6d12a41e72e644f017b6f0e2f7b44c6285f06dd5d2c5b075",
            t.hexdigest())


if __name__ == "__main__":
    unittest.main()
