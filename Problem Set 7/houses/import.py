import csv
import sys
import cs50
from sys import argv


def main():
    argc = len(argv)

    if argc != 2:
        print("Usage : python import.py file.csv")
        exit(1)

    fileName = argv[1]

    dataFromCsv = ReadingFromCsv(fileName)
    allRows = SaveToDataStruct(dataFromCsv)

    SaveInDatabase(allRows)


def ReadingFromCsv(fileName):

    with open(fileName, "r") as character:
        reader = csv.DictReader(character)
        rows = list(reader)
        return rows


# dictFile is a list of all data from a csv file
# the function return  a list. Each item of the has a row with a dictionary data having the keys- values, where the keys are:  first - middle - last - house - birth
def SaveToDataStruct(dictFile):

    # in each row of the dicFile, save into data row treat the data
    dataRow = dict()
    # all rows will be stored in a list
    listOfAllRows = list()

    firstName = None
    middleName = None
    lastName = None

    for row in dictFile:
        name = row["name"]
        house = row["house"]
        birth = row["birth"]

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

        listOfAllRows.append(dataRow.copy())

    return listOfAllRows


def SaveInDatabase(Data):

    db = cs50.SQL("sqlite:///students.db")

    for row in Data:
        firstName = row["first"]
        middleName = row["middle"]
        lastName = row["last"]
        house = row["house"]
        birth = row["birth"]

        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)",
                   firstName, middleName, lastName, house, birth)


if __name__ == "__main__":
    main()
