import unittest

from digits import *

class testLongestDigitsPrefix(unittest.TestCase):

    def test1(self):
        inputString = "123abc"
        self.assertEqual(longestDigitsPrefix(inputString),'123')
    def test2(self):
        inputString = "123456789"
        self.assertEqual(longestDigitsPrefix(inputString),'123456789')

if __name__ == '__main__':
    unittest.main()
