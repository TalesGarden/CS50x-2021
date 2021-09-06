import csv
import sys
from sys import argv


def main():

    argc = len(argv)
    if argc < 2 or argc > 3:
        print("Usage : python dna.py CSVfile SequenceText")
        exit(1)

    csv_filename = argv[1]
    sequence_txt = argv[2]
    row_str = []
    row_names = []

    # reading a csv file and save on row_str and row_names
    with open(csv_filename) as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=",")
        line_count = 0

        for row in csv_reader:
            if line_count == 0:
                line_count += 1
                row_str = row
                row_str.remove("name")
                continue
            row_names.append(row)
            line_count += 1

    name_count_csv = []
    # transform the numbers of csv table into a string to compare with sequences of txt
    for number in row_names:
        string_numb = ''.join(number[1:])
        name_count_csv.append(string_numb)

    string_sequence_count = stringSequence(row_str, sequence_txt)

    # index of the name, if it match
    index_name = 0
    try:
        index_name = name_count_csv.index(string_sequence_count)
    except ValueError:
        print("No match")
        exit(1)

    print(f"{row_names[index_name][0]}")


# transform the values of the str counter sequence into a string
def stringSequence(row_str, sequence_txt):
    sequence_dna = open(sequence_txt, 'r')
    sequence = sequence_dna.read()
    count_sequence = []

    for sec in row_str:
        number = str(countSequence(sec, sequence))
        count_sequence.append(number)

    count_sequence = ''.join(count_sequence)

    return count_sequence


# count the number of a substring into a string
def countSequence(srt_sub, string):

    len_string = len(string)
    len_sub_string = len(srt_sub)
    flag_sequence = False

    max_sequence_count = 0
    sequence_count = 0

    # for each position in the DNA sequence, creates a substring the size of the STR and check
    for index in range(len_string):
        j = len_sub_string + index
        i = index
        part_sequence = string[i:j]

        if part_sequence == srt_sub:
            sequence_count += 1
            flag_sequence = True

            # if finds a substring then check if its a sequence and count
            for index_2 in range(j, len_string, len_sub_string):
                k = index_2 + len_sub_string
                part_sequence_2 = string[index_2:k]

                if part_sequence_2 == srt_sub and flag_sequence == True:
                    sequence_count += 1
                # here the sequence is break
                else:
                    flag_sequence = False
                    # check if the sequence count it's the biggest
                    if max_sequence_count < sequence_count:
                        max_sequence_count = sequence_count
                    # reset the count
                    sequence_count = 0
                    break

    return max_sequence_count


if __name__ == "__main__":
    main()