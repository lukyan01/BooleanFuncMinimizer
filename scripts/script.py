from utility import launch_minimize_display, get_verilog_from_eqns, generate_latex_table, generate_latex_equations


# Retrieve the minimized equations for each SSD
display_eqns = []
for i in range(6):
    print(f"\nMinimizing SSD{i}...")
    display_eqns.append(launch_minimize_display(i))
    generate_latex_table(i)
    generate_latex_equations(display_eqns[i])

get_verilog_from_eqns(display_eqns)

# Write the minimized equations to a file
with open("SSD_Equations.txt", 'w') as file:
    for i, eqns in enumerate(display_eqns):
        file.write(f"\nSSD{i} Equations:\n")
        for j, eqn in enumerate(eqns):
            file.write(f"S_{j} = {eqn}\n")