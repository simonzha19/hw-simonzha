import subprocess


tests = {
    "(7 + 8)":                              "correct",
    "[7 * (6 + 8)]":                        "correct",
    "7+8":                                  "correct",
    "    7         +    8    ":             "correct",
    "(7+/8/1+*4) ** (5+-6) * (--1-5)":      "correct",
    "([]()[()]((())))":                     "correct",
    "":                                     "correct",
    "1+2/(3+4)":                            "correct",
    "[0 + 1 / 34 + 8(1+2)([1])]":           "correct",
    "((([1*(2+3)]+1)/(1+3)*9)+1)+3*(1+2)":  "correct",
    "[7+8":                                 "incorrect",
    "[7+8)":                                "incorrect",
    "([7*5]+(6+8)(15))+5+6)":               "incorrect",
    "[(5+3])":                              "incorrect",
    "(":                                    "incorrect",
    "()[":                                  "incorrect",
    "[()()()()()(())[([])]":                "incorrect",
    "1+3(4)+3)":                            "incorrect",
    "[[":                                   "incorrect",
    "((([1*(2+3)]+1)/(1+3)*9)+1)+3*1+2)":   "incorrect",
}

successes = 0

for test, expected in tests.items():
    response = subprocess.Popen(["./paren.o", test], stdout=subprocess.PIPE)
    result = response.stdout.read().decode().strip()

    if result != expected:
        print("Test failed!\nInput: " + str(test) + "\nExpected: " +
              expected + "\nReceived: " + result + "\n")
    else:
        successes += 1

print(str(successes) + " out of " + str(len(tests)) + " tests passed -- " +
      str(100.0 * successes / len(tests)) + "%.")
