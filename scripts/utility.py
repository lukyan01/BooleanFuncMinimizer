import os
import subprocess
import time

from constants import Char, executable_path, output_file_name, working_directory


def format_hex(display: str):
    result = ""
    for i in display:
        result += " & " + i

    return result

def int_to_bin(num: int):
    bin = format(num, '04b')

    result = ""
    for i in bin:
        result += " & " + i

    return result

def generate_latex_table(ssd_num: int):
    '''
    Generate the latex table for a given SSD
    :param ssd_num: The display to generate the table for
    :return: None
    '''
    display = parse_display_sequence()[ssd_num]

    print(f"SSD{ssd_num} Table: \n")
    for i in range(len(display)):
        print(f"\t{i}{int_to_bin(i)}{format_hex(display[i])} \\\\ \\hline")

def generate_latex_equations(segment_eqns: list[str]):
    '''
    Generate the latex equations for a given SSD
    :param segment_eqns: A list of strings that hold the minimized equations for each segment
    :return: The latex equations
    '''

    replacements = {
        "D'": "\\overline{Q_0}",
        "C'": "\\overline{Q_1}",
        "B'": "\\overline{Q_2}",
        "A'": "\\overline{Q_3}",
        "D": "Q_0",
        "C": "Q_1",
        "B": "Q_2",
        "A": "Q_3",
    }

    print("\nLatex Equations: \n")
    for i, eqn in enumerate(segment_eqns):
        for key, value in replacements.items():
            eqn = eqn.replace(key, value)
        print(f"\tS_{i} &= {eqn} \\\\")


def run_minimizer(executable, minterms, dontcares, output_file, cwd):
    '''
    Run the minimizer with the given parameters
    :param executable: The path to the minimizer executable
    :param minterms: The minterms to minimize
    :param dontcares: The dontcares to minimize
    :param output_file: The output file to write the minimized function to
    :param cwd: Current working directory
    :return: None
    '''
    # Combine the executable path, minterms, dontcares, and output file name into a command list
    command = [executable, minterms, dontcares, output_file]

    print("Running command:", command)

    # Run the subprocess and capture the output
    result = subprocess.run(command, capture_output=True, text=True, cwd=cwd)


def parse_minimizer_output(output_file_name) -> list[str]:
    prime_implicants = []
    with open(output_file_name, "r") as file:
        for line in file.readlines():
            prime_implicants.append(line.replace("\n", ""))

    return prime_implicants


def get_boolean_function(prime_implicants: list[str]) -> str:

    '''
    Convert the prime implicants to a boolean function
    :param prime_implicants: The prime implicants to convert
    :return: The boolean function in terms of A, B, C, and D
    '''
    prime_implicants = [implicant[4:] for implicant in prime_implicants]

    # Since now we have a 4 bit input, most significant bit is A, and least significant bit is D
    # We can now convert the prime implicants to the boolean function
    function = ""
    for implicant in prime_implicants:
        term = ""
        for i in range(4):
            if implicant[i] == "0":
                term += f"{chr(65 + i)}'"
            elif implicant[i] == "1":
                term += f"{chr(65 + i)}"
        function += term + " + "

    return function[:-3]


def parse_display_sequence() -> list[list[str]]:
    '''
    Parse the display sequence from the display_sequence.txt file
    :return: The display sequence as a list of lists of strings that hold binary values for each segment
    '''
    display = [[], [], [], [], [], []]
    with open("display_sequence.txt", "r") as file:
        for i, line in enumerate(file.readlines()):
            for char in line:
                if char == "3":
                    display[i].append(Char.THREE_DASH.value)
                elif char == "-":
                    display[i].append(Char.DASH.value)
                elif char == "C":
                    display[i].append(Char.C.value)
                elif char == "A":
                    display[i].append(Char.A.value)
                elif char == "P":
                    display[i].append(Char.P.value)
                elif char == "E":
                    display[i].append(Char.E.value)

    return display


def get_minterms_for_display(ssd_num: int) -> list[list[int]]:
    '''
    Get the minterms for a given SSD display
    :param ssd_num: The SSD display to get the minterms for
    :return: A list of lists of minterms for each segment
    '''
    minterm_arr = [[], [], [], [], [], [], []]
    display_sequence = parse_display_sequence()

    for (n, hex6_0) in enumerate(display_sequence[ssd_num]):
        for (j, bit) in enumerate(reversed(hex6_0)):
            if bit == "1":
                minterm_arr[j].append(n)

    return minterm_arr

def launch_minimize_display(ssd_num: int) -> list[str]:
    '''
    Launch the minimizer for the given SSD
    :param ssd_num: The SSD display to minimize
    :return: A list of minimized equations for each segment
    '''
    segment_minterms = get_minterms_for_display(ssd_num)
    print(f"SSD{ssd_num} Minterms: {segment_minterms}")

    segment_eqns = []
    for i in range(len(segment_minterms)):
        minterm_str = " ".join([str(minterm) for minterm in segment_minterms[i]])
        dontcare_str = ""
        run_minimizer(executable_path, minterm_str, dontcare_str, output_file_name, working_directory)
        prime_implicants = parse_minimizer_output(output_file_name)
        os.remove(output_file_name)
        segment_eqns.append(get_boolean_function(prime_implicants))
        print(f"Segment {i} Prime Implicants: {prime_implicants}")
        print(f"Segment {i} Minimized Function: {get_boolean_function(prime_implicants)}\n")

    return segment_eqns

def convert_to_verilog_sop(eqn: str, map_to_nand: bool = False) -> str:
    '''
    Convert the minimized equation to a verilog SOP
    :param eqn: The minimized equation
    :param map_to_nand: Whether to map the equation to NAND gates
    :return: The verilog SOP/NAND equation
    '''
    eqn = eqn.replace("'", "n")
    terms = []
    for term in eqn.split(" + "):
        new_term = "("
        for i, char in enumerate(term):
            if len(term) - 1 == i:
                new_term += char
                break
            elif char == "n" and term[i + 1].isupper():
                new_term += "n&"
            elif char.isupper() and term[i + 1].isupper():
                new_term += f"{char}&"
            else:
                new_term += char
        new_term += ")"
        terms.append(new_term)

    if map_to_nand:
        return f"~({" & ".join([f"~{term}" for term in terms])})"

    return " | ".join(terms)

def get_verilog_from_eqns(display_eqns: list[list[str]]):
    '''
    Generate verilog code from the minimized equations
    :param eqns: A list of lists of strings, where each list of strings holds the minimized equations for each SSD
    '''
    with open("verilog_template.txt", "w") as file:
        for i, ssd_eqns in enumerate(display_eqns):
            file.writelines(f"\n// SSD{i} Equations: \n")
            for j, eqn in enumerate(ssd_eqns):
                file.writelines(f"\t// HEX[{j}] = {eqn};\n")
                file.writelines(f"\tassign out[{j}] = {convert_to_verilog_sop(eqn, True)};\n\n")
