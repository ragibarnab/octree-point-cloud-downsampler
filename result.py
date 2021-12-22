import pandas as pd

input_csv = pd.read_csv('input.csv')
output_csv = pd.read_csv('output.csv')

input_points = len(input_csv)
output_points = len(output_csv)
print(f"number input points:\t{input_points}")
print(f"number output points:\t{output_points}")

points_lost = (input_points - output_points)
percent_downsampled = (1 - (output_points/input_points)) * 100

print(f"number of points lost:\t{points_lost}")
print(f"percent downsampled:\t{round(percent_downsampled, 2)}%")