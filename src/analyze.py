import csv
import matplotlib.pyplot as plt
import numpy as np


# values to plot
xvals = []
rel_errs_magic = []
rel_errs_newton = []
yvals = []
yvals_magic = []
yvals_newton = []

# read from csv file
f = csv.reader(open("dump.csv"), delimiter=',')
for line in f:
    line_vals = [float(s) for s in line]
    x = line_vals[0]
    y_magic = line_vals[1]
    y_newton = line_vals[-1]
    y = 1/np.sqrt(x)

    rel_err_magic = (y_magic-y) / y
    rel_err_newton = (y_newton-y) / y

    # add x and y values to lists
    xvals.append(x)
    yvals.append(y)
    yvals_magic.append(y_magic)
    yvals_newton.append(y_newton)

    # add relative errors to lists
    rel_errs_magic.append(rel_err_magic)
    rel_errs_newton.append(rel_err_newton)

    # information about current line read
    print(f'x={x}')
    print(f'y={y} | y_magic={y_magic} | y_newton={y_newton}')
    print(f'rel err magic={rel_err_magic} | rel error Newton={rel_err_newton}')
    print()


# plot function values
plt.figure()
plt.plot(xvals, yvals, 'g-', label='1/√(x)')
plt.plot(xvals, yvals_magic, 'r-', label='magic')
plt.plot(xvals, yvals_newton, 'b-', label='Newton')
plt.legend()

# plot relative errors
plt.figure()
plt.subplot(121)
plt.title('Magic: rel. error')
plt.plot(xvals, rel_errs_magic, 'r-')
plt.subplot(122)
plt.title('Newton: rel. error')
plt.plot(xvals, rel_errs_newton, 'b-')

plt.show()
