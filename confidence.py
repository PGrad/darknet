#######################################################################
#match() matches detected enter/exit image filenames with             #
#correct enter/exit image filenames to calculate accuracy and         #
#false positive rates, which are returned from match().               #
#The CSVs containing the filenames are provided as two command line   #
#arguments to match(). Because the manually entered filenames did not #
#include their file prefixes, prefix is passed as an arg to match() to#
#remove the file prefix from the detected enter/exit filenames.       #
#######################################################################

from sys import argv

def match(prefix,testFN,expectedFN):
    testData = []
    expectedData = {}
    prefixLen = len(prefix)
    with open(testFN,'r') as testF:
        testData = [filename[prefixLen:] for filename in testF.read().split("\n")][:-1]
    with open(expectedFN,'r') as expectedF:
        expectedData = set(expectedF.read().split("\n")[:-1])
    numTest = len(testData)
    numExp = len(expectedData)
    correct = 0
    for data in testData:
        if data in expectedData:
            correct += 1
    accuracy = correct / numExp
    falsePositiveRate = 1 - correct / numTest
    return accuracy, falsePositiveRate

print(match(argv[1],argv[2],argv[3]))
