from cs50 import get_string, get_int


def main():
    number = get_int("Number: ")

    number = str(number)

    if checksum(number) == True:
        checkName(number)


def checksum(number):

    if len(number) > 16:
        print("INVALID")
        return False

    # Luhn’s Algorithm
    sum_of_digits = 0
    size_number = len(number)

    for i in range(size_number-2, -1, -2):
        under_digit = int(number[i]) * 2
        for digit in str(under_digit):
            sum_of_digits += int(digit)

    for i in range(size_number-1, -1, -2):
        sum_of_digits += int(number[i])

    last_digit = len(str(sum_of_digits)) - 1
    str_numb = str(sum_of_digits)

    if int(str_numb[last_digit]) == 0:
        return True
    else:
        print("INVALID")
        return False


def checkName(number):

    s_numb = str(number)
    size_number = len(number)
    s_numb = s_numb[:2]
    s_numb = int(s_numb)

    if size_number == 15 and s_numb == 34 or s_numb == 37:
        print("AMEX")

    if size_number == 16 and s_numb >= 51 and s_numb <= 55:
        print("MASTERCARD")

    s_numb = str(s_numb)
    s_numb = s_numb[:1]
    if int(s_numb) == 4 and size_number == 13 or size_number == 16:
        print("VISA")


if __name__ == "__main__":
    main()
