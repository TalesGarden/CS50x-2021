import csv
import sys
import cs50
from sys import argv


def main():
    argc = len(argv)

    if argc != 2:
        print("Usage : python roster.py name_of_house")
        exit(1)

    houseName = argv[1]
    FindNamesOnDataBase(houseName)

# connect to data base and receive a list of name of the house
def FindNamesOnDataBase(nameHouse):
    db = cs50.SQL("sqlite:///students.db")

    result = db.execute("SELECT DISTINCT first, middle, last, birth FROM students WHERE house = ? ORDER BY last,first", nameHouse)

    dictName = dict()

    for row in result:
        firstName = row["first"]
        middleName = row["middle"]
        lastName = row["last"]
        birth = row["birth"]

        if middleName == None:
            fullName = firstName + " " + lastName
        else:
            fullName = firstName + " " + middleName + " " + lastName

        dictName[fullName] = birth

    for name, birth in dictName.items():
        print(f"{name}, {birth}")


if __name__ == "__main__":
    main()