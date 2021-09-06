from cs50 import get_string


def main():

    letter = 0
    word = 1
    sentence = 0

    text = get_string("Text: ")

    for w in text:
        if w.isalpha():
            letter += 1

        if letter > 0 and w == " ":
            word += 1

        if w == '.' or w == '!' or w == '?':
            sentence += 1

    ave_letter = 100 * letter/word
    ave_sentence = 100 * sentence/word

    grade = int(round(0.0588 * ave_letter - 0.296 * ave_sentence - 15.8))

    if grade < 1:
        print("Before Grade 1")
        return
    if grade >= 16:
        print("Grade 16+")
        return

    print(f"Grade {grade}")


if __name__ == "__main__":
    main()