import csv
import sys
from sys import argv

def main():
    argc = len(argv)

    if argc != 2:
        print ("Usage : python import.py file.csv")
        exit(1)

    fileName = argv[1]

    dictReaderFile = ReadingFromCsv( fileName )
    printFile( dictReaderFile )

def ReadingFromCsv( fileName ):

    with open(fileName, "r") as character:
        reader = csv.DictReader(character)
        rows = list (reader)
        return rows

def printFile(dictFile):

    dataRow = dict()
    listOfRows = list()

    firstName = None
    middleName = None
    lastName = None

    for row in dictFile:
        name = row["name"]
        house = row["house"]
        birth = row["birth"]

       # print(f" Name: {name} - house {house} - birth {birth}")
        fullName = name.split()

        if len(fullName) == 2:
            firstName = fullName[0]
            middleName = None
            lastName = fullName[1]
        else:
            firstName = fullName[0]
            middleName = fullName[1]
            lastName = fullName[2]

        dataRow["first"] = firstName
        dataRow["middle"] = middleName
        dataRow["last"] = lastName
        dataRow["house"] = house
        dataRow["birth"] = birth

        print(dataRow["first"],dataRow["middle"],dataRow["last"], dataRow["house"])


if __name__ == "__main__":
    main()
